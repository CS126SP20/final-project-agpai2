# CS 126 Final Project Proposal: Link's Adventures

#### Author : Aniruddha G Pai

## Project Description
My project will be an adaptation of the orginal Legend of Zelda game. In my implementation, the player will not have to complete certain main/side-quests in order to progress further into the game. The game will have enemies that will appear in random screens. The player can either dodge or attack the enemies with a weapon. The world will also have some secret caves, which Link can access to unveil secrets.

## Background/Motivation
My motivation for doing this project lies in the fact that I am a huge fan of the Zelda series, and I have always dreamt of making a game of Zelda. It excites me to work on this project, as it will bring out the Link in me. This Link will help me embark on an adventure to explore different functionalities and external libraries C++ and Cinder has to offer. Completing this project would mean that I would have defeated the final boss.

## Project Development Timelime
The work is split into 3 major categories: engine, graphics, and user interface (UI).

| Week | Engine | Graphics | UI |
|------|--------|----------|----|
|1|Map class can/contains:<ul><li>Different game screens in a map</ul></li>Engine class can/contains:<ul><li>Player's current location</li><li>Possible/Available moves for a player</li><li>Reject invalid moves (e.g. moving through walls, or moving towards a non-existant area)</li></ul>|Game screen displays:<ul><li>Game level or background</li><li>Game character(Link)</li></ul>|User can interact by:<ul><li>Pressing the arrow or WASD keys to move the player</li></ul>|
|2|Map class contains:<ul><li>List of all maps that are read from a text file and its values</ul></li>Engine class contains:<ul><li>The functionality to collect items|Game screen displays:<ul><li>Collectibles and other items</li></ul>|User can interact by:<ul><li>Pressing arrow or WASD keys to move the player to different screens</li></ul>
|3|Monster class contains:<ul><li>Possible movements of monters and its range of attacks</li><li>The functionality to attack enemies</ul></li>Player class contains:<ul><li>Player's current location, player statistics, and inventory|Game screen displays:<ul><li>Enemies(eg: Octoroks)</li><li>Player's inventory/menu screen</li></ul>|User can interact by:<ul><li>Pressing the spacebar key on the keyboard to attack the enemies</li></ul>|
|4|[EXTRAS](#Extensions-Extras-and-More)|[EXTRAS](#Extensions-Extras-and-More)|[EXTRAS](#Extensions-Extras-and-More)|

## External Libraries
To maintain a list of inventory items and player statistics, I will be using a JSON library. Given below is the hyperlink for
the same:

* [JSON Library - header only](https://github.com/nlohmann/json/releases/download/v3.7.3/include.zip) 

## Extensions, Extras, and More
|Extension|What I would have to do ?|
|---------|-----------------|
|Dynamic Changing of screens |Create a set of offset value, which would allow me to change background dynamically with player movement|
|Dungeons and Bosses|Extended implementation of Dynamic changing of screens. I would have to create another vector for all dungeons. Also, I would have to get the right sized image for bosses.|
