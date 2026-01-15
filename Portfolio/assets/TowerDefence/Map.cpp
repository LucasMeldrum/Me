#include "Map.h"
#include "Observer.h"
#include <iostream>
#include <queue>
#include <algorithm>
#include "BomberTower.h"
#include <SFML/Graphics.hpp>

// Constructor: Initializes the grid, sets default entry/exit, and generates the path.
Map::Map(int w, int l, PathShape shape) : width(w), length(l), pathShape(shape), entryOfX(0), entryOfY(0), exitOfX(w - 1), exitOfY(l - 1)
{
    grid.resize(length, std::vector<Cell>(width, Cell(0, 0, SCENERY)));
    // Set each cell as SCENERY initially.
    for (int i = 0; i < length; i++)
        for (int j = 0; j < width; j++)
            grid[i][j] = Cell(j, i, SCENERY);

    // Set default entry and exit points, then generate the path.
    setEntry(0, 0);
    setExit(w - 1, l - 1);
    generatePath();
}


//Shapes for maps
void Map::generatePath() {
    switch (pathShape) {
        case PathShape::L_SHAPE:
            generateLShapePath();
            break;
        case PathShape::Z_SHAPE:
            generateZShapePath();
            break;
        case PathShape::S_SHAPE:
            generateSShapePath();
            break;
        default:
            generateLShapePath();
            break;
    }
    Notify();
}

// L shape implementation (existing logic).
void Map::generateLShapePath() {
    int x = entryOfX, y = entryOfY;
    // Horizontal part
    while (x != exitOfX) {
        setCell(x, y, PATH);
        x += (exitOfX > entryOfX) ? 1 : -1;
    }
    // Vertical part
    while (y != exitOfY) {
        setCell(x, y, PATH);
        y += (exitOfY > entryOfY) ? 1 : -1;
    }
}

// Example Z shape implementation.
void Map::generateZShapePath() {
    // Ensure we're on a fixed 10x10 grid.
    if (width != 10 || length != 10) {
        std::cout << "Z shape only implemented for a 10x10 map. Falling back to L shape.\n";
        generateLShapePath();
        return;
    }

    // Segment 1: Top horizontal segment from (0,0) to (9,0)
    for (int x = 0; x < width; ++x) {
        setCell(x, 0, PATH);
    }

    // Segment 2: Staircase diagonal from top right (9,0) to (2,9)
    // We need to make 7 left moves (from 9 to 2) and 9 down moves (from 0 to 9).
    int curX = 9, curY = 0;
    int leftMovesRequired = 7;
    int downMovesRequired = 9;
    bool moveLeft = true;
    while (leftMovesRequired > 0) {
        if (moveLeft && curX > 2) {
            curX--;
            leftMovesRequired--;
            setCell(curX, curY, PATH);
        } else if (!moveLeft && curY < 9) {
            curY++;
            downMovesRequired--;
            setCell(curX, curY, PATH);
        }
        moveLeft = !moveLeft; // Alternate moves.
    }
    // Once we have reached column 2, finish with the remaining down moves.
    while (curY < 9) {
        curY++;
        downMovesRequired--;
        setCell(curX, curY, PATH);
    }

    // Segment 3: Bottom horizontal segment from (2,9) to (9,9)
    // This fills only the cells from column 2 to 9 in row 9.
    for (int x = 2; x < width; ++x) {
        setCell(x, 9, PATH);
    }
}



// Example S shape implementation.
void Map::generateSShapePath() {
    // For a 10x10 grid only – otherwise, fall back to L shape.
    if (width != 10 || length != 10) {
        std::cout << "S shape only implemented for 10x10 map. Falling back to L shape.\n";
        generateLShapePath();
        return;
    }
    // Horizontal segment: (0,0) to (8,0)
    for (int x = 0; x <= 8; ++x) {
        setCell(x, 0, PATH);
    }
    // Vertical segment: (8,0) to (8,4)
    for (int y = 0; y <= 4; ++y) {
        setCell(8, y, PATH);
    }
    // Horizontal left: (8,4) to (1,4)
    for (int x = 8; x >= 1; --x) {
        setCell(x, 4, PATH);
    }
    // Vertical down: (1,4) to (1,9)
    for (int y = 4; y <= 9; ++y) {
        setCell(1, y, PATH);
    }
    // Horizontal right: (1,9) to (9,9)
    for (int x = 1; x <= 9; ++x) {
        setCell(x, 9, PATH);
    }
}


