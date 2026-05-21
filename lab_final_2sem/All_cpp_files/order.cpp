#include "../All_hpp_files/order.hpp"
// здесь реализация классов/класса


// конструкторы
Order::Order(unsigned int id, const string& name, const pair<int, int>& addr,
    unsigned int storage_id)
    : id(id), customer_name(name), place(""), storage_id(storage_id),
    delivery_address(addr), is_completed(false), is_active(false),
    assigned_deliver_id(0), distance_from_storage(0), estimated_time(0) {
    // Расстояние пока 0, будет вычислено при назначении
}

unsigned int Order::getId() const { return id; }
string Order::getCustomerName() const { return customer_name; }
pair<int, int> Order::getDeliveryAddress() const { return delivery_address; }
unsigned int Order::getStorageId() const { return storage_id; }
bool Order::getIsCompleted() const { return is_completed; }
bool Order::getIsActive() const { return is_active; }
unsigned int Order::getAssignedDeliverId() const { return assigned_deliver_id; }
double Order::getDistance() const { return distance_from_storage; }
double Order::getEstimatedTime() const { return estimated_time; }

void Order::setIsCompleted(bool completed) { is_completed = completed; }
void Order::setIsActive(bool active) { is_active = active; }
void Order::setAssignedDeliverId(unsigned int deliver_id) { assigned_deliver_id = deliver_id; }
void Order::setDistance(double dist) { distance_from_storage = dist; }
void Order::setEstimatedTime(double time) { estimated_time = time; }

double Order::calculateDistanceTo(const pair<int, int>& point) const {
    double dx = delivery_address.first - point.first;
    double dy = delivery_address.second - point.second;
    return sqrt(dx * dx + dy * dy);
}

void Order::print() const {
    cout << "Заказ ID: " << id << "\n";
    cout << "Клиент: " << customer_name << "\n";
    cout << "Адрес: (" << delivery_address.first << ", " << delivery_address.second << ")\n";
    cout << "Склад ID: " << storage_id << "\n";
    cout << "Расстояние до склада: " << distance_from_storage << "\n";
    cout << "Статус: " << (is_completed ? "Выполнен" : (is_active ? "В обработке" : "В очереди")) << "\n";
    if (is_active) {
        cout << "Курьер ID: " << assigned_deliver_id << "\n";
    }
    cout << "--------------------------\n";
}
