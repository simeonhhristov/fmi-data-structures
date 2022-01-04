#include "interface.h"
#include "queue.cpp"
#include <vector>

struct MyStore : Store
{
private:
    ActionHandler *actionHandler = nullptr;
    int bananaCount = 0;
    int schweppesCount = 0;
    int time = 0;
    int indexOfLastlyArrivedClient = 0;
    int workerCount = 0;
    queue<Worker> sentWorkers{};
    queue<Client> clients{};
    std::vector<Client> waitingClients{};
    std::vector<FutureStock> futureStock;

    bool willBeDeliveredEnough(int leaveTime, int quantity, ResourceType resource)
    {
        if (futureStock.empty())
        {
            return false;
        }

        for (int i = 0; i < futureStock.size() && futureStock[i].atTime <= leaveTime; i++)
        {
            if (resource == ResourceType::banana && futureStock[i].bananaCount >= quantity)
            {
                return true;
            }

            if (resource == ResourceType::schweppes && futureStock[i].schweppesCount >= quantity)
            {
                return true;
            }
        }

        return false;
    }

    // will be used to determine program actions in advanceTo() method
    int getHashCode()
    {
        return (!(waitingClients.empty()) << 0) + (!(clients.isEmpty()) << 1) + (!(sentWorkers.isEmpty()) << 2);
    }

    int getIdxOfnextClientToLeave()
    {
        int idx = 0;
        for (int i = 1; i < waitingClients.size(); i++)
        {
            if (waitingClients[i].maxWaitTime < waitingClients[idx].maxWaitTime)
            {
                idx = i;
            }
        }
        return idx;
    }

    int getIdxOfEarliestToCome()
    {
        int idx = 0;
        for (int i = 1; i < waitingClients.size(); i++)
        {
            if (waitingClients[i].arriveMinute < waitingClients[idx].arriveMinute)
            {
                idx = i;
            }
        }
        return idx;
    }

    int timeOfEarliestEvent()
    {
        int a, b, c;
        a = b = c = INT32_MAX;
        if (!sentWorkers.isEmpty())
        {
            a = sentWorkers.peek().returnTime;
        }

        if (!clients.isEmpty())
        {
            b = clients.peek().arriveMinute;
        }

        if (!waitingClients.empty())
        {
            c = waitingClients[getIdxOfnextClientToLeave()].maxWaitTime;
        }

        return std::min(a, std::min(b, c));
    }

    void clientDepart(int idx, int bananas, int schweppes)
    {
        int bananasToTake = bananas;
        int schweppesToTake = schweppes;

        if (bananasToTake > this->bananaCount)
        {
            bananasToTake = this->bananaCount;
        }
        if (schweppesToTake > this->schweppesCount)
        {
            schweppesToTake = this->schweppesCount;
        }

        this->bananaCount -= bananasToTake;
        this->schweppesCount -= schweppesToTake;

        for (int i = 0; i < futureStock.size(); i++)
        {
            futureStock[i].bananaCount -= bananasToTake;
            futureStock[i].schweppesCount -= schweppesToTake;
        }

        if (this->actionHandler)
        {
            actionHandler->onClientDepart(idx, this->time, bananasToTake, schweppesToTake);
        }
        std::cout << idx << " " << this->time << " " << bananasToTake << " " << schweppesToTake << std::endl;
    }

    void clientOrder(ResourceType resource)
    {
        this->workerCount--;
        if (resource == ResourceType::banana)
        {
            if (this->actionHandler)
            {
                actionHandler->onWorkerSend(this->time, ResourceType::banana);
            }
            sentWorkers.enqueue(Worker(this->time + 60, ResourceType::banana));
            std::cout << "W " << this->time << " banana" << std::endl;
        }
        else
        {
            if (this->actionHandler)
            {
                actionHandler->onWorkerSend(this->time, ResourceType::schweppes);
            }
            sentWorkers.enqueue(Worker(this->time + 60, ResourceType::schweppes));
            std::cout << "W " << this->time << " schweppes" << std::endl;
        }
    }

    void workerRestock()
    {
        Worker currentWorker = sentWorkers.dequeue();
        this->workerCount++;
        if (currentWorker.resource == ResourceType::banana)
        {
            if (this->actionHandler)
            {
                actionHandler->onWorkerBack(this->time, ResourceType::banana);
            }
            this->bananaCount += 100;
            std::cout << "D " << this->time << " banana" << std::endl;
        }
        else
        {
            if (this->actionHandler)
            {
                actionHandler->onWorkerBack(this->time, ResourceType::schweppes);
            }
            this->schweppesCount += 100;
            std::cout << "D " << this->time << " schweppes" << std::endl;
        }

        // handle futureStock
        for (int i = 0; i < futureStock.size(); i++)
        {
            if (futureStock[i].atTime == this->time)
            {
                futureStock.erase(futureStock.begin() + i);
                break;
            }
        }
    }

    // functions for different cases...
    // 000 no more elements to work with(Simulation end / No events to start with)
    void case0()
    {
        return;
    }

    // 001 only waiting clients
    void case1()
    {
        int idx = getIdxOfnextClientToLeave();
        clientDepart(waitingClients[idx].arriveMinute, waitingClients[idx].bananaCount, waitingClients[idx].schweppesCount);

        waitingClients.erase(waitingClients.begin() + idx);
    }

