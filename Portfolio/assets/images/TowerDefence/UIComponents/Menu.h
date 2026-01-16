//
// Created by kfrai on 2025-02-28.
//

#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Button;
class Cell;

class Menu {
private:
    sf::Color outlineColor;
    sf::Color backgroundColor;
    sf::Color textColor;
    sf::Color closeColor;
    sf::Color BTcolor;
    sf::Color STcolor;
    sf::Color WTcolor;

    sf::Font font;

    sf::RenderWindow *window;

    sf::RectangleShape container;
    sf::RectangleShape innerContainer1;
    sf::RectangleShape innerContainer2;
    sf::RectangleShape innerContainer3;
    sf::Text title;
    Button *Close, *BTpurchase, *STpurchase, *WTpurchase, *Upgrade, *Refund;
    sf::Text BTstatText, STstatText, WTstatText, currStatText, upgradeStatText, refundStatText;
    sf::CircleShape BTicon, STicon, WTicon, BTicon2, STicon2, WTicon2, BTicon3, STicon3, WTicon3;

    enum State {
        PURCHASE = 1,
        BOMBERTOWER = 2,
        SNIPERTOWER = 3,
        WIZARDTOWER = 4,
    };

    State state;

public:
    Menu(sf::RenderWindow *window, sf::Font &font);
    ~Menu();

    State checkState(Cell* currCell);
    void displayMenu(Cell* currCell);
    std::vector<Button*> getButtons();
    void disableButtons();
};



#endif //MENU_H
