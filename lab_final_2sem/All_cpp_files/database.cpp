#include "../All_hpp_files/database.hpp"
// здесь реализация класса

// Конструктор
Database::Database() : next_order_id(1) {}

// Добавление склада
void Database::addStorage(const Storage& s) {
    storages.push_back(s);
}

// Добавление курьера
void Database::addDeliver(const Deliver& d) {
    delivers.push_back(d);
}

// Добавление заказа
void Database::addOrder(const Order& o) {
    orders.push_back(o);
    if (o.getId() >= static_cast<unsigned int>(next_order_id)) {
        next_order_id = o.getId() + 1;
    }
}

// Удаление склада по ID
bool Database::removeStorage(unsigned int id) {
    auto it = remove_if(storages.begin(), storages.end(),
        [id](const Storage& s) { return s.getId() == id; });
    if (it != storages.end()) {
        storages.erase(it, storages.end());
        return true;
    }
    return false;
}

// Удаление курьера по ID
bool Database::removeDeliver(unsigned int id) {
    auto it = remove_if(delivers.begin(), delivers.end(),
        [id](const Deliver& d) { return d.getId() == id; });
    if (it != delivers.end()) {
        delivers.erase(it, delivers.end());
        return true;
    }
    return false;
}

// Удаление заказа по ID
bool Database::removeOrder(unsigned int id) {
    auto it = remove_if(orders.begin(), orders.end(),
        [id](const Order& o) { return o.getId() == id; });
    if (it != orders.end()) {
        orders.erase(it, orders.end());
        return true;
    }
    return false;
}

// Поиск склада по ID
Storage* Database::findStorage(unsigned int id) {
    for (auto& storage : storages) {
        if (storage.getId() == id) {
            return &storage;
        }
    }
    return nullptr;
}

// Поиск курьера по ID
Deliver* Database::findDeliver(unsigned int id) {
    for (auto& deliver : delivers) {
        if (deliver.getId() == id) {
            return &deliver;
        }
    }
    return nullptr;
}

// Поиск заказа по ID
Order* Database::findOrder(unsigned int id) {
    for (auto& order : orders) {
        if (order.getId() == id) {
            return &order;
        }
    }
    return nullptr;
}

// Поиск свободных курьеров по ID склада
vector<Deliver*> Database::findFreeDeliversByStorage(unsigned int storage_id) {
    vector<Deliver*> free_delivers;
    for (auto& deliver : delivers) {
        if (deliver.getStorageId() == storage_id &&
            deliver.getIsFree() &&
            !deliver.getIsOnDelivery()) {
            free_delivers.push_back(&deliver);
        }
    }
    return free_delivers;
}

// Получение всех складов
vector<Storage>& Database::getStorages() {
    return storages;
}

// Получение всех курьеров
vector<Deliver>& Database::getDelivers() {
    return delivers;
}

// Получение всех заказов
vector<Order>& Database::getOrders() {
    return orders;
}

// Сохранение в файл
void Database::saveToFile(const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Ошибка открытия файла для сохранения!\n";
        return;
    }

    // Сохраняем склады
    file << "STORAGES\n";
    for (const auto& s : storages) {
        file << s.getId() << "|" << s.getName() << "|"
            << s.getCoordinates().first << "," << s.getCoordinates().second << "|";
        for (auto id : s.getIdDelivers()) {
            file << id << ",";
        }
        file << "|" << s.getIsActive() << "\n";
    }

    // Сохраняем курьеров
    file << "DELIVERS\n";
    for (const auto& d : delivers) {
        file << d.getId() << "|" << d.getName() << "|"
            << d.getCoordinates().first << "," << d.getCoordinates().second << "|"
            << d.getStorageId() << "|" << d.getIsFree() << "\n";
    }

    // Сохраняем заказы
    file << "ORDERS\n";
    for (const auto& o : orders) {
        file << o.getId() << "|" << o.getCustomerName() << "|"
            << o.getDeliveryAddress().first << "," << o.getDeliveryAddress().second << "|"
            << o.getStorageId() << "|" << o.getIsCompleted() << "\n";
    }

    file.close();
    cout << "Данные сохранены в файл: " << filename << "\n";
}

