#include <bits/stdc++.h>
#include "deliver.hpp"
#include "order.hpp"
#include "storage.hpp"

using namespace std;

// нужно реализовать базу данных через 
class DataBase {
private:

    vector<Order> orders; // массив объектов класса Order
    vector<Deliver> delivers; // массив объектов класса Deliver
    vector<Storage> storages; // массив объектов класса Storage


public:

    DataBase();

    //adders
    void addOrder(unsigned int id, unsigned int summary, int date_accepted, int date_delivered, string &place, string &storage, bool is_accepted, bool is_delivered); // добавление объетка класса Order
    void addDeliver(unsigned int id, unsigned int id_linked_storage, string &name, bool is_have_order, bool is_linked_with_storage); // добавление объетка класса Deliver
    void addStorage(unsigned int id, string &name, pair<int, int> &coordinates, vector<unsigned int> &id_linked_delivers, bool is_active); // добавление объетка класса Storage
    // (Примечание) Можно сделать необяхательным заоленение в функции cector<Deliver> &linked_delivers


    //work with files
    void save_to_file(string &str); // сохранение базы в файл
    void load_from_file(string &str); // загрузка базы из файла


    //methods
    void remove(string &str, unsigned int id); // удаление из базы данных одного элемента конкретного класса
    void print(); // пока что без перегузки оператора <<, поэтому метод вывода всей базы данных

};

