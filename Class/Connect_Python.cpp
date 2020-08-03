//
//  Connect_Python.cpp
//  Sample2
//
//  Created by yukiya kuwabara on 2020/07/13.
//  Copyright © 2020 yukiya kuwabara. All rights reserved.
//
#define PY_SSIZE_T_CLEAN
#include<string>
#include<iostream>
#include "Connect_Python.hpp"
#include "MyUtils.h"

#define PYTHON_FILE "gcvision_api.py"

namespace WriteApp {


    void Connector::initiate(){
            Py_Initialize();
                 
            std::string dir = dirForResource(PYTHON_FILE);
            std::string py_code = "import sys, os\nsys.path.append('" + dir + "')";
            PyRun_SimpleString(py_code.c_str());
            
            //探すファイルをしてい-------------------------------------------
            pName = PyUnicode_FromString("gcvision_api");
            pModule = PyImport_Import(pName);
            if (pModule == nullptr)
            {
                PyErr_Print();
                std::exit(1);
                return;
            }
            Py_DECREF(pName);
    }

    void Connector::hit_api(signed char *byteData){
           
            if(pModule == nullptr){
                initiate();
            }

           //タプルの作成    -----------------------------------------------
            pArgs = PyTuple_New(1);//タプルを新しく作成する
            pPointa = PyBytes_FromString((char*)byteData);
            PyTuple_SetItem(pArgs,0,pPointa);//タプルの0の位置にpValueを設定
            //---------------------------------------------------------------
            
            if(pModule != nullptr){
                //pFuncに今回呼び出す関数を設定する(今回はfunc)
                pFunc = PyObject_GetAttrString(pModule, "output_result");
                
                //pFuncを引数を与える(pArgsはタプルでなければならない)
                pTmp = PyObject_CallObject(pFunc, pArgs);
                if (pTmp == nullptr)
                {
                      PyErr_Print();
                      std::exit(1);
                      return;
                }
                char* res;
                if(!PyArg_ParseTuple(pTmp,"s#",&res)){
                  //  std::cout << "invalid returned value" << '\n';
                    return;
                }
                
               // printf("c++: %s\n", res);
            }
    }
        
    Connector::~Connector(){
            Py_Finalize();
    }
}
