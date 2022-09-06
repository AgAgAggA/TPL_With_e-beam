#pragma once
#include <vector>
#include <unordered_map>

class ConflictGraph
{
    std::unordered_map<int, std::vector<int>> cfg;
    double conflictD;

public:
    ConflictGraph(double D) : conflictD(D)
    {
        std::unordered_map<int, std::vector<int>> twoDimVector;
    }
    void setCf(int x, int y)
    {
        if (cfg.find(x) == cfg.end())
        {
            std::vector<int> a;
            cfg[x] = a;
        }
        cfg[x].emplace_back(y);
    }
    std::unordered_map<int, std::vector<int>> &getCfg() { return cfg; }
    double getCfd() { return conflictD; }
};