#ifndef FUNC_H
#define FUNC_H

#include "structs.h"

//Точка
void readPoint(Point& p);
void printPoint(const Point& p);

//Круг
void readCircle(Circle& c);
void printCircle(const Circle& c);
double circleLength(const Circle& c);
double circleArea(const Circle& c);

//Квадрат
void readSquare(Square& s);
void printSquare(const Square& s);
double squarePerimeter(const Square& s);
double squareArea(const Square& s);

//Принадлежность точки
bool isPointInsideCircle(const Point& p, const Circle& c);
bool isPointInsideSquare(const Point& p, const Square& s);

//Нахождение точки
bool isPointOnCircle(const Point& p, const Circle& c);
bool isPointOnSquare(const Point& p, const Square& s);

//Пересечение
bool circlesIntersect(const Circle& c1, const Circle& c2);
bool squaresIntersect(const Square& s1, const Square& s2);
bool circleSquareIntersect(const Circle& c, const Square& s);

//Принадлежность фигур
bool isCircleInsideCircle(const Circle& c1, const Circle& c2);
bool isSquareInsideSquare(const Square& s1, const Square& s2);
bool isSquareInsideCircle(const Square& s, const Circle& c);
bool isCircleInsideSquare(const Circle& c, const Square& s);

#endif