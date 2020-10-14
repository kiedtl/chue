chue(1)

# NAME

*chue* [_OPTION_]... [_FILE_]

# DESCRIPTION

Read colors from FILE, and display a bar of that color and the color
value in hexadecimal RGB form (#RRGGBB).

If not FILE, read from standard input.

# OPTIONS

|[ *-h*
:< Print a short help message and exit.
|  *-V*
:  Print a chue's version and exit.
|  *-c*
:  Do not print the color bar.
|  *-x*
:  Do not print the color value.
|  *-d*
:  Print the color value in decimal RGB form (RRR,GGG,BBB).
|  *-v*
:  Print the color value in HSV form (hsv(H,S,V)).
|  *-l*
:  Print the color value in HSL form (hsl(H,S,L)).


# EXAMPLES

```
echo '#ababab' | ./chue
echo 'hsl(23,0.04,0.02)' | ./chue -v
echo '234,29,65' | ./chue -x
```

# REPORTING BUGS

Report bugs to _https://github.com/lptstr/chue/issues/new_.

# COPYRIGHT

Copyright (c) 2020 Kiëd Llaentenn.
chue is licensed under the MIT license.

# SEE ALSO

The full documentation for *chue* is not maintained as a Texinfo manual.
If the *info* and *chue* programs are properly installed on your system,
the command

	*info chue*

should not give you access to the complete manual.
