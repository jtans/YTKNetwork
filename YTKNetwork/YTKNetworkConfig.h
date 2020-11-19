//
//  YTKNetworkConfig.h
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

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class YTKBaseRequest;
@class AFSecurityPolicy;

typedef void (^AFURLSessionTaskDidFinishCollectingMetricsBlock)(NSURLSession *session, NSURLSessionTask *task, NSURLSessionTaskMetrics * metrics) API_AVAILABLE(ios(10), macosx(10.12), watchos(3), tvos(10));


/// 缓存处理协议
@protocol YTKCacheProtocol <NSObject>

/// 是否有值
/// @param key <#key description#>
- (BOOL)containsObjectForKey:(NSString *)key;

/// 取值
/// @param key <#key description#>
- (nullable id<NSCoding>)objectForKey:(NSString *)key;

/// 设置值
/// @param object <#object description#>
/// @param key <#key description#>
- (void)setObject:(nullable id<NSCoding>)object forKey:(NSString *)key;

/// 移除键值
/// @param key <#key description#>
- (void)removeObjectForKey:(NSString *)key;

/// 移除所有键值
- (void)removeAllObjects;

@end

///  YTKUrlFilterProtocol can be used to append common parameters to requests before sending them.
@protocol YTKUrlFilterProtocol <NSObject>
///  Preprocess request URL before actually sending them.
///
///  @param originUrl request's origin URL, which is returned by `requestUrl`
///  @param request   request itself
///
///  @return A new url which will be used as a new `requestUrl`
- (NSString *)filterUrl:(NSString *)originUrl withRequest:(YTKBaseRequest *)request;
@end

///  YTKNetworkConfig stored global network-related configurations, which will be used in `YTKNetworkAgent`
///  to form and filter requests, as well as caching response.
@interface YTKNetworkConfig : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

///  Return a shared config object.
+ (YTKNetworkConfig *)sharedConfig;

///  Request base URL, such as "http://www.yuantiku.com". Default is empty string.
@property (nonatomic, strong) NSString *baseUrl;
///  Request CDN URL. Default is empty string.
@property (nonatomic, strong) NSString *cdnUrl;
///  URL filters. See also `YTKUrlFilterProtocol`.
@property (nonatomic, strong, readonly) NSArray<id<YTKUrlFilterProtocol>> *urlFilters;
///  Cache handler
@property (nonatomic, strong, readonly) NSArray<id<YTKCacheProtocol>> *cacheHandler;
///  Security policy will be used by AFNetworking. See also `AFSecurityPolicy`.
@property (nonatomic, strong) AFSecurityPolicy *securityPolicy;
///  Whether to log debug info. Default is NO;
@property (nonatomic) BOOL debugLogEnabled;
///  SessionConfiguration will be used to initialize AFHTTPSessionManager. Default is nil.
@property (nonatomic, strong) NSURLSessionConfiguration* sessionConfiguration;
///  NSURLSessionTaskMetrics
@property (nonatomic, strong) AFURLSessionTaskDidFinishCollectingMetricsBlock collectingMetricsBlock API_AVAILABLE(ios(10), macosx(10.12), watchos(3), tvos(10));

///  Add a new URL filter.
- (void)addUrlFilter:(id<YTKUrlFilterProtocol>)filter;
///  Remove all URL filters.
- (void)clearUrlFilter;
///  添加缓存处理器
- (void)addCacheHandler:(id<YTKCacheProtocol>)handler;
///  清空缓存处理器
- (void)clearCacheHandler;

@end

NS_ASSUME_NONNULL_END
