# Final Project

# The Legend Of Zelda - NES Remake
[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

Read [this document](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html) to understand the project
layout.

**Author**: Aniruddha G Pai - [`agpai2@illinois.edu`](mailto:agpai2@illinois.edu)

![](https://media.giphy.com/media/cLqTwD2BmraK0QxrPI/giphy.gif)

## About
My project is an implementation of a remake on The Legend of Zelda - NES edition. 
Unlike the original game, there won't be an specific side/main-quests that will have to be completed in order to 
progress further into the game. The user playing this game is given an opportunity to explore the world and the hidden 
secrets it has to offer.

## Dependencies

- [clang]
- [cmake]

## External Libraries/Third-party Libraries
For the implementation of this game, I will be using a couple of external/third-party libraries listed below:

* [catchorg/Catch2](https://github.com/catchorg/Catch2.git) 
* [JSON Library - header only](https://github.com/nlohmann/json/releases/download/v3.7.3/include.zip) 

## Controls

#### Keyboard

| Key       | Action                                                      |
|---------- |-------------------------------------------------------------|
| `w`       | Move up                                                     |
| `a`       | Move left                                                   |
| `s`       | Move down                                                   |
| `d`       | Move right                                                  |
| `p`       | Toggle game pause, shows inventory also                     |
| `SPACE`   | Attack with sword                                           |
