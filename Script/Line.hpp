//
//  Line.hpp
//  Sample2
//
//  Created by yukiya kuwabara on 2020/07/10.
//  Copyright © 2020 yukiya kuwabara. All rights reserved.
//

#ifndef Line_hpp
#define Line_hpp

#include "Point.hpp"

#include <stdio.h>
#include <vector>


class Line{
private:
    std::vector<Point2D> line;
    Point2D startP;
    Point2D endP;
    int points_size;
public:
    Line(const Point2D& point);
    void set_point(const Point2D& point);
    bool onLine(const Point2D& point) const;
    Point2D startPoint() const;
    Point2D endPoint() const;
    int get_points_size() const;
    std::vector<Point2D> get_points() const;
};

#endif /* Line_hpp */
