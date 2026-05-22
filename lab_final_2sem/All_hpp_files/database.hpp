#pragma once
#include <bits/stdc++.h>
#include "deliver.hpp"
#include "order.hpp"
#include "storage.hpp"

using namespace std;

// Класс базы данных, объединяет все сущности (заказы, курьеры, склады)
class DataBase {
private:

	vector<Order> orders; // массив объектов класса Order
	vector<Deliver> delivers; // массив объектов класса Deliver
	vector<Storage> storages; // массив объектов класса Storage
	int global_time; // глобальное время в часах (от начала работы)

public:

	DataBase(); // конструктор, инициализирует global_time = 0

	// добавление объектов
	void addOrder(unsigned int id, unsigned int summary, int date_accepted, int date_delivered,
		const string &place, const string &storage, bool is_accepted, bool is_delivered,
		const pair<int,int> &place_coordinates); // добавление заказа

	void addDeliver(unsigned int id, unsigned int id_linked_storage, unsigned int speed,
		const string &name, bool is_have_order, bool is_linked_with_storage); // добавление курьера

	void addStorage(unsigned int id, const string &name, const pair<int, int> &coordinates,
		const vector<unsigned int> &id_linked_delivers, bool is_active); // добавление склада

	// удаление объектов (вместо одного remove)
	void removeStorage(unsigned int id); // удаление склада по ID
	void removeDeliver(unsigned int id); // удаление курьера по ID
	void removeOrder(unsigned int id); // удаление заказа по ID

	// вывод информации
	void printAll(); // вывод всей базы данных (склады, курьеры, заказы)
	void printStorageInfo(unsigned int storageId); // информация о конкретном складе
	void printDeliversOnStorage(unsigned int storageId); // курьеры склада (свободные/занятые/в пути)
	void printOrderQueueOfStorage(unsigned int storageId); // очередь заказов склада

	// бизнес-логика
	bool assignOrderToFreeDeliver(Order &order, unsigned int storageId); // назначить заказ свободному курьеру (если нет – в очередь)
	void advanceTime(int hours); // промотка времени на N часов (пересчёт движения курьеров, выдача из очереди)

	// работа с файлами
	void save_to_file(const string &filename); // сохранение БД в файл (с новыми полями)
	void load_from_file(const string &filename); // загрузка БД из файла

	// геттеры для вспомогательного доступа (нужны при сохранении/загрузке)
	vector<Order>& getOrders() { return orders; }
	vector<Deliver>& getDelivers() { return delivers; }
	vector<Storage>& getStorages() { return storages; }
	int getGlobalTime() const { return global_time; }
	void setGlobalTime(int t) { global_time = t; }
};
