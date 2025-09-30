#ifndef STRUCTS_H
#define STRUCTS_H

struct Point {
    double x;
    double y;
};

struct Circle {
    Point center;
    double radius;
};

struct Square {
    Point topLeft;
    double side;
};

#endif