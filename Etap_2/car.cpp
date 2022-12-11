#include "car.hpp"

#include <iostream>

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
    this->is_waiting = false;
    this->is_before_section = false;
    this->is_race_ended = false;
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
    if(!is_race_ended) {
        check_if_is_waiting();
    }
    if(!is_waiting) {
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
}

void Car::stop_car() {
    is_waiting = true;
}

void Car::start_car() {
    is_waiting = false;
}


void Car::check_if_is_waiting() {
    if ((is_first_circuit && cord_x == 19 && cord_y == 9) || (!is_first_circuit && cord_x == 10 && cord_y == 20)) {
        is_before_section = true;
    } 
}

bool Car::check_if_finished_section() {
    if((is_first_circuit && cord_x == 9 && cord_y == 19) || (!is_first_circuit && cord_x == 20 && cord_y == 10)) {
        is_before_section = false;
        return is_before_section;
    } else {
        return is_before_section;
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

void Car::set_direction(Direction direction) {
    this->direction = direction;
}

void Car::set_is_race_ended(bool is_race_ended) {
    this->is_race_ended = true;
}

bool Car::get_is_before_section() {
    return is_before_section;
}