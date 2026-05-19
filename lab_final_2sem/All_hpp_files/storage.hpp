#include <bits/stdc++.h>
#include "../All_hpp_files/deliver.hpp"

using namespace std;


class Storage {
private:

    unsigned int id; // id склада
    string name; // название склада
    pair<int, int> coordinates; // координаты склада
    vector<unsigned int> id_linked_delivers; // массив id доставщиков привязанных к складу
    bool is_active; // состояние скалад что акивен он или нет


public:

    Storage() {
        id = 0;
        name = "-";
        coordinates = {0, 0};
        is_active = false;
    }

    //getters
    unsigned int getId();
    string getName();
    pair<int, int> getCoordinates();
    vector<unsigned int> getIdDelivers();
    bool getIsActive();

    //setters
    void setId(unsigned int id);
    void setName(string &name);
    void setCoordinates(const pair<int, int> &coordinates);
    void setIdDelivers(vector<unsigned int> &id_linked_delivers);
    void setIsActive(bool is_active);

    //methods
    void link_deliver(unsigned int id_deliver); // для того чтобы свзяать доставшика со складом

};