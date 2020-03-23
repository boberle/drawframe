/****************************************************************************
 *
 * This is `drawframe', a simple program that draw a frame on the screen.
 * Copyright (C) 2017 Bruno Oberlé
 *
 * MIT License
 * 
 * Copyright (c) 2020 Bruno Oberle
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * For any question or comment, please contact me at boberle.com.
 *
 ****************************************************************************/

/*
 * The two main function used to initialize and draw the frame have been
 * adapted from recordmydesktop, v0.3.8.1, file rmd_frame.c (.h), by John
 * Varouhakis, which you can download at
 * http://recordmydesktop.sourceforge.net.
 *
 * The page http://www-h.eng.cam.ac.uk/help/tpl/graphics/X/X11R5/node21.html
 * have also been used to understand how to have default values for the X
 * functions.
 *
 * Some other resources that may be useful:
 * http://yenolam.com/writings/xlibbook-0.5.pdf
 * https://en.wikipedia.org/wiki/X11_color_names
 * - https://tronche.com/gui/x/xlib/
 */

/*
 *
 * To compile, use (see Makefile):
 * $ gcc -o drawframe drawframe.c -lX11 -lXext
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // C99
#include <string.h>

/*
 * Note: /usr/include/X11/Xlib.h is found in package `libx11-dev'
 * (https://packages.ubuntu.com/search?suite=xenial&arch=any&mode=exactfilename&searchon=contents&keywords=X11%2FXlib.h).
 *
 * This package also contains the compiled library, found at
 * /usr/lib/x86_64-linux-gnu/libX11.so
 * (https://packages.ubuntu.com/xenial/amd64/libx11-dev/filelist).
 *
 * So you must compile with the -lX11 option.
 *
 * This is used for the main X11 functions, like XCreateWindow.
 */
#include <X11/Xlib.h>

/*
 * Note: /usr/include/X11/extensions/shape.h is found in package
 * `libxext-dev'
 * (https://packages.ubuntu.com/search?suite=xenial&arch=any&mode=exactfilename&searchon=contents&keywords=X11%2Fextensions%2Fshape.h).
 *
 * This package also contains the compiled library, found at
 * /usr/lib/x86_64-linux-gnu/libXext.so
 * (https://packages.ubuntu.com/xenial/amd64/libxext-dev/filelist).
 *
 * So you must compile with the -lXext option.
 *
 * This is used for more specific X11 functions, like XShapeCombineRectangles,
 * etc.
 */
#include <X11/extensions/shape.h>

#include "drawframe.h"

/* CONSTANTS */

#define OUTLINE_WIDTH 1
#define DEFAULT_BORDER_WIDTH 4
#define DEFAULT_COLOR "red"

#define LICENSE_TEXT \
"drawframe version 1.0.0\n"\
"Copyright 2017 Bruno Oberlé.\n\n"\
"This program is free software: you can redistribute it and/or modify\n"\
"it under the terms of the GNU General Public License as published by\n"\
"the Free Software Foundation, either version 3 of the License, or\n"\
"(at your option) any later version.\n\n"\
"This program is distributed in the hope that it will be useful,\n"\
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"\
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"\
"GNU General Public License for more details.\n\n"\
"You should have received a copy of the GNU General Public License\n"\
"along with this program.  If not, see <http://www.gnu.org/licenses/>."

