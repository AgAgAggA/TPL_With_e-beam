#pragma once
#include <functional>
#include <vector>
#include <utility>
#include <cfloat>

namespace Polygon
{
    class Rect
    {
        std::pair<double, double> coord1;
        std::pair<double, double> coord2;
        std::pair<double, double> center;
        double width, height;

    public:
        void setCoord(double x1, double y1, double x2, double y2);
        std::pair<double, double> &getC1() { return coord1; }
        std::pair<double, double> &getC2() { return coord2; }
        std::pair<double, double> &getCenter() { return center; }
        double getWidth() { return width; }
        double getHeight() { return height; }
    };
    class Polygon
    {
        int mask;
        int id;
        std::vector<Rect> rect;
        double leftBoundary = FLT_MAX, rightBoundary = 0.0;

    public:
        std::pair<double, double> getBoundary() const { return std::make_pair(leftBoundary, rightBoundary); }
        void setRBoundary(double b) { rightBoundary = b; }
        void setMask(int mask_id) { mask = mask_id; }
        int getMask() const { return mask; }
        void setId(int pid) { id = pid; }
        int getId() { return id; }
        void setRect(Rect &inRect) { rect.emplace_back(inRect); }
        void setRect(double x1, double y1, double x2, double y2);
        const std::vector<Rect> &getRect() const { return rect; }
    };
}