// Observer management
void Map::Attach(Observer* obs)
{
    observers.push_back(obs);
    std::cout << "Observer attached." << std::endl;
}

void Map::Detach(Observer* obs)
{
    observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    std::cout << "Observer detached." << std::endl;
}

void Map::Notify()
{
    std::cout << "Notifying observers..." << std::endl;
    for (auto obs : observers)
    {
        obs->Update(this);
    }
}


// Sets a cell's type, updates its background color, prints a debug message, and notifies observers.
void Map::setCell(int x, int y, CellType type)
{
    if (x >= 0 && x < width && y >= 0 && y < length)
    {
        grid[y][x].cellType = type;

        // Set background color based on cell type.
        sf::Color pathColor = sf::Color(0x493D30ff);
        sf::Color sceneryColor = sf::Color(0x679865ff);
        if (type == PATH || type == ENTRY || type == CRITTER)
        {
            grid[y][x].setBackgroundColor(pathColor);
        }
        else if (type == EXIT)
        {
            grid[y][x].setBackgroundColor(sf::Color(0x727272ff));
        }
        else
        {
            grid[y][x].setBackgroundColor(sceneryColor);
        }
        Notify();
    }
}

// Sets a tower in a cell (used in GUI mode)
void Map::setCellTower(int x, int y, Tower* t)
{
    if (x >= 0 && x < width && y >= 0 && y < length)
    {
        grid[y][x].setTower(t);
    }
}

// Sets the entry point and updates the corresponding cell.
void Map::setEntry(int x, int y)
{
    entryOfX = x;
    entryOfY = y;
    setCell(x, y, ENTRY);
}

// Sets the exit point and updates the corresponding cell.
void Map::setExit(int x, int y)
{
    exitOfX = x;
    exitOfY = y;
    setCell(x, y, EXIT);
}



// Displays the map in GUI mode: returns a rectangle container representing the map.
sf::RectangleShape Map::displayMap(sf::RenderWindow *window)
{
    // Create a container with size based on the grid dimensions.
    sf::RectangleShape container({static_cast<float>(width) * Cell::cellSize, static_cast<float>(length) * Cell::cellSize});
    container.setFillColor(sf::Color::Green);
    container.setOutlineColor(sf::Color::White);

    int posX = (window->getSize().x / 2) - (width * Cell::cellSize / 2);
    int posY = (window->getSize().y / 2 + window->getSize().y / 8) - (length * Cell::cellSize / 2);
    container.setPosition(sf::Vector2f(posX, posY + 75));

    return container;
}

// Generates cells by positioning each cell's shape relative to the container.
std::vector<Cell *> Map::generateCells(sf::RectangleShape container)
{
    std::vector<Cell *> cells;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < width; j++)
        {
            grid[i][j].shape.setPosition({container.getPosition().x + j * grid[i][j].cellSize, container.getPosition().y + i * grid[i][j].cellSize});
            grid[i][j].BTicon.setPosition({grid[i][j].shape.getPosition().x, grid[i][j].shape.getPosition().y});
            grid[i][j].STicon.setPosition({grid[i][j].shape.getPosition().x, grid[i][j].shape.getPosition().y + 4});
            grid[i][j].WTicon.setPosition({grid[i][j].shape.getPosition().x, grid[i][j].shape.getPosition().y + 2});
            cells.push_back(&grid[i][j]);
        }
    }
    return cells;
}

