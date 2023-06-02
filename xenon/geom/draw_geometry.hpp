#ifndef XENON_DRAW_GEOMETRY
    #define XENON_DRAW_GEOMETRY
    // Includes
    #include "utils/color.hpp"
    #include "geom/geometry.hpp"

    namespace xenon {
        struct DrawPoint : public Point {
            Color color;
            DrawPoint(const Point& point, const Color& color);
        };

        struct DrawLine : public Line {
            Color color;
            DrawLine(const Line& line, const Color& color);
        };

        // Used to create a drawable
        struct DrawTriangle : public Triangle {
            Color color;
            DrawTriangle(const Triangle& triangle, const Color& color);
        };

        struct DrawQuad : public Quadrilateral {
            Color color;
            DrawQuad(const Rectangle& rect, const Color& color);
            DrawQuad(const Quadrilateral& quad, const Color& color);
        };

        struct DrawCircle : public Circle {
            Color color;
            DrawCircle(const Circle& circle, const Color& color);
        };

        // Used to make drawable objects
        namespace drawable
        {
            DrawPoint make(const Point point, const Color color);
            DrawLine make(const Line line, const Color color);
            DrawTriangle make(const Triangle triangle, const Color color);
            DrawQuad make(const Quadrilateral quad, const Color color);
            DrawQuad make(const Rectangle rect, const Color color);
            DrawCircle make(const Circle circle, const Color color);
        }
    }
#endif