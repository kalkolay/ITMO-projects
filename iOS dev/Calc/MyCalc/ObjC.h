#import <Foundation/Foundation.h>

#pragma clang diagnostics push
#pragma GCC diagnostic ignored "-Wstrict-prototypes"

// https://stackoverflow.com/a/36454808
// Check "Objective-C Bridging Header" in project's Build Settings

@interface ObjC : NSObject

+ (BOOL)catchException:(void(^)())tryBlock error:(__autoreleasing NSError **)error;

@end

#pragma clang diagnostics pop