// Displays the map in the console.
void Map::displayMap()
{
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < width; j++)
        {
            switch (grid[i][j].cellType)
            {
                case SCENERY:
                    std::cout << "o ";
                    break;
                case PATH:
                    std::cout << "x ";
                    break;
                case ENTRY:
                    std::cout << "E ";
                    break;
                case EXIT:
                    std::cout << "L ";
                    break;
                case BOMBERTOWER:
                    std::cout << "B ";
                    break;
                case SNIPERTOWER:
                    std::cout << "S ";
                    break;
                case WIZARDTOWER:
                    std::cout << "W ";
                    break;
                case CRITTER:
                    std::cout << "C ";
                    break;
                default:
                    std::cout << "? ";
                    break;
            }
        }
        std::cout << std::endl;
    }
}

// Displays the map in the console with tower range indicators.
void Map::displayMapWithRange()
{
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (grid[i][j].inRangeOfTower == true &&
                grid[i][j].cellType != BOMBERTOWER &&
                grid[i][j].cellType != SNIPERTOWER &&
                grid[i][j].cellType != WIZARDTOWER)
            {
                if (grid[i][j].cellType == PATH)
                    std::cout << "X ";
                else
                    std::cout << "* ";
            }
            else
            {
                switch (grid[i][j].cellType)
                {
                    case SCENERY:
                        std::cout << "o ";
                        break;
                    case PATH:
                        std::cout << "x ";
                        break;
                    case ENTRY:
                        std::cout << "E ";
                        break;
                    case EXIT:
                        std::cout << "L ";
                        break;
                    case BOMBERTOWER:
                        std::cout << "B ";
                        break;
                    case SNIPERTOWER:
                        std::cout << "S ";
                        break;
                    case WIZARDTOWER:
                        std::cout << "W ";
                        break;
                    default:
                        std::cout << "? ";
                        break;
                }
            }
        }
        std::cout << std::endl;
    }
}

int Map::getWidth()
{
    return width;
}

int Map::getLength()
{
    return length;
}

CellType Map::getCellType(int x, int y) const
{
    if (x >= 0 && x < width && y >= 0 && y < length)
        return grid[y][x].cellType;
    return SCENERY;
}

Cell &Map::getCell(int x, int y)
{
    return grid[y][x];
}

int Map::getExitX() const
{
    return exitOfX;
}

int Map::getExitY() const
{
    return exitOfY;
}

// Validates the map by checking if there is a valid path from the entry to the exit.
bool Map::validateMap()
{
    if (entryOfX == -1 || entryOfY == -1 || exitOfX == -1 || exitOfY == -1)
    {
        std::cout << "Error: Entry or Exit point is missing.\n";
        return false;
    }

    std::vector<std::vector<bool>> visited(length, std::vector<bool>(width, false));
    std::queue<std::pair<int, int>> q;

    q.push({entryOfX, entryOfY});
    visited[entryOfY][entryOfX] = true;

    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();

        if (x == exitOfX && y == exitOfY)
        {
            return true;
        }

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < width && ny >= 0 && ny < length &&
                !visited[ny][nx] &&
                (grid[ny][nx].cellType == PATH || grid[ny][nx].cellType == EXIT))
            {
                visited[ny][nx] = true;
                q.push({nx, ny});
            }
        }
    }

    std::cout << "Error: No valid path from Entry to Exit.\n";
    return false;
}

void Map::toggleCell(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= length)
        return;
    // Toggle between SCENERY and PATH. (You can extend this later if needed.)
    if (grid[y][x].cellType == SCENERY) {
        setCell(x, y, PATH);
    } else if (grid[y][x].cellType == PATH) {
        setCell(x, y, SCENERY);
    }
    // setCell() already calls Notify() so the observers update.
}

void Map::setAsEntry(int x, int y) {
    // You might want to reset the previous entry cell’s type here.
    setEntry(x, y);
}

void Map::setAsExit(int x, int y) {
    setExit(x, y);
}
