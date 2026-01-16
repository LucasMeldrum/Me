#include <cmath>
#include <iostream>
#include <memory>
#include <thread>
#include <string>

// SFML includes (used only in GUI mode)
#include <SFML/Graphics.hpp>
#include <SFML/Window/Cursor.hpp>

// Game header files
#include "BomberTower.h"
#include "CritterGroupGenerator.h"
#include "CritterStats.h"
#include "Player.h"
#include "Tower.h"
#include "Map.h"
#include "SniperTower.h"
#include "WizardTower.h"
#include "UIComponents/Button.h"
#include "UIComponents/Menu.h"
#include "MapObserver.h"   // Added from your changes
#include "NearestTargetingStrategy.h"
#include "RandomTargetingStrategy.h"
#include "StrongestTargetingStrategy.h"
#include "TowerDecoratorUtility.h"
#include "TowerStats.h"
#include "limits"

// Global variables common to both modes
static Map *map = nullptr;
static Player *player = nullptr;
static int waveCount = 3;
static int currentWave = 1;
static CritterGroupGenerator* generator = nullptr;

// Global flag to determine which mode is running
static bool useGUI = true;

// ------------------------
// Utility and Common Functions
// ------------------------

// Unified PurchaseNewTower function.
// In GUI mode it will update the display afterwards.
void PurchaseNewTower(Player *player, std::pmr::string towerType, int x, int y) {
    if (!player) {
        std::cout << "Error: No player provided!\n";
        return;
    }

    std::unique_ptr<Tower> t = nullptr;
    if (towerType == "BomberTower") {
        t = std::make_unique<BomberTower>(player, x, y);
    } else if (towerType == "SniperTower") {
        t = std::make_unique<SniperTower>(player, x, y);
    } else if (towerType == "WizardTower") {
        t = std::make_unique<WizardTower>(player, x, y);
    } else {
        std::cout << "Invalid tower type!" << std::endl;
        return;
    }

    if (t) {
        int price = t->getPrice();
        if (player->makePurchase(price, std::move(t))) {
        }
        return;
    }
}

// Generates critters; common to both modes.
CritterGroupGenerator* generateCritters(int crittersPerWave) {
    delete generator;
    generator = new CritterGroupGenerator(map, crittersPerWave);
    return generator;
}

// ------------------------
// Console Mode Functions
// ------------------------

// Validates input ensuring an integer is between two bounds.
int input(const std::string& message, int param1, int param2) {
    int value;
    while (true) {
        std::cout << message;
        if (!(std::cin >> value)) {
            // Clear error state and ignore leftover input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input, please try again.\n";
            continue;
        }
        // Ignore any extra characters on the line
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (value >= param1 && value <= param2) {
            return value;
        }
        std::cout << "Invalid input, please try again.\n";
    }
}

void RefundTower() {
    std::cout << "Choose tower to refund:\n";
    const auto& towers = player->getTowers();
    if (towers.empty()) {
        std::cout << "No towers available to refund!\n";
        return;
    }
    int i = 1;
    for (const std::unique_ptr<Tower>& tower : towers) {
        std::cout << "   " << i << ": " << tower->getName() << " - Level: " << tower->getLevel() << "\n";
        i++;
    }
    int choice = player->input("~ Enter tower number to refund: ", 1, i - 1);
    if (!player->refundTower(towers[choice - 1].get())) {
        std::cout << "Tower refund failed!\n";
    }
}



void UpgradeTower() {
    if (!player->upgradeTower())
        std::cout << "Tower upgrade failed!\n";
}

void generateMap() {
    // int w, h;
    // w = input("~ Enter map width (between 5-26): ", 5, 26);
    // h = input("~ Enter map height (between 5-26): ", 5, 26);
    int w = 10;
    int h = 10;


    do {
        int shapeChoice;
        std::cout << "Select map shape:\n1. L Shape\n2. Z Shape\n3. S Shape\n~ Enter choice: ";
        std::cin >> shapeChoice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear leftover newline

        PathShape chosenShape;
        switch (shapeChoice) {
            case 1: chosenShape = PathShape::L_SHAPE; break;
            case 2: chosenShape = PathShape::Z_SHAPE; break;
            case 3: chosenShape = PathShape::S_SHAPE; break;
            default: chosenShape = PathShape::L_SHAPE; break;
        }
        map = new Map(w, h, chosenShape);
        std::cout << "\nGenerated map:\n";
        map->displayMap();

        if (map->validateMap()) {
            std::cout << "Map is valid.\n";
            Tower::setMap(map);
            break;
        } else {
            std::cout << "Invalid map! Regenerating...\n";
            delete map;
        }
    } while (true);
}

void welcomeText() {
    std::cout << "~~~~~ Welcome to TowerDefense! ~~~~~\n"
              << "Let's start by generating a map.\n";
}

