//#pragma once
#include "gmock/gmock.h"
#include "SimilarityChecker.h"
#include "fix_keyword.h"

TEST(Group, TC1_filenput_Success)
{
	LevenshteinChecker objLevenshteinChecker;
	fixKeyword objFixKeyword(&objLevenshteinChecker);
	bool ret = objFixKeyword.fileInput("keyword_weekday_500.txt");
	EXPECT_EQ(ret, true);
}

TEST(Group, TC1_fileinput_Fail)
{
	LevenshteinChecker objLevenshteinChecker;
	fixKeyword objFixKeyword(&objLevenshteinChecker);
	bool ret = objFixKeyword.fileInput("no_file.txt");
	EXPECT_EQ(ret, false);
}

TEST(Group, TC1_process)
{
	LevenshteinChecker objLevenshteinChecker;
	fixKeyword objFixKeyword(&objLevenshteinChecker);
	bool ret = objFixKeyword.fileInput("keyword_weekday_500.txt");
	EXPECT_EQ(ret, true);
}