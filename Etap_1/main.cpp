#include <iostream>
#include <ncurses.h>
#include <stdio.h>
#include <vector>
#include <thread>
#include <chrono>
#include <random>
#include "car.hpp"
using namespace std;

void draw_circuits(WINDOW * circuits, vector <Car> &cars) {
    for(int y = 0; y < 20; y++) {
        for(int x = 0; x < 20; x++) {
            if(y == 0 || y == 19) {
                mvwprintw(circuits, x, y, "#");
            } else if(x == 0 || x == 19) {
                mvwprintw(circuits, x, y, "#");
            }
        }
    }

    for(int y = 10; y < 30; y++) {
        for(int x = 10; x < 30; x++) {
            if(y == 10 || y == 29) {
                mvwprintw(circuits, x, y, "#");
            } else if(x == 10 || x == 29) {
                mvwprintw(circuits, x, y, "#");
            }
        }
    }

    for(Car &car : cars) {
        mvwprintw(circuits, car.get_cord_y(), car.get_cord_x(), car.get_body());
        //cout << car.get_cord_x();
        car.drive();
    }
}

void driving_function(WINDOW * circuits, vector <Car> &cars, int iteretions) {
    for(int i = 0; i < iteretions; i++) {
        //cout << "\n iteration: " << i << "x: ";
        draw_circuits(circuits, cars);
        wrefresh(circuits);
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main() {
    initscr();
    WINDOW * circuits = newwin(38, 38, 1, 2);
    vector <Car> cars;
    Car car(1, 0, 0);
    Car car1(1, 4, 0);
    Car car2(1, 10, 10);
    cars.push_back(car);
    cars.push_back(car1);
    cars.push_back(car2);
    refresh();
    thread driving_thread(driving_function, circuits, ref(cars), 90);
    driving_thread.join();
    driving_function(circuits, cars, 5);
    int stop = getch();
    delwin(circuits);
    endwin();
    int a = 1;
    for(Car &car : cars) {
        cout << "\ncar " << a;
        cout << " x: " << car.get_cord_x();
        cout << " y: " << car.get_cord_y();
    }
    return 0;
}