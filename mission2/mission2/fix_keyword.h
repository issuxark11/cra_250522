#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Node {
	string w;
	string wk;
};

struct Node2 {
	string name;
	int point;

	bool operator<(const Node2& other) const {
		return point < other.point;
	}
};

class fixKeyword
{
public:
	bool fileInput(const string file_name);
	string processKeyword(const string keyword, const string day);
	int getIndexOfWeekWeekend(const int indexOfDay);
	int getIndexOfDay(const string day);
	void reSortingByPoint(const long long int  max1, const long long int  max2);
	bool similar(const std::string& a, const std::string& b);
	int levenshtein(const std::string& a, const std::string& b);
private:
	vector<Node2> weekWeekendBest[2]; // 林吝, 林富
	vector<Node2> wholeWeekBest[7]; //岿 ~ 老

	int UZ = 9;
};