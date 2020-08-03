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

#import "Viewer.hpp"
#import "Connect_Python.hpp"


typedef enum mode {
    WRITE,
    ERASER
} Mode;

@interface Controller : NSWindow <NSApplicationDelegate>{
    std::shared_ptr<Viewer> appInstance;
    std::vector<NSPoint> points;
    Connector connector;
}
@property (nonatomic, retain) NSOpenGLView* glView;
@property Mode appMode;
@property CGWindowID windowID;
-(Point2D) convertPos:(NSPoint)point;
-(void) mouseDown:(NSEvent *)event;
-(void) mouseUp:(NSEvent *)event;
-(void) mouseDragged:(NSEvent *)event;
-(void)keyDown:(NSEvent *)event;
-(signed char*) CaptureScreen;
@end
