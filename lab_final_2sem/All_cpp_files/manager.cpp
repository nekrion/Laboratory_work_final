#include "../All_hpp_files/manager.hpp"


// конструктор
DeliveryManager::DeliveryManager(Database& database)
    : db(database), current_time(0.0) {}

// добавление заказа в очередь
void DeliveryManager::addOrderToQueue(const Order& order) {
    order_queue.push(order);
    db.addOrder(order);
    cout << "Заказ #" << order.getId() << " добавлен в очередь!\n";
}

// назначение заказов свободным курьерам
void DeliveryManager::assignOrders() {
    vector<Deliver*> free_delivers;

    // собираем всех свободных курьеров
    for (auto& deliver : db.getDelivers()) {
        if (deliver.getIsFree() && !deliver.getIsOnDelivery()) {
            free_delivers.push_back(&deliver);
        }
    }

    // назначаем заказы из очереди
    while (!order_queue.empty() && !free_delivers.empty()) {
        Order order = order_queue.front();
        order_queue.pop();

        // находим склад, от которого будет доставка
        Storage* storage = db.findStorage(order.getStorageId());
        if (!storage) continue;

        // вычисляем расстояние от склада до клиента
        pair<int, int> storage_coords = storage->getCoordinates();
        double distance = order.calculateDistanceTo(storage_coords);
        order.setDistance(distance);

        // ищем ближайшего свободного курьера у этого склада
        Deliver* best_deliver = nullptr;
        double min_distance = 1e9;

        for (auto* deliver : free_delivers) {
            if (deliver->getStorageId() == order.getStorageId()) {
                pair<double, double> deliver_pos = deliver->getPosition();
                double dx = deliver_pos.first - storage_coords.first;
                double dy = deliver_pos.second - storage_coords.second;
                double dist = sqrt(dx * dx + dy * dy);
                if (dist < min_distance) {
                    min_distance = dist;
                    best_deliver = deliver;
                }
            }
        }

        if (best_deliver) {
            // назначаем заказ курьеру
            order.setIsActive(true);
            order.setAssignedDeliverId(best_deliver->getId());
            order.setEstimatedTime(distance / best_deliver->getSpeed());

            // обновляем заказ в БД
            for (auto& o : db.getOrders()) {
                if (o.getId() == order.getId()) {
                    o = order;
                    break;
                }
            }

            // отправляем курьера
            best_deliver->startDelivery(order.getId(), order.getDeliveryAddress());

            // удаляем из списка свободных
            free_delivers.erase(remove(free_delivers.begin(), free_delivers.end(), best_deliver),
                free_delivers.end());

            cout << "[Время " << static_cast<int>(current_time) << "] Заказ #" << order.getId()
                << " назначен курьеру " << best_deliver->getName() << "\n";
        }
        else {
            // если нет подходящего курьера, возвращаем заказ в очередь
            order_queue.push(order);
            break;
        }
    }
}

// перемотка времени
void DeliveryManager::fastForward(int hours) {
    cout << "\n=== ПЕРЕМОТКА ВРЕМЕНИ НА " << hours << " ЧАСОВ ===\n";

    // разбиваем на маленькие шаги для плавного обновления
    const double STEP_HOURS = 0.1;
    double remaining = hours;

    while (remaining > 0) {
        double step = min(STEP_HOURS, remaining);

        // обновляем позиции всех курьеров
        for (auto& deliver : db.getDelivers()) {
            if (deliver.getIsOnDelivery()) {
                deliver.updatePosition(step);

                // проверяем, не завершена ли доставка
                if (deliver.isDeliveryComplete()) {
                    // находим заказ и отмечаем его выполненным
                    unsigned int order_id = deliver.getCurrentOrderId();
                    Order* order = db.findOrder(order_id);
                    if (order) {
                        order->setIsCompleted(true);
                        order->setIsActive(false);
                        cout << "[Время " << current_time + step << "] Курьер " << deliver.getName()
                            << " завершил доставку заказа #" << order_id << "\n";
                    }
                    deliver.completeDelivery();
                }
            }
        }

        remaining -= step;
        current_time += step;
    }

    // округляем время для отображения
    int rounded_time = static_cast<int>(current_time);
    cout << "Текущее время: " << rounded_time << " часов\n";

    // назначаем новые заказы
    assignOrders();
}

// геттеры
queue<Order>& DeliveryManager::getOrderQueue() {
    return order_queue;
}

double DeliveryManager::getCurrentTime() const {
    return current_time;
}

void DeliveryManager::setCurrentTime(double time) {
    current_time = time;
}

// вывод статуса курьеров
void DeliveryManager::printDeliverStatus() const {
    cout << "\n=== СТАТУС КУРЬЕРОВ ===\n";
    for (auto& d : db.getDelivers()) {
        d.print();
    }
}

// вывод очереди заказов
void DeliveryManager::printOrderQueue() const {
    cout << "\n=== ОЧЕРЕДЬ ЗАКАЗОВ ===\n";
    if (order_queue.empty()) {
        cout << "Очередь пуста\n";
    }
    else {
        queue<Order> temp = order_queue;
        int pos = 1;
        while (!temp.empty()) {
            Order o = temp.front();
            temp.pop();
            cout << pos++ << ". Заказ #" << o.getId()
                << " (клиент: " << o.getCustomerName() << ")\n";
        }
    }
}
