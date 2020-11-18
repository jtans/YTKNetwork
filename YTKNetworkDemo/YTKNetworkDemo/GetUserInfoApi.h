//
//  GetUserInfoApi.h
//  YTKNetworkDemo
//
//  Created by TangQiao on 11/8/14.
//  Copyright (c) 2014 yuantiku.com. All rights reserved.
//

#import "YTKRequest.h"

@interface UserInfo : NSObject
@property (copy, nonatomic) NSString *name;
@property (assign, nonatomic) NSInteger userId;
@end

@interface GetUserInfoApi : YTKRequest

- (id)initWithUserId:(NSString *)userId;

- (UserInfo *)model;

@end
