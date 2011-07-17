#include "wm.h"

#include <iostream>
#include <sstream>
#include <string>

#include <curses.h>

#include "ap_draw.h"

using namespace std;

void wfillsquare(WINDOW* win, int y1, int x1, int height, int width) {
  for (int yy = y1; yy < height + y1; yy++)
    for (int xx = x1; xx < width + x1; xx++)
      mvwaddch(win, yy, xx, ' ');
}

void fillsquare(int y1, int x1, int height, int width) {
  wfillsquare(stdscr, y1, x1, height, width);
}

list<Window> Window::win_list;

Window::Window() {
  width = height = 0;
  win_list.push_back(*this);
  own_iter = --win_list.end();
  
  win = NULL;

}

Window::Window(const Window &source) {
  width = source.width;
  height = source.height;
  win = NULL;
}

Window& Window::operator=(const Window &source) {
  width = source.width;
  height = source.height;
  win = NULL;
  return *this;
}

void Window::resize(int x, int y) {
  width = x;
  height = y;
}

void Window::operator<<(const string& s) {
  buffer << s;
}

void Window::operator<<(int i) {
  buffer << i;
}

void Window::operator<<(char s[]) {
  buffer << s;
}

void Window::update() {
  if (!win_list.empty()) {
    for (witer i = win_list.begin(); i != win_list.end(); ++i) {
      if (i->win != NULL)
        wnoutrefresh(i->win);
    }
    if (win != NULL) {
      wattrset(win, color_pair(TEXTFIELD));
      waddstr(win, buffer.str().c_str());
      buffer.str("");
      wnoutrefresh(win);
    }
  }
  //napms(4);
  doupdate();
  napms(4);
}

void Window::display() {
  if (width == 0)
    width = COLS * 7 / 10;
  if (height == 0)
    height = LINES / 2;
  win = newwin(height, width, (LINES-height)/2, (COLS-width)/2);
  wattrset(win, color_pair(HELPMENU));
  wfillsquare(win, 0, 0, height, width);
  wattrset(win, color_pair(MENUSELECT));
  wfillsquare(win, 1, 1, height-2, width-2);
  //wrefresh(win);
  wmove(win, 1, 1);
  update();
}

void Window::destroy() {
  if (win != NULL) {
    delwin(win);
    win = NULL;
    win_list.erase(own_iter);
    update();
  }
}

Window::~Window() {
  destroy();
}
