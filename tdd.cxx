#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "peg.h"

using namespace testing;

TEST(peg,loadBoard)
{
  std::string str{"anan.txt"};
  EXPECT_TRUE(loadBoard(str));
}

TEST(peg,saveBoard)
{
  std::string str{"test.txt"};
  EXPECT_TRUE(saveBoard(str));
}

TEST(peg,parseFileCommandSAVE)
{
  std::string str{"save file.txt"};
  auto retVal = parseFileCommand(str);
  EXPECT_EQ(retVal,FileCommand::SAVE);
}

TEST(peg,parseFileCommandLOAD)
{
  std::string str{"load file.txt"};
  auto retVal = parseFileCommand(str);
  EXPECT_EQ(retVal,FileCommand::LOAD);
}

TEST(peg,parseFileCommandEMPTY)
{
  std::string str{"123hopfile.txt"};
  auto retVal = parseFileCommand(str);
  EXPECT_EQ(retVal,FileCommand::EMPTY);
}

TEST(peg,isFileCommandFALSE)
{
  std::string str{"1231hopfile.txt"};
  EXPECT_FALSE(isFileCommand(str));
}

TEST(peg,isFileCommand)
{
  setBoardType(BoardType::BoardOne);
  setBoardColumnBar(boardColumnBar7);
  std::string str{"save file.txt"};
  EXPECT_TRUE(isFileCommand(str));
}

TEST(peg,userInteract)
{
  // UserCommand command{};
  // EXPECT_TRUE(userInteract(command));
}
