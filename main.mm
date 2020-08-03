//
//  main.h
//  WriteApp
//
//  Created by yukiya kuwabara on 2020/08/03.
//  Copyright © 2020 yukiya kuwabara. All rights reserved.
//

#ifndef main_h
#define main_h

#import <Cocoa/Cocoa.h>
#import "Controller.h"

NSApplication* application;

#define WIDTH 1024
#define HEIGHT 768

int main(int argc, const char * argv[]) {
    Controller* app;
    application = [NSApplication sharedApplication];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    app = [[Controller alloc] initWithContentRect:NSMakeRect(0, 0, WIDTH, HEIGHT)              styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable |  NSWindowStyleMaskMiniaturizable   backing:NSBackingStoreBuffered defer:YES];
    [application setDelegate:app];
    [application run];
}

#endif /* main_h */
