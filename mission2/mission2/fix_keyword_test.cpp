#include "gmock/gmock.h"
#include "fix_keyword.h"

TEST(Group, TC1_filenput_Success)
{
	fixKeyword objFixKeyword;
	bool ret = objFixKeyword.fileInput("keyword_weekday_500.txt");
	EXPECT_EQ(ret, true);
}

TEST(Group, TC1_fileinput_Fail)
{
	fixKeyword objFixKeyword;
	bool ret = objFixKeyword.fileInput("no_file.txt");
	EXPECT_EQ(ret, false);
}

TEST(Group, TC1_process)
{
	fixKeyword objFixKeyword;
	bool ret = objFixKeyword.fileInput("keyword_weekday_500.txt");
	EXPECT_EQ(ret, true);
}