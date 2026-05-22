/**
 * @file order.hpp
 * @brief Определение класса Order (заказ).
 */

#pragma once
#include <bits/stdc++.h>

using namespace std;

/**
 * @brief Класс, представляющий заказ на доставку.
 * 
 * Содержит данные о заказе: ID, ID курьера, сумма, время принятия/доставки,
 * адрес, склад, статусы, координаты доставки.
 */
class Order {
private:
    unsigned int id;                ///< Уникальный номер заказа
    unsigned int id_deliver;        ///< ID курьера, взявшего заказ (0 если не назначен)
    unsigned int summary;           ///< Сумма заказа
    int date_accepted;              ///< Время (часы) принятия заказа
    int date_delivered;             ///< Время (часы) доставки
    string place;                   ///< Адрес (текстовое описание)
    string storage;                 ///< Название склада отправления
    bool is_accepted;               ///< Принят ли заказ (назначен курьер)
    bool is_delivered;              ///< Доставлен ли заказ
    pair<int, int> place_coordinates; ///< Координаты места доставки

public:
    /**
     * @brief Конструктор по умолчанию. Инициализирует заказ значениями по умолчанию.
     */
    Order();

    /**
     * @brief Конструктор с параметрами.
     * @param id ID заказа
     * @param summary Сумма
     * @param date_accepted Время принятия
     * @param date_delivered Время доставки
     * @param place Адрес доставки
     * @param storage Склад отправления
     * @param is_accepted Принят ли
     * @param is_delivered Доставлен ли
     * @param place_coordinates Координаты доставки
     */
    Order(unsigned int id, unsigned int summary, int date_accepted, int date_delivered,
          const string &place, const string &storage, bool is_accepted, bool is_delivered,
          const pair<int, int> &place_coordinates);

    // ---------- Геттеры ----------
    unsigned int getId() const;                ///< @return ID заказа
    unsigned int getIdDeliver() const;         ///< @return ID курьера (0 если не назначен)
    unsigned int getSummary() const;           ///< @return Сумма заказа
    int getDateAccepted() const;               ///< @return Время принятия
    int getDateDelivered() const;              ///< @return Время доставки
    const string& getPlace() const;            ///< @return Адрес доставки
    const string& getStorage() const;          ///< @return Название склада
    bool getIsAccepted() const;                ///< @return Принят ли заказ
    bool getIsDelivered() const;               ///< @return Доставлен ли заказ
    const pair<int, int>& getPlaceCoordinates() const; ///< @return Координаты доставки

    // ---------- Сеттеры ----------
    void setId(unsigned int n_id);                     ///< @param n_id Новый ID
    void setIdDeliver(unsigned int n_id_deliver);      ///< @param n_id_deliver ID курьера
    void setSummary(unsigned int n_summary);           ///< @param n_summary Новая сумма
    void setDateAccepted(int n_date_accepted);         ///< @param n_date_accepted Новое время принятия
    void setDateDelivered(int n_date_delivered);       ///< @param n_date_delivered Новое время доставки
    void setPlace(string &n_place);                    ///< @param n_place Новый адрес
    void setStorage(string &n_storage);                ///< @param n_storage Новый склад
    void setIsAccepted(bool n_is_accepted);            ///< @param n_is_accepted Новый статус принятия
    void setIsDelivered(bool n_is_delivered);          ///< @param n_is_delivered Новый статус доставки
    void setPlaceCoordinates(pair<int, int> &n_place_coordinates); ///< @param n_place_coordinates Новые координаты

    // ---------- Методы ----------
    /**
     * @brief Связать заказ с курьером (назначить курьера).
     * @param n_id_deliver ID курьера
     */
    void link_deliver(unsigned int n_id_deliver);

    /**
     * @brief Вывести информацию о заказе в консоль.
     */
    void print() const;
};
