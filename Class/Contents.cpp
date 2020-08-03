//
//  Contents.cpp
//  Sample2
//
//  Created by yukiya kuwabara on 2020/07/10.
//  Copyright © 2020 yukiya kuwabara. All rights reserved.
//
#include "Contents.hpp"
#include <iostream>

namespace WriteApp {

    void Contents::start_write(const Point2D& p){
        Line new_line(p);
        lines.push_back(new_line);
        lines_points.push_back(p);
        
    }

    void Contents::contine_write(const Point2D& p){
        lines.back().set_point(p);
        lines_points.push_back(p);
    }

    void Contents::end_write(const Point2D& p){
        lines.back().set_point(p);
        lines_points.push_back(p);
    }

    void Contents::clear(){
        lines.clear();
        lines_points.clear();
    }

    std::vector<Point2D> Contents::get_lines() {
        return lines_points;
    }
}
    
