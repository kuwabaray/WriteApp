//
//  Line.cpp
//  Sample2
//
//  Created by yukiya kuwabara on 2020/07/10.
//  Copyright © 2020 yukiya kuwabara. All rights reserved.
//

#include "Line.hpp"
#include <math.h>
#include <cmath>
#include <iostream>

const float NEIGHBOOR = 0.1;

Line::Line(const Point2D& point){
    startP = point;
    points_size = 0;
    set_point(point);
}

void Line::set_point(const Point2D& point){
    line.push_back(point);
    endP = point;
    points_size++;
}

bool Line::onLine(const Point2D& point) const{
    float a,b,c;
    a = startP.y - endP.y;
    b = endP.x - startP.x;
    c = startP.x*endP.y - endP.x*startP.y;
    double d = std::abs(a*point.x + b*point.y + c)/sqrt(a*a + b*b);
    if(d < NEIGHBOOR){return true;}
    else{return false;}
}

Point2D Line::startPoint() const{
    return startP;
}
Point2D Line::endPoint() const{
    return endP;
}

int Line::get_points_size() const{
    return points_size;
}

std::vector<Point2D> Line::get_points() const{
    return line;
}

