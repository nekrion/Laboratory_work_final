#pragma once
#include <bits/stdc++.h>
#include "database.hpp"
#include "deliver.hpp"
#include "order.hpp"
#include "storage.hpp"
#include <cmath>
#include <algorithm>
using namespace std;

// Класс для управления доставками
class DeliveryManager {
private:
    Database& db;
    queue<Order> order_queue;
    double current_time;

public:
    DeliveryManager(Database& database);

    // Работа с заказами
    void addOrderToQueue(const Order& order);
    void assignOrders();  // назначение заказов свободным курьерам
    void fastForward(int hours);  // перемотка времени

    // Геттеры
    queue<Order>& getOrderQueue();
    double getCurrentTime() const;
    void setCurrentTime(double time);

    // Статусы
    void printDeliverStatus() const;
    void printOrderQueue() const;
};
