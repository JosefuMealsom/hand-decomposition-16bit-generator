#include "./watch.h"
#include <CoreServices/CoreServices.h>

/* namespace FileSystem { */
/* void Watch::register_on_save_callback(const char *file_path) { */
/*   CFStringRef path = CFSTR(file_path); */
/*   /* CFArrayRef pathsToWatch = CFArrayCreate(NULL, (const void **)&path, 1,
 */
/*    * NULL)); */
/* } */
/* } // namespace FileSystem */

/* void MyFSEventCallback(ConstFSEventStreamRef streamRef, */
/*                        void *clientCallBackInfo, size_t numEvents, */
/*                        void *eventPaths, */
/*                        const FSEventStreamEventFlags eventFlags[], */
/*                        const FSEventStreamEventId eventIds[]) { */
/*   char **paths = (char **)eventPaths; */
/**/
/*   for (size_t i = 0; i < numEvents; ++i) { */
/*     std::cout << "Event path: " << paths[i] << std::endl; */
/*   } */
/* } */

/*     for (size_t i = 0; i < numEvents; ++i) { */
/*         std::cout << "Event path: " << paths[i] << std::endl; */
/*     } */
/* } */
/**/
/* int main() { */
/*     CFStringRef path = CFSTR("/path/to/monitor"); // Specify the path to
 * monitor */
/*     CFArrayRef pathsToWatch = CFArrayCreate(NULL, (const void **)&path, 1,
 * NULL); */
/**/
/*     FSEventStreamRef stream = FSEventStreamCreate(NULL, */
/*                                                   &MyFSEventCallback, */
/*                                                   NULL, */
/*                                                   pathsToWatch, */
/*                                                   kFSEventStreamEventIdSinceNow,
 */
/*                                                   1.0, */
/*                                                   kFSEventStreamCreateFlagNone);
 */
/**/
/*     FSEventStreamScheduleWithRunLoop(stream, CFRunLoopGetCurrent(),
 * kCFRunLoopDefaultMode); */
/*     FSEventStreamStart(stream); */
/**/
/*     CFRunLoopRun(); */
/**/
/*     FSEventStreamStop(stream); */
/*     FSEventStreamInvalidate(stream); */
/*     FSEventStreamRelease(stream); */
/**/
/*     CFRelease(pathsToWatch); */
/**/
/*     return 0; */
/* } */
