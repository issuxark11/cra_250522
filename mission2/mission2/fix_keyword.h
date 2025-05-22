#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
class SimilarityChecker;

struct PointNode {
	string name;
	int point;

	bool operator<(const PointNode& other) const {
		return point < other.point;
	}
};

class fixKeyword
{
public:
	fixKeyword(SimilarityChecker* objSimilarityChecker)
	{
		s_objSimilarityChecker = objSimilarityChecker;
	}

	bool fileInput(const string& file_name);
	string processKeyword(const string& keyword, const string& day);
	int getIndexOfWeekWeekend(const int& indexOfDay);
	int getIndexOfDay(const string& day);
	void reSortingByPoint(const long long int&  max1, const long long int&  max2);
	bool isSimilar(const std::string& a, const std::string& b);
	void setUZ(int uz);
private:
	vector<PointNode> weekWeekendBest[2]; // ����, �ָ�
	vector<PointNode> wholeWeekBest[7]; //�� ~ ��

	int UZ = 9;

	SimilarityChecker* s_objSimilarityChecker;

	const int max_keyword_point = 2100000000;
};