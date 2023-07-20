#include "geom/geometry.hpp"
#include "utils/logger.hpp"

namespace xenon {
    Point::Point() {
        pos = Vector2(0,0);
    }

    Point::Point(Vector2 pos) {
        this->pos = pos;
    }

    Line::Line() {
        startPoint = Vector2(0,0);
        endPoint = Vector2(0,0);
    }

    Line::Line(Vector2 startPoint, Vector2 endPoint) 
    : startPoint(startPoint) , endPoint(endPoint) {

    }

    Triangle::Triangle() {
        point1 = Vector2(0,0);
        point2 = Vector2(0,0);
        point3 = Vector2(0,0);
    }

    Triangle::Triangle(Vector2 point, float width, float height) 
    {
        this->point1 = point;
        this->point2 = Vector2(point.x + width, point.y);
        this->point3 = Vector2(point.x, point.y + height);
    }

    Triangle::Triangle(Vector2 point1, Vector2 point2, Vector2 point3) 
    : point1(point1), point2(point2), point3(point3) {

    }

    Quadrilateral::Quadrilateral() {
        point1 = Vector2(0,0);
        point2 = Vector2(0,0);    
        point3 = Vector2(0,0);  
        point4 = Vector2(0,0); 
    }

    Quadrilateral::Quadrilateral(Vector2 point1, Vector2 point2, Vector2 point3, Vector2 point4) 
    : point1(point1), point2(point2), point3(point3), point4(point4){

    }

    Rectangle::Rectangle() {
        pos = Vector2(0,0);
        width = 0;
        height = 0;
    }

    Rectangle::Rectangle(float x, float y, float size) 
    : width(size), height(size) {
        pos = Vector2(x, y);
    }

    Rectangle::Rectangle(float x, float y, float width, float height) 
    : width(width), height(height) {
        pos = Vector2(x, y);
    }

    Rectangle::Rectangle(Vector2 pos, float size) 
    : pos(pos), width(size), height(size) {

    }

    Rectangle::Rectangle(Vector2 pos, float width, float height) 
    : pos(pos), width(width), height(height) {

    }

    Circle::Circle() {
        center = Vector2(0,0);
        radius = 0;
    }

    Circle::Circle(Vector2 center, float radius) 
    : center(center), radius(radius) {

    }
}