#pragma once
#include "InputDataHandler/Polygon.hpp"
#include "InputDataHandler/InputData.hpp"
#include "Graph/ConflictGraph.hpp"
#include <vector>
class CfgHandler{
    ConflictGraph &cfg;
    std::vector<Polygon::Polygon> layout;
    public:
        CfgHandler(ConflictGraph &inCfg, std::vector<Polygon::Polygon> & inLayout):cfg(inCfg),layout(inLayout){}
        void setRelation();
};