    // 010 only clients
    void case2()
    {
        Client currClient = clients.dequeue();
        currClient.maxWaitTime += currClient.arriveMinute;
        currClient.arriveMinute = indexOfLastlyArrivedClient++;

        if (currClient.bananaCount <= this->bananaCount && currClient.schweppesCount <= this->schweppesCount)
        {
            clientDepart(currClient.arriveMinute, currClient.bananaCount, currClient.schweppesCount);
        }
        else if (currClient.bananaCount > this->bananaCount && currClient.schweppesCount > this->bananaCount && workerCount == 1)
        {
            FutureStock fStock = FutureStock(this->bananaCount, this->schweppesCount, this->time + 60);
            if (currClient.bananaCount - this->bananaCount >= currClient.schweppesCount - this->schweppesCount)
            {
                clientOrder(ResourceType::banana);
                fStock.bananaCount += 100;
            }
            else
            {
                clientOrder(ResourceType::schweppes);
                fStock.schweppesCount += 100;
            }
            waitingClients.push_back(currClient);
            futureStock.push_back(fStock);
        }
        else if ((currClient.bananaCount > this->bananaCount || currClient.schweppesCount > this->schweppesCount) && this->workerCount >= 1)
        {
            FutureStock fStock = FutureStock(this->bananaCount, this->schweppesCount, this->time + 60);
            if (currClient.bananaCount > this->bananaCount && !willBeDeliveredEnough(currClient.maxWaitTime, currClient.bananaCount, ResourceType::banana))
            {
                clientOrder(ResourceType::banana);
                fStock.bananaCount += 100;
            }
            if (currClient.schweppesCount > this->schweppesCount && !willBeDeliveredEnough(currClient.maxWaitTime, currClient.schweppesCount, ResourceType::schweppes))
            {
                clientOrder(ResourceType::schweppes);
                fStock.schweppesCount += 100;
            }
            waitingClients.push_back(currClient);
            futureStock.push_back(fStock);
        }
        else
        {
            waitingClients.push_back(currClient);
        }
    }

    // 011 - clients and waiting clients
    void case3()
    {   
        int idx = getIdxOfnextClientToLeave();
        if (clients.peek().arriveMinute <= waitingClients[idx].maxWaitTime)
        {
            case2();
        }
        else
        {
            case1();
        }
    }

    // 100 - only workers to return
    void case4()
    {   
        workerRestock();
    }

    // 101 - sent workers and  clients to depart
    void case5()
    {
        int idx = getIdxOfnextClientToLeave();
        if (sentWorkers.peek().returnTime <= waitingClients[idx].maxWaitTime)
        {
            workerRestock();

            int idxOfEarliestToCome = getIdxOfEarliestToCome();

            if (waitingClients[idxOfEarliestToCome].bananaCount <= this->bananaCount && waitingClients[idxOfEarliestToCome].schweppesCount <= this->schweppesCount)
            {
                clientDepart(waitingClients[idxOfEarliestToCome].arriveMinute, waitingClients[idxOfEarliestToCome].bananaCount, waitingClients[idxOfEarliestToCome].schweppesCount);
                waitingClients.erase(waitingClients.begin() + idxOfEarliestToCome);
            }
        }
        else
        {
            case1();
        }
    }

    // 110 - sent workers and comming clients
    void case6()
    {
        if (clients.peek().arriveMinute <= sentWorkers.peek().returnTime)
        {
            case2();
        }
        else
        {
            case4();
        }
    }

    // 111 - all
    void case7()
    {
        int idx = getIdxOfnextClientToLeave();
        if (clients.peek().arriveMinute <= sentWorkers.peek().returnTime && clients.peek().arriveMinute <= waitingClients[idx].maxWaitTime)
        {
            case2();
        }
        else if (sentWorkers.peek().returnTime < clients.peek().arriveMinute && sentWorkers.peek().returnTime <= waitingClients[idx].maxWaitTime)
        {
            case5();
        }
        else
        {
            case1();
        }
    }

public:
    MyStore() = default;

    void setActionHandler(ActionHandler *handler) override
    {
        actionHandler = handler;
    }

    void init(int workerCount, int startBanana, int startSchweppes) override
    {
        this->workerCount = workerCount;
        this->bananaCount = startBanana;
        this->schweppesCount = startSchweppes;
    }

    void addClients(const Client *clients, int count) override
    {
        for (int i = 0; i < count; ++i)
        {
            this->clients.enqueue(clients[i]);
        }
    }

    void advanceTo(int minute) override
    {
        // array with pointers to different case functions
        void (MyStore::*cases[])() = {&MyStore::case0, &MyStore::case1, &MyStore::case2, &MyStore::case3, &MyStore::case4, &MyStore::case5, &MyStore::case6, &MyStore::case7};

        while (timeOfEarliestEvent() <= minute)
        {
            this->time = timeOfEarliestEvent();
            int idx = this->getHashCode();

            (this->*cases[idx])();
        }
    }

    virtual int getBanana() const
    {
        return this->bananaCount;
    }

    virtual int getSchweppes() const
    {
        return this->schweppesCount;
    }
};

Store *createStore()
{
    return new MyStore();
}
