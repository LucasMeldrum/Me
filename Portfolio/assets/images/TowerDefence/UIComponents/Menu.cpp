//
// Created by kfrai on 2025-02-28.
//

#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <cmath>

#include "Button.h"
#include "../BomberTower.h"
#include "../SniperTower.h"
#include "../WizardTower.h"


// Menu for purchasing, upgrading and refunding tower
// Menu appearance changes based on whether the current cell contains a tower already or not
Menu::Menu(sf::RenderWindow *windowInput, sf::Font &font): title(font), BTstatText(font), STstatText(font),
                                                           WTstatText(font), currStatText(font), upgradeStatText(font),
                                                           refundStatText(font),
                                                           font(font),
                                                           window(windowInput),
                                                           state(PURCHASE) {
    // Colors
    outlineColor = sf::Color(0x9B88B4ff);
    backgroundColor = sf::Color::White;
    textColor = sf::Color(0x416363ff);
    closeColor = sf::Color(0xD45555ff);
    BTcolor = sf::Color(0xDD905Fff);
    STcolor = sf::Color(0x44598Cff);
    WTcolor = sf::Color(0xEB7571ff);

    // Setting up shapes
    // Containers
    container.setSize({300, 300});
    container.setOrigin(container.getGeometricCenter());
    container.setPosition({static_cast<float>(window->getSize().x / 2), static_cast<float>(window->getSize().y / 2)});
    container.setFillColor(backgroundColor);
    container.setOutlineColor(outlineColor);
    container.setOutlineThickness(3);

    innerContainer1.setSize({100, 230});
    innerContainer1.setOrigin(innerContainer1.getGeometricCenter());
    innerContainer1.setPosition({
        container.getPosition().x - 100,
        container.getPosition().y + ((container.getSize().y - innerContainer1.getSize().y) / 2)
    });
    innerContainer1.setFillColor(backgroundColor);
    innerContainer1.setOutlineColor(outlineColor);
    innerContainer1.setOutlineThickness(3);

    innerContainer2.setSize({100, 230});
    innerContainer2.setOrigin(innerContainer1.getGeometricCenter());
    innerContainer2.setPosition({
        container.getPosition().x,
        container.getPosition().y + ((container.getSize().y - innerContainer2.getSize().y) / 2)
    });
    innerContainer2.setFillColor(backgroundColor);
    innerContainer2.setOutlineColor(outlineColor);
    innerContainer2.setOutlineThickness(3);

    innerContainer3.setSize({100, 230});
    innerContainer3.setOrigin(innerContainer1.getGeometricCenter());
    innerContainer3.setPosition({
        container.getPosition().x + 100,
        container.getPosition().y + ((container.getSize().y - innerContainer3.getSize().y) / 2)
    });
    innerContainer3.setFillColor(backgroundColor);
    innerContainer3.setOutlineColor(outlineColor);
    innerContainer3.setOutlineThickness(3);

    // Title Text
    title.setCharacterSize(16);
    title.setFillColor(textColor);
    auto center = title.getGlobalBounds().size / 2.f;
    auto localBounds = center + title.getLocalBounds().position;
    auto rounded = sf::Vector2f{std::round(localBounds.x), std::round(localBounds.y)};
    title.setOrigin(rounded);
    title.setPosition(sf::Vector2f(container.getPosition().x - 100, container.getPosition().y - 125));
    title.setString("Purchase");

    // Buttons
    Close = new Button({30, 30}, {container.getPosition().x + 135, container.getPosition().y - 135}, font, "X",
                       closeColor);
    BTpurchase = new Button({84, 36}, {innerContainer1.getPosition().x, innerContainer1.getPosition().y - 20}, font,
                            "Bomber\n Tower", outlineColor);
    STpurchase = new Button({84, 36}, {innerContainer2.getPosition().x, innerContainer2.getPosition().y - 20}, font,
                            "Sniper\n Tower", outlineColor);
    WTpurchase = new Button({84, 36}, {innerContainer3.getPosition().x, innerContainer3.getPosition().y - 20}, font,
                            "Wizard\n Tower", outlineColor);
    Upgrade = new Button({84, 36}, {innerContainer2.getPosition().x, innerContainer2.getPosition().y - 20}, font,
                         "Upgrade", outlineColor);
    Refund = new Button({84, 36}, {innerContainer3.getPosition().x, innerContainer3.getPosition().y - 20}, font,
                        "Refund", outlineColor);

    // Stat texts
    std::ostringstream stream;
    stream.precision(0);
    stream << std::fixed;
    BTstatText.setCharacterSize(8);
    BTstatText.setFillColor(textColor);
    stream << "\nPrice : $" << BomberTower::bPrice
            << "\n\nDamage : " << BomberTower::bDamage
            << "\n\nRate of \nfire : " << BomberTower::bRoF
            << "\n\nRange : " << BomberTower::bRange;
    BTstatText.setString(stream.str());
    center = BTstatText.getGlobalBounds().size / 2.f;
    localBounds = center + BTstatText.getLocalBounds().position;
    rounded = sf::Vector2f{std::round(localBounds.x), std::round(localBounds.y)};
    BTstatText.setOrigin(rounded);
    BTstatText.setPosition(sf::Vector2f(innerContainer1.getPosition().x, innerContainer1.getPosition().y + 45));

    std::ostringstream stream2;
    stream2.precision(0);
    stream2 << std::fixed;
    STstatText.setCharacterSize(8);
    STstatText.setFillColor(textColor);
    stream2 << "\nPrice : $" << SniperTower::sPrice
            << "\n\nDamage : " << SniperTower::sDamage
            << "\n\nRate of \nfire : " << SniperTower::sRoF
            << "\n\nRange : " << SniperTower::sRange;
    STstatText.setString(stream2.str());
    center = STstatText.getGlobalBounds().size / 2.f;
    localBounds = center + STstatText.getLocalBounds().position;
    rounded = sf::Vector2f{std::round(localBounds.x), std::round(localBounds.y)};
    STstatText.setOrigin(rounded);
    STstatText.setPosition(sf::Vector2f(innerContainer2.getPosition().x, innerContainer2.getPosition().y + 45));

    std::ostringstream stream3;
    stream3.precision(0);
    stream3 << std::fixed;
    WTstatText.setCharacterSize(8);
    WTstatText.setFillColor(textColor);
    stream3 << "\nPrice : $" << WizardTower::wPrice
            << "\n\nDamage : " << WizardTower::wDamage
            << "\n\nRate of \nfire : " << WizardTower::wRoF
            << "\n\nRange : " << WizardTower::wRange;
    WTstatText.setString(stream3.str());
    center = WTstatText.getGlobalBounds().size / 2.f;
    localBounds = center + WTstatText.getLocalBounds().position;
    rounded = sf::Vector2f{std::round(localBounds.x), std::round(localBounds.y)};
    WTstatText.setOrigin(rounded);
    WTstatText.setPosition(sf::Vector2f(innerContainer3.getPosition().x, innerContainer3.getPosition().y + 45));

    currStatText.setCharacterSize(8);
    currStatText.setFillColor(textColor);
    center = currStatText.getGlobalBounds().size / 2.f;
    localBounds = center + currStatText.getLocalBounds().position;
    rounded = sf::Vector2f{std::round(localBounds.x), std::round(localBounds.y)};
    currStatText.setOrigin(rounded);
    currStatText.setPosition(sf::Vector2f(innerContainer1.getPosition().x - 45, innerContainer1.getPosition().y));

    upgradeStatText.setCharacterSize(8);
    upgradeStatText.setFillColor(textColor);
    center = upgradeStatText.getGlobalBounds().size / 2.f;
    localBounds = center + upgradeStatText.getLocalBounds().position;
    rounded = sf::Vector2f{std::round(localBounds.x), std::round(localBounds.y)};
    upgradeStatText.setOrigin(rounded);
    upgradeStatText.setPosition(sf::Vector2f(innerContainer2.getPosition().x - 45, innerContainer2.getPosition().y));

    refundStatText.setCharacterSize(8);
    refundStatText.setFillColor(textColor);
    center = refundStatText.getGlobalBounds().size / 2.f;
    localBounds = center + refundStatText.getLocalBounds().position;
    rounded = sf::Vector2f{std::round(localBounds.x), std::round(localBounds.y)};
    refundStatText.setOrigin(rounded);
    refundStatText.setPosition(sf::Vector2f(innerContainer3.getPosition().x - 45, innerContainer3.getPosition().y));

    // Tower shapes
    BTicon.setFillColor(BTcolor);
    BTicon.setRadius(27);
    BTicon.setOrigin(BTicon.getGeometricCenter());
    BTicon.setPosition(sf::Vector2f(innerContainer1.getPosition().x, innerContainer1.getPosition().y - 75));

    STicon.setFillColor(STcolor);
    STicon.setPointCount(3);
    STicon.setRadius(31);
    STicon.setOrigin(STicon.getGeometricCenter());
    STicon.setPosition(sf::Vector2f(innerContainer2.getPosition().x, innerContainer2.getPosition().y - 70));

    WTicon.setFillColor(WTcolor);
    WTicon.setPointCount(5);
    WTicon.setRadius(31);
    WTicon.setOrigin(WTicon.getGeometricCenter());
    WTicon.setPosition(sf::Vector2f(innerContainer3.getPosition().x, innerContainer3.getPosition().y - 75));

    // duplicate icons
    BTicon2 = BTicon;
    BTicon2.setPosition(sf::Vector2f(innerContainer2.getPosition().x, innerContainer2.getPosition().y - 75));
    BTicon3 = BTicon;
    BTicon3.setPosition(sf::Vector2f(innerContainer3.getPosition().x, innerContainer3.getPosition().y - 75));

    STicon2 = STicon;
    STicon2.setPosition(sf::Vector2f(innerContainer1.getPosition().x, innerContainer1.getPosition().y - 70));
    STicon3 = STicon;
    STicon3.setPosition(sf::Vector2f(innerContainer3.getPosition().x, innerContainer3.getPosition().y - 70));

    WTicon2 = WTicon;
    WTicon2.setPosition(sf::Vector2f(innerContainer1.getPosition().x, innerContainer1.getPosition().y - 75));
    WTicon3 = WTicon;
    WTicon3.setPosition(sf::Vector2f(innerContainer2.getPosition().x, innerContainer2.getPosition().y - 75));
}

