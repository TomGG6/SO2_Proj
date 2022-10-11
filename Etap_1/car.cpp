#include "car.hpp"
#include <iostream>
using namespace std;

Car::Car(int speed, int cord_x, int cord_y, bool is_first_circuit) {
    this->body = "+";
    this->speed = speed;
    this->cord_x = cord_x;
    this->cord_y = cord_y;
    this->direction = "right";
    this->laps = 3;
    this->is_first_circuit = is_first_circuit;

}

Car::~Car(){
    body = NULL;
    delete body;
}

void Car::reach_corner() {
    if((direction == "up" && cord_x == 0 && cord_y == 0) || (direction == "up" && cord_x == 10 && cord_y == 10)) {
        change_direction();
    } else if((direction == "right" && cord_x == 19 && cord_y == 0) || (direction == "right" && cord_x == 29 && cord_y == 10)) {
        change_direction();
    } else if((direction == "down" && cord_x == 19 && cord_y == 19) || (direction == "down" && cord_x == 29 && cord_y == 29)) {
        change_direction();
    } else if((direction == "left" && cord_x == 0 && cord_y == 19) || (direction == "left" && cord_x == 10 && cord_y == 29)) {
        change_direction();
    }
}

void Car::change_direction() {
    if(direction == "up") {
        direction = "right";
    } else if(direction == "right") {
        direction = "down";
    } else if(direction == "down") {
        direction = "left";
    } else if(direction == "left") {
        direction = "up";
    }
}

void Car::drive() {
    reach_corner();
    if(direction == "up") {
        --cord_y;
    } else if(direction == "right") {
        //cout << "żyte jest";
        ++cord_x;
    } else if(direction == "down") {
        ++cord_y;
    } else if(direction == "left") {
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

void Car::set_laps(int less_laps) {
    laps = less_laps;
}

bool Car::get_is_first_circuit() {
    return is_first_circuit;
}