#include "Graph/SolutionGraph.hpp"
#include "InputDataHandler/Polygon.hpp"
#include "InputDataHandler/InputData.hpp"
#include "Graph/SolGraphNode.hpp"
#include "ShortestPath/ShortestPath.hpp"
#include <vector>
#include <queue>
#include <climits>
#include <utility>

typedef std::pair<int, int> iPair;

int Pow(int x, int p)
{
    if (p == 0)
        return 1;
    if (p == 1)
        return x;
    return x * Pow(x, p - 1);
}

void ShortestPath::shortestPath(std::vector<Polygon::Polygon> &layout_R,SolutionGraph &sg, InputData &indata, int row)
{

    auto sol_graph = sg.getSolGraph();
    auto cutsets = sg.getCutSet();
    int node_num = sol_graph.size();
    auto Nduplicate = sg.getNDuplicate();
    std::vector<int> dist(node_num, INT_MAX);
    std::vector<int> pred(node_num, -1);
    std::priority_queue<iPair, std::vector<iPair>, std::greater<iPair>> pq;
    int first_col = Pow(4, cutsets[0].size());
    int en = 0;
    for (int i = 0; i < first_col; i++)
    {
        pq.push(std::make_pair(sol_graph[i].getEnum(), i));
        dist[i] = sol_graph[i].getEnum();
    }
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        auto u_neighbor = sol_graph[u].getNeighbor();
        for (auto &x : u_neighbor)
        {
            int weight = sol_graph[x].getEnum();
            if (dist[x] > dist[u] + weight)
            {
                dist[x] = dist[u] + weight;
                pred[x] = u;
                pq.push(std::make_pair(dist[x], x));
            }
        }
    }
    int back_trace = pred[node_num - 1];
    std::vector<std::vector<Polygon::Polygon>> &layout = indata.getLayout();
    int bias = layout[row][0].getId();
    int index = 0;
    while (back_trace >= 0)
    {
        auto cs = sol_graph[back_trace].getColorSet();
        for (auto &c : cs)
        {
            int id = layout_R[c.first].getId();
            layout[row][id-bias].setMask(c.second);
            //std::cout<<c.second<<" ";
        }
        //std::cout<<" \n-----------------\n";
        back_trace = pred[back_trace];
    }
}