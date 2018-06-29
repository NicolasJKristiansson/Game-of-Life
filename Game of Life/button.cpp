#include "button.h"

Button::Button(sf::Vector2f pos, int charSize, std::string txt, bool tog) : state(false), toggle(tog){
    button.setPosition(pos);
    button.setSize(sf::Vector2f(charSize,charSize));
    button.setFillColor(sf::Color::Blue);
    button.setOutlineColor(sf::Color::Blue);
    button.setOutlineThickness(-3);

    if(!font.loadFromFile("consola.ttf")){
        std::cout << "oh fuck";
    }
    label.setPosition(sf::Vector2f(pos.x+charSize,pos.y-charSize*.25));
    label.setFont(font);
    label.setString(" "+txt);
    label.setCharacterSize(charSize);
    label.setFillColor(sf::Color::Black);
}

void Button::draw(sf::RenderWindow* window){
    window->draw(button);
    window->draw(label);
}

void Button::trigger(){
    if(toggle){
        state = !state;
    }
    else{
        state = true;
    }
    if(state){
        button.setFillColor(sf::Color::Cyan);
    }
    else{
        button.setFillColor(sf::Color::Blue);
    }
}

bool Button::getState(){
    bool s = state;
    if(!toggle){
        state = false;
        button.setFillColor(sf::Color::Blue);
    }
    return s;
}

bool Button::check(sf::Vector2f pos){
    sf::FloatRect bounds = button.getGlobalBounds();
    return bounds.contains(pos);
}
