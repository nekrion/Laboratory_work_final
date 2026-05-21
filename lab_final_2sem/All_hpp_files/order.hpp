#pragma once
#include <bits/stdc++.h>
#include <cmath>

using namespace std;

class Order {
private:

    unsigned int id;  // id или номер заказа
    string customer_name;
    string place;  // куда доставить
    unsigned int storage_id; // от какого склада
    pair<int, int> delivery_address; // координаты доставки
    bool is_completed; // статус выполнения заказа
    bool is_active; // назначен ли курьеру
    unsigned int assigned_deliver_id; // id доставки
    double distance_from_storage; // расстояние от склада до клиента
    double estimated_time; // оценочное время доставки

    // также можно в будущем добавить тип заказа, например, 
    // продукты это или техника или ещё что-то

public:

    // конструкторы
    Order() : id(0), customer_name("-"), place(""), storage_id(0),
        delivery_address({ 0, 0 }), is_completed(false), is_active(false),
        assigned_deliver_id(0), distance_from_storage(0), estimated_time(0) {}

    Order(unsigned int id, const string& name, const pair<int, int>& addr,
        unsigned int storage_id);

    // геттеры
    unsigned int getId() const;
    string getCustomerName() const;
    pair<int, int> getDeliveryAddress() const;
    unsigned int getStorageId() const;
    bool getIsCompleted() const;
    bool getIsActive() const;
    unsigned int getAssignedDeliverId() const;
    double getDistance() const;
    double getEstimatedTime() const;

    // сеттеры
    void setIsCompleted(bool completed);
    void setIsActive(bool active);
    void setAssignedDeliverId(unsigned int deliver_id);
    void setDistance(double dist);
    void setEstimatedTime(double time);

    void print() const;

    // вычисление расстояния до точки
    double calculateDistanceTo(const pair<int, int>& point) const;
};
