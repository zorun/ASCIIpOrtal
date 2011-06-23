#include <string>
#include <iostream>

#include "curses-window.h"

using namespace std;

void word_wrap(string & s, int width) {
  // stores the position of the last char of the current line
  int eol = width;
  int pos_space = 0;
  while (eol < s.size()) {
    pos_space = s.rfind(' ', eol);

    // a nasty big word that won't file on the line
    if (pos_space == string::npos || pos_space < eol - width) {
      s.insert(eol-1, "-\n");
      eol += 1 + width;
    }
    // base case: we cut between two words
    else {
      s.replace(pos_space, 1, 1, '\n');
      eol = pos_space + 1 + width;
    }
  }
}

Window::Window(int _height, int _width, win_style _style) {
  height = _height;
  width = _width;
  outerwin = newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
  // We keep an empty column on each side, and an empty line at the top
  innerwin = derwin(outerwin, height - 1, width - 2, 1, 1);
  

}

Window::add_text(string & s) {
  // A bit of indentation (TODO)
  s.replace_all("\n", "\n ");

  word_wrap(s, width-2);
  mvwprintw(win, 1, cur_line, s.c_str());
  cur_line += s.count("\n") + 1; // maybe +2?
}

Window::~Window() {
  delwin(innerwin);
  delwin(outerwin);
}


// only used for atoi
#include <cstdlib>

// Only used to debug that f*** word-wrap function
int main(int argc, char* argv[]) {
  string truc = "Looooooongue longue phrase, qui devrait se wrapper comme il faut. Mais si, mais si, je vous jure qu'elle fonctionne correctement ! Ah, il faut le prouver ? Euh... J'en suis moins sûr, tout d'un coup... Mais anticonstitutionnellement est un mot tellement long qu'il va se faire découper :)";

  int size = 23;
  if (argc > 1) size = atoi(argv[1]);

  word_wrap(truc, size);

  for (int i = 0; i < size; ++i) {
    if (i % 10 == 0)
      cout << i / 10;
    else
      cout << ' ';
  }

  cout << endl;

  for (int i = 0; i < size; ++i)
    cout << i % 10;

  cout << endl << truc << endl;

}
