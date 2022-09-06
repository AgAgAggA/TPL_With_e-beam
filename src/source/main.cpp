#include <iostream>
#include "InputDataHandler/Polygon.hpp"
#include "InputDataHandler/Parser.hpp"
#include "InputDataHandler/InputData.hpp"
#include "Calculator/DistCalculator.hpp"
#include "Calculator/PermuteCalculator.hpp"
#include "Graph/ConflictGraph.hpp"
#include "Graph/SolutionGraph.hpp"
#include "GraphHandler/CfgHandler.hpp"
#include "GraphHandler/SlgHandler.hpp"
#include "ShortestPath/ShortestPath.hpp"
#include "Agent/Agent.hpp"
#include <string>
#include <cassert>
#include <unordered_map>
#include <chrono>
#include <thread>

int main(int argc, char *argv[])
{
    assert(argc == 4);
    InputData inputdata;
    Parser parser;
    parser.read_file(inputdata, argv);
    auto Layout = inputdata.getLayout();
    int layout_size = Layout.size();
    const auto processor_count = std::thread::hardware_concurrency();
    std::cout << "parallel (" << processor_count << " threads):" << std::endl;
    std::vector<std::thread> threads(processor_count);
    for (std::size_t t = 0; t < processor_count; t++)
    {
        threads[t] = std::thread(std::bind(
            [&](const int bi, const int ei, const int t)
            {
                for (int i = bi; i < ei; i++)
                {
                    {
                        Agent agent(inputdata, i);
                        agent.getSingleRowAnswer(i);
                    }
                }
            },
            t * layout_size / processor_count, (t + 1) == processor_count ? layout_size : (t + 1) * layout_size / processor_count, t));
    }
    std::for_each(threads.begin(), threads.end(), [](std::thread &x)
                  { x.join(); });
    parser.output_file(inputdata, argv);
    return 0;
}