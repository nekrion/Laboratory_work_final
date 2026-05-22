/**
 * @file database.hpp
 * @brief Определение класса DataBase (база данных).
 */

#pragma once
#include <bits/stdc++.h>
#include "deliver.hpp"
#include "order.hpp"
#include "storage.hpp"

using namespace std;

/**
 * @brief Класс базы данных, объединяющий все сущности и управляющий бизнес-логикой.
 * 
 * Содержит векторы складов, курьеров, заказов, глобальное время.
 * Предоставляет методы для добавления, удаления, вывода,
 * назначения заказов, промотки времени, сохранения/загрузки.
 */
class DataBase {
private:
    vector<Order> orders;    ///< Вектор всех заказов
    vector<Deliver> delivers; ///< Вектор всех курьеров
    vector<Storage> storages; ///< Вектор всех складов
    int global_time;          ///< Глобальное время в часах (от начала работы)

public:
    /**
     * @brief Конструктор. Инициализирует глобальное время нулём.
     */
    DataBase();

    // ---------- Добавление объектов ----------
    /**
     * @brief Добавить новый заказ.
     * @param id ID заказа
     * @param summary Сумма
     * @param date_accepted Время принятия
     * @param date_delivered Время доставки
     * @param place Адрес
     * @param storage Название склада
     * @param is_accepted Принят ли
     * @param is_delivered Доставлен ли
     * @param place_coordinates Координаты доставки
     */
    void addOrder(unsigned int id, unsigned int summary, int date_accepted, int date_delivered,
                  const string &place, const string &storage, bool is_accepted, bool is_delivered,
                  const pair<int,int> &place_coordinates);

    /**
     * @brief Добавить нового курьера.
     * @param id ID курьера
     * @param id_linked_storage ID склада привязки
     * @param speed Скорость
     * @param name Имя
     * @param is_have_order Флаг наличия заказа
     * @param is_linked_with_storage Флаг привязки
     */
    void addDeliver(unsigned int id, unsigned int id_linked_storage, unsigned int speed,
                    const string &name, bool is_have_order, bool is_linked_with_storage);

    /**
     * @brief Добавить новый склад.
     * @param id ID склада
     * @param name Название
     * @param coordinates Координаты
     * @param id_linked_delivers Вектор ID привязанных курьеров
     * @param is_active Активен ли
     */
    void addStorage(unsigned int id, const string &name, const pair<int, int> &coordinates,
                    const vector<unsigned int> &id_linked_delivers, bool is_active);

    // ---------- Удаление объектов ----------
    void removeStorage(unsigned int id);   ///< Удалить склад по ID
    void removeDeliver(unsigned int id);   ///< Удалить курьера по ID
    void removeOrder(unsigned int id);     ///< Удалить заказ по ID

    // ---------- Вывод информации ----------
    void printAll();                       ///< Вывести всю базу данных
    void printStorageInfo(unsigned int storageId);          ///< Информация о конкретном складе
    void printDeliversOnStorage(unsigned int storageId);    ///< Курьеры склада (свободные/занятые)
    void printOrderQueueOfStorage(unsigned int storageId);  ///< Очередь заказов склада

    // ---------- Бизнес-логика ----------
    /**
     * @brief Назначить заказ свободному курьеру на указанном складе.
     * @param order Заказ (ссылка)
     * @param storageId ID склада
     * @return true, если назначение удалось; false, если свободных курьеров нет (заказ идёт в очередь)
     */
    bool assignOrderToFreeDeliver(Order &order, unsigned int storageId);

    /**
     * @brief Прокрутить время на заданное количество часов.
     * @param hours Количество часов
     * 
     * Обновляет глобальное время, перемещает курьеров,
     * завершает доставки, возвращает курьеров на склад,
     * выдаёт заказы из очереди.
     */
    void advanceTime(int hours);

    // ---------- Работа с файлами ----------
    void save_to_file(const string &filename);   ///< Сохранить БД в файл
    void load_from_file(const string &filename); ///< Загрузить БД из файла

    // ---------- Геттеры для доступа извне (нужны для сохранения/загрузки) ----------
    vector<Order>& getOrders() { return orders; }       ///< @return Вектор заказов
    vector<Deliver>& getDelivers() { return delivers; } ///< @return Вектор курьеров
    vector<Storage>& getStorages() { return storages; } ///< @return Вектор складов
    int getGlobalTime() const { return global_time; }   ///< @return Глобальное время
    void setGlobalTime(int t) { global_time = t; }      ///< @param t Новое глобальное время
};
