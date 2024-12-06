// AudioPreviewController.h
@import AVFoundation;

@interface AudioPreviewController : NSObject

- (void)playPreviewAtPath:(NSString *)path
                fromTime:(NSTimeInterval)startTime
                toTime:(NSTimeInterval)endTime;
                
@end

// AudioPreviewController.m
@implementation AudioPreviewController {
    AVAudioPlayer *_player;
}

- (void)playPreviewAtPath:(NSString *)path
                fromTime:(NSTimeInterval)startTime
                toTime:(NSTimeInterval)endTime {
    NSError *error;
    _player = [[AVAudioPlayer alloc] initWithContentsOfURL:[NSURL fileURLWithPath:path]
                                                    error:&error];
    if (error) {
        NSLog(@"Audio preview error: %@", error);
        return;
    }
    
    _player.currentTime = startTime;
    [_player play];
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(endTime * NSEC_PER_SEC)),
                  dispatch_get_main_queue(), ^{
        [self->_player stop];
    });
}

@end
