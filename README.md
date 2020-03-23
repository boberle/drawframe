# drawframe -- drawing a frame on your screen

`drawframe' allows you to draw a frame on the screen.  This frame will always appears on the top of all windows.  Il is useful if you want to record the desktop for a screencast, for example.

## Usage

With the binary for Linux, either from github or from your own compilation (see below), run the program with:

```
./drawframe 720p
```

This assumes it has the execution permission.  If not:

```
chmod u+x drawframe
```

The program takes one argument, wich can be a geometry in the form of `<WIDTH>x<HEIGHT>`, for example `1280x720`.  You could also add an offset, positive or negative, for example `1280x720+100+100`.  So:

```
./drawframe 1280x720+100+100
```

You can also use a list of predefined resolution, with an offset of `+100+100`:

| res   |  width | height |
| ----- |  ----- | ------ |
| 720p  |  1280  |  720   |
| 1080p |  1920  | 1080   |
| vga   |  640   |  480   |
| svga  |  800   |  600   |
| xga   |  1024  |  768   |
| wxga  |  1280  |  800   |

For example:

```
./drawframe 720p
```

To get more help, use the `-h` flag.


## Compilation from source


If you want to compile from source, use the `Makefile` and juste run `make`.  You will need the X11 and Xext libraries (you can install them with the packages `libx11-dev` and `libxext-dev` on Ubuntu).


## License

Copyright (C) 2017 Bruno Oberle

As of 2020, the license has changed to MIT, see the `LICENSE` file.

## Contact

For any question or comment, please contact me at [boberle.com](http://boberle.com).


## Acknowledgments

Some parts of the code hav been inspired and adapted from `recordmydesktop` (v0.3.8.1) by John Varouhakis, which you can download at [recordmydesktop.sourceforge.net](http://recordmydesktop.sourceforge.net).

