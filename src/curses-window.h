// ASCIIpOrtal ver 1.3 by Joseph Larson
// Copyright (c) 2009, 2011 Joseph Larson
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// The source links with SDL, PDCurses compiled for SDL rendering (PDCSDL)
// and SDL mixer.

/* Curses is fairly low-level; having some abstraction shouldn't
 * hurt. This handles windows management in an easy way.
 * 
 * There are some C++ bindings for ncurses out there, but they are
 * either too heavy or too old (ndk++ seems promising, but it hasn't
 * been updated for years)
 */

#ifndef AP_WINDOW_H_INCLUDED
#define AP_WINDOW_H_INCLUDED

#include <string>

#include <curses.h>

#include "asciiportal.h"

// Style of a window
struct win_style {
  //  int background;
  //  int foreground;
};

// Clever word-wrapping (at least a bit more clever than the brutish
// way ncurses is using) that wraps only between words.
void word_wrap(std::string &, int width);

class Window {
protected:
  // Size of the outer window. We keep an extra column on each side to
  // have a pretty output.
  int height;
  int width;
  win_style style;
  WINDOW* outerwin;
  WINDOW* innerwin;
  
public:
  Window(int _height, int _width, win_style _style);

  // It gets displayed first and centered
  void set_title(const std::string &);

  void draw();
};

#endif
