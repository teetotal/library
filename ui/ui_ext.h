//
// Created by daejung on 2018-07-24.
//

#ifndef _UI_EXT_H
#define _UI_EXT_H

#include "cocos2d.h"
#include "ui_color.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;

class guiExt {
public:
    static DrawNode * drawCircleForPhysics (Node * p, Vec2 center, float radius, COLOR_RGB& color);
    static DrawNode * drawRectForPhysics(Node * p, Vec2 pos, Size size, COLOR_RGB& color, bool isSolid = true, float thick = .1f);
};
#endif //_UI_EXT_H
