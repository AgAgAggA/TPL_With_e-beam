#pragma once
#include "InputDataHandler/Polygon.hpp"
#include <utility>

class DistCalculator
{
    double cfd;

public:
    void setCfd(double cd) { cfd = cd; }
    double getDistPolygon(Polygon::Polygon &ip1, Polygon::Polygon &ip2);
    double getDistRect(Polygon::Rect &rc1, Polygon::Rect &rc2);
    std::pair<double, double> getCenter(Polygon::Rect &rc);
    bool compare_double(double x, double y);
};