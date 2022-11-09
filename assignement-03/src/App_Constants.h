#pragma once

#include "ofMain.h"

namespace App_Constants {
    static const int APP_WINDOW_WIDTH        = 1280;
    static const int APP_WINDOW_HEIGHT        = 720;
    static const int APP_DESIRED_FRAMERATE    = 60;

    static const std::string VIDEO_PATH_GRAYSCALE    = "fingers.mov";
    static const int VIDEO_WIDTH    = 320;    //both videos are very low resolution (change this if you use a diff video)
    static const int VIDEO_HEIGHT    = 240;

    static const int VIDEO_BORDER_SIZE = 10;;

    //!!
    enum APP_MODE {
        FIND_DIFFERENCE,
        FIND_COLOR,
        LIVE_CAM
    };
};

