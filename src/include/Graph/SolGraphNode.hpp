#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include <iostream>

class SolGraphNode
{
    std::unordered_map<int, int> color;
    std::vector<int> neighbor;
    int e_num = 0;

public:
    void setColor(int poly, int c ,bool set)
    {
        if (c == 3 && set)
            e_num++;
        color[poly] = c;
    }
    bool isInColor(int poly)
    {
        if (color.find(poly) == color.end()){
            return false;
        }
        return true;
    }
    int getColor(int poly) { return color[poly]; }
    std::unordered_map<int, int> &getColorSet() { return color; }
    void setNeighbor(int neigh) { neighbor.emplace_back(neigh); }
    std::vector<int> &getNeighbor() { return neighbor; }
    int getEnum() { return e_num; }
};