#pragma once
#include <Graph/SolGraphNode.hpp>
#include <vector>
#include <iostream>
#include <unordered_map>

class SolutionGraph
{
    std::vector<std::vector<int>> cutset;
    std::vector<std::vector<int>> not_duplicate_element;
    std::vector<SolGraphNode> solutiongraph;
    std::vector<int> dup_num;

public:
    const std::vector<std::vector<int>> &getCutSet()
    {
        return cutset;
    }
    const std::vector<std::vector<int>> &getNDuplicate() { return not_duplicate_element; }
    void insertCutSet(std::vector<int> &set) { cutset.emplace_back(set); }
    void insertNDuplicate(std::vector<int> &set) { not_duplicate_element.emplace_back(set); }
    void insertNDuplicate(int x, int y) { not_duplicate_element[x].emplace_back(y); }
    void insertCutSet(int x, int y) { cutset[x].emplace_back(y); }
    void getCutSetSize(std::vector<bool> &cutset_size_num)
    {
        for (auto &cut : cutset)
        {
            int cut_size = cut.size();
            cutset_size_num[cut_size] = true;
        }
    }
    void insertSolGraph(SolGraphNode &node) { solutiongraph.emplace_back(node); }
    std::vector<SolGraphNode> &getSolGraph() { return solutiongraph; }
    std::vector<int> &getDupNum() { return dup_num; }
    void setDupNum(int in) { dup_num.emplace_back(in); }
    void setDupNum(int setn, int in) { dup_num[setn] += in; }
};
