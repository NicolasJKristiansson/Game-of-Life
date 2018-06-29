#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>

class Button{
private:
    sf::RectangleShape button;
    sf::Text label;
	sf::Font font;
    bool state, toggle;

public:
    Button(sf::Vector2f, int, std::string, bool);

    void draw(sf::RenderWindow*);
	void trigger();
	bool getState();
    bool check(sf::Vector2f);
};

#endif
