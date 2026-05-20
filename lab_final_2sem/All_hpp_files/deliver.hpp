#pragma once
#include<bits/stdc++.h>

using namespace std;

class Deliver {
private:

    unsigned int id; // id доставщика
    unsigned int id_linked_storage; // id склада с которым связан курьер
    unsigned int speed; // скорость курьера
    string name; // имя курьера
    bool is_have_order; // состояние что есть ли заказ
    bool is_linked_with_storage; // состояние что привязан ли к какому-либо складу

public:

    //constructors
    Deliver() {
        id = 0;
        id_linked_storage = 0;
        speed = 0;
        name = "-";
        is_have_order = false;
        is_linked_with_storage = false;
    }

    Deliver::Deliver(unsigned int id, unsigned int id_linked_storage, unsigned int speed, 
                 const string &name, bool is_have_order, bool is_linked_with_storage);

    //getters
    unsigned int getId() const;
    unsigned int getIdLinkedStorage() const;
    unsigned int getSpeed() const;
    const string& getName() const;
    bool getIsHaveOrder() const;
    bool getIsLinkedWithStorage() const;

    //setters
    void setId(unsigned int n_id);
    void setIdLinkedStorage(unsigned int n_id_linked_storage);
    void setSpeed(unsigned int n_speed);
    void setName(const string &name);
    void setIsHaveOrder(bool n_is_have_order);
    void setIsLinkedWithStorage(bool n_is_linked_with_storage);

    //methods
    

};
