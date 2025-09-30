#include "structs.h"
#include <cmath>
#include <iostream>

using namespace std;

//Точка
void readPoint(Point& p) {
    cout << "x: ";
    cin >> p.x;
    cout << "y: ";
    cin >> p.y;
}

void printPoint(const Point& p) {
    cout << "(" << p.x << ", " << p.y << ")";
}

//Круг
void readCircle(Circle& c) {
    readPoint(c.center);
    cout << "Radius: ";
    cin >> c.radius;
}

void printCircle(const Circle& c) {
    cout << "Circle:";
    printPoint(c.center);
    cout << ", radius = " << c.radius;
}

double circleLength(const Circle& c) {
    return 2 * M_PI * c.radius;
}

double circleArea(const Circle& c) {
    return M_PI * c.radius * c.radius;
}

//Квадрат
void readSquare(Square& s) {
    readPoint(s.topLeft);
    cout << "Side: ";
    cin >> s.side;
}

void printSquare(const Square& s) {
    cout << "left ";
    printPoint(s.topLeft);
    cout << ", side = " << s.side;
}

double squarePerimeter(const Square& s) {
    return 4 * s.side;
}

double squareArea(const Square& s) {
    return s.side * s.side;
}

double distance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

//Принадлежность точки
bool isPointInsideCircle(const Point& p, const Circle& c) {
    return distance(p, c.center) < c.radius;
}

bool isPointInsideSquare(const Point& p, const Square& s) {
    return (p.x > s.topLeft.x && p.x < s.topLeft.x + s.side &&
            p.y < s.topLeft.y && p.y > s.topLeft.y - s.side);
}

//Нахождение точки
bool isPointOnCircle(const Point& p, const Circle& c) {
    return abs(distance(p, c.center) - c.radius) < 1e-9;
}

bool isPointOnSquare(const Point& p, const Square& s) {
    double left = s.topLeft.x;
    double right = s.topLeft.x + s.side;
    double top = s.topLeft.y;
    double bottom = s.topLeft.y - s.side;
    
    return ((abs(p.x - left) < 1e-9 || abs(p.x - right) < 1e-9) && 
            p.y <= top && p.y >= bottom) ||
           ((abs(p.y - top) < 1e-9 || abs(p.y - bottom) < 1e-9) && 
            p.x >= left && p.x <= right);
}

//Пересечение
bool circlesIntersect(const Circle& c1, const Circle& c2) {
    double dist = distance(c1.center, c2.center);
    return dist <= (c1.radius + c2.radius) && 
           dist >= abs(c1.radius - c2.radius);
}

bool squaresIntersect(const Square& s1, const Square& s2) {
    double left1 = s1.topLeft.x;
    double right1 = s1.topLeft.x + s1.side;
    double top1 = s1.topLeft.y;
    double bottom1 = s1.topLeft.y - s1.side;
    
    double left2 = s2.topLeft.x;
    double right2 = s2.topLeft.x + s2.side;
    double top2 = s2.topLeft.y;
    double bottom2 = s2.topLeft.y - s2.side;
    
    return !(right1 <= left2 || left1 >= right2 || 
             bottom1 >= top2 || top1 <= bottom2);
}

bool circleSquareIntersect(const Circle& c, const Square& s) {
    //Пересечение окружности с каждой стороной квадрата
    double left = s.topLeft.x;
    double right = s.topLeft.x + s.side;
    double top = s.topLeft.y;
    double bottom = s.topLeft.y - s.side;

    if (c.center.x >= left && c.center.x <= right && 
        c.center.y <= top && c.center.y >= bottom) {
        return true;
    }
    
    //Пересечение с каждой стороной квадрата, левая
    if (c.center.x + c.radius >= left && c.center.x <= left && 
        c.center.y >= bottom && c.center.y <= top) {
        return true;
    }
    //Правая
    if (c.center.x - c.radius <= right && c.center.x >= right && 
        c.center.y >= bottom && c.center.y <= top) {
        return true;
    }
    //Верхняя
    if (c.center.y - c.radius <= top && c.center.y >= top && 
        c.center.x >= left && c.center.x <= right) {
        return true;
    }
    //Нижняя
    if (c.center.y + c.radius >= bottom && c.center.y <= bottom && 
        c.center.x >= left && c.center.x <= right) {
        return true;
    }
    
    //Углы квадрата
    Point corners[4] = {
        {left, top}, {right, top}, {right, bottom}, {left, bottom}
    };
    
    for (int i = 0; i < 4; i++) {
        if (distance(corners[i], c.center) <= c.radius) {
            return true;
        }
    }
    
    return false;
}

// Принадлежность
bool isCircleInsideCircle(const Circle& c1, const Circle& c2) {
    return distance(c1.center, c2.center) + c1.radius <= c2.radius;
}

bool isSquareInsideSquare(const Square& s1, const Square& s2) {
    double left1 = s1.topLeft.x;
    double right1 = s1.topLeft.x + s1.side;
    double top1 = s1.topLeft.y;
    double bottom1 = s1.topLeft.y - s1.side;
    
    double left2 = s2.topLeft.x;
    double right2 = s2.topLeft.x + s2.side;
    double top2 = s2.topLeft.y;
    double bottom2 = s2.topLeft.y - s2.side;
    
    return (left1 >= left2 && right1 <= right2 && 
            top1 <= top2 && bottom1 >= bottom2);
}

bool isSquareInsideCircle(const Square& s, const Circle& c) {
    Point corners[4] = {
        {s.topLeft.x, s.topLeft.y},
        {s.topLeft.x + s.side, s.topLeft.y},
        {s.topLeft.x + s.side, s.topLeft.y - s.side},
        {s.topLeft.x, s.topLeft.y - s.side}
    };
    
    for (int i = 0; i < 4; i++) {
        if (distance(corners[i], c.center) > c.radius) {
            return false;
        }
    }
    return true;
}

bool isCircleInsideSquare(const Circle& c, const Square& s) {
    double left = s.topLeft.x;
    double right = s.topLeft.x + s.side;
    double top = s.topLeft.y;
    double bottom = s.topLeft.y - s.side;
    
    return (c.center.x - c.radius >= left && 
            c.center.x + c.radius <= right && 
            c.center.y + c.radius <= top && 
            c.center.y - c.radius >= bottom);
}