#include <string>

class Car{
    const char * body;
    int speed;
    int cord_x;
    int cord_y;
    int laps;
    bool is_first_circuit;
    std::string direction;

public:
    int id;
    Car(int speed, int cord_x, int cord_y, bool is_first_circuit);
    ~Car();
    void reach_corner();
    void change_direction();
    void drive();

    int get_cord_x();
    int get_cord_y();
    const char * get_body();
    int get_laps();
    void set_laps(int less_laps);
    bool get_is_first_circuit();
    int get_speed();
};