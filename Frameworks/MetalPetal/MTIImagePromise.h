//
//  MTIImagePromise.h
//  Pods
//
//  Created by YuAo on 27/06/2017.
//
//

#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>
#import <simd/simd.h>
#import <CoreImage/CoreImage.h>
#import <ModelIO/ModelIO.h>
#if __has_include(<MetalPetal/MetalPetal.h>)
#import <MetalPetal/MTIColor.h>
#import <MetalPetal/MTITextureDimensions.h>
#import <MetalPetal/MTIAlphaType.h>
#else
#import "MTIColor.h"
#import "MTITextureDimensions.h"
#import "MTIAlphaType.h"
#endif

NS_ASSUME_NONNULL_BEGIN

@class MTIImage, MTIImageRenderingContext, MTIFunctionDescriptor, MTITextureDescriptor, MTIImagePromiseRenderTarget, MTIImagePromiseDebugInfo, MTICIImageRenderingOptions, MTIImageProperties;

@protocol MTIImagePromise <NSObject, NSCopying>

@property (nonatomic, readonly) MTITextureDimensions dimensions;

@property (nonatomic, readonly, copy) NSArray<MTIImage *> *dependencies;

@property (nonatomic, readonly) MTIAlphaType alphaType;

- (nullable MTIImagePromiseRenderTarget *)resolveWithContext:(MTIImageRenderingContext *)renderingContext error:(NSError **)error;

- (instancetype)promiseByUpdatingDependencies:(NSArray<MTIImage *> *)dependencies;

@property (nonatomic, strong, readonly) MTIImagePromiseDebugInfo *debugInfo;

@end

#pragma mark - Promises

__attribute__((objc_subclassing_restricted))
@interface MTIImageURLPromise : NSObject <MTIImagePromise>

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

- (nullable instancetype)initWithContentsOfURL:(NSURL *)URL
                                    dimensions:(MTITextureDimensions)dimensions
                                       options:(nullable NSDictionary<MTKTextureLoaderOption, id> *)options
                                     alphaType:(MTIAlphaType)alphaType;

@end

__attribute__((objc_subclassing_restricted))
@interface MTICGImagePromise : NSObject <MTIImagePromise>

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithCGImage:(CGImageRef)cgImage options:(nullable NSDictionary<MTKTextureLoaderOption, id> *)options alphaType:(MTIAlphaType)alphaType;

@end

__attribute__((objc_subclassing_restricted))
@interface MTITexturePromise : NSObject <MTIImagePromise>

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithTexture:(id<MTLTexture>)texture alphaType:(MTIAlphaType)alphaType;

@end

__attribute__((objc_subclassing_restricted))
@interface MTICIImagePromise : NSObject <MTIImagePromise>

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithCIImage:(CIImage *)ciImage bounds:(CGRect)bounds isOpaque:(BOOL)isOpaque options:(MTICIImageRenderingOptions *)options;

@end

__attribute__((objc_subclassing_restricted))
@interface MTIColorImagePromise: NSObject <MTIImagePromise>

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, readonly) MTIColor color;

- (instancetype)initWithColor:(MTIColor)color sRGB:(BOOL)sRGB size:(CGSize)size;

@end

__attribute__((objc_subclassing_restricted))
@interface MTIBitmapDataImagePromise: NSObject <MTIImagePromise>

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithBitmapData:(NSData *)data width:(NSUInteger)width height:(NSUInteger)height bytesPerRow:(NSUInteger)bytesPerRow pixelFormat:(MTLPixelFormat)pixelFormat alphaType:(MTIAlphaType)alphaType;

@end

__attribute__((objc_subclassing_restricted))
NS_AVAILABLE(10_12, 10_0)
@interface MTINamedImagePromise: NSObject <MTIImagePromise>

@property (nonatomic, copy, readonly) NSString *name;
@property (nonatomic, strong, readonly, nullable) NSBundle *bundle;
@property (nonatomic, readonly) CGFloat scaleFactor;

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithName:(NSString *)name
                      bundle:(nullable NSBundle *)bundle
                        size:(CGSize)size
                 scaleFactor:(CGFloat)scaleFactor
                     options:(nullable NSDictionary<MTKTextureLoaderOption, id> *)options
                   alphaType:(MTIAlphaType)alphaType;

@end

__attribute__((objc_subclassing_restricted))
NS_AVAILABLE(10_12, 10_0)
@interface MTIMDLTexturePromise: NSObject <MTIImagePromise>

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithMDLTexture:(MDLTexture *)texture
                           options:(nullable NSDictionary<MTKTextureLoaderOption, id> *)options
                         alphaType:(MTIAlphaType)alphaType;

@end

NS_ASSUME_NONNULL_END

