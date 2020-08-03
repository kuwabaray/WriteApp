//
//  Point.hpp
//  Sample2
//
//  Created by yukiya kuwabara on 2020/07/10.
//  Copyright © 2020 yukiya kuwabara. All rights reserved.
//

#pragma once
#ifndef Point_hpp
#define Point_hpp

#include <stdio.h>

namespace WriteApp {

    class Point2D{
        public:
            float x;
            float y;
            Point2D(){
                x = 0;y=0;
            }
            Point2D(float x, float y){
                this->x = x;this->y = y;
            }
        };
}
#endif /* Point_hpp */

