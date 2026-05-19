#include<bits/stdc++.h>

using namespace std;

class Deliver {
private:

    unsigned int id; // id доставщика
    unsigned int id_linked_storage; // id склада с которым связан курьер
    string name; // имя курьера
    bool is_have_order; // состояние что есть ли заказ
    bool is_linked_with_storage; // состояние что привязан ли к какому-либо складу

public:

    Deliver() {
        id = 0;
        id_linked_storage = 0;
        name = "-";
        is_have_order = false;
        is_linked_with_storage = false;
    }

    //getters
    unsigned int getId();
    unsigned int getIdLinkedStorage();
    string getName();
    bool getIsHaveOrder();
    bool getIsLinkedWithStorage();

    //setters
    void setId(unsigned int id);
    void setIdLinkedStorage(unsigned int id_linked_storage);
    void setName(string &name);
    void setIsHaveOrder(bool is_have_order);
    void setIsLinkedWithStorage(bool is_linked_with_storage);

    //methods
    

};
