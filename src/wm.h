#ifndef WM_H_INCLUDED
#define WM_H_INCLUDED

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <list>

#include <curses.h>

void fillsquare(int, int, int, int);
void wfillsquare(WINDOW*, int, int, int, int);

class Window {
protected:
  static std::list<Window> win_list;
  std::list<Window>::iterator own_iter;
  std::stringstream buffer;

  // if one of these is 0, then the size is determined automatically
  // at display time
  int width, height;

  WINDOW* win;

public:
  Window();
  // copy constructor and assignment
  Window(const Window &);
  Window& operator=(const Window &);

  void resize(int x, int y);
  void operator<<(const std::string&);
  void operator<<(int);
  void operator<<(char[]);
  void update();
  void display();
  void destroy();
  ~Window();
};

typedef std::list<Window>::iterator witer;

class Infobox : public Window {

};

class Dialogbox : public Window {

};

#endif // WM_H_INCLUDED
