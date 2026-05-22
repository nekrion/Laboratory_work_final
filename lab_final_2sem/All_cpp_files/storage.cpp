#include "./../All_hpp_files/storage.hpp"
// здесь реализация классов/класса


// constructors

Storage::Storage(unsigned int id, const string &name, const pair<int, int> &coordinates, 
				 const vector<unsigned int> &id_linked_delivers, bool is_active) {

	this->id = id;
	this->name = name;
	this->coordinates = coordinates;
	this->id_linked_delivers = id_linked_delivers;
	this->is_active = is_active;
	// очередь по умолчанию пуста (создаётся автоматически)
}


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

queue<unsigned int> Storage::getOrderQueue() const {
	return order_queue; // возвращаем копию очереди (для сохранения)
}


// реализация setters

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

void Storage::setOrderQueue(queue<unsigned int> q) {
	order_queue = q;
}


// methods

void Storage::link_deliver(unsigned int id_deliver) {
	// добавляем id курьера в список, если его там ещё нет
	for (unsigned int did : id_linked_delivers) {
		if (did == id_deliver) return; // уже есть
	}
	id_linked_delivers.push_back(id_deliver);
}

void Storage::print() const {
	cout << "--------------------------\n";
	cout << "Тип: Склад\n";
	cout << "ID: " << id << "\n";
	cout << "Название склада: " << name << "\n";
	cout << "Координаты x: " << coordinates.first << " y: " << coordinates.second << "\n";
	cout << "ID курьеров, закрепленных за данным складом: ";
	if (id_linked_delivers.empty()) {
		cout << "Нет курьеров\n";
	} else {
		for (auto i : id_linked_delivers) {
			cout << i << " ";
		}
		cout << "\n";
	}
	if (is_active) {
		cout << "Склад работает\n";
	} else {
		cout << "Склад не работает\n";
	}
	cout << "--------------------------\n";
}


// методы для работы с очередью заказов

void Storage::addToQueue(unsigned int orderId) {
	order_queue.push(orderId);
}

unsigned int Storage::popFromQueue() {
	if (order_queue.empty()) return 0;
	unsigned int front = order_queue.front();
	order_queue.pop();
	return front;
}

bool Storage::isQueueEmpty() const {
	return order_queue.empty();
}

void Storage::clearQueue() {
	while (!order_queue.empty()) order_queue.pop();
}
