# drawframe -- drawing a frame on your screen

`drawframe' allows you to draw a frame on the screen.  This frame will always appears on the top of all windows.  Il is useful if you want to record the desktop for a screencast, for example.


## Compilation and execution

In binary form for Linux, just copy the `drawframe' executable on you hard
drive, give it the execute permission and execute it:

```
chmod u+x drawframe
./drawframe 720p
```

For help, use:

```
./drawframe -h
```

If you want to compile from source, use the `Makefile` and juste run `make`.  You will need the X11 and Xext libraries (you can install them with the packages `libx11-dev` and `libxext-dev` on Ubuntu).


## License

Copyright (C) 2017 Bruno Oberlé

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


## Contact

For any question or comment, please contact me at [boberle.com](http://boberle.com).


## Acknowledgments

Some parts of the code hav been inspired and adapted from `recordmydesktop` (v0.3.8.1) by John Varouhakis, which you can download at [recordmydesktop.sourceforge.net](http://recordmydesktop.sourceforge.net).

