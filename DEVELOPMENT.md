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