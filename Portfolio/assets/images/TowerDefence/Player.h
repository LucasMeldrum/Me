//
// Created by kfrai on 2025-02-13.
//
#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <algorithm>
#include <memory>

class Tower;

class Player {
private:
    int coinBalance;
    int lives;
    std::vector<std::unique_ptr<Tower>> towers;

public:
    // Move the getter to the public section
    const std::vector<std::unique_ptr<Tower>>& getTowers() const { return towers; }

    Player();
    Player(int coinBalance, int lives = 5);
    ~Player();

    void loseLife(int amount);
    int getLives() const;
    bool isAlive() const;

    static void handleGameOver();
    static void restartGame();

    bool checkBalance(int cost);
    int getCoinBalance();
    bool upgradeTower();
    void updatePlayersTowers();
    void setCoinBalance(int coinBalance);
    bool makePurchase(int cost, std::unique_ptr<Tower> t);
    bool refundTower(Tower* tower);
    void refundPlayer(int refundAmt);
    void printInfo();
    int input(std::string message, int param1, int param2);
    void loseCoins(int c);
};

#endif //PLAYER_H
