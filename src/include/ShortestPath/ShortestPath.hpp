#pragma once
#include "Graph/SolutionGraph.hpp"
#include "InputDataHandler/Polygon.hpp"
#include "InputDataHandler/InputData.hpp"
#include <vector>

class ShortestPath{
    public:
        void shortestPath(std::vector<Polygon::Polygon> &layout_R,SolutionGraph &sg ,InputData &indata, int row);


};