#define HELP_TEXT \
"This is `drawframe', I draw a frame on the screen.\n\n"\
"Usage: drawframe [OPTIONS] GEOMETRY\n\n"\
"GEOMETRY is a string as WIDTHxHEIGHT, for example 800x600. You may specify\n"\
"an x and y offset: 800x600+100+200.  Offsets may be negative, but when they\n"\
"are positive, you **need** to write the `+'.  The GEOMETRY format is similar\n"\
"to the one of ImageMagick `convert'.\n\n"\
"GEOMETRY can also be one of the following (offset are 100 pixels, except for vga\n"\
"(50 pixels):\n"\
"720p:    width = 1280; height =  720;\n"\
"1080p:   width = 1920; height = 1080;\n"\
"vga:     width =  640; height =  480;\n"\
"svga:    width =  800; height =  600;\n"\
"xga:     width = 1024; height =  768;\n"\
"wxga:    width = 1280; height =  800;\n\n"\
"OPTIONS:\n"\
"-c COLOR_NAME  One of the Xlib colors (red by default). Common colors\n"\
"               include black, blue, brown, cyan, gold, gray, green, indigo,\n"\
"               magenta, pink, purple, red, white, yellow.  You can find\n"\
"               a more complete list at en.wikipedia.org/wiki/X11_color_names.\n"\
"-w INTEGER     The border width (4 by default).\n"\
"-h             Print this help.\n"\
"-H             Version and license information.\n\n"\
"Version: 1.0.0\n"\
"Copyright 2017 Bruno Oberlé.  Use -H for details."


/*
 * start here
 */
int main(int argc, char **argv) {

   // variables for parameters
   int width, height, x_offset, y_offset;
   int border_width;
   int ans;
   char color[20];

   // variables for X and drawing
   int screen;
   Display *display;
   Window root_window;
   Window win;

   // variable for waiting
   char buf;

   // reading command line arguments

   ans = read_arguments(argc, argv, &width, &height,
      &x_offset, &y_offset, color, &border_width);
   
   if (!ans) {
      puts(HELP_TEXT);
      return 1;
   }

   puts("Your choices:");
   printf("Width: %d\nHeight: %d\nX offset: %d\nY offset: %d\n",
      width, height, x_offset, y_offset);
   printf("Color: %s\nBorder width: %d\n", color, border_width);


   // preparing and getting window

   display = XOpenDisplay(NULL);
   screen = DefaultScreen(display);
   root_window = XRootWindow(display,screen);

   win = init_frame(display, screen, root_window, x_offset, y_offset,
      width, height, color, border_width);

   // Window is an integer, and the function return 0 if there was an error
   // (e.g. a bad color name)
   if (win == 0) {
      return 1;
   }

   // drawing the screen on the screen

   draw_frame(display, screen, win, width, height, border_width);

   // waiting...

   printf("Press Enter to quit...");
   scanf("%c", &buf);

   return 0;

}


/*
 * read commands line arguments
 */
bool read_arguments(int argc, char **argv, int *width, int *height,
      int *x_offset, int *y_offset, char *color, int *border_width) {

   int i;
   bool geometry_values_already_defined = false;

   // default values
   *width = 0;
   *height = 0;
   *x_offset = 0;
   *y_offset = 0;
   *border_width = DEFAULT_BORDER_WIDTH;
   strcpy(color, DEFAULT_COLOR);

   if (!(argc > 1)) {
      puts("*** missing argument ***");
      return false;
   }

   for (i=1; i<argc; i++) {
      if (!strcmp(argv[i], "-c")) {
         if (i+1<argc) {
            strcpy(color, argv[i+1]);
            i++;
         } else {
            puts("*** no value for option -c ***");
            return false;
         }
      } else if (!strcmp(argv[i], "-w")) {
         if (i+1<argc) {
            *border_width = atoi(argv[i+1]);
            i++;
            if (!*border_width) {
               puts("*** bad value for option -w ***");
               return false;
            }
         } else {
            puts("*** no value for option -w ***");
            return false;
         }
      } else if (!strcmp(argv[i], "-h")) {
         puts(HELP_TEXT);
         exit(0);
      } else if (!strcmp(argv[i], "-H")) {
         puts(LICENSE_TEXT);
         exit(0);
      } else if (strlen(argv[i]) && argv[i][0] == '-') {
         printf("*** unknow option `%s' ***\n", argv[i]);
         return false;
      } else if (strlen(argv[i])) {
         if (geometry_values_already_defined) {
            puts("*** trailing arguments ***");
            return false;
         }
         if (!strcmp(argv[i], "720p")) {
            *width = 1280;
            *height = 720;
            *x_offset = 100;
            *y_offset = 100;
         } else if (!strcmp(argv[i], "1080p")) {
            *width = 1920;
            *height = 1080;
            *x_offset = 100;
            *y_offset = 100;
         } else if (!strcmp(argv[i], "vga")) {
            *width = 640;
            *height = 480;
            *x_offset = 50;
            *y_offset = 50;
         } else if (!strcmp(argv[i], "svga")) {
            *width = 800;
            *height = 600;
            *x_offset = 100;
            *y_offset = 100;
         } else if (!strcmp(argv[i], "xga")) {
            *width = 1024;
            *height = 768;
            *x_offset = 100;
            *y_offset = 100;
         } else if (!strcmp(argv[i], "wxga")) {
            *width = 1280;
            *height = 800;
            *x_offset = 100;
            *y_offset = 100;
         } else {
            sscanf(argv[i], "%dx%d%d%d", width, height, x_offset, y_offset);
         }
         geometry_values_already_defined = true;
      } else {
         puts("*** invalid argument ***");
         return false;
      }
   }

   if (!(*width > 0 && *height > 0)) {
      puts("*** invalid geometry ***");
      return false;
   }

   return true;

}


