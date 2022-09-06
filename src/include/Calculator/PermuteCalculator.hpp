#pragma once
#include <vector>
#include <unordered_map>
#include <string>
class PermuteCalculator
{

public:
    PermuteCalculator() {}
    void calculate2(std::unordered_map<int, std::unordered_map<std::string, int>> &permuteSets, std::vector<bool> &cutset_num);
    std::vector<std::vector<int>> calculate(std::vector<std::vector<bool>> valid_color,std::vector<std::vector<bool>>&, int cutsize,int print);
    std::vector<std::vector<int>> calculate_same(std::vector<bool> valid_color, int cutsize);
};