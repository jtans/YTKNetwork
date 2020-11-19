//
//  YTKNetworkConfig.m
//
//  Copyright (c) 2012-2016 YTKNetwork https://github.com/yuantiku
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#import "YTKNetworkConfig.h"
#import "YTKBaseRequest.h"
#import "YTKDefaultCacheHandler.h"

#if __has_include(<AFNetworking/AFSecurityPolicy.h>)
#import <AFNetworking/AFSecurityPolicy.h>
#else
#import <AFNetworking/AFSecurityPolicy.h>
#endif

@implementation YTKNetworkConfig {
    NSMutableArray<id<YTKUrlFilterProtocol>> *_urlFilters;
    NSMutableArray<id<YTKCacheProtocol>> *_cacheHandler;
}

+ (YTKNetworkConfig *)sharedConfig {
    static id sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[self alloc] init];
    });
    return sharedInstance;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        _baseUrl = @"";
        _cdnUrl = @"";
        _urlFilters = [NSMutableArray array];
        _cacheHandler = [NSMutableArray array];
        _securityPolicy = [AFSecurityPolicy defaultPolicy];
        _debugLogEnabled = NO;
        
        //Default cache
        [_cacheHandler addObject:[[YTKDefaultCacheHandler alloc] init]];
    }
    return self;
}

- (void)addUrlFilter:(id<YTKUrlFilterProtocol>)filter {
    [_urlFilters addObject:filter];
}

- (void)clearUrlFilter {
    [_urlFilters removeAllObjects];
}

- (NSArray<id<YTKUrlFilterProtocol>> *)urlFilters {
    return [_urlFilters copy];
}

- (void)addCacheHandler:(id<YTKCacheProtocol>)handler {
    [_cacheHandler addObject:handler];
}

- (void)clearCacheHandler {
    [_cacheHandler removeAllObjects];
}

#pragma mark - NSObject

- (NSString *)description {
    return [NSString stringWithFormat:@"<%@: %p>{ baseURL: %@ } { cdnURL: %@ }", NSStringFromClass([self class]), self, self.baseUrl, self.cdnUrl];
}

@end
