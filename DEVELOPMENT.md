# Project Development Log

## Week 1: Including external libraries and implementing basic game designs
1. Added a Box2D cinder block and gflags to Cmakelists.

2. Still exploring additional external libraries required for game design and functionality

3. Created few classes to account for player's location and movement
    * Using arrow keys or WASD keys to move player is still in development

- [x] The User can now move the player(Link) using the arrow keys or WASD keys


4. Working on implementing a game screen for the character(Link)
    * The character must be able to move through free space and not through walls 
    
- [x] The player can now move through free spaces. The player does not move through walls

5. Finally, decided and confirmed to use Box2d for game animations


## Week 2: Placing enemies/items in Overworld and implementing screen transitions
1. Working on implementing screen transitions. That is, the screen should change as the player 
   moves to the next screen
   
- [x] The player can now move to different screens 

2. Developed and modified code in the Map class to account for any general screen change

3. Made a change in code to show Link's movement while moving

4. Wrote test cases for as many testable functions as possible

5. Working on expanding the game map and making most/all caves accessible 

- [x] Expanded the game map towards the first dungeon
- [x] Most caves are now accessible to Link

6. The Player's inventory count shows on the console. Next step is to make it appear on the game screen

## Week 3: Completing the missing elements of game and final touches
1. Not using Box2D to implement any functionality in the game. Instead, using a json library to implement 
   pause menu/player inventory
   
2. Working on placing monsters on game screen and moving them randomly

- [x] The monsters are incorporated into the zeldamaps.txt denoted by M. They now move randomly in the free space

3. Wrote code to make Link attack. Link can attack in all directions

4. Wrote code to display the pause menu. The details to be printed in the pause menu are being printed in the 
   console. Next step would be to display them on the menu

5. Link can now attack the monsters. Attacking the monsters will cause them to disappear from the screen