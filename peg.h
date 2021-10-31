#pragma once
#include <vector>
#include <bitset>
#include <tuple>

enum class Direction : char
{
  Up = 0,
  Down,
  Right,
  Left,
  Empty,
};

enum class BoardType : char
{
  BoardOne = 0,
  BoardTwo,
  BoardThree,
  BoardFour,
  BoardFive,
};

enum GamePlayer : char
{
  Human = 1,
  Computer
};

enum class FileCommand : char
{
  EMPTY,
  LOAD,
  SAVE
};

using Row = int;
using Column = int;
using UserCommand = std::tuple<Row,Column,Direction>;

const std::string directionMap {"udrl"};
const std::string boardColumnBar7 {"abcdefg"};
const std::string boardColumnBar8 {boardColumnBar7 + 'h'};
const std::string boardColumnBar9 {boardColumnBar8 + 'i'};

extern std::vector<std::bitset<7>> boardOne;
extern std::vector<std::bitset<9>> boardTwo;
extern std::vector<std::bitset<8>> boardThree;
extern std::vector<std::bitset<7>> boardFour;
extern std::vector<std::bitset<9>> boardFive;

const std::vector<std::bitset<7>> boardOneValidCells{0b0011100,
                                                    0b0111110,
                                                    0b1111111,
                                                    0b1111111,
                                                    0b1111111,
                                                    0b0111110,
                                                    0b0011100};

const std::vector<std::bitset<9>> boardTwoValidCells = {  0b000111000,
                                                          0b000111000,
                                                          0b000111000,
                                                          0b111111111,
                                                          0b111111111,
                                                          0b111111111,
                                                          0b000111000,
                                                          0b000111000,
                                                          0b000111000};

const std::vector<std::bitset<8>> boardThreeValidCells = {0b00111000,
                                                          0b00111000,
                                                          0b00111000,
                                                          0b11111111,
                                                          0b11111111,
                                                          0b11111111,
                                                          0b00111000,
                                                          0b00111000};

const std::vector<std::bitset<7>> boardFourValidCells = { 0b0011100,
                                                          0b0011100,
                                                          0b1111111,
                                                          0b1111111,
                                                          0b1111111,
                                                          0b0011100,
                                                          0b0011100};

const std::vector<std::bitset<9>> boardFiveValidCells = { 0b000010000,
                                                          0b000111000,
                                                          0b001111100,
                                                          0b011111110,
                                                          0b111111111,
                                                          0b011111110,
                                                          0b001111100,
                                                          0b000111000,
                                                          0b000010000};
// std::vector<std::bitset<5>> boardSix = {  0b00100,
//                                           0b001100,
//                                           0b001111100,
//                                           0b011111110,
//                                           0b111101111,
//                                           0b011111110,
//                                           0b001111100,
//                                           0b000111000,
//                                           0b000010000};

extern bool loadBoard(const std::string& fileName);
extern bool saveBoard(const std::string& fileName);
extern bool userInteract(UserCommand&);
extern bool isFileCommand(std::string& commandString);
extern FileCommand parseFileCommand(std::string& command);
extern void setBoardType(BoardType type);
extern void setBoardColumnBar(const std::string& bar);
 
 
