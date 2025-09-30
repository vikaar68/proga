#include <iostream>
#include "structs.h"
#include "func.h"

using namespace std;

int main() {
    cout << "=== DEMONSTRATION ===\n\n";
    
    //Точка
    cout << "1. POINT:\n";
    Point p1;
    readPoint(p1);
    cout << "Point: ";
    printPoint(p1);
    cout << "\n\n";
    
    //Круг
    cout << "2. CIRCLE:\n";
    Circle c1;
    readCircle(c1);
    printCircle(c1);
    cout << "\nCircum: " << circleLength(c1);
    cout << "\nArea: " << circleArea(c1);
    cout << "\n\n";
    
    //Квадрат
    cout << "3. SQUARE:\n";
    Square s1;
    readSquare(s1);
    printSquare(s1);
    cout << "\nPerimeter: " << squarePerimeter(s1);
    cout << "\nArea: " << squareArea(s1);
    cout << "\n\n";
    
    //Принадлежность точки
    cout << "4. POINT INSIDE FIGURES:\n";
    cout << "Point "; printPoint(p1); 
    cout << (isPointInsideCircle(p1, c1) ? " inside " : " outside ");
    cout << "circle\n";
    
    cout << "Point "; printPoint(p1);
    cout << (isPointInsideSquare(p1, s1) ? " inside " : " outside ");
    cout << "square\n\n";
    
    //Нахождение точки
    cout << "5. POINT ON CONTOUR:\n";
    cout << "Point "; printPoint(p1);
    cout << (isPointOnCircle(p1, c1) ? " on " : " not on ");
    cout << "circle\n";
    
    cout << "Point "; printPoint(p1);
    cout << (isPointOnSquare(p1, s1) ? " on " : " not on ");
    cout << "square\n\n";
    
    //Пересечение
    cout << "6. INTERSECTION\n";
    
    Circle c2;
    readCircle(c2);
    
    Square s2;
    readSquare(s2);
    
    //Пересечение
    cout << "\nINTERSECTIONS:\n";
    cout << "Circles " << (circlesIntersect(c1, c2) ? "intersect" : "don't intersect") << endl;
    cout << "Squares " << (squaresIntersect(s1, s2) ? "intersect" : "don't intersect") << endl;
    cout << "Circle and square " << (circleSquareIntersect(c1, s1) ? "intersect" : "don't intersect") << endl;
    
    cout << "\nCONTAINMENT:\n";
    cout << "Circle 1 " << (isCircleInsideCircle(c1, c2) ? "inside" : "not inside") << " circle 2\n";
    cout << "Square 1 " << (isSquareInsideSquare(s1, s2) ? "inside" : "not inside") << " square 2\n";
    cout << "Square " << (isSquareInsideCircle(s1, c1) ? "inside" : "not inside") << " circle\n";
    cout << "Circle " << (isCircleInsideSquare(c1, s1) ? "inside" : "not inside") << " square\n";
    
    return 0;
}