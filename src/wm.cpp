#include "wm.h"

#include <iostream>
#include <sstream>
#include <string>

#include <curses.h>

using namespace std;

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

void Window::operator<<(string& s) {
  buffer << s;
}

void Window::operator<<(int i) {
  buffer << i;
}

void Window::operator<<(char s[]) {
  buffer << s;
}

void Window::update() {
  waddstr(win, buffer.str().c_str());
  buffer.clear();
  for (witer i = win_list.begin(); i != win_list.end(); ++i) {
    if (i->win != NULL)
      wnoutrefresh(i->win);
  }
  if (win != NULL)
    wnoutrefresh(win);
  doupdate();
}

void Window::display() {
  if (width == 0)
    width = COLS * 7 / 10;
  if (height == 0)
    height = LINES / 2;
  win = newwin(height, width, (LINES-height)/2, (COLS-width)/2);
  update();
}

void Window::destroy() {
  win_list.erase(own_iter);
  delwin(win);
  win = NULL;
  display();
}

Window::~Window() {
  destroy();
}
