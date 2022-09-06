#include "InputDataHandler/Polygon.hpp"
#include "InputDataHandler/InputData.hpp"
#include "Graph/ConflictGraph.hpp"
#include "GraphHandler/CfgHandler.hpp"
#include "Calculator/DistCalculator.hpp"
#include <vector>
#include <cmath>
#include <iostream>

void CfgHandler::setRelation()
{
    DistCalculator cal;
    int layout_size = layout.size();
    double cfd = cfg.getCfd();
    cal.setCfd(cfd);
    for (int i = 0; i < layout_size; i++)
    {
        for (int j = i + 1; j < layout_size; j++)
        {
            double answer = cal.getDistPolygon(layout[i], layout[j]);
            if ((answer < cfd) || cal.compare_double(answer, cfd))
            {
                cfg.setCf(i, j);
            }
        }
    }
}
