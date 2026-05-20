#include <windows.h>
#include "database.hpp"
#include "deliver.hpp"
#include "order.hpp"
#include "storage.hpp"

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
    system("cls");
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
    cout << "||===========================================================||\n";
}


int main() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // здесь реализация менюшки
    // ну и еще заполнение
    // также какое-то тестовое заполнение для теста функций можно

    LoadTerminal(); // запуск терминала
    
    ShowTerminal(); // показывает стандартное окно терминала


    queue<Order> all_orders; // очередь заказов
    int k;
    int time = 0;

    if (!(cin >> k)) {
        cout << "!      Input_Error      !\n";
        cout << "Brake up";
        cin.clear();
        cin.ignore(10000, '\n');
        return 1;

    } else {
        while (k != 0) {
            switch(k) {
                case 0: {
                    cout << "Спасибо за пользование терминалом!\n";
                    break;
                }
                case 1: {
                    
                }
            }
        }
        
    }


    return 0;
}