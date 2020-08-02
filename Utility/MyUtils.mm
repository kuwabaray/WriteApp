//
//  Utils.mm
//  Sample2
//
//  Created by yukiya kuwabara on 2020/07/26.
//  Copyright © 2020 yukiya kuwabara. All rights reserved.
//

#include <Cocoa/Cocoa.h>

const char *pathForResource(const char *name)
{
    NSString *path = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:name]ofType: nil];
    return [path fileSystemRepresentation];
}

char *dirForResource(const char *name){
    const char* path = pathForResource(name);
    auto len =  strlen(path);
    char* dir = (char*)malloc(len*sizeof(char));
    int sep = 0;
    for(int i =0; i<len; i++){
      if(path[i] == '/'){sep = i;}
      dir[i] = path[i];
    }
    dir[sep+1] = '\0';
    return dir;
}