void addTower() {
    std::cout << "\nWhat kind of tower would you like to add?\n"
              << "Your coins: " << player->getCoinBalance() << "$\n"
              << "  1. Bomber Tower " << BomberTower::bPrice << "$\n"
              << "  2. Sniper Tower " << SniperTower::sPrice << "$\n"
              << "  3. Wizard Tower " << WizardTower::wPrice << "$\n";
    int choice = input("~ Enter choice: ", 1, 3);
    int xCoord = input("~ Enter X Coordinate: ", 0, (map->getWidth() - 1));
    int yCoord = input("~ Enter Y Coordinate: ", 0, (map->getLength() - 1));
    switch (choice) {
        case 1:
            PurchaseNewTower(player, "BomberTower", xCoord, yCoord);
            break;
        case 2:
            PurchaseNewTower(player, "SniperTower", xCoord, yCoord);
            break;
        case 3:
            PurchaseNewTower(player, "WizardTower", xCoord, yCoord);
            break;
        default:
            std::cout << "Invalid choice!\n";
            break;
    }
}

void waveLoop() {
    generator->spawnWave();
    while (!generator->isWaveCleared()) {
        generator->update();
        generator->displayCritters();
        map->displayMap();
        player->updatePlayersTowers();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    int waveReward = 500 + (currentWave * 150);
    player->setCoinBalance(player->getCoinBalance() + waveReward);
}

void mainMenu() {
    bool cont = true;
    while (cont) {
        std::cout << "\n--- What would you like to do before the next wave? ---\n"
                  << "  1. View my stats\n"
                  << "  2. View the map (without tower ranges)\n"
                  << "  3. View the map (with tower ranges)\n"
                  << "  4. Add a tower\n"
                  << "  5. Upgrade a tower\n"
                  << "  6. Refund a tower\n"
                  << "  7. Begin next wave\n"
                  << "  8. Quit\n"
                  << "-------------------------------------------------------\n";
        int choice = input("~ Enter choice: ", 1, 8);
        switch (choice) {
            case 1:
                player->printInfo();
                break;
            case 2:
                map->displayMap();
                break;
            case 3:
                map->displayMapWithRange();
                break;
            case 4:
                addTower();
                break;
            case 5:
                UpgradeTower();
                break;
            case 6:
                RefundTower();
                break;
            case 7:
                waveLoop();
                break;
            case 8:
                cont = false;
                std::cout << "\nThanks for playing!\n";
                exit(0);
        }
    }
}

void gameManager() {
    while (currentWave <= waveCount) {
        mainMenu();
    }
}

void runConsoleMode() {
    // Set initial coin balance for console mode (per your changes)
    player = new Player(700);
    Critter::setPlayer(player);

    welcomeText();
    generateMap();

    // Attach MapObserver (updates map view on state changes)
    MapObserver mapObserver(map);

    generator = generateCritters(5);
    gameManager();

    delete generator;
    delete player;
    delete map;
}

// ------------------------
// GUI Mode Functions
// ------------------------

// Globals for GUI mode
static unsigned int guiWidth = 1050;
static unsigned int guiHeight = 1050;
static sf::RenderWindow *window = nullptr;
static sf::Font font;

sf::Vector2f round(const sf::Vector2f vector)
{
    return sf::Vector2f{ std::round(vector.x), std::round(vector.y) };
}

void runGUIMode() {
    // Set coin balance for GUI mode (per original main file)
    player = new Player(10000);
    Critter::setPlayer(player);
    int mapSizeX = 20; // Max 20 for now, if want more we need to adjust window size
    int mapSizeY = 10; // Max 10 for now, if want more we need to adjust window size

    // Create the window and load font
    window = new sf::RenderWindow(sf::VideoMode({guiWidth, guiHeight}), "Tower Defense");
    if (!font.openFromFile("fonts/Daydream.ttf")) {
        throw std::runtime_error("Could not open font file");
    }
    window->setFramerateLimit(60);

    // Create UI elements
    std::vector<Button*> buttons;
    sf::Text title(font);
    title.setCharacterSize(24);
    title.setFillColor(sf::Color::White);
    title.setString("Tower Defense");
    auto center = title.getGlobalBounds().size / 2.f;
    auto localBounds = center + title.getLocalBounds().position;
    auto rounded = round(localBounds);
    title.setOrigin(rounded);
    title.setPosition(sf::Vector2f(guiWidth / 2, 50));

    sf::Text playerStats(font);
    playerStats.setCharacterSize(16);
    playerStats.setFillColor(sf::Color::White);
    center = playerStats.getGlobalBounds().size / 2.f;
    localBounds = center + playerStats.getLocalBounds().position;
    rounded = round(localBounds);
    playerStats.setOrigin(rounded);
    playerStats.setPosition(sf::Vector2f(30, 30));

    Button nextWave({100,50},{970,50},font,"Next Wave",sf::Color(0x9B88B4ff));
    buttons.push_back(&nextWave);

    sf::Text towerStats(font);
    towerStats.setCharacterSize(14);
    towerStats.setFillColor(sf::Color::White);
    towerStats.setPosition(sf::Vector2f(30, 150));
    std::string tsStr = "Tower Stats:\n";
    towerStats.setString(tsStr);
    TowerStats towerStatsObj(tsStr);


    sf::Text critterStats(font);
    critterStats.setCharacterSize(14);
    critterStats.setFillColor(sf::Color::White);
    critterStats.setPosition(sf::Vector2f(window->getSize().x - 325, 150));
    std::string csStr = "Critter Stats:\n";
    critterStats.setString(csStr);
    CritterStats critterStatsObj(csStr);


    // Generate the map and set it to the Tower class.
    map = new Map(mapSizeX, mapSizeY);
    sf::RectangleShape mapContainer = map->displayMap(window);
    Tower::setMap(map);
    std::vector<Cell* > cells = map->generateCells(mapContainer);
    generator = generateCritters(5);

    // Create cursors
    sf::Cursor handCursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Hand).value();
    sf::Cursor arrowCursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value();

    // State variables
    bool isMenuOpen = false;
    bool isAnyHovered = false;
    bool isButtonClicked = false;
    Cell* currCell = nullptr;
    Menu* menu = nullptr;
    bool isWaveActive = false;
    sf::Clock waveClock;
    const sf::Time waveUpdateInterval = sf::seconds(1);
    std::unique_ptr<TargetingStrategy> strategy = nullptr;

    // Main game loop
    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window->close();
            } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                window->close();
            }
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        if (isAnyHovered) {
            window->setMouseCursor(handCursor);
        } else {
            window->setMouseCursor(arrowCursor);
        }
        window->clear(sf::Color(0x416363ff));

        window->draw(title);
        playerStats.setString("Player Stats:\nCoins: " + std::to_string(player->getCoinBalance()));
        window->draw(playerStats);
        window->draw(mapContainer);
        tsStr = towerStatsObj.update();
        towerStats.setString(tsStr);
        window->draw(towerStats);
        csStr = critterStatsObj.update();
        critterStats.setString(csStr);
        window->draw(critterStats);

        isAnyHovered = false;
        for (auto& cell : cells) {
            sf::RectangleShape cellShapeAdjustedBounds = cell->shape;
            cellShapeAdjustedBounds.setSize(sf::Vector2f(cell->shape.getSize().x - 6, cell->shape.getSize().y - 6));
            cellShapeAdjustedBounds.setPosition(sf::Vector2f(cell->shape.getPosition().x + 3, cell->shape.getPosition().y + 3));

            if (!isWaveActive && !isMenuOpen &&
                cellShapeAdjustedBounds.getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y)) &&
                cell->cellType != ENTRY && cell->cellType != EXIT && cell->cellType != PATH) {
                sf::Color hoverColor = cell->getBackgroundColor();
                hoverColor.r = std::min(255, hoverColor.r - 20);
                hoverColor.g = std::min(255, hoverColor.g - 20);
                hoverColor.b = std::min(255, hoverColor.b - 20);
                cell->shape.setFillColor(hoverColor);

                isAnyHovered = true;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !isButtonClicked) {
                    currCell = cell;
                    isButtonClicked = true;
                }
            } else {
                cell->shape.setFillColor(cell->getBackgroundColor());
            }
            window->draw(cell->shape);
            if (cell->cellType == BOMBERTOWER) {
                window->draw(cell->BTicon);
            }
            if (cell->cellType == SNIPERTOWER) {
                window->draw(cell->STicon);
            }
            if (cell->cellType == WIZARDTOWER) {
                window->draw(cell->WTicon);
            }
            Critter* critter = cell->getCritter();
            if (critter != nullptr && critter->getShape() != nullptr) {
                sf::Vector2f newPos = cell->shape.getPosition();
                newPos += sf::Vector2f(cell->shape.getSize().x / 2, cell->shape.getSize().y / 2);
                critter->getShape()->setPosition(newPos);
                window->draw(*critter->getShape());
            }
        }

        for (auto& button : buttons) {
            if (button->hover(sf::Vector2f(mousePos.x, mousePos.y), window)) {
                isAnyHovered = true;
            }
            button->click(sf::Vector2f(mousePos.x, mousePos.y), sf::Mouse::Button::Left, window);
        }

        if (currCell != nullptr) {
            if (menu == nullptr) {
                menu = new Menu(window, font);
                std::vector<Button*> tempButtons = menu->getButtons();
                for (auto& button : tempButtons) {
                    buttons.push_back(button);
                }
            }
            isMenuOpen = true;
            menu->displayMenu(currCell);
        }

        // Menu closing (example: if second button is clicked, close menu)
        if (isMenuOpen && buttons[1]->click(sf::Vector2f(mousePos.x, mousePos.y), sf::Mouse::Button::Left, window)) {
            currCell = nullptr;
            isMenuOpen = false;
        }

        // Purchasing Towers
        if (isMenuOpen && currCell != nullptr && buttons[2]->click(sf::Vector2f(mousePos.x, mousePos.y), sf::Mouse::Button::Left, window) && !isButtonClicked) {
            PurchaseNewTower(player, "BomberTower", currCell->getPosX(), currCell->getPosY());
            strategy = std::make_unique<NearestTargetingStrategy>();
            currCell->getTower()->setTargetingStrategy(std::move(strategy));
            currCell = nullptr;
            isMenuOpen = false;
            isButtonClicked = true;
        }
        if (isMenuOpen && currCell != nullptr && buttons[3]->click(sf::Vector2f(mousePos.x, mousePos.y), sf::Mouse::Button::Left, window) && !isButtonClicked) {
            PurchaseNewTower(player, "SniperTower", currCell->getPosX(), currCell->getPosY());
            strategy = std::make_unique<StrongestTargetingStrategy>();
            currCell->getTower()->setTargetingStrategy(std::move(strategy));
            currCell = nullptr;
            isMenuOpen = false;
            isButtonClicked = true;
        }
        if (isMenuOpen && currCell != nullptr && buttons[4]->click(sf::Vector2f(mousePos.x, mousePos.y), sf::Mouse::Button::Left, window) && !isButtonClicked) {
            PurchaseNewTower(player, "WizardTower", currCell->getPosX(), currCell->getPosY());
            strategy = std::make_unique<RandomTargetingStrategy>();
            currCell->getTower()->setTargetingStrategy(std::move(strategy));
            currCell = nullptr;
            isMenuOpen = false;
            isButtonClicked = true;
        }
        // Upgrading and refunding towers using menu buttons (indices 5 and 6)
        if (isMenuOpen && currCell != nullptr && buttons[5]->click(sf::Vector2f(mousePos.x, mousePos.y), sf::Mouse::Button::Left, window) && !isButtonClicked) {
            currCell->getTower()->upgrade();
            Tower* tower = currCell->getTower();
            if (currCell->cellType == BOMBERTOWER) {
                applyDecorator(tower, "splash");
            }
            else if (currCell->cellType == SNIPERTOWER) {
                applyDecorator(tower, "burning");
            }
            else if (currCell->cellType == WIZARDTOWER) {
                applyDecorator(tower, "freezing");
            }
            currCell = nullptr;
            isMenuOpen = false;
            isButtonClicked = true;
        }
        if (isMenuOpen && currCell != nullptr && buttons[6]->click(sf::Vector2f(mousePos.x, mousePos.y), sf::Mouse::Button::Left, window) && !isButtonClicked) {
            player->refundTower(currCell->getTower());
            currCell = nullptr;
            isMenuOpen = false;
            isButtonClicked = true;
        }
        // Next wave button handling
        if (buttons[0]->click(sf::Vector2f(mousePos.x, mousePos.y), sf::Mouse::Button::Left, window) && !isButtonClicked) {
            if (!isWaveActive) {
                generator->spawnWave();
                waveClock.restart();
                isWaveActive = true;
                isButtonClicked = true;
            }
        }
        if (isWaveActive) {
            buttons[0]->setEnabled(false);
            if (waveClock.getElapsedTime() >= waveUpdateInterval) {
                generator->update();
                player->updatePlayersTowers();
                waveClock.restart();
            }
            if (generator->isWaveCleared()) {
                int waveReward = 500 + (currentWave * 150);
                player->setCoinBalance(player->getCoinBalance() + waveReward);
                isWaveActive = false;
            }
        } else {
            buttons[0]->setEnabled(true);
            window->draw(buttons[0]->getShape());
            window->draw(buttons[0]->getText());
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false && isButtonClicked) {
            isButtonClicked = false;
        }
        window->display();
    }
    delete generator;
    delete menu;
    delete player;
    delete map;
    delete window;
}

// ------------------------
// Main Function
// ------------------------

int main() {
    std::cout << "Select game mode:\n 1. GUI Mode\n 2. Console Mode\n~ Enter choice: ";
    int mode;
    std::cin >> mode;
    if (mode == 1) {
        useGUI = true;
        runGUIMode();
    } else {
        useGUI = false;
        runConsoleMode();
    }
    return 0;
}
