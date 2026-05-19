#include "../All_hpp_files/storage.hpp"
// здесь реализация классов/класса


// реализация getters
unsigned int Storage::getId() const {
    return id;
}

const string& Storage::getName() const {
    return name;
}

const pair<int, int>& Storage::getCoordinates() const {
    return coordinates;
}

const vector<unsigned int>& Storage::getIdDelivers() const {
    return id_linked_delivers;
}

bool Storage::getIsActive() const {
    return is_active;
}



//реализация settters
void Storage::setId(unsigned int n_id) {
    id = n_id;
}

void Storage::setName(const string &n_name) {
    name = n_name;
}

void Storage::setCoordinates(const pair<int, int> &n_coordinates) {
    coordinates = n_coordinates;
}

void Storage::setIdDelivers(const vector<unsigned int> &n_id_linked_delivers) {
    id_linked_delivers = n_id_linked_delivers;
}

void Storage::setIsActive(bool n_is_active) {
    is_active = n_is_active;
}

