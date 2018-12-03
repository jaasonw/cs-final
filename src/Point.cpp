#include "Point.h"

Point::Point() : Entity() {
    this->point.setRadius(RADIUS);
    this->point.setFillColor(color);
}

Point::Point(double graph_x, double graph_y)
    : graph_x(graph_x), graph_y(graph_y) {
    this->point.setRadius(RADIUS);
    this->point.setFillColor(color);
}
Point::~Point() {}
void Point::step() {}

void Point::render(sf::RenderWindow& window) { window.draw(this->point); }

void Point::plot(double screen_x, double screen_y) {
    this->point.setPosition(screen_x, screen_y);
}