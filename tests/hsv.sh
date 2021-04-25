#!/bin/sh

. tests/lib.sh

begin "hsv->rgb: cyan"   && expect "1fc8d1" f v 183 85  82
begin "hsv->rgb: purple" && expect "8c3183" f v 306 65  55
begin "hsv->rgb: yellow" && expect "f2f5a6" f v  62 32  96
begin "hsv->rgb: green"  && expect "32a852" f v 136 70  66

begin "rgb->hsv: cyan"   && expect "183 85 82"    t v     1f c8 d1
begin "rgb->hsv: purple" && expect "306 65 55"    t v     8c 31 83
begin "rgb->hsv: yellow" && expect "62 32 96"     t v     f2 f5 a6
begin "rgb->hsv: green"  && expect "136 70 66"    t v     32 a8 52
