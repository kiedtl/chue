#ifndef OPTIONS_H
#define OPTIONS_H

enum DisplayType {
	HEXRGB, DECRGB,
	HSL, HSV, NONE
};

struct Options {
	_Bool display_color;
	enum DisplayType display;
};

#endif
