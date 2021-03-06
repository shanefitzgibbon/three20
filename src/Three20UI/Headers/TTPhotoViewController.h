//
// Copyright 2009-2011 Facebook
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// UI
#import "Three20UI/TTModelViewController.h"
#import "Three20UI/TTScrollViewDelegate.h"
#import "Three20UI/TTScrollViewDataSource.h"
#import "Three20UI/TTThumbsViewControllerDelegate.h"

@protocol TTPhotoSource;
@class TTScrollView;
@class TTPhotoView;
@class TTStyle;

enum TTPhotoViewControllerOptions {
    TTPhotoViewControllerOptionsNone = 0, //!< No options
    TTPhotoViewControllerOptionsNoChrome = 1 << 0, //!< No navigation chrome will be displayed. Tap regions will be used instead of arrow buttons
    TTPhotoViewControllerOptionsDisableDoubleTapToZoom = 1 << 1, //dissable use of the double tap guesture to zoom out to fit or zoom in to the 1/3 of the maximum scale
};
typedef NSUInteger TTPhotoViewControllerOptions;

@interface TTPhotoViewController : TTModelViewController <
  TTScrollViewDelegate,
  TTScrollViewDataSource,
  TTThumbsViewControllerDelegate
> {
  id<TTPhoto>       _centerPhoto;
  NSInteger         _centerPhotoIndex;

  UIView*           _innerView;
  TTScrollView*     _scrollView;
  TTPhotoView*      _photoStatusView;

  UIToolbar*        _toolbar;
  UIBarButtonItem*  _nextButton;
  UIBarButtonItem*  _previousButton;

  TTStyle*          _captionStyle;

  UIImage*          _defaultImage;

  NSString*         _statusText;

  NSTimer*          _slideshowTimer;
  NSTimer*          _loadTimer;

  BOOL              _delayLoad;

  TTThumbsViewController* _thumbsController;

  id<TTPhotoSource> _photoSource;
    
  TTPhotoViewControllerOptions _options;
}



/**
 * The source of a sequential photo collection that will be displayed.
 */
@property (nonatomic, retain) id<TTPhotoSource> photoSource;

/**
 * The photo that is currently visible and centered.
 *
 * You can assign this directly to change the photoSource to the one that contains the photo.
 */
@property (nonatomic, retain) id<TTPhoto> centerPhoto;

/**
 * The index of the currently visible photo.
 *
 * Because centerPhoto can be nil while waiting for the source to load the photo, this property
 * must be maintained even though centerPhoto has its own index property.
 */
@property (nonatomic, readonly) NSInteger centerPhotoIndex;

/**
 * The default image to show before a photo has been loaded.
 */
@property (nonatomic, retain) UIImage* defaultImage;

/**
 * The style to use for the caption label.
 */
@property (nonatomic, retain) TTStyle* captionStyle;

- (id)initWithPhoto:(id<TTPhoto>)photo;
- (id)initWithPhotoSource:(id<TTPhotoSource>)photoSource;
- (id)initWithPhoto:(id<TTPhoto>)photo andOptions:(TTPhotoViewControllerOptions)theOptions;
- (id)initWithPhotoSource:(id<TTPhotoSource>)photoSource andOptions:(TTPhotoViewControllerOptions)theOptions;

/**
 * Creates a photo view for a new page.
 *
 * Do not call this directly. It is meant to be overriden by subclasses.
 */
- (TTPhotoView*)createPhotoView;

/**
 * Creates the thumbnail controller used by the "See All" button.
 *
 * Do not call this directly. It is meant to be overriden by subclasses.
 */
- (TTThumbsViewController*)createThumbsViewController;

/**
 * Sent to the controller after it moves from one photo to another.
 */
- (void)didMoveToPhoto:(id<TTPhoto>)photo fromPhoto:(id<TTPhoto>)fromPhoto;

/**
 * Shows or hides an activity label on top of the photo.
 */
- (void)showActivity:(NSString*)title;

@end
