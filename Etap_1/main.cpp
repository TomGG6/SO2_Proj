#include <iostream>
#include <ncurses.h>
#include <stdio.h>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "car.hpp"

void prepare_color_pairs() {
    init_pair(0, COLOR_BLUE, COLOR_WHITE);
    init_pair(1, COLOR_GREEN, COLOR_WHITE);
    init_pair(2, COLOR_CYAN, COLOR_WHITE);
    init_pair(3, COLOR_RED, COLOR_WHITE);
    init_pair(4, COLOR_MAGENTA, COLOR_WHITE);
    init_pair(5, COLOR_YELLOW, COLOR_WHITE);
    init_pair(6, COLOR_BLACK, COLOR_WHITE);
    init_pair(7, COLOR_WHITE, COLOR_WHITE);
}

void draw_circuits(WINDOW *circuits, std::vector<Car *> &cars)
{
    wattron(circuits, COLOR_PAIR(7));
    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 20; x++)
        {
            if (y == 0 || y == 19)
            {
                mvwprintw(circuits, x, y, " ");
            }
            else if (x == 0 || x == 19)
            {
                mvwprintw(circuits, x, y, " ");
            }
        }
    }

    for (int y = 10; y < 30; y++)
    {
        for (int x = 10; x < 30; x++)
        {
            if (y == 10 || y == 29)
            {
                mvwprintw(circuits, x, y, " ");
            }
            else if (x == 10 || x == 29)
            {
                mvwprintw(circuits, x, y, " ");
            }
        }
    }

    for (auto &car : cars)
    {
        if((*car).get_laps() > 0) {
            wattron(circuits, COLOR_PAIR((*car).get_color()));
            mvwprintw(circuits, (*car).get_cord_y(), (*car).get_cord_x(), (*car).get_body());
        }
    }
}

void driving_function(Car * car, bool &run)
{
    while (run)
    {
        (*car).drive();
        std::this_thread::sleep_for(std::chrono::milliseconds((*car).get_speed()));
    }
}

void spawn_cars_function(std::vector<std::thread *> &threads, std::vector<Car *> &cars, bool &run)
{
    int speed, car_counter = 0;;
    for (int i = 10; i < 30; i += 3)
    {
        speed = (rand() % 1000) + 100;
        Car * car = new Car(car_counter, car_counter % 7, speed, i, 10, false);
        car_counter++;
        cars.emplace_back(car);
    }

    for(auto &car : cars) {
        threads.emplace_back(new std::thread(driving_function, std::ref(car), std::ref(run)));
    }

    int spawn_delay;
    while (run)
    {
        spawn_delay = (rand() % 10000) + 4000;
        speed = (rand() % 1000) + 100;
        std::this_thread::sleep_for(std::chrono::milliseconds(spawn_delay));
        Car *car = new Car(car_counter, car_counter % 7, speed, 0, 0, true);
        car_counter++;
        cars.emplace_back(car);
        threads.emplace_back(new std::thread(driving_function, std::ref(car), std::ref(run)));
    }
}

void delete_car_function(std::vector<Car *> &cars, std::vector<std::thread *> &threads, bool &run)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(4000));
    while(run) {
        for (auto &car : cars) {
            if ((*car).get_is_first_circuit() && (*car).get_laps() == 0)
            {
                (*threads[(*car).get_id()]).join();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void drawing_function(WINDOW *circuits, std::vector<Car *> &cars, bool &run)
{
    while (run)
    {
        draw_circuits(circuits, cars);
        refresh();
        wrefresh(circuits);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void end_race(WINDOW *circuits, bool &run)
{
    char key;
    do
    {
        key = getch();
    } while (key != 'q' && key != 'Q');
    run = false;
}

int main()
{
    srand(time(NULL));
    initscr();
    start_color();
    prepare_color_pairs();

    WINDOW *circuits = newwin(38, 38, 1, 2);
    refresh();

    std::vector<Car *> cars;
    std::vector<std::thread *> driving_threads;
    bool run = true;

    std::thread spawn_thread(spawn_cars_function, ref(driving_threads), ref(cars), std::ref(run));
    std::thread delete_cars_thread(delete_car_function, ref(cars), ref(driving_threads), std::ref(run));
    std::thread drawing_thread(drawing_function, circuits, ref(cars), std::ref(run));
    std::thread race_thread(end_race, circuits, std::ref(run));

    race_thread.join();
    spawn_thread.join();
    drawing_thread.join();
    delete_cars_thread.join();

    delwin(circuits);
    endwin();

    for (auto &t : driving_threads)
    {
        if((*t).joinable()) {
            (*t).join();
            delete t;
            t = NULL;
        }
    }

    for(auto &c : cars) {
        delete c;
        c = NULL;
    }

    return 0;
}