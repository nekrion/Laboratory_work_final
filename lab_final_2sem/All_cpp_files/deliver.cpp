#include "../All_hpp_files/deliver.hpp"
// здесь реализация классов/класса


// конструкторы
Deliver::Deliver(unsigned int id, const string& name, const pair<int, int>& coords,
    unsigned int storage_id, double sp)
    : id(id), name(name), coordinates(coords), storage_id(storage_id),
    is_free(true), is_on_delivery(false), current_order_id(0),
    speed(sp), position({ coords.first, coords.second }),
    remaining_distance(0), target_point(coords), time_to_target(0) {}

// геттеры
unsigned int Deliver::getId() const { return id; }
string Deliver::getName() const { return name; }
pair<int, int> Deliver::getCoordinates() const { return coordinates; }
unsigned int Deliver::getStorageId() const { return storage_id; }
bool Deliver::getIsFree() const { return is_free; }
bool Deliver::getIsOnDelivery() const { return is_on_delivery; }
unsigned int Deliver::getCurrentOrderId() const { return current_order_id; }
double Deliver::getSpeed() const { return speed; }
pair<double, double> Deliver::getPosition() const { return position; }
double Deliver::getRemainingDistance() const { return remaining_distance; }

// сеттеры
void Deliver::setIsFree(bool free) { is_free = free; }
void Deliver::setCoordinates(const pair<int, int>& coords) { coordinates = coords; }
void Deliver::setPosition(const pair<double, double>& pos) { position = pos; }
void Deliver::setRemainingDistance(double dist) { remaining_distance = dist; }

// метод начала доставки
void Deliver::startDelivery(unsigned int order_id, const pair<int, int>& destination) {
    current_order_id = order_id;
    is_on_delivery = true;
    is_free = false;
    target_point = destination;

    // вычисляем расстояние до цели (Евклидово)
    double dx = destination.first - position.first;
    double dy = destination.second - position.second;
    remaining_distance = sqrt(dx * dx + dy * dy);
    time_to_target = remaining_distance / speed;
}

// обновление позиции за прошедшее время
void Deliver::updatePosition(double hours) {
    if (!is_on_delivery) return;

    // сколько можем проехать за это время
    double max_distance = speed * hours;

    if (max_distance >= remaining_distance) {
        // доехали до цели
        position = { static_cast<double>(target_point.first), static_cast<double>(target_point.second) };
        remaining_distance = 0;
        time_to_target = 0;
        completeDelivery();
    }
    else {
        // движемся
        double fraction = max_distance / remaining_distance;
        double dx = target_point.first - position.first;
        double dy = target_point.second - position.second;
        position.first += dx * fraction;
        position.second += dy * fraction;
        remaining_distance -= max_distance;
        time_to_target -= hours;
    }
}

bool Deliver::isDeliveryComplete() const {
    return is_on_delivery && remaining_distance <= 0.01;
}

void Deliver::completeDelivery() {
    is_on_delivery = false;
    is_free = true;
    current_order_id = 0;
    // обновляем координаты склада на текущую позицию
    coordinates = { static_cast<int>(position.first), static_cast<int>(position.second) };
}

void Deliver::print() const {
    cout << "Курьер ID: " << id << "\n";
    cout << "Имя: " << name << "\n";
    cout << "Позиция: (" << position.first << ", " << position.second << ")\n";
    cout << "Скорость: " << speed << " ед/час\n";
    cout << "Статус: " << (is_on_delivery ? "В доставке" : (is_free ? "Свободен" : "Занят")) << "\n";
    if (is_on_delivery) {
        cout << "Текущий заказ ID: " << current_order_id << "\n";
        cout << "Осталось расстояния: " << remaining_distance << "\n";
        cout << "Примерное время: " << time_to_target << " часов\n";
    }
    cout << "--------------------------\n";
}
