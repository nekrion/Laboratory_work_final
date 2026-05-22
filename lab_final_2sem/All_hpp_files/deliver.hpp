#pragma once
#include<bits/stdc++.h>

using namespace std;

// Состояние курьера
enum class CourierState {
	FREE,				// свободен на складе
	GOING_TO_CUSTOMER,	// едет к клиенту
	RETURNING_TO_BASE	// возвращается на склад
};

class Deliver {
private:

	unsigned int id; // id доставщика
	unsigned int id_linked_storage;	// id склада с которым связан курьер
	unsigned int speed; // скорость курьера (условных единиц расстояния в час)
	string name; // имя курьера
	bool is_have_order; // состояние что есть ли заказ
	bool is_linked_with_storage; // состояние что привязан ли к какому-либо складу

	// дополнительные поля для движения (промотка времени)
	CourierState state; // текущее состояние курьера
	double remaining_distance; // оставшееся расстояние до цели (в условных единицах)
	pair<int, int> target_coords; // координаты текущей цели (куда едет)

public:

	//constructors
	Deliver() {
		id = 0;
		id_linked_storage = 0;
		speed = 0;
		name = "-";
		is_have_order = false;
		is_linked_with_storage = false;
		state = CourierState::FREE;
		remaining_distance = 0.0;
		target_coords = {0, 0};
	}

	Deliver(unsigned int id, unsigned int id_linked_storage, unsigned int speed,
			const string &name, bool is_have_order, bool is_linked_with_storage);

	// getters (старые)
	unsigned int getId() const;
	unsigned int getIdLinkedStorage() const;
	unsigned int getSpeed() const;
	const string& getName() const;
	bool getIsHaveOrder() const;
	bool getIsLinkedWithStorage() const;

	// getters (новые для движения)
	CourierState getState() const;
	double getRemainingDistance() const;
	pair<int, int> getTargetCoords() const;

	// setters (старые)
	void setId(unsigned int n_id);
	void setIdLinkedStorage(unsigned int n_id_linked_storage);
	void setSpeed(unsigned int n_speed);
	void setName(const string &n_name);
	void setIsHaveOrder(bool n_is_have_order);
	void setIsLinkedWithStorage(bool n_is_linked_with_storage);

	// setters (новые для движения)
	void setState(CourierState n_state);
	void setRemainingDistance(double n_remaining_distance);
	void setTargetCoords(const pair<int, int> &n_target_coords);

	//methods
	void print() const; // удобный вывод информации о Deliver
};
