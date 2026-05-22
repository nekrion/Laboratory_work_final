/**
 * @file database.cpp
 * @brief Реализация методов класса Database.
 */
// ... реализация
#include "./../All_hpp_files/database.hpp"
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

// вспомогательная функция для вычисления евклидова расстояния между двумя точками
static double distance(const pair<int,int>& a, const pair<int,int>& b) {
	int dx = a.first - b.first;
	int dy = a.second - b.second;
	return sqrt(dx*dx + dy*dy);
}

// конструктор

DataBase::DataBase() : global_time(0) {}

// добавление объектов

void DataBase::addOrder(unsigned int id, unsigned int summary, int date_accepted, int date_delivered,
						const string &place, const string &storage_name, bool is_accepted, bool is_delivered,
						const pair<int,int> &place_coordinates) {
	// найти ID склада по имени (склады хранятся в storages)
	unsigned int storageId = 0;
	for (const auto &s : storages) {
		if (s.getName() == storage_name) {
			storageId = s.getId();
			break;
		}
	}

	Order new_order(id, summary, date_accepted, date_delivered, place, storage_name, is_accepted, is_delivered, place_coordinates);
	orders.push_back(new_order);

	// если склад найден, пытаемся сразу назначить заказ свободному курьеру
	if (storageId != 0) {
		assignOrderToFreeDeliver(orders.back(), storageId);
	} else {
		cout << "Предупреждение: склад \"" << storage_name << "\" не найден, заказ ID " << id << " не привязан к складу.\n";
	}
	cout << "Заказ ID:" << id << " добавлен в базу данных\n";
}

void DataBase::addDeliver(unsigned int id, unsigned int id_linked_storage, unsigned int speed,
						  const string &name, bool is_have_order, bool is_linked_with_storage) {
	Deliver new_deliver(id, id_linked_storage, speed, name, is_have_order, is_linked_with_storage);
	delivers.push_back(new_deliver);
	cout << "Курьер ID: " << id << " был создан\n";
}

void DataBase::addStorage(unsigned int id, const string &name, const pair<int, int> &coordinates,
						  const vector<unsigned int> &id_linked_delivers, bool is_active) {
	Storage new_storage(id, name, coordinates, id_linked_delivers, is_active);
	storages.push_back(new_storage);
	cout << "Склад ID: " << id << " был создан\n";
}


// удаление объектов

void DataBase::removeStorage(unsigned int id) {
	auto it = remove_if(storages.begin(), storages.end(),
		[id](const Storage &s) { return s.getId() == id; });
	if (it != storages.end()) {
		storages.erase(it, storages.end());
		// отвязать курьеров от этого склада
		for (auto &d : delivers) {
			if (d.getIdLinkedStorage() == id) {
				d.setIsLinkedWithStorage(false);
				d.setIdLinkedStorage(0);
				d.setState(CourierState::FREE);
				d.setIsHaveOrder(false);
			}
		}
		cout << "Склад ID " << id << " удалён.\n";
	} else {
		cout << "Склад с ID " << id << " не найден.\n";
	}
}

void DataBase::removeDeliver(unsigned int id) {
	auto it = remove_if(delivers.begin(), delivers.end(),
		[id](const Deliver &d) { return d.getId() == id; });
	if (it != delivers.end()) {
		delivers.erase(it, delivers.end());
		// удалить ID курьера из списков привязанных курьеров на складах
		for (auto &s : storages) {
			vector<unsigned int> newList;
			for (unsigned int did : s.getIdDelivers()) {
				if (did != id) newList.push_back(did);
			}
			s.setIdDelivers(newList);
		}
		cout << "Курьер ID " << id << " удалён.\n";
	} else {
		cout << "Курьер с ID " << id << " не найден.\n";
	}
}