// Загрузка из файла
void Database::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Файл не найден: " << filename << "\n";
        return;
    }

    // Очищаем текущие данные
    storages.clear();
    delivers.clear();
    orders.clear();

    string line;
    string section;
    unsigned int max_id = 0;

    while (getline(file, line)) {
        if (line == "STORAGES") {
            section = "STORAGES";
            continue;
        }
        else if (line == "DELIVERS") {
            section = "DELIVERS";
            continue;
        }
        else if (line == "ORDERS") {
            section = "ORDERS";
            continue;
        }

        if (line.empty()) continue;

        stringstream ss(line);
        string token;
        vector<string> parts;

        while (getline(ss, token, '|')) {
            parts.push_back(token);
        }

        if (section == "STORAGES" && parts.size() >= 5) {
            unsigned int id = stoul(parts[0]);
            string name = parts[1];

            // Парсим координаты
            stringstream coord_ss(parts[2]);
            string coord_x, coord_y;
            getline(coord_ss, coord_x, ',');
            getline(coord_ss, coord_y, ',');
            pair<int, int> coords(stoi(coord_x), stoi(coord_y));

            // Парсим ID курьеров
            vector<unsigned int> deliver_ids;
            stringstream deliver_ss(parts[3]);
            string deliver_id;
            while (getline(deliver_ss, deliver_id, ',')) {
                if (!deliver_id.empty()) {
                    deliver_ids.push_back(stoul(deliver_id));
                }
            }

            bool is_active = (parts[4] == "1");

            storages.push_back(Storage(id, name, coords, deliver_ids, is_active));
            if (id > max_id) max_id = id;

        }
        else if (section == "DELIVERS" && parts.size() >= 5) {
            unsigned int id = stoul(parts[0]);
            string name = parts[1];

            stringstream coord_ss(parts[2]);
            string coord_x, coord_y;
            getline(coord_ss, coord_x, ',');
            getline(coord_ss, coord_y, ',');
            pair<int, int> coords(stoi(coord_x), stoi(coord_y));

            unsigned int storage_id = stoul(parts[3]);
            bool is_free = (parts[4] == "1");

            Deliver d(id, name, coords, storage_id);
            d.setIsFree(is_free);
            delivers.push_back(d);
            if (id > max_id) max_id = id;

        }
        else if (section == "ORDERS" && parts.size() >= 5) {
            unsigned int id = stoul(parts[0]);
            string customer_name = parts[1];

            stringstream coord_ss(parts[2]);
            string coord_x, coord_y;
            getline(coord_ss, coord_x, ',');
            getline(coord_ss, coord_y, ',');
            pair<int, int> address(stoi(coord_x), stoi(coord_y));

            unsigned int storage_id = stoul(parts[3]);
            bool is_completed = (parts[4] == "1");

            Order o(id, customer_name, address, storage_id);
            o.setIsCompleted(is_completed);
            orders.push_back(o);
            if (id > max_id) max_id = id;
        }
    }

    next_order_id = max_id + 1;
    file.close();
    cout << "Данные загружены из файла: " << filename << "\n";
}

// Вывод всей БД на экран
void Database::printAll() const {
    cout << "\n========== БАЗА ДАННЫХ ==========\n";

    cout << "\n--- Склады ---\n";
    if (storages.empty()) {
        cout << "Нет складов\n";
    }
    else {
        for (const auto& s : storages) {
            s.print();
        }
    }

    cout << "\n--- Курьеры ---\n";
    if (delivers.empty()) {
        cout << "Нет курьеров\n";
    }
    else {
        for (const auto& d : delivers) {
            d.print();
        }
    }

    cout << "\n--- Заказы ---\n";
    if (orders.empty()) {
        cout << "Нет заказов\n";
    }
    else {
        for (const auto& o : orders) {
            o.print();
        }
    }

    cout << "================================\n";
}

// Получение следующего ID для заказа
int Database::getNextOrderId() {
    return next_order_id++;
}
