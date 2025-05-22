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

TEST(Group, TC2_fileinput_Fail)
{
	LevenshteinChecker objLevenshteinChecker;
	fixKeyword objFixKeyword(&objLevenshteinChecker);
	bool ret = objFixKeyword.fileInput("no_file.txt");
	EXPECT_EQ(ret, false);
}

TEST(Group, TC3_process)
{
	LevenshteinChecker objLevenshteinChecker;
	fixKeyword objFixKeyword(&objLevenshteinChecker);
	bool ret = objFixKeyword.fileInput("keyword_weekday_500.txt");
	EXPECT_EQ(ret, true);
}

TEST(Group, TC4_max_point)
{
	LevenshteinChecker objLevenshteinChecker;
	fixKeyword objFixKeyword(&objLevenshteinChecker);
	objFixKeyword.setUZ(2100000000);
	bool ret = objFixKeyword.fileInput("keyword_weekday_500.txt");
	EXPECT_EQ(ret, true);
}

TEST(Group, TC5_perfect_hit)
{
	LevenshteinChecker objLevenshteinChecker;
	fixKeyword objFixKeyword(&objLevenshteinChecker);
	objFixKeyword.processKeyword("apple", "monday");
	objFixKeyword.processKeyword("apple", "monday");
	objFixKeyword.processKeyword("apple", "monday");
	objFixKeyword.processKeyword("apple", "monday");
	objFixKeyword.processKeyword("apple", "monday");
	objFixKeyword.processKeyword("apple", "monday");
	
}

TEST(Group, TC6_similar_hit)
{
	LevenshteinChecker objLevenshteinChecker;
	fixKeyword objFixKeyword(&objLevenshteinChecker);
	objFixKeyword.processKeyword("aaaaaaaaaaaaa", "monday");
	objFixKeyword.processKeyword("aaaaaaaaaaaaab", "monday");
}

TEST(Group, TC7_resorting_week_hit)
{
	LevenshteinChecker objLevenshteinChecker;
	fixKeyword objFixKeyword(&objLevenshteinChecker);
	objFixKeyword.processKeyword("aaaaaaaaaaaaa", "monday");
	objFixKeyword.processKeyword("aaaaaaaaaaaaab", "monday");
	objFixKeyword.setUZ(2100000000);
	objFixKeyword.processKeyword("aaaaaaaaaaaaac", "monday");
}

TEST(Group, TC8_resorting_weekend_hit)
{
	LevenshteinChecker objLevenshteinChecker;
	fixKeyword objFixKeyword(&objLevenshteinChecker);
	objFixKeyword.processKeyword("aaaaaaaaaaaaa", "saturday");
	objFixKeyword.processKeyword("aaaaaaaaaaaaab", "saturday");
	objFixKeyword.setUZ(2100000000);
	objFixKeyword.processKeyword("aaaaaaaaaaaaac", "saturday");
}
