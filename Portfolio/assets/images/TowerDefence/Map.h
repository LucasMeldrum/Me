#ifndef MAP_H
#define MAP_H

#include "Cell.h"
#include "Subject.h"
#include <vector>
#include <queue>
#include <SFML/Graphics.hpp>

// New enum for the path shape options.
enum class PathShape {
    L_SHAPE,
    Z_SHAPE,
    S_SHAPE
};

class Tower; // Forward declaration

class Map : public Subject {
private:
    int width, length;
    std::vector<std::vector<Cell>> grid;
    int entryOfX, entryOfY, exitOfX, exitOfY;
    std::vector<Observer*> observers;
    PathShape pathShape; // New member for path shape

    // Helper functions for different shapes.
    void generateLShapePath();
    void generateZShapePath();
    void generateSShapePath();

public:
    // Modified constructor with an optional path shape parameter.
    Map(int w, int l, PathShape shape = PathShape::L_SHAPE);

    // Observer management
    void Attach(Observer* obs) override;
    void Detach(Observer* obs) override;
    void Notify() override;

    // Setters that change the map state
    void setCell(int x, int y, CellType type);
    void setCellTower(int x, int y, Tower *t);
    void setEntry(int x, int y);
    void setExit(int x, int y);

    // Getters
    int getWidth();
    int getLength();
    CellType getCellType(int x, int y) const;
    Cell& getCell(int x, int y);
    int getExitX() const;
    int getExitY() const;

    // Map methods
    void generatePath();
    sf::RectangleShape displayMap(sf::RenderWindow * window);
    std::vector<Cell *> generateCells(sf::RectangleShape);
    void displayMap();
    void displayMapWithRange();
    bool validateMap();

    // Map customization functions
    void toggleCell(int x, int y);
    void setAsEntry(int x, int y);
    void setAsExit(int x, int y);
};

#endif
