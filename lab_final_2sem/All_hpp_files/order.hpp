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
    
    //getters
    unsigned int getId();
    unsigned int getIdDeliver();
    unsigned int getSummary();
    int getDateAccepted();
    int getDateDelivered();
    string getPlace();
    string getStorage();
    bool getIsAccepted();
    bool getIsDelivered();


    //setters
    void setId(unsigned int id);
    void setIdDeliver();
    void setSummary(unsigned int summary);
    void setDateAccepted(int date_accepted);
    void setDateDelivered(int date_delivered);
    void setPlace(string &place);
    void setStorage(string &storage);
    void setIsAccepted(bool is_accepted);
    void setIsDelivered(bool is_delivered);

    //methods
    void link_deliver(unsigned int id_deliver); // метод для связывания заказа с курьером
    

    // плюс нужно добавить перегрузку оператора вывода для удобного вывода информации
    // можно и перегрузить оператор ввода (по желанию)


};