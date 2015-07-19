#ifndef __COMMON_H__
#define __COMMON_H__

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const float MIN_COLOR = 0.0f;
const float MAX_COLOR = 1.0f;

#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

#endif // __COMMON_H__
