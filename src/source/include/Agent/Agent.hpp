#pragma once
#include "InputDataHandler/InputData.hpp"
#include "InputDataHandler/Polygon.hpp"
#include <string>
#include <unordered_map>
#include <iostream>
class Agent
{
    std::vector<Polygon::Polygon> layout;
    InputData &indata;

public:
    Agent(InputData &IN,int row) : indata(IN)
    {
        std::vector<std::vector<Polygon::Polygon>> &og_layout = IN.getLayout();
        layout.reserve(og_layout[row].size());
        layout.insert(layout.end(), og_layout[row].begin(), og_layout[row].end());
    }
    void getSingleRowAnswer(int row);
};