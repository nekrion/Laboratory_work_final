#pragma once
#include <bits/stdc++.h>

using namespace std;

class Order {
private:

    unsigned int id;  // id или номер заказа
    unsigned int id_deliver; // id курьера, кто взял заказ
    unsigned int summary; // сумма заказа
    int date_accepted; // когда приняли
    int date_delivered;  // когда доставили
    string place;  // куда доставить
    string storage;  // с какого склада
    bool is_accepted;  // состояние что заказ принят
    bool is_delivered; // состояние что заказ доставлен

    // также можно в будущем добавить тип заказа, например, продукты это или техника или ещё что-то


public:

    //constructors
    Order() {
        id = 0;
        id_deliver = 0;
        summary = 0;
        date_accepted = 0;
        date_delivered = 0;
        place = "-";
        storage = "-";
        is_accepted = false;
        is_delivered = false;
    }

    Order(unsigned int id, unsigned int summary, int date_accepted, int date_delivered, 
          const string &place, const string &storage, bool is_accepted, bool is_delivered);
    
    //getters
    unsigned int getId() const;
    unsigned int getIdDeliver() const;
    unsigned int getSummary() const;
    int getDateAccepted() const;
    int getDateDelivered() const;
    const string& getPlace() const;
    const string& getStorage() const;
    bool getIsAccepted() const;
    bool getIsDelivered() const;


    //setters
    void setId(unsigned int n_id);
    void setIdDeliver(unsigned int n_id_deliver);
    void setSummary(unsigned int n_summary);
    void setDateAccepted(int n_date_accepted);
    void setDateDelivered(int n_date_delivered);
    void setPlace(string &n_place);
    void setStorage(string &n_storage);
    void setIsAccepted(bool n_is_accepted);
    void setIsDelivered(bool n_is_delivered);

    //methods
    void link_deliver(unsigned int n_id_deliver); // метод для связывания заказа с курьером
    

    // плюс нужно добавить перегрузку оператора вывода для удобного вывода информации
    // можно и перегрузить оператор ввода (по желанию)


};