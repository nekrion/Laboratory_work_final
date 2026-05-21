#include "../All_hpp_files/database.hpp"
// здесь реализация класса

void DataBase::addOrder(unsigned int id, unsigned int summary, int date_accepted, int date_delivered, 
                        const string &place, const string &storage, bool is_accepted, bool is_delivered, const pair<int, int> &place_coordinates) {
    
    Order new_order(id, summary, date_accepted, date_delivered, place, storage, is_accepted, is_delivered, place_coordinates);
    orders.push_back(new_order);
    
    cout << "Заказ ID:" << id << " добавлен в базу данных\n";
}

void DataBase::addDeliver(unsigned int id, unsigned int id_linked_storage, unsigned int speed, const string &name,
        bool is_have_order, bool is_linked_with_storage) {

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

//work with files

void DataBase::save_to_file(string &str) {
    ofstream out(str);
    if (!out.is_open()) {
        cout << "!    ERROR      !\n";
        return;
    }


    out << "[STORAGES]\n" << storages.size() << "\n";
    for (const auto &s : storages) {
        out << s.getId() << " " << s.getName() << " " 
            << s.getCoordinates().first << " " << s.getCoordinates().second << " " << s.getIsActive() << "\n";

        out << s.getIdDelivers().size() << " ";

        for (auto d_id : s.getIdDelivers()) {
            out << d_id << " ";
        }
        out << "\n";

    }

    out << "[DELIVERS]\n" << delivers.size() << "\n";
    for (const auto &d : delivers) {
        out << d.getId() << " " << d.getIdLinkedStorage() << " " << d.getSpeed() << " " << d.getName() << " " 
            << d.getIsHaveOrder() << " " << d.getIsLinkedWithStorage() << "\n";
    }

    out << "[ORDERS]\n" << orders.size() << "\n";
    for (const auto &o : orders) {
        out << o.getId() << " " << o.getIdDeliver() << " " << o.getSummary() << " " << o.getDateAccepted() << " " 
        << o.getDateDelivered() << " " << o.getPlace() << " " << o.getStorage() << " " << o.getIsAccepted() << " " 
        << o.getIsDelivered() << " " << o.getPlaceCoordinates().first << " " << o.getPlaceCoordinates().second << "\n";
    }

    out.close();
    cout << "БД сохранена\n";
}


void DataBase::load_from_file(string &str) {
    ifstream in(str);
    if (!in.is_open()) {
        cout << "!    ERROR      !\n";
        return;
    }

    storages.clear();
    delivers.clear();
    orders.clear();

    string section;
    while (in >> section) {
        if (section == "[STORAGES]") {
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
                storages.push_back(Storage(id, name, {x, y}, linked_delivers, is_active));
            }
        } 
        else if (section == "[DELIVERS]") {
            size_t count;
            in >> count;
            for (size_t i = 0; i < count; ++i) {
                unsigned int id, id_linked_storage, speed; string name; bool is_have_order, is_linked_with_storage;
                in >> id >> id_linked_storage >> speed >> name >> is_have_order >> is_linked_with_storage;
                delivers.push_back(Deliver(id, id_linked_storage, speed, name, is_have_order, is_linked_with_storage));
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
                pair<int, int> place_coordinates;
                in >> id >> id_deliver >> summary >> date_accepted >> date_delivered 
                >> place >> storage_name >> is_accepted >> is_delivered >> place_coordinates.first >> place_coordinates.second;
                
                Order loaded_order(id, summary, date_accepted, date_delivered, place, storage_name, is_accepted, is_delivered, place_coordinates);
                loaded_order.setIdDeliver(id_deliver);
                orders.push_back(loaded_order);
            }
        }
    }

    in.close();
    cout << "БД загружена из файла\n";
}