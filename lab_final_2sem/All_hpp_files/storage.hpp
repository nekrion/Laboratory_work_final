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
    unsigned int getId() const;
    const string& getName() const;
    const pair<int, int>& getCoordinates() const;
    const vector<unsigned int>& getIdDelivers() const;
    bool getIsActive() const;

    //setters
    void setId(unsigned int n_id);
    void setName(const string &n_name);
    void setCoordinates(const pair<int, int> &n_coordinates);
    void setIdDelivers(const vector<unsigned int> &n_id_linked_delivers);
    void setIsActive(bool n_is_active);

    //methods
    void link_deliver(unsigned int id_deliver); // для того чтобы свзяать доставшика со складом

};