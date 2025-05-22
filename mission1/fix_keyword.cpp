#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct PointNode {
	string name;
	int point;

	bool operator<(const PointNode& other) const {
		return point < other.point;
	}
};

vector<PointNode> weekWeekendBest[2]; // 주중, 주말
vector<PointNode> wholeWeekBest[7]; //월 ~ 일

int UZ = 9;

// 레벤슈타인 거리 계산 알고리즘 (문자열 유사도 검사)
int levenshtein(const std::string& a, const std::string& b) {
	const size_t len_a = a.size();
	const size_t len_b = b.size();

	std::vector<std::vector<int>> d(len_a + 1, std::vector<int>(len_b + 1));

	for (size_t i = 0; i <= len_a; ++i) d[i][0] = i;
	for (size_t j = 0; j <= len_b; ++j) d[0][j] = j;

	for (size_t i = 1; i <= len_a; ++i) {
		for (size_t j = 1; j <= len_b; ++j) {
			if (a[i - 1] == b[j - 1])
				d[i][j] = d[i - 1][j - 1];
			else
				d[i][j] = 1 + std::min({ d[i - 1][j], d[i][j - 1], d[i - 1][j - 1] });
		}
	}
	return d[len_a][len_b];
}

// 점수 환산
bool similar(const std::string& a, const std::string& b) {
	if (a.empty() && b.empty()) return true;
	if (a.empty() || b.empty()) return false;

	int dist = levenshtein(a, b);
	int max_len = static_cast<int>(std::max(a.length(), b.length()));
	// 유사도 비율 (1.0: 완전히 같음, 0.0: 전혀 다름)
	double similarity = 1.0 - (double)dist / max_len;

	int score = 1 + static_cast<int>(similarity * 99);

	if (score >= 80) return true;
	return false;
}

void reSortingByPoint(const long long int  max1, const long long int  max2)
{
	const int sizeOfDay = 7;
	if (UZ >= 2100000000 || max1 >= 2100000000 || max2 >= 2100000000) {
		UZ = 9;
		for (int i = 0; i < sizeOfDay; i++) {
			int num = 1;
			for (PointNode& node : wholeWeekBest[i]) {
				node.point = num;
				num++;
			}
		}
		for (int i = 0; i < 2; i++) {
			int num = 1;
			for (PointNode& node : weekWeekendBest[i]) {
				node.point = num;
				num++;
			}
		}
	}
}

int getIndexOfDay(const string day)
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

int getIndexOfWeekWeekend(const int indexOfDay)
{
	//평일 / 주말
	int indexOfWeekWeekend = 0;
	if (indexOfDay >= 0 && indexOfDay <= 4) indexOfWeekWeekend = 0;
	else indexOfWeekWeekend = 1;

	return indexOfWeekWeekend;
}

string processKeyword(const string keyword, const string day) {
	
	int indexOfDay = getIndexOfDay(day);
	int indexOfWeekWeekend = getIndexOfWeekWeekend(indexOfDay);

	int point = ++UZ;

	long long int max1 = 0;
	long long int max2 = 0;

	//관리 목록에 존재하는지 확인
	//관리되는 키워드이면 점수가 증가
	bool isPerfectHit = false;

	for (PointNode& node : wholeWeekBest[indexOfDay]) {
		if (node.name == keyword) {
			max1 = node.point + (node.point * 0.1);
			node.point += (node.point * 0.1);
			isPerfectHit = true;
			break;
		}
	}

	for (PointNode& node : weekWeekendBest[indexOfWeekWeekend]) {
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
	for (PointNode& node : wholeWeekBest[indexOfDay]) {
		if (similar(node.name, keyword)) {
			return node.name;
		}
	}

	for (PointNode& node : weekWeekendBest[indexOfWeekWeekend]) {
		if (similar(node.name, keyword)) {
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

void fileInput() {

	try {
		ifstream fin("keyword_weekday_500.txt"); 

		if (!fin) 
			throw std::runtime_error("파일 없음");

		//500개 데이터 입력
		int input_size = 500;
		for (int index = 0; index < input_size; index++) {
			string keyword, day;
			fin >> keyword >> day;
			string ret = processKeyword(keyword, day);
			std::cout << ret << "\n";
		}
	}
	catch (const std::exception& e) {
		std::cerr << "예외 발생: " << e.what() << std::endl;
	}
}

int main() {
	fileInput();
}