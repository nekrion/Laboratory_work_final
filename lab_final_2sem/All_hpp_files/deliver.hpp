/**
 * @file deliver.hpp
 * @brief Определение класса Deliver (курьер) и перечисления CourierState.
 */

#pragma once
#include<bits/stdc++.h>

using namespace std;

/**
 * @brief Состояние курьера.
 */
enum class CourierState {
    FREE,                ///< Свободен на складе
    GOING_TO_CUSTOMER,   ///< Едет к клиенту
    RETURNING_TO_BASE    ///< Возвращается на склад
};

/**
 * @brief Класс курьера (доставщика).
 * 
 * Хранит ID, ID привязанного склада, скорость, имя,
 * флаги наличия заказа и привязки, текущее состояние,
 * оставшееся расстояние до цели и координаты цели.
 */
class Deliver {
private:
    unsigned int id;                 ///< Уникальный ID курьера
    unsigned int id_linked_storage;  ///< ID склада, к которому привязан курьер (0 если не привязан)
    unsigned int speed;              ///< Скорость курьера (условных единиц расстояния в час)
    string name;                     ///< Имя курьера
    bool is_have_order;              ///< Есть ли у курьера активный заказ
    bool is_linked_with_storage;     ///< Привязан ли курьер к какому-либо складу

    // Дополнительные поля для движения (промотка времени)
    CourierState state;              ///< Текущее состояние курьера
    double remaining_distance;       ///< Оставшееся расстояние до цели (в условных единицах)
    pair<int, int> target_coords;    ///< Координаты текущей цели (куда едет)

public:
    /**
     * @brief Конструктор по умолчанию. Инициализирует курьера значениями по умолчанию.
     */
    Deliver();

    /**
     * @brief Конструктор с параметрами.
     * @param id ID курьера
     * @param id_linked_storage ID привязанного склада
     * @param speed Скорость
     * @param name Имя
     * @param is_have_order Флаг наличия заказа
     * @param is_linked_with_storage Флаг привязки к складу
     */
    Deliver(unsigned int id, unsigned int id_linked_storage, unsigned int speed,
            const string &name, bool is_have_order, bool is_linked_with_storage);

    // ---------- Старые геттеры ----------
    unsigned int getId() const;                ///< @return ID курьера
    unsigned int getIdLinkedStorage() const;   ///< @return ID привязанного склада
    unsigned int getSpeed() const;             ///< @return Скорость курьера
    const string& getName() const;             ///< @return Имя курьера
    bool getIsHaveOrder() const;               ///< @return Есть ли заказ
    bool getIsLinkedWithStorage() const;       ///< @return Привязан ли к складу

    // ---------- Новые геттеры для движения ----------
    CourierState getState() const;             ///< @return Текущее состояние
    double getRemainingDistance() const;       ///< @return Оставшееся расстояние
    pair<int, int> getTargetCoords() const;    ///< @return Координаты цели

    // ---------- Старые сеттеры ----------
    void setId(unsigned int n_id);                         ///< @param n_id Новый ID
    void setIdLinkedStorage(unsigned int n_id_linked_storage); ///< @param n_id_linked_storage Новый ID склада
    void setSpeed(unsigned int n_speed);                   ///< @param n_speed Новая скорость
    void setName(const string &n_name);                    ///< @param n_name Новое имя
    void setIsHaveOrder(bool n_is_have_order);             ///< @param n_is_have_order Флаг наличия заказа
    void setIsLinkedWithStorage(bool n_is_linked_with_storage); ///< @param n_is_linked_with_storage Флаг привязки

    // ---------- Новые сеттеры для движения ----------
    void setState(CourierState n_state);                   ///< @param n_state Новое состояние
    void setRemainingDistance(double n_remaining_distance); ///< @param n_remaining_distance Новое остаток расстояния
    void setTargetCoords(const pair<int, int> &n_target_coords); ///< @param n_target_coords Новые координаты цели

    /**
     * @brief Вывести информацию о курьере в консоль.
     */
    void print() const;
};
