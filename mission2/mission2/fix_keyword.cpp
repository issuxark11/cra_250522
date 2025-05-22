#pragma once
#include "fix_keyword.h"
#include "SimilarityChecker.h"

bool fixKeyword::isSimilar(const std::string& a, const std::string& b) {
	if (a.empty() && b.empty()) return true;
	if (a.empty() || b.empty()) return false;

	int dist = s_objSimilarityChecker->RunAlgorithm(a, b);
	int max_len = std::max(a.length(), b.length());
	// 유사도 비율 (1.0: 완전히 같음, 0.0: 전혀 다름)
	double similarity = 1.0 - (double)dist / max_len;

	int score = 1 + static_cast<int>(similarity * 99);

	if (score >= 80) return true;
	return false;
}

void fixKeyword::reSortingByPoint(const long long int & max1, const long long int & max2)
{
	const int sizeOfDay = 7;
	if (UZ >= 2100000000 || max1 >= 2100000000 || max2 >= 2100000000) {
		UZ = 9;
		for (int i = 0; i < sizeOfDay; i++) {
			int num = 1;
			for (Node2& node : wholeWeekBest[i]) {
				node.point = num;
				num++;
			}
		}
		for (int i = 0; i < 2; i++) {
			int num = 1;
			for (Node2& node : weekWeekendBest[i]) {
				node.point = num;
				num++;
			}
		}
	}
}

int fixKeyword::getIndexOfDay(const string& day)
{
	int index = 0;
	if (day == "monday") index = 0;
	if (day == "tuesday") index = 1;
	if (day == "wednesday") index = 2;
	if (day == "thursday") index = 3;
	if (day == "friday") index = 4;
	if (day == "saturday") index = 5;
	if (day == "sunday") index = 6;

	return index;
}

int fixKeyword::getIndexOfWeekWeekend(const int& indexOfDay)
{
	//평일 / 주말
	int indexOfWeekWeekend = 0;
	if (indexOfDay >= 0 && indexOfDay <= 4) indexOfWeekWeekend = 0;
	else indexOfWeekWeekend = 1;

	return indexOfWeekWeekend;
}

string fixKeyword::processKeyword(const string& keyword, const string& day) {
	
	int indexOfDay = getIndexOfDay(day);
	int indexOfWeekWeekend = getIndexOfWeekWeekend(indexOfDay);

	int point = ++UZ;

	long long int max1 = 0;
	long long int max2 = 0;

	//관리 목록에 존재하는지 확인
	//관리되는 키워드이면 점수가 증가
	bool isPerfectHit = false;

	for (Node2& node : wholeWeekBest[indexOfDay]) {
		if (node.name == keyword) {
			max1 = node.point + (node.point * 0.1);
			node.point += (node.point * 0.1);
			isPerfectHit = true;
			break;
		}
	}

	for (Node2& node : weekWeekendBest[indexOfWeekWeekend]) {
		if (node.name == keyword) {
			max2 = node.point + (node.point * 0.1);
			node.point += (node.point * 0.1);
			break;
		}
	}

	if (isPerfectHit == true) {
		return keyword;
	}

	//재정렬 작업
	reSortingByPoint(max1, max2);

	//찰떡 HIT
	for (Node2& node : wholeWeekBest[indexOfDay]) {
		if (isSimilar(node.name, keyword)) {
			return node.name;
		}
	}

	for (Node2& node : weekWeekendBest[indexOfWeekWeekend]) {
		if (isSimilar(node.name, keyword)) {
			return node.name;
		}
	}

	//완벽 HIT / 찰떡 HIT 둘다 아닌경우
	if (wholeWeekBest[indexOfDay].size() < 10) {
		wholeWeekBest[indexOfDay].push_back({ keyword, point });
		std::sort(wholeWeekBest[indexOfDay].begin(), wholeWeekBest[indexOfDay].end());
	}

	if (weekWeekendBest[indexOfWeekWeekend].size() < 10) {
		weekWeekendBest[indexOfWeekWeekend].push_back({ keyword, point });
		std::sort(weekWeekendBest[indexOfWeekWeekend].begin(), weekWeekendBest[indexOfWeekWeekend].end());
	}

	if (wholeWeekBest[indexOfDay].size() == 10) {
		if (wholeWeekBest[indexOfDay].back().point < point) {
			wholeWeekBest[indexOfDay].pop_back();
			wholeWeekBest[indexOfDay].push_back({ keyword, point });
			std::sort(wholeWeekBest[indexOfDay].begin(), wholeWeekBest[indexOfDay].end());
		}
	}

	if (weekWeekendBest[indexOfWeekWeekend].size() == 10) {
		if (weekWeekendBest[indexOfWeekWeekend].back().point < point) {
			weekWeekendBest[indexOfWeekWeekend].pop_back();
			weekWeekendBest[indexOfWeekWeekend].push_back({ keyword, point });
			std::sort(weekWeekendBest[indexOfWeekWeekend].begin(), weekWeekendBest[indexOfWeekWeekend].end());
		}
	}

	return keyword;
}

bool fixKeyword::fileInput(const string& file_name) {

	try {
		ifstream fin(file_name);

		if (!fin) 
			throw std::runtime_error("no file error");

		//500개 데이터 입력
		int input_size = 500;
		for (int index = 0; index < input_size; index++) {
			string keyword, day;
			fin >> keyword >> day;
			string ret = processKeyword(keyword, day);
			std::cout << ret << "\n";
		}

		return true;
	}
	catch (const std::exception& e) {
		std::cerr << "exception happend: " << e.what() << std::endl;
		return false;
	}
}
