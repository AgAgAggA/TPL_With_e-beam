#include <InputDataHandler/Polygon.hpp>
#include <vector>
#include <utility>
namespace Polygon
{
        void Rect::setCoord(double x1, double y1, double x2, double y2)
        {
                coord1.first = x1;
                coord1.second = y1;
                coord2.first = x2;
                coord2.second = y2;
                center = std::make_pair((x1 + x2) / 2, (y1 + y2) / 2);
                width = (x2 - x1);
                height = (y2 - y1);
        }
        void Polygon::setRect(double x1, double y1, double x2, double y2)
        {
                Rect nRect;
                nRect.setCoord(x1, y1, x2, y2);
                if (x1 < leftBoundary)
                        leftBoundary = x1;
                if (x2 > rightBoundary)
                        rightBoundary = x2;
                rect.emplace_back(nRect);
        }
}