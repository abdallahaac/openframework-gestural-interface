#pragma once

#include "ofMain.h"

namespace Constants {
static const int APP_WINDOW_WIDTH        = 1280;
static const int APP_WINDOW_HEIGHT        = 720;
static const int APP_DESIRED_FRAMERATE    = 60;

static const std::string VIDEO_PATH_COLOR_ONE    = "tupperware.mov";
static const int VIDEO_WIDTH    = 640;    //both videos are very low resolution (change this if you use a diff video)
static const int VIDEO_HEIGHT    = 480;

static const int VIDEO_BORDER_SIZE = 10;
static const int VIDEO_BORDER_BOX_WIDTH = 100;
static const int VIDEO_BORDER_BOX_HEIGHT = 100;


//!!
enum APP_MODE {
    FIND_DIFFERENCE,
    FIND_COLOR,
    
};

enum VIDEO_INPUT {
    LIVE_CAM,
    VIDEO_ONE,
    VIDEO_TWO
};
};

