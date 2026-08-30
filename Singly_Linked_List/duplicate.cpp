#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <unordered_map>
#include <memory>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <iomanip>

using Clock = std::chrono::steady_clock;
using TimePoint = std::chrono::time_point<Clock>;

// ==========================================
// 1. DATA STRUCTURES & INTERFACES
// ==========================================

enum class Priority
{
    LOW = 0,
    MEDIUM = 1,
    HIGH = 2
};

struct Request
{
    std::string clientId;
    int requestId;
    Priority priority;
    TimePoint timestamp;

    Request(std::string cId, int rId, Priority p = Priority::LOW)
        : clientId(std::move(cId)), requestId(rId), priority(p), timestamp(Clock::now()) {}

    bool operator<(const Request &other) const
    {
        return static_cast<int>(priority) < static_cast<int>(other.priority);
    }
};

class RatePolicy
{
public:
    virtual ~RatePolicy() = default;
    virtual bool allow() = 0;
};

// ==========================================
// 2. RATE LIMITING STRATEGIES
// ==========================================

// Token Bucket: Allows bursts up to capacity, refills smoothly over time.
class TokenBucketPolicy : public RatePolicy
{
private:
    double capacity;
    double refillRatePerSec;
    double tokens;
    TimePoint lastRefill;

public:
    TokenBucketPolicy(double cap, double rate)
        : capacity(cap), refillRatePerSec(rate), tokens(cap), lastRefill(Clock::now()) {}

    bool allow() override
    {
        TimePoint now = Clock::now();
        std::chrono::duration<double> elapsed = now - lastRefill;
        lastRefill = now;

        tokens = std::min(capacity, tokens + elapsed.count() * refillRatePerSec);
        if (tokens >= 1.0)
        {
            tokens -= 1.0;
            return true;
        }
        return false;
    }
};

// Sliding Window: Exact timestamp tracking via std::deque; strictly bounds rate.
class SlidingWindowPolicy : public RatePolicy
{
private:
    int maxRequests;
    std::chrono::milliseconds windowDuration;
    std::deque<TimePoint> timestamps;

public:
    SlidingWindowPolicy(int limit, std::chrono::milliseconds window)
        : maxRequests(limit), windowDuration(window) {}

    bool allow() override
    {
        TimePoint now = Clock::now();
        TimePoint boundary = now - windowDuration;

        while (!timestamps.empty() && timestamps.front() <= boundary)
        {
            timestamps.pop_front();
        }

        if (static_cast<int>(timestamps.size()) < maxRequests)
        {
            timestamps.push_back(now);
            return true;
        }
        return false;
    }
};

// Leaky Bucket: Enforces smooth, constant departure pacing.
class LeakyBucketPolicy : public RatePolicy
{
private:
    std::chrono::milliseconds intervalBetweenRequests;
    TimePoint nextAvailableTime;

public:
    explicit LeakyBucketPolicy(std::chrono::milliseconds interval)
        : intervalBetweenRequests(interval), nextAvailableTime(Clock::now()) {}

    bool allow() override
    {
        TimePoint now = Clock::now();
        if (now >= nextAvailableTime)
        {
            nextAvailableTime = now + intervalBetweenRequests;
            return true;
        }
        return false;
    }
};

// RateLimiter Manager: Thread-safe per-client policy dispatch
class RateLimiter
{
private:
    std::mutex mtx;
    std::unordered_map<std::string, std::unique_ptr<RatePolicy>> clientPolicies;
    double defaultCapacity;
    double defaultRefillRate;

public:
    RateLimiter(double cap = 10.0, double rate = 5.0)
        : defaultCapacity(cap), defaultRefillRate(rate) {}

    bool evaluate(const Request &req)
    {
        std::lock_guard<std::mutex> lock(mtx);
        auto it = clientPolicies.find(req.clientId);
        if (it == clientPolicies.end())
        {
            clientPolicies[req.clientId] = std::make_unique<TokenBucketPolicy>(defaultCapacity, defaultRefillRate);
            it = clientPolicies.find(req.clientId);
        }
        return it->second->allow();
    }
};

// ==========================================
// 3. SERVER & LOAD BALANCER
// ==========================================

struct Server
{
    std::string id;
    int activeConnections{0};
    int totalProcessed{0};

    explicit Server(std::string sId) : id(std::move(sId)) {}
};

struct HeapEntry
{
    std::string serverId;
    int load;

    bool operator>(const HeapEntry &other) const
    {
        return load > other.load;
    }
};

enum class LBStrategy
{
    ROUND_ROBIN,
    LEAST_LOAD
};

class LoadBalancer
{
private:
    std::mutex mtx;
    std::vector<std::string> serverOrder;
    std::unordered_map<std::string, Server> servers;
    size_t rrIndex{0};
    LBStrategy strategy;
    std::priority_queue<HeapEntry, std::vector<HeapEntry>, std::greater<HeapEntry>> minHeap;

public:
    explicit LoadBalancer(LBStrategy strat = LBStrategy::LEAST_LOAD) : strategy(strat) {}

    void addServer(const std::string &id)
    {
        std::lock_guard<std::mutex> lock(mtx);
        servers.emplace(id, Server(id));
        serverOrder.push_back(id);
        minHeap.push({id, 0});
    }

    std::string dispatch()
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (serverOrder.empty())
            return "";

        if (strategy == LBStrategy::ROUND_ROBIN)
        {
            std::string selected = serverOrder[rrIndex];
            rrIndex = (rrIndex + 1) % serverOrder.size();
            servers[selected].activeConnections++;
            servers[selected].totalProcessed++;
            return selected;
        }

