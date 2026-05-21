#include "../All_hpp_files/deliver.hpp"
// здесь реализация классов/класса


//constructors
Deliver::Deliver(unsigned int id, unsigned int id_linked_storage, unsigned int speed, 
                 const string &name, bool is_have_order, bool is_linked_with_storage) 
{
    this->id = id;
    this->id_linked_storage = id_linked_storage;
    this->speed = speed;
    this->name = name;
    this->is_have_order = is_have_order;
    this->is_linked_with_storage = is_linked_with_storage;
}

//реализация getters
unsigned int Deliver::getId() const {
    return id;
}

unsigned int Deliver::getIdLinkedStorage() const {
    return id_linked_storage;
}

unsigned int Deliver::getSpeed() const {
    return speed;
}

const string& Deliver::getName() const {
    return name;
}

bool Deliver::getIsHaveOrder() const {
    return is_have_order;
}

bool Deliver::getIsLinkedWithStorage() const {
    return is_linked_with_storage;
}


// реализация setters
void Deliver::setId(unsigned int n_id) {
    id = n_id;
}

void Deliver::setIdLinkedStorage(unsigned int n_id_linked_storage) {
    id_linked_storage = n_id_linked_storage;
}

void Deliver::setSpeed(unsigned int n_speed) {
    speed = n_speed;
}

void Deliver::setName(const string &n_name) {
    name = n_name;
}

void Deliver::setIsHaveOrder(bool n_is_have_order) {
    is_have_order = n_is_have_order;
}

void Deliver::setIsLinkedWithStorage(bool n_is_linked_with_storage) {
    is_linked_with_storage = n_is_linked_with_storage;
}


//methods
void Deliver::print() const {
    cout << "--------------------------\n";
    cout << "Тип: Курьер\n";
    cout << "ID: " << id << "\n";
    cout << "Имя: " << name << "\n";
    cout << "Скорость: " << speed << "\n";
    if (id_linked_storage == 0) {
        cout << "Не привязан к складу\n";
    } else {
        cout << "Привязан к складу ID: " << id_linked_storage << "\n";
    }
    if (is_have_order) {
        cout << "Есть заказ\n";
    } else {
        cout << "Не назначен на заказ\n";
    }
    cout << "--------------------------\n";
}
