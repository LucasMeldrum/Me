//
// Created by kfrai on 2025-02-27.
//

#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;

    sf::Color baseColor;
    bool isHovered;
    bool wasPressed;

    bool isEnabled;


public:

    Button(sf::Vector2f size, sf::Vector2f position, sf::Font& font, sf::String buttonText, sf::Color color);

    void setEnabled(bool enabled);

    bool getIsEnabled();

    sf::RectangleShape& getShape();
    sf::Text& getText();

    bool hover(sf::Vector2f position, sf::RenderWindow *window);
    bool click(sf::Vector2f position, sf::Mouse::Button key, sf::RenderWindow *window);

};



#endif //BUTTON_H
