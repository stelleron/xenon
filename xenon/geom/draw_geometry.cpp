#include "geom/draw_geometry.hpp"

namespace xenon { 
    DrawPoint::DrawPoint(const Point& point, const Color& color) {
        this->pos = point.pos;
        this->color = color;
    }

    DrawLine::DrawLine(const Line& line, const Color& color) {
        this->startPoint = line.startPoint;
        this->endPoint = line.endPoint;
        this->color = color;
    }

    DrawTriangle::DrawTriangle(const Triangle& triangle, const Color& color) {
        this->point1 = triangle.point1;
        this->point2 = triangle.point2;
        this->point3 = triangle.point3;
        this->color = color;
    }

    DrawQuad::DrawQuad(const Quadrilateral& quad, const Color& color) {
        this->point1 = quad.point1;
        this->point2 = quad.point2;
        this->point3 = quad.point3;
        this->point4 = quad.point4;
        this->color = color;
    }

    DrawQuad::DrawQuad(const Rectangle& rect, const Color& color) {
        this->point1 = rect.pos;
        this->point2 = Vector2(rect.pos.x, rect.pos.y + rect.height);
        this->point3 = Vector2(rect.pos.x + rect.width, rect.pos.y);
        this->point4 = Vector2(rect.pos.x + rect.width, rect.pos.y + rect.height);
        this->color = color;
    }

    DrawCircle::DrawCircle(const Circle& circle, const Color& color) {
        this->center = circle.center;
        this->radius = circle.radius;
        this->color = color;
    }

    namespace drawable {
        DrawPoint make(const Point point, const Color color) {
            return DrawPoint(point, color);
        }

        DrawLine make(const Line line, const Color color) {
            return DrawLine(line, color);
        }

        DrawTriangle make(const Triangle triangle, const Color color) {
            return DrawTriangle(triangle, color);
        }   

        DrawQuad make(const Quadrilateral quad, const Color color) {
            return DrawQuad(quad, color);
        }

        DrawQuad make(const Rectangle rect, const Color color) {
            return DrawQuad(rect, color);
        }

        DrawCircle make(const Circle circle, const Color color) {
            return DrawCircle(circle, color);
        }
    }
}