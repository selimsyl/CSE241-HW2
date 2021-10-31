#include <iostream>
#include <array>
#include "peg.h"
#include <iomanip>
#include <limits>
#include <tuple>
#include <functional>
#include <random>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iterator>

std::vector<std::bitset<7>> boardOne = {  0b0011100,
                                          0b0111110,
                                          0b1110111,
                                          0b1111111,
                                          0b1111111,
                                          0b0111110,
                                          0b0011100};

std::vector<std::bitset<9>> boardTwo = {  0b000111000,
                                          0b000111000,
                                          0b000111000,
                                          0b111111111,
                                          0b111101111,
                                          0b111111111,
                                          0b000111000,
                                          0b000111000,
                                          0b000111000};

std::vector<std::bitset<8>> boardThree = {0b00111000,
                                          0b00111000,
                                          0b00111000,
                                          0b11111111,
                                          0b11101111,
                                          0b11111111,
                                          0b00111000,
                                          0b00111000};
std::vector<std::bitset<7>> boardFour = { 0b0011100,
                                          0b0011100,
                                          0b1111111,
                                          0b1110111,
                                          0b1111111,
                                          0b0011100,
                                          0b0011100};
std::vector<std::bitset<9>> boardFive = { 0b000010000,
                                          0b000111000,
                                          0b001111100,
                                          0b011111110,
                                          0b111101111,
                                          0b011111110,
                                          0b001111100,
                                          0b000111000,
                                          0b000010000};

static BoardType currentBoardType;
static std::string boardColumnBar;
static GamePlayer gamePlayer;
static std::function<bool(UserCommand&)> getCommand;
static std::istringstream inputStream;

void printBoard(std::ostream& out = std::cout,bool rowColumn = true)
{
  //print columnbar
  if (rowColumn)
    out << "  " + boardColumnBar << "\n";
  for (size_t i = 0; i < boardColumnBar.size(); ++i)
  {
    if (rowColumn)
      out << i+1 << " ";
    for (size_t k = 0; k < boardColumnBar.size(); ++k){
      switch (currentBoardType)
      {
      case BoardType::BoardOne:
        out << (boardOne.at(i).test(k) ? '*' : ' ');
        break;
      case BoardType::BoardTwo:
        out << (boardTwo.at(i).test(k) ? '*' : ' ');
        break;
      case BoardType::BoardThree:
        out << (boardThree.at(i).test(k) ? '*' : ' ');
      break;
      case BoardType::BoardFour:
        out << (boardFour.at(i).test(k) ? '*' : ' ');
      break;
      case BoardType::BoardFive:
        out << (boardFive.at(i).test(k) ? '*' : ' ');
      break;

      default:
        break;
      }
    }
    out << "\n";
  }
}

void printInputError(const std::string outMessage)
{
  if (!outMessage.empty())
    std::cout << outMessage;
}

template<typename T>
bool getInput(T& input,std::string errorMessage="")
{
  std::cin >> input;
  if (std::cin.fail())
  {
    // std::cout << "cin.fail()\n";
    printInputError(errorMessage);
    return false;
  }
  return true;
}

std::string getInput()
{
  std::string input{};
  if (!std::cin.good())
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
  }
  std::getline(std::cin,input);
  return input;
}

