#include <iostream>
#include <vector>
#include "queue.cpp"
#include "interface.h"

int main()
{
    Store *market = createStore();

    int workerCount;
    int clientCount;
    std::cin >> workerCount >> clientCount;

    Client *clients = new Client[clientCount];
    for (int i = 0; i < clientCount; i++)
    {
        Client newClient;
        std::cin >> newClient;
        clients[i] = newClient;
    }
    std::cout << std::endl;
    market->init(workerCount, 0, 0);
    market->addClients(clients, clientCount);
    market->advanceTo(clients[clientCount - 1].maxWaitTime + clients[clientCount - 1].arriveMinute);
}