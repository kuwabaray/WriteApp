//
//  Contents.hpp
//  Sample2
//
//  Created by yukiya kuwabara on 2020/07/10.
//  Copyright © 2020 yukiya kuwabara. All rights reserved.
//
#ifndef Contents_hpp
#define Contents_hpp

#include <stdio.h>
#include <vector>
#include "Line.hpp"


namespace WriteApp {

    class Contents{
    private:
        Point2D bef_point;
        std::vector<Line> lines;
        std::vector<Point2D> lines_points;
    public:
        Contents(){};
        void start_write(const Point2D& p);
        void contine_write(const Point2D& p);
        void end_write(const Point2D& p);
        void organize();
        void clear();
        std::vector<Point2D> get_lines();
    };
}
#endif /* Contents_hpp */
