#pragma once
#include <string>

class SimilarityChecker {
public:
    virtual int RunAlgorithm(const std::string& a, const std::string& b) = 0;
};

class LevenshteinChecker : public SimilarityChecker {
public:
	int RunAlgorithm(const std::string& a, const std::string& b);
	int levenshtein(const std::string& a, const std::string& b);
};