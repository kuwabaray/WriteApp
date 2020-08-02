//
//  Application.hpp
//  Sample2
//
//  Created by yukiya kuwabara on 2020/07/10.
//  Copyright © 2020 yukiya kuwabara. All rights reserved.
//

#ifndef Viewer_hpp
#define Viewer_hpp
#include <iostream>
#include <OpenGL/gl3.h>
#include "Contents.hpp"
#include <vector>


typedef enum state{
    Down,
    Drag,
    Up,
    OFF
} State;


class Viewer{
private:
    GLuint shader;
    GLuint vbo, vao;
    GLuint texture;
    int width, height;
    Contents contents;
    std::vector<Point2D> points;
    State state;
    void copyImageIntoTexture(GLuint* tex);
    void setUpShader();
    void readShaderSource(GLuint shaderObj, const std::string fileName);
public:
    Viewer(){};
    ~Viewer();
    void initiate();
    void write(const State m, const Point2D& p);
    void clear();
};

#endif /* Viewer_hpp */