Menu::~Menu() {
    delete Close;
    delete BTpurchase;
    delete STpurchase;
    delete WTpurchase;
    delete Upgrade;
    delete Refund;
}

// Checks which menu should be displayed based on cell's type
Menu::State Menu::checkState(Cell* currCell) {
    switch (currCell->getCellType()) {
        case 1:
            return PURCHASE;
        case 2:
            return PURCHASE;
        case 3:
            return PURCHASE;
        case 4:
            return PURCHASE;
        case 5:
            return PURCHASE;
        case 6:
            return BOMBERTOWER;
        case 7:
            return SNIPERTOWER;
        case 8:
            return WIZARDTOWER;
        case 9:
            return BOMBERTOWER;
    }
    return PURCHASE;
}

void Menu::displayMenu(Cell* currCell) {
    // Display menu elements common throughout all menus
    window->draw(container);
    window->draw(innerContainer1);
    window->draw(innerContainer2);
    window->draw(innerContainer3);
    window->draw(Close->getShape());
    window->draw(Close->getText());

    switch (checkState(currCell)) {
        case PURCHASE:
            title.setString("Purchase");
            if (!Close->getIsEnabled()) Close->setEnabled(true);
            if (!BTpurchase->getIsEnabled()) BTpurchase->setEnabled(true);
            if (!STpurchase->getIsEnabled()) STpurchase->setEnabled(true);
            if (!WTpurchase->getIsEnabled()) WTpurchase->setEnabled(true);
            if (Upgrade->getIsEnabled()) Upgrade->setEnabled(false);
            if (Refund->getIsEnabled()) Refund->setEnabled(false);

            window->draw(title);
            window->draw(BTpurchase->getShape());
            window->draw(STpurchase->getShape());
            window->draw(WTpurchase->getShape());
            window->draw(BTpurchase->getText());
            window->draw(STpurchase->getText());
            window->draw(WTpurchase->getText());
            window->draw(BTstatText);
            window->draw(STstatText);
            window->draw(WTstatText);
            window->draw(BTicon);
            window->draw(STicon);
            window->draw(WTicon);
            break;
        case BOMBERTOWER:
        case SNIPERTOWER:
        case WIZARDTOWER:
            title.setString(
                checkState(currCell) == BOMBERTOWER ? "Bomber Tower" :
                checkState(currCell) == SNIPERTOWER ? "Sniper Tower" :
                "Wizard Tower");

            if (!Close->getIsEnabled()) Close->setEnabled(true);
            if (BTpurchase->getIsEnabled()) BTpurchase->setEnabled(false);
            if (STpurchase->getIsEnabled()) STpurchase->setEnabled(false);
            if (WTpurchase->getIsEnabled()) WTpurchase->setEnabled(false);
            if (!Upgrade->getIsEnabled()) Upgrade->setEnabled(true);
            if (!Refund->getIsEnabled()) Refund->setEnabled(true);
            window->draw(title);
            window->draw(Upgrade->getShape());
            window->draw(Refund->getShape());
            window->draw(Upgrade->getText());
            window->draw(Refund->getText());

            std::ostringstream stream;
            stream.precision(0);
            stream << std::fixed;
            stream << "Level : " << (currCell->getTower()->getLevel())
                    << "\n\nDamage : " << currCell->getTower()->getDamage()
                    << "\n\nRate of \nfire : " << currCell->getTower()->getRateOfFire()
                    << "\n\nRange : " << currCell->getTower()->getRange();
            currStatText.setString(stream.str());

            std::ostringstream stream2;
            stream2.precision(0);
            stream2 << std::fixed;

            stream2 << "\nPrice : $" << (currCell->getTower()->getUpgradePrice())
                    << "\n\nDamage : " << (currCell->getTower()->getDamageUpgrade())
                    << "\n\nRate of \nfire : " << (currCell->getTower()->getRoFUpgrade())
                    << "\n\nRange : " << (currCell->getTower()->getRangeUpgrade());
            upgradeStatText.setString(stream2.str());

            std::ostringstream stream3;
            stream3.precision(0);
            stream3 << std::fixed;
            stream3 << "\nAmt : $" << (currCell->getTower()->getRefundAmt());
            refundStatText.setString(stream3.str());

            window->draw(currStatText);
            window->draw(upgradeStatText);
            window->draw(refundStatText);

            if (checkState(currCell) == BOMBERTOWER) {
                window->draw(BTicon);
                window->draw(BTicon2);
                window->draw(BTicon3);
            }
            if (checkState(currCell) == SNIPERTOWER) {
                window->draw(STicon);
                window->draw(STicon2);
                window->draw(STicon3);
            }
            if (checkState(currCell) == WIZARDTOWER) {
                window->draw(WTicon);
                window->draw(WTicon2);
                window->draw(WTicon3);
            }
            break;
    }
}

// Returns a vector of buttons attached to menu so that main can add the buttons to its local button vector
// Currently order DOES matter, refer to button menu in main
std::vector<Button*> Menu::getButtons() {
    std::vector<Button*> buttons;
    buttons.push_back(Close);
    buttons.push_back(BTpurchase);
    buttons.push_back(STpurchase);
    buttons.push_back(WTpurchase);
    buttons.push_back(Upgrade);
    buttons.push_back(Refund);
    return buttons;
}
