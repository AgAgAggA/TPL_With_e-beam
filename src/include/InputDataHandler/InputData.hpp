#pragma once
#include "InputDataHandler/Polygon.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
class InputData
{
    std::vector<std::vector<Polygon::Polygon>> layout;
    double conflictD;
    std::vector<std::vector<int>> conflictG;
    std::vector<std::vector<std::vector<int>>> permutesets;
    std::vector<std::vector<double>> rowInfo;

public:
    void insertRowInfo(std::vector<double> &tmp) { rowInfo.emplace_back(tmp); }
    std::vector<std::vector<double>> &getRowInfo() { return rowInfo; };
    void setConflictD(double d) { conflictD = d; }
    double getConflictD() const { return conflictD; }
    void addRow(std::vector<Polygon::Polygon> row) { layout.emplace_back(row); }
    std::vector<std::vector<Polygon::Polygon>> &getLayout()
    {
        return layout;
    }
    void sortRow(std::vector<Polygon::Polygon> &Layout)
    {
        std::sort(Layout.begin(), Layout.end(), [](const Polygon::Polygon &lhs, const Polygon::Polygon &rhs)
                  { return lhs.getBoundary().first < rhs.getBoundary().first; });
    }
    void setPermuteSets(int index, std::vector<std::vector<int>> add) { permutesets[index] = add; }
    void initPermuteSets(std::vector<std::vector<std::vector<int>>> &init) { permutesets = init; }
    std::vector<std::vector<std::vector<int>>> &getPermuteSets() { return permutesets; }
};