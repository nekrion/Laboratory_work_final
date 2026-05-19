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
    unsigned int getId() const;
    unsigned int getIdLinkedStorage() const;
    const string& getName() const;
    bool getIsHaveOrder() const;
    bool getIsLinkedWithStorage() const;

    //setters
    void setId(unsigned int n_id);
    void setIdLinkedStorage(unsigned int n_id_linked_storage);
    void setName(const string &name);
    void setIsHaveOrder(bool n_is_have_order);
    void setIsLinkedWithStorage(bool n_is_linked_with_storage);

    //methods
    

};
