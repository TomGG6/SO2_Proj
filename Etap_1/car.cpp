#include "car.hpp"
#include <iostream>
using namespace std;

Car::Car(int id, int color, int speed, int cord_x, int cord_y, bool is_first_circuit) {
    this->body = "#";
    this->id = id;
    this->color = color;
    this->speed = speed;
    this->cord_x = cord_x;
    this->cord_y = cord_y;
    this->direction = Direction::right;
    this->laps = 3;
    this->is_first_circuit = is_first_circuit;

}

Car::~Car() {
    body = NULL;
    delete body;
}

void Car::reach_corner() {
    if((direction == Direction::up && cord_x == 0 && cord_y == 0) || (direction == Direction::up && cord_x == 10 && cord_y == 10)) {
        if(is_first_circuit == true) {
            --laps;
        }
        change_direction();
    } else if((direction == Direction::right && cord_x == 19 && cord_y == 0) || (direction == Direction::right && cord_x == 29 && cord_y == 10)) {
        change_direction();
    } else if((direction == Direction::down && cord_x == 19 && cord_y == 19) || (direction == Direction::down && cord_x == 29 && cord_y == 29)) {
        change_direction();
    } else if((direction == Direction::left && cord_x == 0 && cord_y == 19) || (direction == Direction::left && cord_x == 10 && cord_y == 29)) {
        change_direction();
    }
}

void Car::change_direction() {
    if(direction == Direction::up) {
        direction = Direction::right;
    } else if(direction == Direction::right) {
        direction = Direction::down;
    } else if(direction == Direction::down) {
        direction = Direction::left;
    } else if(direction == Direction::left) {
        direction = Direction::up;
    }
}

void Car::drive() {
    reach_corner();
    if(direction == Direction::up) {
        --cord_y;
    } else if(direction == Direction::right) {
        ++cord_x;
    } else if(direction == Direction::down) {
        ++cord_y;
    } else if(direction == Direction::left) {
        --cord_x;
    }
}

int Car::get_cord_x() {
        return cord_x;
    }

int Car::get_cord_y() {
    return cord_y;
}

const char * Car::get_body() {
    return body;
}

int Car::get_laps() {
    return laps;
}

bool Car::get_is_first_circuit() {
    return is_first_circuit;
}

int Car::get_speed() {
    return speed;
}

int Car::get_id() {
    return id;
}

int Car::get_color() {
    return color;
}

Direction Car::get_direction() {
    return direction;
}