void DataBase::removeOrder(unsigned int id) {
	auto it = remove_if(orders.begin(), orders.end(),
		[id](const Order &o) { return o.getId() == id; });
	if (it != orders.end()) {
		orders.erase(it, orders.end());
		cout << "Заказ ID " << id << " удалён.\n";
	} else {
		cout << "Заказ с ID " << id << " не найден.\n";
	}
}


// вывод информации

void DataBase::printAll() {
	cout << "\n========== БАЗА ДАННЫХ ==========\n";
	cout << "--- Склады ---\n";
	if (storages.empty()) cout << "Нет складов.\n";
	for (const auto &s : storages) {
		s.print();
	}
	cout << "--- Курьеры ---\n";
	if (delivers.empty()) cout << "Нет курьеров.\n";
	for (const auto &d : delivers) {
		d.print();
	}
	cout << "--- Заказы ---\n";
	if (orders.empty()) cout << "Нет заказов.\n";
	for (const auto &o : orders) {
		o.print();
	}
	cout << "Текущее время: " << global_time << " часов\n";
	cout << "=================================\n";
}

void DataBase::printStorageInfo(unsigned int storageId) {
	const Storage* st = nullptr;
	for (const auto &s : storages) {
		if (s.getId() == storageId) {
			st = &s;
			break;
		}
	}
	if (!st) {
		cout << "Склад с ID " << storageId << " не найден.\n";
		return;
	}
	st->print();
	cout << "Очередь заказов (ID): ";
	queue<unsigned int> q = st->getOrderQueue();
	if (q.empty()) {
		cout << "пуста\n";
	} else {
		while (!q.empty()) {
			cout << q.front() << " ";
			q.pop();
		}
		cout << "\n";
	}
}

void DataBase::printDeliversOnStorage(unsigned int storageId) {
	cout << "Курьеры на складе ID " << storageId << ":\n";
	bool found = false;
	for (const auto &d : delivers) {
		if (d.getIdLinkedStorage() == storageId) {
			found = true;
			d.print();
		}
	}
	if (!found) {
		cout << "Нет курьеров, привязанных к этому складу.\n";
	}
}

void DataBase::printOrderQueueOfStorage(unsigned int storageId) {
	for (const auto &s : storages) {
		if (s.getId() == storageId) {
			cout << "Очередь заказов склада \"" << s.getName() << "\" (ID): ";
			queue<unsigned int> q = s.getOrderQueue();
			if (q.empty()) {
				cout << "пуста\n";
			} else {
				while (!q.empty()) {
					cout << q.front() << " ";
					q.pop();
				}
				cout << "\n";
			}
			return;
		}
	}
	cout << "Склад с ID " << storageId << " не найден.\n";
}


// назначение заказa

bool DataBase::assignOrderToFreeDeliver(Order &order, unsigned int storageId) {
	// ищем склад
	Storage* targetStorage = nullptr;
	for (auto &s : storages) {
		if (s.getId() == storageId) {
			targetStorage = &s;
			break;
		}
	}
	if (!targetStorage) return false;

	// ищем свободного курьера, привязанного к складу
	for (auto &d : delivers) {
		if (d.getIdLinkedStorage() == storageId && d.getState() == CourierState::FREE && !d.getIsHaveOrder()) {
			// назначаем заказ
			d.setIsHaveOrder(true);
			d.setState(CourierState::GOING_TO_CUSTOMER);
			d.setTargetCoords(order.getPlaceCoordinates());
			double dist = distance(targetStorage->getCoordinates(), order.getPlaceCoordinates());
			d.setRemainingDistance(dist);
			order.setIdDeliver(d.getId());
			order.setIsAccepted(true);
			order.setDateAccepted(global_time);
			cout << "Заказ ID " << order.getId() << " назначен курьеру ID " << d.getId() << "\n";
			return true;
		}
	}
	// нет свободных курьеров – в очередь
	targetStorage->addToQueue(order.getId());
	cout << "Нет свободных курьеров, заказ ID " << order.getId() << " добавлен в очередь склада.\n";
	return false;
}


