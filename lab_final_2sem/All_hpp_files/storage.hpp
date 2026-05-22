/**
 * @file storage.hpp
 * @brief Определение класса Storage (склад).
 * @authors Грачев Никита, Салтысюк Анастасия, Павлюченков Артем, Пропажин Антон, Луконин Валерий.
 * @date 2026
 */
#pragma once
#include <bits/stdc++.h>
#include <queue>
#include "deliver.hpp"

using namespace std;
/**
 * @brief Класс, представляющий склад компании доставки.
 * 
 * Хранит информацию о складе: ID, название, координаты,
 * список привязанных курьеров, активность и очередь заказов,
 * ожидающих свободного курьера.
 */


class Storage {
private:

	unsigned int id; // id склада
	string name; // название склада
	pair<int, int> coordinates; // координаты склада
	vector<unsigned int> id_linked_delivers; // массив id доставщиков привязанных к складу
	bool is_active; // состояние скалад что акивен он или нет
	queue<unsigned int> order_queue; // очередь заказов (id), ожидающих свободного курьера

public:

	Storage() {
		 /**
     * @brief Конструктор с параметрами.
     * @param id ID склада
     * @param name Название
     * @param coordinates Координаты
     * @param id_linked_delivers Вектор ID привязанных курьеров
     * @param is_active Активен ли
     */
		id = 0;
		name = "-";
		coordinates = {0, 0};
		is_active = false;
		// очередь пуста по умолчанию
	}

	Storage(unsigned int id, const string &name, const pair<int, int> &coordinates, 
			const vector<unsigned int> &id_linked_delivers, bool is_active);

	//getters
	unsigned int getId() const;
	const string& getName() const;
	const pair<int, int>& getCoordinates() const;
	const vector<unsigned int>& getIdDelivers() const;
	bool getIsActive() const;
	queue<unsigned int> getOrderQueue() const; // для сохранения

	//setters
	void setId(unsigned int n_id);
	void setName(const string &n_name);
	void setCoordinates(const pair<int, int> &n_coordinates);
	void setIdDelivers(const vector<unsigned int> &n_id_linked_delivers);
	void setIsActive(bool n_is_active);
	void setOrderQueue(queue<unsigned int> q); // для загрузки

	//methods
	void link_deliver(unsigned int id_deliver); // для того чтобы связать доставщика со складом
	void print() const; // удобный вывод информации о Storage

	// методы для работы с очередью заказов
	void addToQueue(unsigned int orderId);	// добавить заказ в очередь
	unsigned int popFromQueue(); // извлечь заказ из очереди (и удалить)
	bool isQueueEmpty() const; // проверка, пуста ли очередь
	void clearQueue(); // очистить очередь (при удалении склада)
};
