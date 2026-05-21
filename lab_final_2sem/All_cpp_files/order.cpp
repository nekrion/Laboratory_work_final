#include "../All_hpp_files/order.hpp"
// здесь реализация классов/класса


//constructors
Order::Order(unsigned int id, unsigned int summary, int date_accepted, int date_delivered, 
          const string &place, const string &storage, bool is_accepted, bool is_delivered, const pair<int, int> &place_coordinates) {
    
    this->id = id;
    this->id_deliver = 0;
    this->summary = summary;
    this->date_accepted = date_accepted;
    this->date_delivered = date_delivered;
    this->place = place;
    this->storage = storage;
    this->is_accepted = is_accepted;
    this->is_delivered = is_delivered;
    this->place_coordinates = place_coordinates;
}   



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

const pair<int, int>& Order::getPlaceCoordinates() const {
    return place_coordinates;
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

void Order::setPlaceCoordinates(pair<int, int> &n_place_coordinates) {
    place_coordinates = n_place_coordinates;
}


//methods
void Order::print() const{
    cout << "--------------------------\n";
    cout << "Тип: Заказ\n";
    cout << "ID: " << id << "\n";
    if (id_deliver == 0) {
        cout << "Курьер не назначен\n";
    } else {
        cout << "ID курьера, назанченного на данный заказ: " << id_deliver << "\n";
    }
    cout << "Сумма: " << summary << "\n";
    cout << "Время принятия заказа: " << date_accepted << "\n";
    cout << "Время доставки: " << date_delivered << "\n";
    cout << "Откуда: " << storage << "\n";
    cout << "Куда: " << place << "( x: " << place_coordinates.first << " y: " << place_coordinates.second << ")\n";
    if (is_accepted) {
        cout << "Заказ принят\n";
    } else {
        cout << "Заказ не принят\n";
    }
    if (is_delivered) {
        cout << "Заказ доставлен\n";
    } else {
        cout << "Заказ не доставлен\n";
    }
    cout << "--------------------------\n";

    
}