// Промотка времени

void DataBase::advanceTime(int hours) {
	if (hours <= 0) {
		cout << "Количество часов должно быть положительным.\n";
		return;
	}
	global_time += hours;
	cout << "Прокрутка времени на " << hours << " ч. Текущее время: " << global_time << " ч.\n";

	// перебираем всех курьеров
	for (auto &d : delivers) {
		if (d.getState() == CourierState::FREE) continue;

		double dist_covered = d.getSpeed() * hours;
		double remain = d.getRemainingDistance() - dist_covered;

		if (remain <= 0.0) {
			// достиг цели
			if (d.getState() == CourierState::GOING_TO_CUSTOMER) {
				// найти заказ, который вёз этот курьер, и отметить доставленным
				for (auto &order : orders) {
					if (order.getIdDeliver() == d.getId() && !order.getIsDelivered()) {
						order.setIsDelivered(true);
						order.setDateDelivered(global_time);
						cout << "Курьер ID " << d.getId() << " доставил заказ ID " << order.getId() << "\n";
						break;
					}
				}
				// начинаем возврат на склад
				Storage* st = nullptr;
				for (auto &s : storages) {
					if (s.getId() == d.getIdLinkedStorage()) {
						st = &s;
						break;
					}
				}
				if (st) {
					double dist_back = distance(d.getTargetCoords(), st->getCoordinates());
					d.setState(CourierState::RETURNING_TO_BASE);
					d.setRemainingDistance(dist_back);
					d.setTargetCoords(st->getCoordinates());
					cout << "Курьер ID " << d.getId() << " возвращается на склад, осталось " << dist_back << " ед.\n";
				} else {
					// склад не найден – курьер становится свободным
					d.setState(CourierState::FREE);
					d.setIsHaveOrder(false);
					d.setRemainingDistance(0);
				}
			}
			else if (d.getState() == CourierState::RETURNING_TO_BASE) {
				// вернулся на склад
				d.setState(CourierState::FREE);
				d.setIsHaveOrder(false);
				d.setRemainingDistance(0);
				cout << "Курьер ID " << d.getId() << " вернулся на склад и свободен.\n";
				// проверить очередь заказов на его складе
				for (auto &s : storages) {
					if (s.getId() == d.getIdLinkedStorage()) {
						if (!s.isQueueEmpty()) {
							unsigned int nextOrderId = s.popFromQueue();
							for (auto &order : orders) {
								if (order.getId() == nextOrderId) {
									assignOrderToFreeDeliver(order, s.getId());
									break;
								}
							}
						}
						break;
					}
				}
			}
		} else {
			// не доехал
			d.setRemainingDistance(remain);
		}
	}
}


// Сохранение и загрузка из файла


