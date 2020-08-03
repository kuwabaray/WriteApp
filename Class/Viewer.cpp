//
//  Viewer.cpp
//  Sample2
//
//  Created by yukiya kuwabara on 2020/07/10.
//  Copyright © 2020 yukiya kuwabara. All rights reserved.
//
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include "Viewer.hpp"
#include "MyUtils.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define VERT_FILE "shader.vert"
#define FRAG_FILE "shader.frag"
#define BRUSH_IMAGE "Droplet.png"

#define kBrushScale 6


namespace WriteApp {

    void Viewer::readShaderSource(GLuint shaderObj, const std::string fileName){
        //ファイルの読み込み
        std::string filePath = pathForResource(fileName.c_str());
        std::string shaderFile = filePath;
        std::ifstream ifs(shaderFile);
        if (!ifs)
        {
            std::cout << "error" << std::endl;
        }

        std::string source;
        std::string line;
        while (getline(ifs, line))
        {
            source += line + "\n";
        }

        // シェーダのソースプログラムをシェーダオブジェクトへ読み込む
        const GLchar *sourcePtr = (const GLchar *)source.c_str();
        GLint length = source.length();
        glShaderSource(shaderObj, 1, &sourcePtr, &length);
    }

    void Viewer::copyImageIntoTexture(GLuint* tex){
        
        int n;
        int force_channels = 4;

        unsigned char* image_data = stbi_load (pathForResource(BRUSH_IMAGE), &width, &height, &n, force_channels);
        if (!image_data) {
            std::cerr << "ERROR: could not load"  << BRUSH_IMAGE  << std::endl;
        }
        
        glGenTextures (1, tex);
        glBindTexture (GL_TEXTURE_2D, *tex);
        glActiveTexture (GL_TEXTURE0);
        glTexImage2D (
          GL_TEXTURE_2D,
          0,
          GL_RGBA,
          width,
          height,
          0,
          GL_RGBA,
          GL_UNSIGNED_BYTE,
          image_data
        );
        
        GLenum err;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            std::cout << "glTexImage2D:" <<  err << '\n';
        }
        glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        
        free(image_data);
    }

    void Viewer::setUpShader(){

        // vertex shader
        int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        readShaderSource(vertexShader, VERT_FILE);
        glCompileShader(vertexShader);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        // fragment shader
        int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        readShaderSource(fragmentShader, FRAG_FILE);
        glCompileShader(fragmentShader);
        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        
         // link shaders
        shader = glCreateProgram();
        glAttachShader(shader, vertexShader);
        glAttachShader(shader, fragmentShader);
        glLinkProgram(shader);
         
        // check for linking errors
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
       
        copyImageIntoTexture(&texture);
        glUseProgram (shader);
        glUniform1i(glGetUniformLocation(shader, "tex"), 0);
        glUniform1f(glGetUniformLocation(shader, "pointSize"), (float)(width / kBrushScale));
        glUniform4f(glGetUniformLocation(shader, "color"), 0.0f, 0.0f, 0.0f, 1.0f);
    }

    void Viewer::initiate(){
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        
        glEnable (GL_PROGRAM_POINT_SIZE);
        glPointParameteri (GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT);
        setUpShader();
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    }


    static const GLfloat green[] = { 1.0f, 1.0f, 1.0f, 1.0f };
     

    void Viewer::write(const State m, const Point2D& p){

        if(m == Down){
            contents.start_write(p);
        }
        else if(m == Drag){
            contents.contine_write(p);
        }
        else if(m == Up){
            contents.end_write(p);
        }
        
        points = contents.get_lines();
        long size = points.size();
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER,sizeof(Point2D)*size, &points[0], GL_DYNAMIC_DRAW);
        glBindVertexArray(vao);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        glClearBufferfv(GL_COLOR, 0, green);
        glUseProgram(shader);
        glDrawArrays(GL_POINTS, 0, size-1);
    }



    void Viewer::clear(){
        points.clear();
        contents.clear();
        
        glBindVertexArray(vao);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);
        
        glClearBufferfv(GL_COLOR, 0, green);
        glUseProgram(shader);
    }

    Viewer::~Viewer(){
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteProgram(shader);
    }

}

