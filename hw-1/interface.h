#include <iostream>
#pragma once
/// The type of resource, used when creating events
enum class ResourceType
{
    banana,
    schweppes,
};

struct ActionHandler
{
    virtual void onWorkerSend(int minute, ResourceType resource) = 0;

    virtual void onWorkerBack(int minute, ResourceType resource) = 0;

    virtual void onClientDepart(int index, int minute, int banana, int schweppes) = 0;
};

struct FutureStock
{
    int bananaCount;
    int schweppesCount;
    int atTime;

    FutureStock(int banana, int schweppes, int time) : bananaCount(banana), schweppesCount(schweppes), atTime(time)
    {
    }
};

/// Descriptor of a client that arrives at the store
struct Client
{
    int arriveMinute;
    int bananaCount;
    int schweppesCount;
    int maxWaitTime;

    Client() = default;
    Client(int arriveMinute_, int bananaCount_, int schweppesCount_, int maxWaitTime_) : arriveMinute(arriveMinute_),
                                                                                         bananaCount(bananaCount_),
                                                                                         schweppesCount(schweppesCount_),
                                                                                         maxWaitTime(maxWaitTime_)
    {
    }
    friend std::istream &operator>>(std::istream &in, Client &other)
    {
        in >> other.arriveMinute >> other.bananaCount >> other.schweppesCount >> other.maxWaitTime;
        return in;
    }
};

struct Worker
{
    int returnTime = 0;
    ResourceType resource = ResourceType::banana;

    Worker() = default;
    Worker(int returnTime, ResourceType resource)
    {
        this->returnTime = returnTime;
        this->resource = resource;
    }
};

struct Store
{
    virtual void init(int workerCount, int startBanana = 0, int startSchweppes = 0) = 0;

    virtual void setActionHandler(ActionHandler *handler) = 0;

    virtual void addClients(const Client *clients, int count) = 0;

    virtual void advanceTo(int minute) = 0;

    virtual int getBanana() const = 0;

    virtual int getSchweppes() const = 0;

    virtual ~Store() {}
};

Store *createStore();