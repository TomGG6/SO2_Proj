#include <condition_variable>
#include <mutex>

#include "direction.hpp"

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
    bool can_pass;
    bool finished_section;
    bool is_before_section;
    bool is_race_ended;
    Direction direction;

    std::condition_variable cv;
    std::mutex mu;

public:
    Car(int id, int color, int speed, int cord_x, int cord_y, bool is_first_circuit);
    ~Car();
    void reach_corner();
    void change_direction();
    void drive();
    void stop_car();
    void start_car();
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
    bool get_is_waiting();
    void set_is_waiting(bool is_waiting);
    void set_is_race_ended(bool is_race_ended);
    Direction get_direction();
    void set_direction(Direction direction);
    bool get_can_pass();
    void set_can_pass(bool can_pass);
    bool get_is_before_section();
};