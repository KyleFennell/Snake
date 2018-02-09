#pragma once

class Point{
public:

    Point(){ _x = 0; _y = 0; }
    Point(int x, int y){ _x = x; _y = y; }
    ~Point(){ _x = 0; _y = 0; };

    int x() const { return _x; }
    int y() const { return _y; }
    Point& operator+=(Point& p){
        _x += p.x();
        _y += p.y();
        return *this;
    }
    friend Point operator+(Point p1, const Point p2){
        p1._x += p2.x();
        p1._y += p2.y();
        return p1;
    }


private:

    int _x;
    int _y;

};