void DataBase::save_to_file(const string &filename) {
	ofstream out(filename);
	if (!out.is_open()) {
		cout << "Ошибка: не удалось открыть файл для сохранения.\n";
		return;
	}

	// сохраняем глобальное время
	out << "[GLOBAL_TIME]\n" << global_time << "\n";

	// сохраняем склады
	out << "[STORAGES]\n" << storages.size() << "\n";
	for (const auto &s : storages) {
		out << s.getId() << " " << s.getName() << " "
			<< s.getCoordinates().first << " " << s.getCoordinates().second << " " << s.getIsActive() << "\n";
		// сохраняем список привязанных курьеров
		const auto &del_ids = s.getIdDelivers();
		out << del_ids.size() << " ";
		for (auto did : del_ids) out << did << " ";
		out << "\n";
		// сохраняем очередь заказов (временно копируем, чтобы не разрушить)
		queue<unsigned int> q = s.getOrderQueue();
		out << q.size() << " ";
		while (!q.empty()) {
			out << q.front() << " ";
			q.pop();
		}
		out << "\n";
	}

	// сохраняем курьеров
	out << "[DELIVERS]\n" << delivers.size() << "\n";
	for (const auto &d : delivers) {
		out << d.getId() << " " << d.getIdLinkedStorage() << " " << d.getSpeed() << " " << d.getName() << " "
			<< d.getIsHaveOrder() << " " << d.getIsLinkedWithStorage() << " "
			<< static_cast<int>(d.getState()) << " " << d.getRemainingDistance() << " "
			<< d.getTargetCoords().first << " " << d.getTargetCoords().second << "\n";
	}

	// сохраняем заказы
	out << "[ORDERS]\n" << orders.size() << "\n";
	for (const auto &o : orders) {
		out << o.getId() << " " << o.getIdDeliver() << " " << o.getSummary() << " "
			<< o.getDateAccepted() << " " << o.getDateDelivered() << " "
			<< o.getPlace() << " " << o.getStorage() << " "
			<< o.getIsAccepted() << " " << o.getIsDelivered() << " "
			<< o.getPlaceCoordinates().first << " " << o.getPlaceCoordinates().second << "\n";
	}

	out.close();
	cout << "База данных сохранена в файл \"" << filename << "\"\n";
}

void DataBase::load_from_file(const string &filename) {
	ifstream in(filename);
	if (!in.is_open()) {
		cout << "Ошибка: не удалось открыть файл для загрузки.\n";
		return;
	}

	// очищаем текущие данные
	storages.clear();
	delivers.clear();
	orders.clear();

	string section;
	while (in >> section) {
		if (section == "[GLOBAL_TIME]") {
			in >> global_time;
		}
		else if (section == "[STORAGES]") {
			size_t count;
			in >> count;
			for (size_t i = 0; i < count; ++i) {
				unsigned int id; string name; int x, y; bool is_active;
				in >> id >> name >> x >> y >> is_active;
				size_t del_count;
				in >> del_count;
				vector<unsigned int> linked_delivers(del_count);
				for (size_t j = 0; j < del_count; ++j) {
					in >> linked_delivers[j];
				}
				size_t qsize;
				in >> qsize;
				queue<unsigned int> q;
				for (size_t j = 0; j < qsize; ++j) {
					unsigned int oid; in >> oid;
					q.push(oid);
				}
				Storage new_storage(id, name, {x, y}, linked_delivers, is_active);
				new_storage.setOrderQueue(q);
				storages.push_back(new_storage);
			}
		}
		else if (section == "[DELIVERS]") {
			size_t count;
			in >> count;
			for (size_t i = 0; i < count; ++i) {
				unsigned int id, id_linked, speed; string name;
				bool have_order, linked_storage;
				int state_int;
				double rem_dist;
				int tx, ty;
				in >> id >> id_linked >> speed >> name >> have_order >> linked_storage
				   >> state_int >> rem_dist >> tx >> ty;
				Deliver d(id, id_linked, speed, name, have_order, linked_storage);
				d.setState(static_cast<CourierState>(state_int));
				d.setRemainingDistance(rem_dist);
				d.setTargetCoords({tx, ty});
				delivers.push_back(d);
			}
		}
		else if (section == "[ORDERS]") {
			size_t count;
			in >> count;
			for (size_t i = 0; i < count; ++i) {
				unsigned int id, id_deliver, summary;
				int date_accepted, date_delivered;
				string place, storage_name;
				bool is_accepted, is_delivered;
				int px, py;
				in >> id >> id_deliver >> summary >> date_accepted >> date_delivered
				   >> place >> storage_name >> is_accepted >> is_delivered >> px >> py;
				Order o(id, summary, date_accepted, date_delivered, place, storage_name, is_accepted, is_delivered, {px, py});
				o.setIdDeliver(id_deliver);
				orders.push_back(o);
			}
		}
	}

	in.close();
	cout << "База данных загружена из файла \"" << filename << "\"\n";
}
