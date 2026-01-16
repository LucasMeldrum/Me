Assignment 3 - Tower Defence Game - README

Contributors
Lucas Meldrum - 40285386
Oumayma Bennamoun - 40264352
Ethan Logie - 40273449
Katrina Frain - 40249400

Project Overview
This is the third installment of our Tower Defense project for COMP345. The focus here is on Object-Oriented Design Patterns—namely the Strategy, Factory, and Decorator patterns. Our codebase expands on the previous assignments to demonstrate the following:

Tower Strategy Pattern
- Allows towers to switch between targeting strategies (e.g., nearest to tower, nearest to exit, strongest, weakest).

Critter Factory Pattern
- Dynamically creates critters of varying difficulty based on the wave count.

Tower Decorator Pattern
- Enables enhanced tower abilities through “decorators” (e.g. splash damage, burning damage, freezing).

Game Instructions
1. Generate a Map: The game prompts for map width & height (between 5-26).
2. Validation Check: Ensures the path from entry to exit is connected.
3. Tower Management:
- Purchase & place towers on valid positions.
- Upgrade or refund towers.
4. Start the Waves:
- Critters will spawn and follow the path.
- Towers attack critters within range.
5. Earn & Spend Coins:
- Earn coins per defeated critter.
- Use coins to purchase & upgrade towers.
6. Survive the Waves:
- If critters reach the exit, they reduce your coins.
- Creatures get stronger, faster, and steal more money as the waves increase
- Survive multiple waves to win the game.



