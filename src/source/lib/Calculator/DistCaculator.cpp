#include "Calculator/DistCalculator.hpp"
#include "InputDataHandler/Polygon.hpp"
#include <cmath>
#include <utility>
#include <iostream>

bool DistCalculator::compare_double(double x, double y)
{
    if (fabs(x - y) <= 0.00001)
        return true;
    return false;
}
double DistCalculator::getDistPolygon(Polygon::Polygon &p1, Polygon::Polygon &p2)
{
    auto p1Rects = p1.getRect();
    auto p2Rects = p2.getRect();

    double min = 9999999;
    for (auto &p1Rect : p1Rects)
    {
        for (auto &p2Rect : p2Rects)
        {
            double dist = getDistRect(p1Rect, p2Rect);
            if (dist < min && min != -1)
                min = dist;
        }
    }
    return min;
}
double DistCalculator::getDistRect(Polygon::Rect &rc1, Polygon::Rect &rc2)
{
    double min_dist;
    auto c1 = getCenter(rc1);
    auto c2 = getCenter(rc2);
    double rc1Width = rc1.getWidth();
    double rc2Width = rc2.getWidth();
    double rc1Height = rc1.getHeight();
    double rc2Height = rc2.getHeight();
    double Dx = std::abs(c2.first - c1.first);
    double Dy = std::abs(c2.second - c1.second);
    double w_h = (rc1Width + rc2Width) / 2;
    double h_h = (rc1Height + rc2Height) / 2;
    if ((Dx < w_h) && (Dy > h_h || compare_double(Dy,h_h)))
    {
        min_dist = Dy - h_h;
    }

    else if ((Dx >= w_h || compare_double(Dx,w_h)) && (Dy < h_h))
    {
        min_dist = Dx - w_h;
    }

    else if ((Dx > w_h || compare_double(Dx,w_h)) && (Dy >= h_h|| compare_double(Dy,h_h)))
    {
        double delta_x = Dx - w_h;
        double delta_y = Dy - h_h;
        min_dist = std::sqrt(delta_x * delta_x + delta_y * delta_y);
    }
    else
    {
        min_dist = -1;
    }
    return min_dist;
}
std::pair<double, double> DistCalculator::getCenter(Polygon::Rect &rc)
{
    return std::make_pair((rc.getC1().first + rc.getC2().first) / 2, (rc.getC1().second + rc.getC2().second) / 2);
}