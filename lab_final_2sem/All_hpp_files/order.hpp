#include <bits/stdc++.h>

using namespace std;

class Order {
private:

    unsigned int id;  // id или номер заказа
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
        summary = 0;
        date_accepted = 0;
        date_delivered = 0;
        place = "-";
        storage = "-";
        is_accepted = false;
        is_delivered = false;
    }
    
    
    unsigned int getId();

    unsigned int getSummary();

    int getDateAccepted();

    int getDateDelivered();

    string getPlace();

    string getStorage();

    bool getIsAccepted();

    bool getIsDelivered();

    // нужны также setters

    // плюс нужно добавить перегрузку оператора вывода для удобного вывода информации
    // можно и перегрузить оператор ввода (по желанию)


};