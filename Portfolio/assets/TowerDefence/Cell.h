#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>

class Critter;
class Tower;

enum CellType {
    ENTRY = 1,
    SCENERY = 2,
    PATH = 3,
    EXIT = 4,
    CRITTER = 5,
    BOMBERTOWER = 6,
    SNIPERTOWER = 7,
    WIZARDTOWER = 8,
    TOWER = 9,
};


struct Cell {

private:
    int x, y;

    Critter *occupiedByCritter = nullptr;

    sf::Color backgroundColor;
    sf::Color BT;
    sf::Color ST;
    sf::Color WT;

    Tower* tower;

public:

    static float cellSize;

    bool inRangeOfTower;

    CellType cellType;

    Cell(int x, int y, CellType type);

    void setInRangeOfTower(bool inRangeOfTower);

    CellType getCellType();

    int getPoxY();

    int getPosX();

    int getPosY();

    sf::Color getBackgroundColor();

    void setBackgroundColor(sf::Color);

    Critter *getCritter();

    float getSize();

    void setCritter(Critter *critter);

    void removeCritter();

    bool isOccupiedByCritter() const;

    sf::RectangleShape shape;
    sf::CircleShape BTicon;
    sf::CircleShape STicon;
    sf::CircleShape WTicon;

    Tower* getTower();
    void setTower(Tower *tower);

};

#endif
