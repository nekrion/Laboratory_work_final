#include <bits/stdc++.h>
#include "../All_hpp_files/deliver.hpp"

using namespace std;


class Storage {
private:
    unsigned int id; // id склада
    string name; // название склада
    pair<int, int> coordinates; // координаты склада
    vector<Deliver> linked_delivers; // массив доставщиков привязанных к складу
    bool is_active; // состояние скалад что акивен он или нет


public:
    Storage() {
        id = 0;
        name = "-";
        coordinates = {0, 0};
        is_active = false;
    }

    unsigned int getId();

    string getName();

    pair<int, int> getCoordinates();

    vector<Deliver> getDelivers();

    bool getIsActive();

};