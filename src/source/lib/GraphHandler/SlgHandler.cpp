#include "InputDataHandler/InputData.hpp"
#include "GraphHandler/SlgHandler.hpp"
#include "Graph/SolutionGraph.hpp"
#include "Graph/SolGraphNode.hpp"
#include "Calculator/PermuteCalculator.hpp"
#include "Calculator/DistCalculator.hpp"
#include <vector>
#include <iostream>
#include <unordered_map>
#include <string>

void SlgHandler::formCutSet(std::vector<Polygon::Polygon> &layout)
{
    DistCalculator dc;
    dc.setCfd(cg.getCfd());
    int poly_num = layout.size();
    for (int i = 0; i < poly_num; i++)
    {
        double cutline = layout[i].getBoundary().first;
        std::vector<int> cutset;
        std::vector<int> cutlineset;
        cutlineset.emplace_back(i);
        for (int j = 0; j < poly_num; j++)
        {
            double j_left = layout[j].getBoundary().first;
            double j_right = layout[j].getBoundary().second;
            if (j_left > cutline)
                break;
            else if (j_right < cutline)
                continue;
            if (cutline <= j_right && (cutline > j_left || dc.compare_double(cutline, j_left)))
            {
                cutset.emplace_back(j);
                if (dc.compare_double(cutline, j_left) && i != j)
                {
                    cutlineset.emplace_back(j);
                }
            }
        }
        sg.insertCutSet(cutset);
        sg.insertNDuplicate(cutlineset);
    }
}
void SlgHandler::dummyExt(std::vector<Polygon::Polygon> &layout)
{

    auto cfg = cg.getCfg();
    int poly_num = layout.size();

    for (int i = 0; i < poly_num; i++)
    {
        double i_bound = layout[i].getBoundary().first;
        double i_rbound = layout[i].getBoundary().second;
        if (cfg[i].size() != 0)
        {
            auto i_last = cfg[i].back();
            double i_last_bound = layout[i_last].getBoundary().first;

            if (i_last_bound > i_bound && i_rbound < i_last_bound)
            {
                layout[i].setRBoundary(i_last_bound - 0.00005);
            }
        }
    }
}
void construct_conflict(std::vector<std::vector<bool>> &conflict, std::vector<int> &cutlineset, std::unordered_map<int, std::vector<int>> &cfg)
{
    int cutlineset_size = cutlineset.size();
    for (int p = 0; p < cutlineset_size; p++)
    {
        std::vector<bool> c;
        bool flag = false;
        for (int np = p + 1; np < cutlineset_size; np++)
        {
            for (const auto &cf : cfg[cutlineset[p]])
            {
                if (cf == cutlineset[np] && cf != cutlineset[p])
                    flag = true;
            }
            if (flag)
                c.push_back(true);
            else
                c.push_back(false);
        }
        conflict.emplace_back(c);
    }
}
void SlgHandler::createSg(std::vector<Polygon::Polygon> &layout, std::unordered_map<int, std::unordered_map<std::string, int>> &pre_lib)
{
    auto cutsets = sg.getCutSet();
    auto Nduplicate = sg.getNDuplicate();
    std::vector<SolGraphNode> &lsg = sg.getSolGraph();
    auto cfg = cg.getCfg();
    int cutsets_num = cutsets.size(), head = 0, index = 0;
    PermuteCalculator pc;

    for (auto &cutset : cutsets)
    {
        int cutset_num = cutset.size();
        int lsg_size = lsg.size();
        if (index == 0)
        {
            auto cutlineset = Nduplicate[index];
            int cutlineset_size = cutlineset.size();
            lsg_size = lsg.size();
            std::vector<std::vector<bool>> conflict;
            construct_conflict(conflict, cutlineset, cfg);
            std::vector<bool> color(4, true);
            std::vector<std::vector<bool>> valid_color;
            for (int co = 0; co < cutlineset_size; co++)
                valid_color.emplace_back(color);
            auto permutes = pc.calculate(valid_color, conflict, cutset_num,0);
            for (auto &p : permutes)
            {
                SolGraphNode node;
                for (int i = 0; i < cutset_num; i++)
                    node.setColor(cutset[i], p[i], 1);
                sg.insertSolGraph(node);
            }
        }
        if (index == cutsets_num - 1)
        {
            SolGraphNode node;
            sg.insertSolGraph(node);
            lsg_size = lsg.size();
            for (int i = head; i < lsg_size - 1; i++)
            {
                lsg[i].setNeighbor(lsg_size - 1);
            }
            break;
        }
        auto cutlineset = Nduplicate[index + 1];
        int cutline = cutlineset[0];
        int cutlineset_size = cutlineset.size();
        lsg_size = lsg.size();
        auto next_cut = cutsets[index + 1];
        int next_cut_size = next_cut.size();

        std::unordered_map<std::string, int> lib = pre_lib[next_cut_size];
        std::unordered_map<std::string, int> nlib;

        std::vector<std::vector<bool>> conflict;
        // coflict construct
        construct_conflict(conflict, cutlineset, cfg);
        for (int i = head; i < lsg_size; i++)
        {
            std::vector<bool> color(4, true);
            std::vector<std::vector<bool>> valid_color;
            for (int co = 0; co < cutlineset_size; co++)
                valid_color.emplace_back(color);
            auto color_set = lsg[i].getColorSet();
            for (const auto &c : color_set)
            {
                auto now_poly = c.first;
                for (const auto &cf : cfg[now_poly])
                {
                    for (int cl = 0; cl < cutlineset_size; cl++)
                    {
                        if (cf == cutlineset[cl] && (c.second != 3))
                        {
                            valid_color[cl][c.second] = false;
                        }
                    }
                }
            }
            if (cutlineset.size() == 1)
            {
                for (int v = 0; v < 4; v++)
                {
                    std::string check = "";
                    if (valid_color[0][v])
                    {
                        SolGraphNode node;
                        for (auto &c : next_cut)
                        {
                            if (c != cutline)
                            {
                                node.setColor(c, lsg[i].getColor(c), 0);
                                check += std::to_string(lsg[i].getColor(c));
                            }
                        }
                        node.setColor(cutline, v, 1);
                        check += std::to_string(v);
                        if (lib[check] == -1)
                        {
                            sg.insertSolGraph(node);
                            int now = lsg.size() - 1;
                            lsg[i].setNeighbor(now);
                            lib[check] = now;
                        }
                        else
                        {
                            lsg[i].setNeighbor(lib[check]);
                        }
                    }
                }
            }
            else
            {
                if (!lsg[i].isInColor(cutlineset[0]))
                {
                    auto permutes = pc.calculate(valid_color, conflict, cutlineset.size(),1);
                    for (auto &p : permutes)
                    {
                        SolGraphNode node;
                        std::string check = "";
                        int n_index = 0;
                        for (const auto &nd : cutlineset)
                        {
                            node.setColor(nd, p[n_index], 1);
                            check += std::to_string(p[n_index]);
                            n_index++;
                        }
                        for (auto &c : next_cut)
                        {
                            std::vector<int>::iterator it = std::find(cutlineset.begin(), cutlineset.end(), c);
                            if (it == cutlineset.end())
                            {
                                node.setColor(c, lsg[i].getColor(c), 0);
                                check += std::to_string(lsg[i].getColor(c));
                            }
                        }
                        if (nlib.find(check) == nlib.end())
                        {
                            sg.insertSolGraph(node);
                            int now = lsg.size() - 1;
                            lsg[i].setNeighbor(now);
                            nlib[check] = now;
                        }
                        else
                        {
                            lsg[i].setNeighbor(nlib[check]);
                        }
                    }
                }
                else
                {
                    SolGraphNode node;
                    for (auto &c : next_cut)
                    {
                        node.setColor(c, lsg[i].getColor(c), 0);
                    }
                    sg.insertSolGraph(node);
                    int now = lsg.size() - 1;
                    lsg[i].setNeighbor(now);
                }
            }
        }
        head = lsg_size;
        index++;
    }
}