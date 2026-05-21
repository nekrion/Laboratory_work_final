#include <windows.h>
#include "database.hpp"
#include "deliver.hpp"
#include "order.hpp"
#include "storage.hpp"
#include "manager.hpp"
#include <queue>
#include <cmath>

void LoadTerminal() {
    cout << "Запуск терминала";
    this_thread::sleep_for(chrono::seconds(1));
    cout << "\nТерминал запущен\n";
    this_thread::sleep_for(chrono::seconds(1));
    system("cls");
}

void ShowTerminal() {
    cout << "||===========================================================||\n";
    cout << "Вас приветствует служба доставки Delivery Co.\n";
    cout << "Вы находитесь в терминале №1 компании по доставке Delivery Co.\n";
    cout << "Для взаимодействия с меню Вы можете использовать следующие команды:\n";
    cout << "0 - Выход из терминала\n";
    cout << "1 - Вывод БД на экран\n";
    cout << "2 - Добавить тестовый заказ\n";
    cout << "3 - Назначить заказы (вручную)\n";
    cout << "4 - Перемотка времени\n";
    cout << "5 - Показать статус курьеров\n";
    cout << "6 - Показать очередь заказов\n";
    cout << "||===========================================================||\n";
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    LoadTerminal();

    Database db;
    DeliveryManager manager(db);

    // первое назначение заказов
    manager.assignOrders();

    int choice;
    while (true) {
        ShowTerminal();
        cout << "\nТекущее время: " << static_cast<int>(manager.getCurrentTime()) << " часов\n";
        cout << "Ваш выбор: ";

        if (!(cin >> choice)) {
            cout << "Ошибка ввода!\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
        case 0:
            cout << "Спасибо за пользование терминалом!\n";
            return 0;

        case 1:
            db.printAll();
            break;

        case 2: {
            static int test_id = 200;
            string name;
            int x, y;
            cout << "Имя клиента: ";
            cin >> name;
            cout << "Координата X: ";
            cin >> x;
            cout << "Координата Y: ";
            cin >> y;
            cout << "ID склада: ";
            int storage_id;
            cin >> storage_id;

            Order new_order(test_id++, name, { x, y }, storage_id);
            manager.addOrderToQueue(new_order);
            break;
        }

        case 3:
            manager.assignOrders();
            break;

        case 4: {
            int hours;
            cout << "На сколько часов перемотать время? ";
            cin >> hours;
            manager.fastForward(hours);
            break;
        }

        case 5:
            manager.printDeliverStatus();
            break;

        case 6:
            manager.printOrderQueue();
            break;

        default:
            cout << "Неверная команда!\n";
        }

        cout << "\nНажмите Enter для продолжения...";
        cin.ignore();
        cin.get();
        system("cls");
    }

    return 0;
}