/** 
 * List board types for selection
*/
void listBoardType() {
  // std::cout.fill('-');
  for (unsigned int i = 0; i < 9; i++)
  {
    if (boardOne.size() > i)
    {
      // std::cout << std::setw(0);
      for(int k = boardOne.at(i).size()-1; k >= 0; --k)
      {
        std::cout <<  (boardOne.at(i).test(k) ? '*' : ' ');
      }
    } else {
      for (unsigned int j = 0; j<boardOne.at(0).size();++j)
        std::cout << ' ';
    }
    if (boardTwo.size() > i)
    {
      std::cout << std::setw(10);
      for(int k = boardTwo.at(i).size()-1; k >= 0; --k)
      {
        std::cout  << (boardTwo.at(i).test(k) ? '*' : ' ');
      }
    }else {
      for (unsigned int j = 0; j<boardTwo.at(0).size();++j)
        std::cout << ' ';
    }
    if (boardThree.size() > i)
    {
      std::cout << std::setw(10);
      for(int k = boardThree.at(i).size()-1; k >= 0; --k)
      {
        std::cout << (boardThree.at(i).test(k) ? '*' : ' ');
      }
    }else {
      std::cout << std::setw(10);
      for (unsigned int j = 0; j<boardThree.at(0).size();++j)
        std::cout << ' ';
    }
    if (boardFour.size() > i)
    {
      std::cout << std::setw(10);
      for(int k = boardFour.at(i).size()-1; k >= 0; --k)
      {
        std::cout << (boardFour.at(i).test(k) ? '*' : ' ');
      }
    }
    else {
      std::cout << std::setw(10);
      for (unsigned int j = 0; j<boardFour.at(0).size();++j)
        std::cout << ' ';
    }
    if (boardFive.size() > i)
    {
      std::cout << std::setw(10);
      for(int k = boardFive.at(i).size()-1; k >= 0; --k)
      {
        std::cout << (boardFive.at(i).test(k) ? '*' : ' ');
      }
    }
    else {
      for (unsigned int j = 0; j<boardFive.at(0).size();++j)
        std::cout << ' ';
    }
    std::cout << "\n";
  }
  
  std::cout << std::setw(5) <<  "[1]";
  std::cout << std::setw(17) << "[2]";
  std::cout << std::setw(17) << "[3]";
  std::cout << std::setw(17) << "[4]";
  std::cout << std::setw(17) << "[5]";

  std::cout << "\n\n";

}

void setBoardType(BoardType type)
{
  currentBoardType = type;
}

void setBoardColumnBar(const std::string& bar)
{
  boardColumnBar = bar;
}

bool selectBoardType()
{
  std::cout << std::setw(5) << "Please choose a board type from left to rigth\n"
                                "Enter a number 1 to 5 : ";
  int boardNo = 0;
  while(!getInput(boardNo))
  {
    std::cout << "Please enter a valid board type number : ";
  }
  switch (boardNo)
  {
  case 1:
    setBoardType(BoardType::BoardOne);
    setBoardColumnBar(boardColumnBar7);
  break;
  case 2:
    setBoardType(BoardType::BoardTwo);
    setBoardColumnBar(boardColumnBar9);
  break;
  case 3:
    setBoardType(BoardType::BoardThree);
    setBoardColumnBar(boardColumnBar8);
  break;
  case 4:
    setBoardType(BoardType::BoardFour);
    setBoardColumnBar(boardColumnBar7);
  break;
  case 5:
    setBoardType(BoardType::BoardFive);
    setBoardColumnBar(boardColumnBar9);
  break;

  default:
    return false;
    break;
  }
  return true;
}

