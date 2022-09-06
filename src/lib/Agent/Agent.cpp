#include "Agent/Agent.hpp"
#include "InputDataHandler/Polygon.hpp"
#include "InputDataHandler/InputData.hpp"
#include "Calculator/DistCalculator.hpp"
#include "Calculator/PermuteCalculator.hpp"
#include "Graph/ConflictGraph.hpp"
#include "Graph/SolutionGraph.hpp"
#include "GraphHandler/CfgHandler.hpp"
#include "GraphHandler/SlgHandler.hpp"
#include "ShortestPath/ShortestPath.hpp"
#include <unordered_map>
#include <mutex>

void Agent::getSingleRowAnswer(int row)
{
    indata.sortRow(layout);
    ConflictGraph cfg(indata.getConflictD());
    CfgHandler cfgh(cfg, layout);
    cfgh.setRelation();
    auto con_g = cfg.getCfg();
    SolutionGraph sg;
    SlgHandler sgh(sg, cfg, indata);
    sgh.dummyExt(layout);
    sgh.formCutSet(layout);
    std::vector<bool> cutset_size_num(1000, false);
    auto cutset = sg.getCutSet();
    sg.getCutSetSize(cutset_size_num);
    PermuteCalculator pc;
    std::unordered_map<int, std::unordered_map<std::string, int>> permutesets;
    pc.calculate2(permutesets, cutset_size_num);
    sgh.createSg(layout, permutesets);
    auto sgg = sg.getSolGraph();
    ShortestPath sp;
    sp.shortestPath(layout, sg, indata, row);
}