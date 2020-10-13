#ifndef OPTIONS_H
#define OPTIONS_H

#include "bool.h"

enum DisplayType {
	HEXRGB, DECRGB,
	HSL, HSV, NONE
};

struct Options {
	bool display_color;
	enum DisplayType display;
};

#endif
