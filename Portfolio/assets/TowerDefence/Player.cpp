//
// Created by kfrai on 2025-02-13.
//

#include "Player.h"

#include <iostream>

#include "Map.h"
#include "Tower.h"
#include "TowerStats.h"

Player::Player() : coinBalance(0), lives(5) {}


Player::Player(int coinBalance, int lives) : coinBalance(coinBalance), lives(lives) {}

Player::~Player() {
    towers.clear();
}

void Player::loseLife(int amount) {
    lives -= amount;
    if (lives <= 0) {
        lives = 0;
        std::cout << "Game Over! You have lost all your lives.\n";
        handleGameOver();  // Call the game-over function
    } else {
        std::cout << "You lost " << amount << " life/lives. Remaining life/lives: " << lives << std::endl;
    }
}
void Player::handleGameOver() {
    std::cout << "Would you like to restart the game? (y/n): ";
    char choice;
    std::cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        restartGame();
    } else {
        std::cout << "Exiting game...\n";
        exit(0);  // Stop the program
    }
}
void Player::restartGame() {
    std::cout << "Restarting game...\n";
    std::cout << "Exiting game...\n"; // Can implement proper restart not really need
    exit(0);
}




int Player::getLives() const {
    return lives;
}

bool Player::isAlive() const {
    return lives > 0;
}

bool ::Player::checkBalance(int cost) {
    if (coinBalance >= cost) {
        coinBalance -= cost;
        return true;
    } else {
        std::cout << "Not enough coins for this purchase!\n";
        return false;
    }
}

bool Player::makePurchase(int cost, std::unique_ptr<Tower> t) {
    if (!t) {
        std::cout << "Error: Attempted to purchase a nullptr tower!" << std::endl;
        return false;
    }
    if (checkBalance(cost)) {
        t->purchase();
        std::cout << "Purchased: " << t->getName() << std::endl; // Debugging

        t->printInfo();
        t->getMap()->displayMapWithRange();
        towers.push_back(std::move(t));
        return true;
    }
    return false;
}


bool Player::refundTower(Tower* t) {
    refundPlayer((t)->getRefundAmt());
    for (auto it = towers.begin(); it != towers.end(); ++it) {
        if (it->get() == t) {
            towers.erase(it);
            return true;
        }
        TowerStats::removeTower(t);
    }
    return false;
}

void Player::setCoinBalance(int coinBalance) {
    this->coinBalance = coinBalance;
}

void Player::refundPlayer(int refundAmt) {
    coinBalance += refundAmt;
}

int Player::getCoinBalance() {
    return coinBalance;
}

bool Player::upgradeTower() {
    std::cout << "Choose tower to upgrade:\n";
    if (towers.empty()) {
        std::cout << "   No towers found!\n";
        return false;
    } else {
        int i = 1;
        for (const std::unique_ptr<Tower> &tower: towers) {
            std::cout << "   " << i << ": " << tower->getName() << " - Level: " << tower->getLevel() << "\n";
            i++;
        }
        int choice = input("~ Enter Choice: ", 1, i - 1);
        if (towers[choice - 1]) {
            towers[choice - 1]->upgrade();
            towers[choice - 1]->printInfo();
            return true;
        } else {
            std::cout << "Invalid tower selected!\n";
            return false;
        }
    }
}

void Player::updatePlayersTowers() {
    if (!towers.empty()) {
        for (const std::unique_ptr<Tower> &tower: towers) {
            tower->checkRange();
        }
    }
}

void Player::printInfo() {
    std::cout << "------- Player Info: -------\n"
            << "Coins: " << coinBalance << "\n"
            << "Towers: \n";
    if (towers.empty()) {
        std::cout << "   No towers found!\n";
    } else {
        int i = 1;
        for (const std::unique_ptr<Tower> &tower: towers) {
            std::cout << "   " << i << ": " << tower->getName() << " - Level: " << tower->getLevel() << "\n";
            i++;
        }
    }
    std::cout << "----------------------------\n\n";
}

int Player::input(std::string message, int param1, int param2) {
    int input;
    while (true) {
        std::cout << message;
        std::cin >> input;
        if (input >= param1 && input <= param2) {
            return input;
        }
        std::cout << "Invalid input" << std::endl;
    }
}

void Player::loseCoins(int c) {
    coinBalance -= c;
}
