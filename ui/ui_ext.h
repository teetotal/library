//
// Created by daejung on 2018-07-24.
//

#ifndef _UI_EXT_H
#define _UI_EXT_H

#include "cocos2d.h"
#include "ui_color.h"
#include "ui_roulette.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;

class guiExt {
public:
    static DrawNode * drawCircleForPhysics (Node * p, Vec2 center, float radius, COLOR_RGB& color);
    static DrawNode * drawRectForPhysics(Node * p, Vec2 pos, Size size, COLOR_RGB& color, bool isSolid = true, float thick = .1f);
    static DrawNode * drawRectRoundShadow  (Node * p, Vec2 pos, Size size, COLOR_RGB& color);
    static ui_roulette * addRoulette(Node * p, Size size, Vec2 center, COLOR_RGB& color, COLOR_RGB& bg, const string sz);
};
#endif //_UI_EXT_H
