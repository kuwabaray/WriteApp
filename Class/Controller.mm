//
//  Controller.mm
//  Sample1
//
//  Created by yukiya kuwabara on 2020/06/23.
//  Copyright © 2020 yukiya kuwabara. All rights reserved.
//
#import "Controller.h"
#import <Appkit/Appkit.h>

@implementation Controller

@synthesize glView;

BOOL shouldStop = NO;

-(id)init{
    self = [super init];
    if(self){
       _appMode = WRITE;
    }
    return self;
}

-(id)initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)aStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)flag{
if(self = [super initWithContentRect:contentRect styleMask:aStyle backing:bufferingType defer:flag]){
    //sets the title of the window (Declared in Plist)
    [self setTitle:[[NSProcessInfo processInfo] processName]];
 
    //This is pretty important.. OS X starts always with a context that only supports openGL 2.1
    //This will ditch the classic OpenGL and initialises openGL 4.1
    NSOpenGLPixelFormatAttribute pixelFormatAttributes[] ={
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAColorSize    , 24                           ,
            NSOpenGLPFAAlphaSize    , 8                            ,
            NSOpenGLPFADoubleBuffer ,
            NSOpenGLPFAAccelerated  ,
            NSOpenGLPFANoRecovery   ,
            0
    };

    NSOpenGLPixelFormat* format = [[NSOpenGLPixelFormat alloc]initWithAttributes:pixelFormatAttributes];
    //Initialize the view
    glView = [[NSOpenGLView alloc]initWithFrame:contentRect pixelFormat:format];
    
    //Set context and attach it to the window
    [[glView openGLContext]makeCurrentContext];
  
    //finishing off
    [self setContentView:glView];
        [glView prepareOpenGL];
        [self makeKeyAndOrderFront:self];
        [self setAcceptsMouseMovedEvents:YES];
        [self makeKeyWindow];
        [self setOpaque:YES];

        //Start the c++ code
        appInstance = std::shared_ptr<Viewer>(new Viewer());
        appInstance->initiate();
    }
    return self;
    }

-(Point2D) convertPos:(NSPoint) point{
    float x = (point.x - (WIDTH/2))/(WIDTH/2);
    float y = (point.y - (HEIGHT/2))/(HEIGHT/2);
    Point2D p2(x, y);
    return p2;
 }

-(void) mouseDown:(NSEvent *)event{
//    _windowID = (CGWindowID)[event windowNumber];
    if(_appMode == WRITE){
     
        NSPoint p = [event locationInWindow];
        Point2D p2 = [self convertPos:p];
        appInstance.get()->write(Down,p2);
        [glView update];
        [[glView openGLContext] flushBuffer];
      
    }
}

-(void) mouseUp:(NSEvent *)event{
    if(_appMode == WRITE){
    
        NSPoint p = [event locationInWindow];
        Point2D p2 = [self convertPos:p];
        appInstance.get()->write(Up, p2);
        [glView update];
        [[glView openGLContext] flushBuffer];
     
      
    }
}

-(void) mouseDragged:(NSEvent *)event{
    if(_appMode == WRITE){
     
        NSPoint p = [event locationInWindow];
        Point2D p2 = [self convertPos:p];
        appInstance.get()->write(Drag, p2);
        [glView update];
        [[glView openGLContext] flushBuffer];
      
       
    }
}

-(void)keyDown:(NSEvent *)event{
//    unsigned char  keycode = [event keyCode];
//    NSLog(@"%d\n",  keycode);
    /*enter*/
    if([event keyCode] == 36){
        appInstance.get()->clear();
        [glView update];
        [[glView openGLContext] flushBuffer];
    }
    /*space*/
    else if([event keyCode] == 49){
        signed char* byteData =[self CaptureScreen];
        _connector.hit_api(byteData);
    }
}

NSInteger resolution = 100;
-(signed char*) CaptureScreen{
  
    // Get the Screen Rect
    NSRect fullRect = [[NSScreen mainScreen] frame];
    
    NSPoint viewPos = glView.window.frame.origin;
    NSSize viewSize = glView.frame.size;
    NSRect cgRect;
    
    cgRect.origin.x = viewPos.x;
    cgRect.origin.y = fullRect.size.height - (viewSize.height + viewPos.y);
    cgRect.size = viewSize;
  
    // Create a CGImage with the screen contents
    CGImageRef cgImage = CGWindowListCreateImage(cgRect, kCGWindowListOptionAll, kCGNullWindowID, kCGWindowImageNominalResolution);
    
    // Convert the CGImage into a NSBitmapImageRep
    NSBitmapImageRep *rep = [[NSBitmapImageRep alloc] initWithCGImage:cgImage];

    NSDictionary *pJpeg = [NSDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithFloat:1.0],
                         NSImageCompressionFactor,
                         [NSNumber numberWithInteger:resolution], kCGImagePropertyDPIHeight,
                         [NSNumber numberWithInteger:resolution], kCGImagePropertyDPIWidth,
                         nil];
    
    NSData *jpegData = [rep representationUsingType:NSBitmapImageFileTypeJPEG properties:pJpeg];
    bool result = [ jpegData writeToFile : @"./test.jpeg" atomically : NO ];
    if(!result){
     std::cout << "fail to save image" << '\n';
    }
    
    signed char* array = (signed char*) [jpegData bytes];
    return array;
}


- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication{
    return YES;
}

- (void)applicationWillTerminate:(NSNotification *)aNotification{
    shouldStop = YES;
}
 

@end
