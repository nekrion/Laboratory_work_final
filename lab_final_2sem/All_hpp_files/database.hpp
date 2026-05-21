#pragma once
#include <bits/stdc++.h>
#include "deliver.hpp"
#include "order.hpp"
#include "storage.hpp"
#include <fstream>
#include <algorithm>
using namespace std;


class Database {
private:
    vector<Storage> storages;
    vector<Deliver> delivers;
    vector<Order> orders;
    int next_order_id;

public:
    Database();

    // Добавление
    void addStorage(const Storage& s);
    void addDeliver(const Deliver& d);
    void addOrder(const Order& o);

    // Удаление
    bool removeStorage(unsigned int id);
    bool removeDeliver(unsigned int id);
    bool removeOrder(unsigned int id);

    // Поиск
    Storage* findStorage(unsigned int id);
    Deliver* findDeliver(unsigned int id);
    Order* findOrder(unsigned int id);
    vector<Deliver*> findFreeDeliversByStorage(unsigned int storage_id);

    // Получение
    vector<Storage>& getStorages();
    vector<Deliver>& getDelivers();
    vector<Order>& getOrders();

    // Загрузка/сохранение
    void saveToFile(const string& filename);
    void loadFromFile(const string& filename);

    void printAll() const;
    int getNextOrderId();
};
