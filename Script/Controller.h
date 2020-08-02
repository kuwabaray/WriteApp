//
//  Controller.h
//  Sample1
//
//  Created by yukiya kuwabara on 2020/06/23.
//  Copyright © 2020 yukiya kuwabara. All rights reserved.
//
//Controller_H
#import <Cocoa/Cocoa.h>
#import <memory>
#include <vector>

#import "Viewer.hpp"
#import "Connect_Python.hpp"


NSApplication* application;

#define WIDTH 1024
#define HEIGHT 768

typedef enum mode {
    WRITE,
    ERASER
} Mode;

@interface Controller : NSWindow <NSApplicationDelegate>{
    std::shared_ptr<Viewer> appInstance;
}
@property (nonatomic, retain) NSOpenGLView* glView;
@property Mode appMode;
@property std::vector<NSPoint> points;
@property Connector connector;
@property CGWindowID windowID;
-(Point2D) convertPos:(NSPoint)point;
-(void) mouseDown:(NSEvent *)event;
-(void) mouseUp:(NSEvent *)event;
-(void) mouseDragged:(NSEvent *)event;
-(void)keyDown:(NSEvent *)event;
-(signed char*) CaptureScreen;
@end

int main(int argc, const char * argv[]) {
    Controller* app;
    application = [NSApplication sharedApplication];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    app = [[Controller alloc] initWithContentRect:NSMakeRect(0, 0, WIDTH, HEIGHT)              styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable |  NSWindowStyleMaskMiniaturizable   backing:NSBackingStoreBuffered defer:YES];
    [application setDelegate:app];
    [application run];
}
