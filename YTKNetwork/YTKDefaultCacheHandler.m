//
//  YTKFileCacheHandler.m
//  YTKNetwork
//
//  Created by ts on 2020/11/19.
//

#import "YTKDefaultCacheHandler.h"
#import <YYCache/YYCache.h>

@implementation YTKDefaultCacheHandler
{
    YYCache *_cache;
}

- (instancetype)init {
    if (self = [super init]) {
        _cache = [YYCache cacheWithName:@"ytk_cache"];
    }
    return self;
}

- (BOOL)containsObjectForKey:(nonnull NSString *)key {
    return [_cache containsObjectForKey:key];
}

- (nullable id<NSCoding>)objectForKey:(nonnull NSString *)key {
    return [_cache objectForKey:key];
}

- (void)setObject:(nullable id<NSCoding>)object forKey:(nonnull NSString *)key {
    [_cache setObject:object forKey:key];
}

- (void)removeAllObjects {
    [_cache removeAllObjects];
}

- (void)removeObjectForKey:(nonnull NSString *)key {
    [_cache removeObjectForKey:key];
}


@end
