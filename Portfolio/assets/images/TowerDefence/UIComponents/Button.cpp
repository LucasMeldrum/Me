//
// Created by kfrai on 2025-02-27.
//

#include "Button.h"

#include <cmath>
#include <iostream>

// General button class to give all buttons similar behaviour such as the ability to be hovered and clicked, and change color accordingly
Button::Button(sf::Vector2f size, sf::Vector2f position, sf::Font &font, sf::String buttonText, sf::Color color)
    : text(font), baseColor(color), isEnabled(false) {
    shape.setSize(size);
    shape.setOrigin(shape.getGeometricCenter());
    shape.setPosition(position);
    shape.setFillColor(color);

    text.setFont(font);
    text.setString(buttonText);
    text.setCharacterSize(8);
    text.setFillColor(sf::Color::White);

    // Center text in the button
    auto center = text.getGlobalBounds().size / 2.f;
    auto localBounds = center + text.getLocalBounds().position;
    auto rounded = sf::Vector2f{std::round(localBounds.x), std::round(localBounds.y)};
    text.setOrigin(rounded);
    text.setPosition(sf::Vector2f(shape.getPosition().x, shape.getPosition().y));

    isHovered = false;
}

void Button::setEnabled(bool enabled) {
    isEnabled = enabled;
}

bool Button::getIsEnabled() {
    return isEnabled;
}

sf::RectangleShape& Button::getShape() {
    return shape;
}

sf::Text& Button::getText() {
    return text;
}

bool Button::hover(sf::Vector2f position, sf::RenderWindow *window) {
    if (!isEnabled) {
        return false; // Ignore hover if disabled

    }
    if (shape.getGlobalBounds().contains(position)) {
        if (!isHovered) {
            sf::Color hoverColor = baseColor;
            hoverColor.r = std::max(0, hoverColor.r - 40);
            hoverColor.g = std::max(0, hoverColor.g - 40);
            hoverColor.b = std::max(0, hoverColor.b - 40);
            shape.setFillColor(hoverColor);
            isHovered = true;
        }
        return true;
    } else {
        if (isHovered) {
            shape.setFillColor(baseColor);
            isHovered = false;
        }
    }
    return false;
}

bool Button::click(sf::Vector2f position, sf::Mouse::Button key, sf::RenderWindow *window) {
    if (!isEnabled) return false; // Ignore clicks if disabled
    return hover(position, window) && sf::Mouse::isButtonPressed(key);
}
