#ifndef XENON_GEOMETRY
    #define XENON_GEOMETRY
    // Includes
    #include "utils/vector.hpp"

    namespace xenon {
        // Used to create a point object
        struct Point {
            Vector2 pos;
            
            // Constructors
            Point();
            Point(Vector2 pos);
        };

        // Used to create a line object
        struct Line {
            Vector2 startPoint;
            Vector2 endPoint;
            
            // Constructors
            Line();
            Line(Vector2 startPoint, Vector2 endPoint);
        };

        // Used to create a triangle
        struct Triangle {
            Vector2 point1;
            Vector2 point2;
            Vector2 point3;

            // Constructors
            Triangle();
            Triangle(Vector2 point, float width, float height); // Right angle triangle
            Triangle(Vector2 point1, Vector2 point2, Vector2 point3);
        };

        // Used to create a quadrilateral
        struct Quadrilateral {
            Vector2 point1;
            Vector2 point2;
            Vector2 point3;
            Vector2 point4;

            // Constructors
            Quadrilateral();
            Quadrilateral(Vector2 point1, Vector2 point2, Vector2 point3, Vector2 point4);
        };   

        // Used to create a rectangle
        struct Rectangle {
            Vector2 point;
            float width;
            float height;

            // Constructors
            Rectangle();
            Rectangle(Vector2 point, float size); // Square
            Rectangle(Vector2 point, float width, float height);
        };

        // Used to create a circle
        struct Circle {
            Vector2 center;
            float radius;

            // Constructors
            Circle();
            Circle(Vector2 center, float radius);
        };    
    }
#endif
