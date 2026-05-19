#include "../All_hpp_files/deliver.hpp"
// здесь реализация классов/класса


//реализация getters
unsigned int Deliver::getId() const {
    return id;
}

unsigned int Deliver::getIdLinkedStorage() const {
    return id_linked_storage;
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

void Deliver::setName(const string &n_name) {
    name = n_name;
}

void Deliver::setIsHaveOrder(bool n_is_have_order) {
    is_have_order = n_is_have_order;
}

void Deliver::setIsLinkedWithStorage(bool n_is_linked_with_storage) {
    is_linked_with_storage = n_is_linked_with_storage;
}


