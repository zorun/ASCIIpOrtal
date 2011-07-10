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

#ifndef AP_OBJECT_H_INCLUDED
#define AP_OBJECT_H_INCLUDED

#include <vector>
#include <list>
#include "asciiportal.h"

using namespace std;

// TODO: verify() and dump() might not work because of the
// introduction of 'width' and 'height'.
// Also, doors, switches and triggers might not work properly if given
// a width or height strictly greater than 1.

class object {
public:
  object(int x, int y);

  /* position. For objects that span on more than 1 area, it represents
     the top-left position of the object.
   */
  XY coord;
  int type, tick;

  // velocity
  XY v;

  /* direction. Only used for some objects (e.g. aim direction for
     player, normal direction for portals) */
  XY d;

  // custom state (e.g. for doors: state of openness; for player:
  // SHOT1 or SHOT2 depending on the color of the next shot)
  int state;

  // for switches/doors or texttriggers, the identification that makes
  // the matching possible (from 0 to 12 for doors, from 0 to 8 for texttriggers)
  int id;

  int width;
  int height;
};

typedef list<object>::iterator objiter;
typedef list<objiter> objset;

class ObjectManager {
  public:
  list<object> objs;
  vector< vector<objset> > objmap;
  objiter NULLOBJ;
  objiter player;
  objiter portals[2];
  objiter shots[2];
  vector< vector<objiter> > doors;
  vector< vector<objiter> > switches;
  vector< vector<objiter> > triggers;
  int mw, mh;
  void resetmap(int w, int h);
  void addobj(object& obj);
  objiter delobj(objiter it);
  void moveobj(objiter it, int x, int y);
  void killtriggers(int n);
  int verify();
  void dump();
};

#endif // AP_OBJECT_H_INCLUDED
