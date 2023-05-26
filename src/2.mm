#include <Cocoa/Cocoa.h>
#include <CoreGraphics/CoreGraphics.h>

@interface TransparentWindow : NSWindow
@end

@implementation TransparentWindow
- (BOOL)canBecomeKeyWindow {
    return YES;
}
@end

int main(int argc, const char * argv[]) {
    // Create a transparent window
    TransparentWindow *window = [[TransparentWindow alloc] initWithContentRect:NSMakeRect(0, 0, 500, 500) styleMask:NSWindowStyleMaskBorderless backing:NSBackingStoreBuffered defer:NO];
    [window setBackgroundColor:[NSColor clearColor]];
    [window setOpaque:NO];
    [window setLevel:NSNormalWindowLevel];
    [window makeKeyAndOrderFront:nil];
    
    // Draw a bounding box with given coordinates
    CGContextRef context = [[NSGraphicsContext currentContext] CGContext];
    CGRect rect = CGRectMake(100, 1000, 200, 700);
    CGContextSetLineWidth(context, 2);
    CGContextSetStrokeColorWithColor(context, [[NSColor whiteColor] CGColor]);
    CGContextStrokeRect(context, rect);
    
    // Run the main event loop
    while (true) {
    [[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate distantFuture]];
}
    [NSApp run];
    
    return 0;
}
