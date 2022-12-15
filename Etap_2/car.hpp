#include "direction.hpp"

#include <mutex>
#include <condition_variable>

class Car {
    const char * body;
    int id;
    int color;
    int speed;
    int cord_x;
    int cord_y;
    int laps;
    bool is_first_circuit;
    bool is_waiting;
    bool finished_section;
    bool is_before_section;
    bool is_race_ended;
    Direction direction;
    std::mutex car_mu;
    std::condition_variable cv;

public:
    Car(int id, int color, int speed, int cord_x, int cord_y, bool is_first_circuit);
    ~Car();
    void reach_corner();
    void change_direction();
    void drive(int passing_car_id, bool stop_cars);
    void check_if_is_waiting();
    bool check_if_finished_section();
    void notify();

    int get_cord_x();
    int get_cord_y();
    const char * get_body();
    int get_laps();
    bool get_is_first_circuit();
    int get_speed();
    int get_id();
    int get_color();
    void set_is_race_ended(bool is_race_ended);
    Direction get_direction();
    void set_direction(Direction direction);
    bool get_is_before_section();
};