void selectGamePlayer()
{
  std::cout << "1-Human\n2-Computer\nChoose player type : ";
  int playerType{};
  while(true)
  {
    while(!getInput(playerType,"Please enter 1 or 2\n"));
    if (playerType == 1 || playerType == 2)
      break;
    else 
      std::cout << "Enter valid number\n";
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
  gamePlayer = static_cast<GamePlayer>(playerType);
}

bool isColumnValid(char column)
{
  auto fresult = boardColumnBar.find(std::tolower(column));
  return fresult != std::string::npos;
}

bool isRowValid(int row)
{
  return row > 0 &&  row <= boardColumnBar.size();
}

bool isSeperatorValid(char seperator)
{
  return seperator == '-';
}

bool isDirectionValid(char direction)
{
  auto fresult = directionMap.find(std::tolower(direction));
  return fresult != std::string::npos;
}

std::istream& operator>>(std::istream& is, Direction& direction)
{
  char directionInput;
  // getInput(directionInput);
  is >> directionInput;

  if (isDirectionValid(directionInput)) {
    direction = static_cast<Direction>(directionMap.find(std::tolower(directionInput)));
  }else{
    is.setstate(std::ios::failbit);
  }
    
  return is;
}

int getRandom(int min,int max)
{
  std::mt19937 generator(std::random_device{}());
  std::uniform_int_distribution<uint_least32_t> distribute(min,max);
  return distribute(generator);
}

UserCommand createRandomCommand()
{
  Row row = 0; 
  Column column = 0;
  Direction direction;
  
  row = getRandom(0,boardColumnBar.size()-1);
  column = getRandom(0,boardColumnBar.size()-1);
  direction = static_cast<Direction>(getRandom(0,3));

  return std::tuple<Row,Column,Direction>{row,column,direction};
}

bool getUserMove(UserCommand& userCommand)
{
  char column = 0;
  int row     = 0;
  char commandSeperator = 0;
  Direction direction = Direction::Empty;
  
  inputStream >> column;  
  if (!inputStream.good() || !isColumnValid(column)) {
    printInputError("Please enter a valid cell column character\n");
    return false;
  }
  
  inputStream >> row;
  if (!inputStream.good() || !isRowValid(row)) {
    printInputError("Please enter a valid cell row number\n");
    return false;
  }

  inputStream >> commandSeperator;
  if(!inputStream.good() || !isSeperatorValid(commandSeperator))
  {
    printInputError("Please enter command proper to (CELL)(ROW)-(DIRECTION) struct\n");
    return false;
  }

  inputStream >> direction;
  if (!inputStream.good()) {
    printInputError("Please enter a valid movement direction\n");
    return false;
  }

  userCommand = std::make_tuple(row-1,boardColumnBar.find(std::tolower(column)),direction);
  return true;
}

bool isPeg(Row row,Column column)
{
  // std::cout << "row : " << row;
  // std::cout << " | column : " << column << "\n";
  try {
    switch (currentBoardType)
    {
    case BoardType::BoardOne:
      return boardOne.at(row).test(column);
    break;
    case BoardType::BoardTwo:
      return boardTwo.at(row).test(column);
    break;
    case BoardType::BoardThree:
      return boardThree.at(row).test(column);
    break;
    case BoardType::BoardFour:
      return boardFour.at(row).test(column);
    break;
    case BoardType::BoardFive:
      return boardFive.at(row).test(column);
    break;
    
    default:
      return false;
      break;
    }
  } catch (std::out_of_range& e) {
    // std::cout << "std::out_of_range exception caught\n";
    return false;
  }
}

bool isJumpedOverCellIsAPeg(Row row, Column column,Direction direction)
{
  switch (direction)
  {
  case Direction::Up:
    return isPeg(row-1,column);
  break;
  case Direction::Down:
    return isPeg(row+1,column);
  break;
  case Direction::Left:
    return isPeg(row,column-1);
  break;
  case Direction::Right:
    return isPeg(row,column+1);
  break;
  default:
    return false;
    break;
  }
}

std::pair<Row,Column> getDestPeg(Row row, Column column,Direction direction)
{
  switch (direction)
  {
  case Direction::Up:
    row -= 2;
  break;
  case Direction::Down:
    row += 2;
  break;
  case Direction::Left:
    column -= 2;
  break;
  case Direction::Right:
    column += 2;
  break;
  default:
    return {};
    break;
  }
  return std::pair<Row,Column>{row,column};
}

bool isDestCellNotAPeg(Row row, Column column,Direction direction)
{
  auto rowColumnPair = getDestPeg(row,column,direction);
  return !isPeg(rowColumnPair.first,rowColumnPair.second);
  // switch (direction)
  // {
  // case Direction::Up:
  //   return !isPeg(row-2,column);
  // break;
  // case Direction::Down:
  //   return !isPeg(row+2,column);
  // break;
  // case Direction::Left:
  //   return !isPeg(row,column-2);
  // break;
  // case Direction::Right:
  //   return !isPeg(row,column+2);
  // break;
  // default:
  //   return false;
  //   break;
  // }
}

bool isDestCellInBorder(Row row, Column column,Direction direction)
{
  auto rowColumnPair = getDestPeg(row,column,direction);
  try {
    switch (currentBoardType)
    {
    case BoardType::BoardOne:
      return boardOneValidCells.at(rowColumnPair.first).test(rowColumnPair.second);
    break;
    case BoardType::BoardTwo:
      return boardTwoValidCells.at(rowColumnPair.first).test(rowColumnPair.second);
    break;
    case BoardType::BoardThree:
      return boardThreeValidCells.at(rowColumnPair.first).test(rowColumnPair.second);
    break;
    case BoardType::BoardFour:
      return boardFourValidCells.at(rowColumnPair.first).test(rowColumnPair.second);
    break;
    case BoardType::BoardFive:
      return boardFiveValidCells.at(rowColumnPair.first).test(rowColumnPair.second);
    break;
    
    default:
      return false;
      break;
    }
  } catch (std::out_of_range& e) {
    // std::cout << "std::out_of_range exception caught\n";
    return false;
  }
}

bool isCommandPegValid(const UserCommand& userCommand)
{
  Row row = std::get<0>(userCommand);
  Column column = std::get<1>(userCommand);
  Direction direction = std::get<2>(userCommand);

  auto ret =  isDestCellInBorder(row,column,direction) && 
              isPeg(row,column) && 
              isJumpedOverCellIsAPeg(row,column,direction) && 
              isDestCellNotAPeg(row,column,direction); 
  return  ret;
}

void setPeg(Row row,Column column)
{
  switch (currentBoardType)
  {
  case BoardType::BoardOne:
    boardOne.at(row).set(column);
    break;
  case BoardType::BoardTwo:
    boardTwo.at(row).set(column);
    break;
  case BoardType::BoardThree:
    boardThree.at(row).set(column);
  break;
  case BoardType::BoardFour:
    boardFour.at(row).set(column);
  break;
  case BoardType::BoardFive:
    boardFive.at(row).set(column);
  break;

  default:
    break;
  }
}

void resetPeg(Row row,Column column)
{
  switch (currentBoardType)
  {
  case BoardType::BoardOne:
    boardOne.at(row).reset(column);
    break;
  case BoardType::BoardTwo:
    boardTwo.at(row).reset(column);
    break;
  case BoardType::BoardThree:
    boardThree.at(row).reset(column);
  break;
  case BoardType::BoardFour:
    boardFour.at(row).reset(column);
  break;
  case BoardType::BoardFive:
    boardFive.at(row).reset(column);
  break;

  default:
    break;
  }
}

void executeCommand(UserCommand& userCommand)
{
  Row row = std::get<0>(userCommand);
  Column column = std::get<1>(userCommand);
  Direction direction = std::get<2>(userCommand);

  resetPeg(row,column);
  switch (direction)
  {
  case Direction::Up:
    setPeg(row-2,column);
    resetPeg(row-1,column);
  break;
  case Direction::Down:
    setPeg(row+2,column);
    resetPeg(row+1,column);
  break;
  case Direction::Left:
    setPeg(row,column-2);
    resetPeg(row,column-1);
  break;
  case Direction::Right:
    setPeg(row,column+2);
    resetPeg(row,column+1);
  break;
  default:
    break;
  }
}

/** 
 * Check a peg has a valid movement to decide whether game is finished
*/
bool isPegMovable(Row row,Column column)
{
  std::tuple<Row,Column,Direction> commandUp{row,column,Direction::Up};
  std::tuple<Row,Column,Direction> commandDown{row,column,Direction::Down};
  std::tuple<Row,Column,Direction> commandLeft{row,column,Direction::Left};
  std::tuple<Row,Column,Direction> commandRight{row,column,Direction::Right};

  if (isCommandPegValid(commandUp) ||
      isCommandPegValid(commandDown) ||
      isCommandPegValid(commandLeft) ||
      isCommandPegValid(commandRight))
    return true;

  return false;
}

bool isGameFinished()
{
  for (size_t i = 0; i < boardColumnBar.size(); ++i)
  {
    for (size_t k = 0; k <boardColumnBar.size(); ++k){
      switch (currentBoardType)
      {
      case BoardType::BoardOne:
        if (boardOne.at(i).test(k) && isPegMovable(i,k)) {
          return false;          
        }
        break;
      case BoardType::BoardTwo:
        if (boardTwo.at(i).test(k) && isPegMovable(i,k)) {
          return false;          
        }
        break;
      case BoardType::BoardThree:
        if (boardThree.at(i).test(k) && isPegMovable(i,k)) {
          return false;          
        }
      break;
      case BoardType::BoardFour:
        if (boardFour.at(i).test(k) && isPegMovable(i,k)) {
          return false;          
        }
      break;
      case BoardType::BoardFive:
        if (boardFive.at(i).test(k) && isPegMovable(i,k)) {
          return false;          
        }
      break;

      default:
        return false;
        break;
      }
    }
  }
  return true;
}

int calculateRemainPegs()
{
  int totalPeg = 0;
  for (size_t i = 0; i < boardColumnBar.size(); ++i)
  {
    for (size_t k = 0; k <boardColumnBar.size(); ++k){
      switch (currentBoardType)
      {
      case BoardType::BoardOne:
        boardOne.at(i).test(k) ? ++totalPeg : totalPeg;
        break;
      case BoardType::BoardTwo:
        boardTwo.at(i).test(k) ? ++totalPeg : totalPeg;
        break;
      case BoardType::BoardThree:
        boardThree.at(i).test(k) ? ++totalPeg : totalPeg;
      break;
      case BoardType::BoardFour:
        boardFour.at(i).test(k) ? ++totalPeg : totalPeg;
      break;
      case BoardType::BoardFive:
        boardFive.at(i).test(k) ? ++totalPeg : totalPeg;
      break;

      default:
        break;
      }
    }
  }
  return totalPeg;
}

/** 
 * Used to print computer generated command
*/
void printCommand(UserCommand& userCommand)
{
  std::cout << "Entered Command : ";
  std::cout << std::toupper(boardColumnBar[static_cast<char>(std::get<1>(userCommand))],std::locale{});
  std::cout << std::get<0>(userCommand)<< '-';
  switch (std::get<2>(userCommand))
  {
  case Direction::Up:
    std::cout << "U";
    break;
  case Direction::Down:
    std::cout << "D";
    break;
  case Direction::Left:
    std::cout << "L";
  break;
  case Direction::Right:
    std::cout << "R";
    break;
  default:
    break;
  }
  std::cout << '\n';
}

bool getComputerMove(UserCommand& userCommand)
{
  UserCommand computerCommand;
  while(true)
  {
    computerCommand = createRandomCommand();
    if(isCommandPegValid(computerCommand))
      break;
  }
  userCommand = computerCommand;

  printCommand(userCommand);
  
  return true;
}

void setInputCommandSource()
{
  getCommand = gamePlayer == Human ? getUserMove : getComputerMove;
}

std::string getFileNameFromCommand(std::string& commandString)
{
  return commandString.substr(commandString.rfind(' ')+1,commandString.rfind(std::string{".txt"}));
}

bool saveBoard(const std::string& fileName)
{
  std::ofstream ofs{fileName,std::ios::binary};
  printBoard(ofs,false);
  ofs << "player:" << gamePlayer << '\n';
  ofs.close();
  std::cout << "Game is saved to " << fileName << "\n"; 
  return true;
}

bool loadBoard(const std::string& fileName)
{
  std::ifstream board{fileName,std::ios::in};
  board >> std::noskipws;
  std::string boardString(std::istream_iterator<char>(board),{});
  auto index = boardString.rfind(std::string{"player"});
  decltype(boardString) playerString = boardString.substr(index);
  decltype(boardString) mapString = boardString.substr(0,index);
  int maxLenght = 0;
  int count = 0;
  
  for(auto&& ch : mapString) {
    if (ch == '\n'){
      if (count > maxLenght)
        maxLenght = count;
      count = 0;
    } else {
      count++;
    }
  }

  auto playerType = std::stoul(playerString.substr(playerString.size()-2));
  gamePlayer = static_cast<GamePlayer>(playerType);

  std::cout << mapString;
  std::cout << playerType;
  std::cout << maxLenght;
  return true;
}

FileCommand parseFileCommand(std::string& command)
{
  std::string str = command.substr(0,4);
  std::transform(str.begin(),str.end(),str.begin(),[](unsigned char ch){
    return std::tolower(ch);
  });

  if (str == std::string{"load"}) {
    return FileCommand::LOAD;
  }
  
  if (str == std::string{"save"}) {
    return FileCommand::SAVE;
  }

  return FileCommand::EMPTY;
}

bool isFileCommand(std::string& commandString)
{
  auto fileName = getFileNameFromCommand(commandString);
  switch (parseFileCommand(commandString))
  {
  case FileCommand::LOAD:
    loadBoard(fileName);
    break;
  case FileCommand::SAVE:
  {
    saveBoard(fileName);  
  }
    break;
  case FileCommand::EMPTY:
    return false;
    break;
  default:
    break;
  }

  return true;
}

bool userInteract(UserCommand& command)
{
  if (!inputStream.good())
  {
    inputStream.clear();
  }
  std::cout << "Please enter command : ";
  std::string commandString = getInput();
  inputStream.str(commandString);
  auto inputStartPos = inputStream.tellg();
  
  if (isFileCommand(commandString)) {
    return false;
  } else {
    inputStream.seekg(std::ios::beg);
  }

  return getCommand(command);
}

int main()
{
  listBoardType();
  while(!selectBoardType());
  //list selected board
  selectGamePlayer();
  setInputCommandSource();
  std::cout << "---------GAME IS ON---------\n";
  printBoard();
  UserCommand userCommand{};

  while(true) {
    while(!userInteract(userCommand));
    if (isCommandPegValid(userCommand)){
      executeCommand(userCommand);
      printBoard();
      if(isGameFinished())
      {
        std::cout << "---------GAME IS FINISHED---------\n";
        std::cout << "Reamainig Pegs : " << calculateRemainPegs() << "\n";
        break;
      }
    } else {
      std::cout << "command valid degil\n";
    }
  }
}