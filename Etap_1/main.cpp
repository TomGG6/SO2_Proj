#include <iostream>
#include <ncurses.h>
#include <stdio.h>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "car.hpp"


void draw_circuits(WINDOW * circuits, std::vector <Car> &cars) {
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

    for(auto& car : cars) {
        mvwprintw(circuits, car.get_cord_y(), car.get_cord_x(), car.get_body());
    }
}

void spawn_cars_function(std::vector <Car> &cars) {
    int speed;
    int count = 0;
    for(int i = 10; i < 30; i += 3) {
        speed = (rand() % 1000) + 100;
        Car car(speed, i, 10, false);
        car.id = count;
        count ++;
        cars.push_back(car);
    }

    int spawn_delay;
    for(int i = 0; i < 3; i++) {
        spawn_delay = (rand() % 1000) + 10;
        speed = (rand() % 1000) + 100;
        std::this_thread::sleep_for(std::chrono::milliseconds(spawn_delay));
        Car car(speed, 0, 0, true);
        cars.push_back(car);
    }
}

void driving_function(Car &car) {
    for(int i = 0; i < 40; i++)
    {
        car.drive();
        std::this_thread::sleep_for(std::chrono::milliseconds(car.get_speed()));
    }
}

void create_vector_of_threads(std::vector <std::thread> &threads, std::vector <Car> &cars) {
    for(auto& car : cars) {
        threads.emplace_back([&] () {driving_function(std::ref(car));});
    }
}

void drawing_function(WINDOW * circuits, std::vector <Car> &cars, int iteretions) {
    for(int i = 0; i < iteretions; i++) {
        draw_circuits(circuits, cars);
        wrefresh(circuits);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void end_race(WINDOW * circuits)
{
    char key;
    do
    {
        key = wgetch(circuits);
    } while (key != 'q');
    //shouldEnd = true;
}

int main() {
    srand(time(NULL));
    initscr();
    WINDOW * circuits = newwin(38, 38, 1, 2);
    std::vector <Car> cars;
    std::vector <std::thread> driving_threads;


    refresh();
    std::thread spawn_thread(spawn_cars_function, ref(cars));
    spawn_thread.join();
    create_vector_of_threads(driving_threads, cars);
    std::thread drawing_thread(drawing_function, circuits, ref(cars), 1000);
    for(auto& t : driving_threads) t.join();
    drawing_thread.join();

    int stop = getch();


    delwin(circuits);
    endwin();
    std::cout << "size: " << cars.size() << "\n";
    for(auto& car : cars) {
        std::cout << "\ncar: " << car.id;
        std::cout << " x: " << car.get_cord_x();
        std::cout << " y: " << car.get_cord_y();
        std::cout << " s: " << car.get_speed();
    }

    return 0;
}