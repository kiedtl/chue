#!/bin/sh

. tests/lib.sh

begin "hsl->rgb: cyan"   && expect "1fc8d1" f l 183 74  47
begin "hsl->rgb: white"  && expect "ffffff" f l   0  0 100
begin "hsl->rgb: purple" && expect "8c3183" f l 306 48  37
begin "hsl->rgb: yellow" && expect "f2f5a6" f l  62 79  81
begin "hsl->rgb: green"  && expect "32a852" f l 136 54  43

begin "rgb->hsl: cyan"   && expect "183 74 47"    t l     1f c8 d1
begin "rgb->hsl: white"  && expect "0 0 100"      t l     ff ff ff
begin "rgb->hsl: purple" && expect "306 48 37"    t l     8c 31 83
begin "rgb->hsl: yellow" && expect "62 79 81"     t l     f2 f5 a6
begin "rgb->hsl: green"  && expect "136 54 43"    t l     32 a8 52
