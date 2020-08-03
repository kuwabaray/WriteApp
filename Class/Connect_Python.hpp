//
//  Connect_Python.h
//  Sample2
//
//  Created by yukiya kuwabara on 2020/07/31.
//  Copyright © 2020 yukiya kuwabara. All rights reserved.
//

#ifndef Connect_Python_h
#define Connect_Python_h

#include<Python.h>

namespace WriteApp {

    class Connector{
    private:
        void initiate();
    public:
        PyObject *pName, *pModule, *pTmp, *pFunc, *pArgs, *pPointa;
        ~Connector();
        //signed char
        void hit_api(signed char *byteData);
    };
}
#endif /* Connect_Python_h */
