// #include <windows.h>
#include <thread>
#include <chrono>
#include <limits>
#include "database.hpp"
#include "deliver.hpp"
#include "order.hpp"
#include "storage.hpp"

using namespace std;

void LoadTerminal() {
	cout << "Запуск терминала";
	this_thread::sleep_for(chrono::seconds(3));
	for (int i = 0; i < 3; i++) {
		cout << "." << flush;
		this_thread::sleep_for(chrono::seconds(1));
	}

	for (int i = 0; i <= 100; i += 10) {
		cout << "\rLoading: [";
		int progress = i / 10;

		for (int j = 0; j < 10; ++j) {
			if (j < progress) {
				cout << "#";
			} else {
				cout << " ";
			}
		}

		cout << "] " << i << "%" << flush;

		if(i <= 50) {
			this_thread::sleep_for(chrono::milliseconds(150));
		} else {
			this_thread::sleep_for(chrono::milliseconds(500));
		}
	}

	cout << "\nТерминал запущен\n";
	this_thread::sleep_for(chrono::seconds(2));
	cout << "\033[2J\033[1;1H"; // очистка экрана
//	system("cls");
}

void ShowTerminal() {
	cout << "||===========================================================||\n";
	cout << "Вас приветствует служба доставки Delivery Co.\n";
	cout << "Вы находитесь в терминале №1 компании по доставке Delivery Co.\n";
	cout << "Для взаимодействия с меню Вы можете использовать следующие команды:\n";
	cout << "0 - Выход из терминала\n";
	cout << "1 - Вывод БД на экран\n";
	cout << "2 - Удаление элемента из БД\n";
	cout << "3 - Сохранение БД в файл\n";
	cout << "4 - Загрузка из файла\n";
	cout << "5 - Перемотка времени\n";
	cout << "6 - Добавить склад\n";
	cout << "7 - Добавить курьера\n";
	cout << "8 - Добавить заказ\n";
	cout << "9 - Просмотр курьеров на складе\n";
	cout << "10 - Просмотр очереди заказов склада\n";
	cout << "||===========================================================||\n";
}

// (опционально) функция для тестового заполнения
void fillTestData(DataBase &db) {
	// добавляем склад
	db.addStorage(1, "Склад Южный", {0, 0}, {}, true);
	// добавляем курьера на склад
	db.addDeliver(101, 1, 10, "Иван", false, true);
	// привязываем курьера к складу
	for (auto &s : db.getStorages()) {
		if (s.getId() == 1) s.link_deliver(101);
	}
	// добавляем заказ
	db.addOrder(1001, 500, 0, 0, "ул. Ленина, 5", "Склад Южный", false, false, {10, 10});
}

int main() {
	// SetConsoleCP(65001); братва я на линуксе, не обессудьте
	// SetConsoleOutputCP(65001);

	DataBase db;
	// fillTestData(db); // раскомментировать для тестового заполнения

	LoadTerminal(); // запуск терминала

	int choice;
	do {
		ShowTerminal(); // показывает стандартное окно терминала
		cout << "Введите команду: ";

		if (!(cin >> choice)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Ошибка ввода. Введите число.\n";
			continue;
		}

		switch (choice) {
			case 0: {
				cout << "Спасибо за пользование терминалом!\n";
				break;
			}
			case 1: {
				db.printAll();
				break;
			}
			case 2: {
				int type, id;
				cout << "Что удалить? (1 - склад, 2 - курьер, 3 - заказ): ";
				cin >> type;
				cout << "Введите ID: ";
				cin >> id;
				if (type == 1) db.removeStorage(id);
				else if (type == 2) db.removeDeliver(id);
				else if (type == 3) db.removeOrder(id);
				else cout << "Неверный тип.\n";
				break;
			}
			case 3: {
				string filename;
				cout << "Введите имя файла для сохранения: ";
				cin >> filename;
				db.save_to_file(filename);
				break;
			}
			case 4: {
				string filename;
				cout << "Введите имя файла для загрузки: ";
				cin >> filename;
				db.load_from_file(filename);
				break;
			}
			case 5: {
				int hours;
				cout << "На сколько часов прокрутить время? ";
				cin >> hours;
				db.advanceTime(hours);
				break;
			}
			case 6: {
				unsigned int id;
				string name;
				int x, y;
				bool active;
				cout << "ID склада: "; cin >> id;
				cout << "Название: "; cin >> name;
				cout << "Координаты (x y): "; cin >> x >> y;
				cout << "Активен (1 - да, 0 - нет): "; cin >> active;
				db.addStorage(id, name, {x, y}, {}, active);
				break;
			}
			case 7: {
				unsigned int id, storageId, speed;
				string name;
				cout << "ID курьера: "; cin >> id;
				cout << "ID склада, к которому привязать: "; cin >> storageId;
				cout << "Скорость (ед/час): "; cin >> speed;
				cout << "Имя курьера: "; cin >> name;
				db.addDeliver(id, storageId, speed, name, false, true);
				// привязываем к складу
				for (auto &s : db.getStorages()) {
					if (s.getId() == storageId) {
						s.link_deliver(id);
						break;
					}
				}
				break;
			}
			case 8: {
				unsigned int id, summary;
				string place, storageName;
				int x, y;
				cout << "ID заказа: "; cin >> id;
				cout << "Сумма: "; cin >> summary;
				cout << "Название склада (откуда): "; cin >> storageName;
				cout << "Адрес доставки: "; cin >> place;
				cout << "Координаты доставки (x y): "; cin >> x >> y;
				db.addOrder(id, summary, 0, 0, place, storageName, false, false, {x, y});
				break;
			}
			case 9: {
				unsigned int storageId;
				cout << "ID склада: "; cin >> storageId;
				db.printDeliversOnStorage(storageId);
				break;
			}
			case 10: {
				unsigned int storageId;
				cout << "ID склада: "; cin >> storageId;
				db.printOrderQueueOfStorage(storageId);
				break;
			}
			default: {
				cout << "Неизвестная команда. Попробуйте снова.\n";
				break;
			}
		}

		if (choice != 0) {
			cout << "\nНажмите Enter, чтобы продолжить...";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get();
			cout << "\033[2J\033[1;1H"; // очистка
//			system("cls");
		}
	} while (choice != 0);

	return 0;
}
