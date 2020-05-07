# Final Project

# Link's Adventures
[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

Read [this document](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html) to understand the project
layout.

**Author**: Aniruddha G Pai - [`agpai2@illinois.edu`](mailto:agpai2@illinois.edu)

![](https://media.giphy.com/media/cLqTwD2BmraK0QxrPI/giphy.gif)

## Disclaimer
THIS GAME IS AN ADAPTATION FROM THE ORIGINAL NES&reg; GAME TITLED "THE LEGEND OF ZELDA&reg;", PRODUCED BY NINTENDO&trade;.
ONLY A PART OF THE GAME HAS BEEN REPRODUCED AND MODIFIED SOLELY TO SUBMIT A PROJECT FOR CS 126 AT THE 
UNIVERSITY OF ILLINOIS AT URBANA-CHAMPAIGN, AND IS NOT INTENDED FOR ANY OTHER USE BY ANYONE.
ALL CHARACTERS, GAME ELEMENTS, AND CONTENT ARE OWNED BY NINTENDO&trade;. NES&reg;, ZELDA&reg;, NINTENDO&reg; ARE
REGISTERED TRADEMARKS OF NINTENDO OF AMERICA INC. NO PART OF THIS GAME MAY BE REPRODUCED, MODIFIED, DISTRIBUTED, OR
COPIED IN ANY FORM WITHOUT EXPRESS WRITTEN PERMISSION. 
ALL RIGHTS RESERVED.

I MAKE NO REPRESENTATION OR WARRANTY AND ASSUME NO LIABILITY WHATSOEVER FOR REPRODUCING THE GAME CONTENT, AS IT 
IS MADE PURELY FOR A COMPUTER SCIENCE PROJECT.

## About
My project is an adaptation from the original NES&reg; game titled "THE LEGEND OF ZELDA&reg;", produced by NINTENDO&trade;. 
Unlike the original game, there won't be an specific side/main-quests that will have to be completed in order to 
progress further into the game. The user playing this game is given an opportunity to explore the world and the hidden 
secrets the game has to offer.

## Installation

### For Windows Users
1. If you don't have Visual Studio, [install Visual Studio](https://docs.microsoft.com/en-us/visualstudio/install/install-visual-studio?view=vs-2017).
2. If you don't have Cinder 0.9.2, [download it](https://libcinder.org/download) and follow the instructions 
   in the setup guide to set up [Cinder + Git](https://libcinder.org/docs/guides/git/index.html). 
3. Install [JSON Library - header only](https://github.com/nlohmann/json/releases/download/v3.7.3/include.zip) and 
   [catchorg/Catch2](https://github.com/catchorg/Catch2.git) and add these libraries to the CMake files. 
4. Clone this repository using git clone https://github.com/CS126SP20/final-project-agpai2.git
5. Build and run the project from Visual Studio. 

### For Mac Users
1. Follow steps 2-4 in installation process for Windows users

## Dependencies
* CMake
* clang/clang++

## External Libraries/Third-party Libraries
For the implementation of this game, I will be using a couple of external/third-party libraries listed below:

* [Cinder](https://github.com/cinder/Cinder) 
* [catchorg/Catch2](https://github.com/catchorg/Catch2.git) 
* [JSON Library - header only](https://github.com/nlohmann/json/releases/download/v3.7.3/include.zip) 

## Documentation
This codebase follows the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) with Doxygen-style 
documentation. You can generate your own HTML version of the documentation, 
see [the guide on the Doxygen page](http://www.doxygen.nl/manual/doxygen_usage.html).

## Game Controls

#### Keyboard

| Key                    | Action                                                      |
|------------------------|-------------------------------------------------------------|
| `W / Up arrow key`     | Move up                                                     |
| `A / Left arrow key`   | Move left                                                   |
| `S / Down arrow key`   | Move down                                                   |
| `D / Right arrow key`  | Move right                                                  |
| `P`                    | Toggle game pause, shows inventory/menu screen              |
| `SPACEBAR`             | Attack with sword                                           |
| `ENTER`                | Skip through the game introduction                          |
| `TAB`                  | Enter the game play after the user enter the name           |
