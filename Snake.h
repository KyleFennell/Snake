#include "SDL.h"
#include "SDL_image.h"
#include <vector>

class Point;

class Snake{
public:

    void handleEvents();
    void update();
    void draw();

private:

    bool move(int xDir, int yDir);  // returns false if it dies
    bool eat();                     // returns true if successfully ate something
    int length;                     // length of the snake
    std::vector<Point> snake;       // the coordinates the snake currently occupies from head to tail

};

struct Point{
public:
    int x(){ return _x; }
    int y(){ return _y; }
private:
    int _x;
    int _y;
};
