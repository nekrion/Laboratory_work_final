#include "../All_hpp_files/order.hpp"
// здесь реализация классов/класса

//getters
unsigned int Order::getId() const {
    return id;
}

unsigned int Order::getIdDeliver() const {
    return id_deliver;
}

unsigned int Order::getSummary() const {
    return summary;
}

int Order::getDateAccepted() const {
    return date_accepted;
}

int Order::getDateDelivered() const {
    return date_delivered;
}

const string& Order::getPlace() const {
    return place;
}

const string& Order::getStorage() const {
    return storage;
}

bool Order::getIsAccepted() const {
    return is_accepted;
}

bool Order::getIsDelivered() const {
    return is_delivered;
}


//setters
void Order::setId(unsigned int n_id) {
    id = n_id;
}

void Order::setIdDeliver(unsigned int n_id_deliver) {
    id_deliver = n_id_deliver;
}

void Order::setSummary(unsigned int n_summary) {
    summary = n_summary;
}

void Order::setDateAccepted(int n_date_accepted) {
    date_accepted = n_date_accepted;
}

void Order::setDateDelivered(int n_date_delivered) {
    date_delivered = n_date_delivered;
}

void Order::setPlace(string &n_place) {
    place = n_place;
}

void Order::setStorage(string &n_storage) {
    storage = n_storage;
}

void Order::setIsAccepted(bool n_is_accepted) {
    is_accepted = n_is_accepted;
}

void Order::setIsDelivered(bool n_is_delivered) {
    is_delivered = n_is_delivered;
}