/**
 * @file storage.hpp
 * @brief Определение класса Storage (склад).
 * @authors Грачев Никита, Салтысюк Анастасия, Павлюченков Артем, Пропажин Антон, Луконин Валерий.
 * @date 2026
 */

#pragma once
#include <bits/stdc++.h>
#include <queue>
#include "deliver.hpp"

using namespace std;

/**
 * @brief Класс, представляющий склад компании доставки.
 * 
 * Хранит информацию о складе: ID, название, координаты,
 * список привязанных курьеров, активность и очередь заказов,
 * ожидающих свободного курьера.
 */
class Storage {
private:
    unsigned int id;                      ///< Уникальный идентификатор склада
    string name;                          ///< Название склада
    pair<int, int> coordinates;           ///< Координаты склада (x, y)
    vector<unsigned int> id_linked_delivers; ///< ID курьеров, привязанных к складу
    bool is_active;                       ///< Активен ли склад (работает/не работает)
    queue<unsigned int> order_queue;      ///< Очередь заказов (ID), ожидающих свободного курьера

public:
    /// @brief Конструктор по умолчанию.
    Storage();

    /**
     * @brief Конструктор с параметрами.
     * @param id ID склада
     * @param name Название
     * @param coordinates Координаты
     * @param id_linked_delivers Вектор ID привязанных курьеров
     * @param is_active Активен ли
     */
    Storage(unsigned int id, const string &name, const pair<int, int> &coordinates,
            const vector<unsigned int> &id_linked_delivers, bool is_active);

    // ---------- Геттеры ----------
    unsigned int getId() const;                ///< @return ID склада
    const string& getName() const;             ///< @return Название склада
    const pair<int, int>& getCoordinates() const; ///< @return Координаты
    const vector<unsigned int>& getIdDelivers() const; ///< @return ID привязанных курьеров
    bool getIsActive() const;                  ///< @return Активен ли
    queue<unsigned int> getOrderQueue() const; ///< @return Копия очереди заказов (для сохранения)

    // ---------- Сеттеры ----------
    void setId(unsigned int n_id);                     ///< @param n_id Новый ID
    void setName(const string &n_name);                ///< @param n_name Новое название
    void setCoordinates(const pair<int, int> &n_coordinates); ///< @param n_coordinates Новые координаты
    void setIdDelivers(const vector<unsigned int> &n_id_linked_delivers); ///< @param n_id_linked_delivers Новый список курьеров
    void setIsActive(bool n_is_active);                ///< @param n_is_active Новое состояние активности
    void setOrderQueue(queue<unsigned int> q);         ///< @param q Новая очередь заказов (при загрузке)

    // ---------- Методы ----------
    /**
     * @brief Привязать курьера к складу (добавить ID в список).
     * @param id_deliver ID курьера
     */
    void link_deliver(unsigned int id_deliver);

    /// @brief Вывод информации о складе в консоль.
    void print() const;

    // ---------- Работа с очередью ----------
    void addToQueue(unsigned int orderId);    ///< Добавить заказ в очередь
    unsigned int popFromQueue();              ///< Извлечь заказ из очереди (удалить) @return ID заказа или 0, если очередь пуста
    bool isQueueEmpty() const;                ///< @return true, если очередь пуста
    void clearQueue();                        ///< Очистить очередь (при удалении склада)
};