        // Lazy-deletion Min-Heap
        while (!minHeap.empty())
        {
            HeapEntry top = minHeap.top();
            minHeap.pop();

            auto it = servers.find(top.serverId);
            if (it != servers.end() && it->second.activeConnections == top.load)
            {
                it->second.activeConnections++;
                it->second.totalProcessed++;
                minHeap.push({top.serverId, it->second.activeConnections});
                return top.serverId;
            }
            // Stale entry discarded
        }

        std::string fallback = serverOrder[0];
        servers[fallback].activeConnections++;
        servers[fallback].totalProcessed++;
        minHeap.push({fallback, servers[fallback].activeConnections});
        return fallback;
    }

    void release(const std::string &serverId)
    {
        std::lock_guard<std::mutex> lock(mtx);
        auto it = servers.find(serverId);
        if (it != servers.end())
        {
            if (it->second.activeConnections > 0)
            {
                it->second.activeConnections--;
            }
            minHeap.push({serverId, it->second.activeConnections});
        }
    }

    void printStats()
    {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "\n--- Server Load Distribution ---\n";
        for (const auto &id : serverOrder)
        {
            const auto &s = servers[id];
            std::cout << "Server [" << s.id << "] -> Processed: "
                      << s.totalProcessed << ", Active: " << s.activeConnections << "\n";
        }
    }
};

// ==========================================
// 4. METRICS & SYNTHETIC CLIENTS
// ==========================================

class TrafficMonitor
{
private:
    std::mutex mtx;
    int totalAllowed{0};
    int totalRejected{0};

public:
    void record(bool allowed)
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (allowed)
            totalAllowed++;
        else
            totalRejected++;
    }

    void printSummary()
    {
        std::lock_guard<std::mutex> lock(mtx);
        int total = totalAllowed + totalRejected;
        double passRate = total > 0 ? (static_cast<double>(totalAllowed) / total) * 100.0 : 0.0;
        std::cout << "\n================ Traffic Summary ================\n";
        std::cout << "Total Requests : " << total << "\n";
        std::cout << "Allowed (200 OK): " << totalAllowed << "\n";
        std::cout << "Blocked (429)   : " << totalRejected << "\n";
        std::cout << "Pass Rate       : " << std::fixed << std::setprecision(2) << passRate << "%\n";
        std::cout << "=================================================\n";
    }
};

class Client
{
protected:
    std::string clientId;
    RateLimiter &rateLimiter;
    LoadBalancer &loadBalancer;
    TrafficMonitor &monitor;
    std::atomic<bool> &running;

public:
    Client(std::string id, RateLimiter &rl, LoadBalancer &lb, TrafficMonitor &tm, std::atomic<bool> &run)
        : clientId(std::move(id)), rateLimiter(rl), loadBalancer(lb), monitor(tm), running(run) {}

    virtual ~Client() = default;
    virtual std::chrono::milliseconds nextInterval() = 0;

    void run()
    {
        int reqId = 1;
        while (running.load())
        {
            Request req(clientId, reqId++);
            bool allowed = rateLimiter.evaluate(req);
            monitor.record(allowed);

            if (allowed)
            {
                std::string server = loadBalancer.dispatch();
                // Simulate processing latency
                std::this_thread::sleep_for(std::chrono::milliseconds(25));
                loadBalancer.release(server);
            }

            std::this_thread::sleep_for(nextInterval());
        }
    }
};

// Normal: ~1 req/sec -> within rate limit
class NormalClient : public Client
{
public:
    using Client::Client;
    std::chrono::milliseconds nextInterval() override
    {
        return std::chrono::milliseconds(1000);
    }
};

// Bursty: 15 rapid requests (20ms) followed by 2s cooldown
class BurstyClient : public Client
{
private:
    int burstCount{0};

public:
    using Client::Client;
    std::chrono::milliseconds nextInterval() override
    {
        if (burstCount < 15)
        {
            burstCount++;
            return std::chrono::milliseconds(20);
        }
        burstCount = 0;
        return std::chrono::milliseconds(2000);
    }
};

// Abusive: ~100 req/sec (10ms) -> aggressive flooding
class AbusiveClient : public Client
{
public:
    using Client::Client;
    std::chrono::milliseconds nextInterval() override
    {
        return std::chrono::milliseconds(10);
    }
};

// ==========================================
// 5. PIPELINE TEST EXECUTION
// ==========================================

int main()
{
    std::cout << "Initializing Traffic Management Pipeline (C++17)...\n";

    // Rate Limiter: Capacity = 10, Refill = 5 tokens/sec
    RateLimiter rateLimiter(10.0, 5.0);
    LoadBalancer loadBalancer(LBStrategy::LEAST_LOAD);
    TrafficMonitor monitor;

    loadBalancer.addServer("srv-alpha");
    loadBalancer.addServer("srv-beta");
    loadBalancer.addServer("srv-gamma");

    std::atomic<bool> running{true};
    std::vector<std::unique_ptr<Client>> clientInstances;
    std::vector<std::thread> threads;

    clientInstances.push_back(std::make_unique<NormalClient>("client-normal", rateLimiter, loadBalancer, monitor, running));
    clientInstances.push_back(std::make_unique<BurstyClient>("client-bursty", rateLimiter, loadBalancer, monitor, running));
    clientInstances.push_back(std::make_unique<AbusiveClient>("client-abusive", rateLimiter, loadBalancer, monitor, running));

    std::cout << "Running multi-threaded traffic simulation for 4 seconds...\n";
    for (auto &client : clientInstances)
    {
        threads.emplace_back(&Client::run, client.get());
    }

    std::this_thread::sleep_for(std::chrono::seconds(4));
    running.store(false);

    for (auto &th : threads)
    {
        if (th.joinable())
            th.join();
    }

    loadBalancer.printStats();
    monitor.printSummary();

    return 0;
}