/*
 * initialize the window and return it
 */
Window init_frame(Display *display,
                    int screen,
                    Window root_window,
                    int x,
                    int y,
                    int width,
                    int height,
                    char *colorname,
                    int border_width){

    XSetWindowAttributes attribs;
    XColor color, color_e;
    Window win;
    unsigned long valuemask=CWBackPixmap|CWBackPixel|
                            CWSaveUnder|CWOverrideRedirect|CWColormap;
    int status;

    // status is 0 if there is an error (bad name)
    status = XAllocNamedColor(display, DefaultColormap(display, screen),
      colorname, &color, &color_e);

   if (!status) {
       printf("Unknowd color `%s'.\n", colorname);
       // Window is an integer, it seems; so we can return 0
       return 0;
   }

    attribs.background_pixmap=None;
    attribs.background_pixel=color.pixel;
    attribs.save_under=True;
    attribs.override_redirect=True;
    attribs.colormap=DefaultColormap(display,screen);

    win = XCreateWindow(display,
                        root_window,
                        x-border_width,
                        y-border_width,
                        width+border_width*2,
                        height+border_width*2,
                        0,
                        CopyFromParent,
                        InputOutput,
                        CopyFromParent,
                        valuemask,
                        &attribs);

    XRectangle rect;
    rect.x=rect.y=border_width;
    rect.width=width;
    rect.height=height;

    XShapeCombineRectangles(display,
                            win,
                            ShapeBounding,
                            0,
                            0,
                            &rect,
                            1,
                            ShapeSubtract,
                            0);

    XMapWindow(display, win);

    return win;

}


/*
 * draw the window
 */
void draw_frame(Display *dpy,
                  int screen,  
                  Window win,
                  int width,
                  int height,
                  int border_width){

    GC gc;
    XGCValues gcv;
    XColor white, white_e,
           black, black_e ;
    unsigned long gcmask=GCForeground;

    // these colors where found in the original source code by John
    // Varouhakis, but they don't seem to have any effect on the color.
    XAllocNamedColor(dpy, DefaultColormap(dpy, screen), "white", &white, &white_e);
    XAllocNamedColor(dpy, DefaultColormap(dpy, screen), "black", &black, &black_e);

    gcv.foreground = black.pixel;
    gc = XCreateGC(dpy,win, gcmask,&gcv);
    XFillRectangle(dpy,
                   win,
                   gc,
                   OUTLINE_WIDTH,
                   OUTLINE_WIDTH,
                   width+(border_width-OUTLINE_WIDTH)*2,
                   height+(border_width-OUTLINE_WIDTH)*2);
    gcv.foreground = white.pixel;
    XChangeGC(dpy,gc,gcmask,&gcv);
    XFillRectangle(dpy,
                   win,
                   gc,
                   border_width-OUTLINE_WIDTH,
                   border_width-OUTLINE_WIDTH,
                   width+OUTLINE_WIDTH*2,
                   height+OUTLINE_WIDTH*2);

    XFreeGC(dpy, gc);

}


