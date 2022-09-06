#pragma once
#include "Graph/SolGraphNode.hpp"
#include "Graph/SolutionGraph.hpp"
#include "Graph/ConflictGraph.hpp"
#include "InputDataHandler/InputData.hpp"
#include <vector>
#include <unordered_map>
#include <string>
class SlgHandler
{
    SolutionGraph &sg;
    ConflictGraph &cg;
    InputData &id;
    std::unordered_map<int,int> cutset_back;

public:
    SlgHandler(SolutionGraph &solg, ConflictGraph &cong, InputData &idi) : sg(solg), cg(cong), id(idi) {}
    void formCutSet(std::vector<Polygon::Polygon> &layout);
    void dummyExt(std::vector<Polygon::Polygon> &layout);
    void createSg(std::vector<Polygon::Polygon> &layout,std::unordered_map<int, std::unordered_map<std::string, int>> &);
};