#include "Function.h"
#include "engine/Engine.h"

Function::Function() : Entity() {
    // example test function
    this->function_string = "sin(x)";
    this->postfix = infix_to_postfix(tokenize(function_string));
    for (auto it = postfix.begin(); it != NULL; it++) {
        std::cout << **it << std::endl;
    }
    this->update_graph();

    this->color.r = rand() % 255;
    this->color.g = rand() % 255;
    this->color.b = rand() % 255;
}

Function::Function(std::string function_string) : Entity(), function_string(function_string) {
    this->color.r = rand() % 255;
    this->color.g = rand() % 255;
    this->color.b = rand() % 255;
    try {
        this->postfix = infix_to_postfix(tokenize(function_string));
    }
    catch(...) {
        std::cout << "error parsing function: " << function_string << std::endl;
        return;
    }
    this->update_graph();
}

Function::~Function() {
    while (!postfix.empty()) {
        delete postfix.pop();
    }
}

void Function::step(sf::RenderWindow& window, sf::Event& event, bool poll) {
    // TODO: maybe change this so it plots a point every frame instead
    // of the constructor
}

void Function::render(sf::RenderWindow& window) {
    // do translating to screen coords here
    for (unsigned int i = 0; i < points.size(); i++) {
        double x1 = (points[i].x * this->zoom) + origin_x;
        double y1 = -((points[i].y * this->zoom)) + origin_y;
        if (i != 0) {
            double x2 = (points[i - 1].x * this->zoom) + origin_x;
            double y2 = -((points[i - 1].y * this->zoom)) + origin_y;
            window.draw(create_line(x1, y1, x2, y2, this->color));
        }
    }
}

void Function::plot(double screen_x, double screen_y, double zoom) {
    this->zoom = zoom;
    this->origin_x = screen_x;
    this->origin_y = screen_y;
}

void Function::update_graph() {
    for (double i = interval_start; i < interval_end; i += point_frequency) {
        try {
            points.push_back(sf::Vector2f(i, eval(postfix, i)));
        }
        catch(...) {
            std::cout << "something went wrong here, maybe an asymtote, maybe an invalid expression" << std::endl;
        }
    }
}

void Function::set_bounds(double low, double high) {
    if (low > high) {
        this->interval_start = high;
        this->interval_end = low;
    }
    else {
        this->interval_start = low;
        this->interval_end = high;
    }
    this->update_graph();
}