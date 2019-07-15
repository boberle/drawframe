/****************************************************************************
 *
 * This is `drawframe', a simple program that draw a frame on the screen.
 * Copyright (C) 2017 Bruno Oberlé
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * For any question or comment, please contact me at boberle.com.
 *
 ****************************************************************************/

/*
 * read commands line arguments
 */
bool read_arguments(int, char **, int *, int *, int *, int *, char *, int *);

/*
 * initialize a window
 */
Window init_frame(Display *, int, Window, int, int, int, int, char *, int);

/*
 * draw the initialized window on the scree
 */
void draw_frame(Display *, int, Window, int, int, int);


