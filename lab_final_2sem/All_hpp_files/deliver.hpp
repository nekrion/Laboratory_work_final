#pragma once
#include<bits/stdc++.h>
#include <cmath>

using namespace std;

class Deliver {
private:

    unsigned int id; // id доставщика
    string name; // имя курьера
    pair<int, int> coordinates; // координаты курьера
    unsigned int storage_id;
    // состояние курьера
    bool is_free;
    bool is_on_delivery;

    unsigned int current_order_id; // id текущего заказа (0 если нет)
    double speed; // скорость курьера
    pair<double, double> position; // текущая позиция (интерполяция между точками)
    double remaining_distance; // оставшееся расстояние до цели
    pair<int, int> target_point; // куда едет (склад или клиент)
    double time_to_target; // время в часах до цели

public:
    // конструкторы
    Deliver() : id(0), name("-"), coordinates({ 0,0 }), storage_id(0),
        is_free(true), is_on_delivery(false), current_order_id(0),
        speed(30.0), position({ 0,0 }), remaining_distance(0),
        target_point({ 0,0 }), time_to_target(0) {}
    
    Deliver(unsigned int id, const string& name, const pair<int, int>& coords,
        unsigned int storage_id, double sp = 30.0);
    // геттеры
    unsigned int getId() const;
    string getName() const;
    pair<int, int> getCoordinates() const;
    unsigned int getStorageId() const;
    bool getIsFree() const;
    bool getIsOnDelivery() const;
    unsigned int getCurrentOrderId() const;
    double getSpeed() const;
    pair<double, double> getPosition() const;
    double getRemainingDistance() const;
    // сеттеры
    void setIsFree(bool free);
    void setCoordinates(const pair<int, int>& coords);
    void setPosition(const pair<double, double>& pos);
    void setRemainingDistance(double dist);

    // Методы для движения
    void startDelivery(unsigned int order_id, const pair<int, int>& destination);
    void updatePosition(double hours); // обновить позицию за время
    bool isDeliveryComplete() const; // завершена ли доставка
    void completeDelivery(); // завершить доставку

    void print() const;
};
