//
// Created by daejung on 2018-07-24.
//

#ifndef _UI_EXT_H
#define _UI_EXT_H

#include "cocos2d.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;

class guiExt {
public:
    static DrawNode * drawCircleForPhysics (Node * p, Vec2 center, float radius, Color4F color);
    static DrawNode * drawRectForPhysics(Node * p, Vec2 pos, Size size, Color4F color, bool isSolid);
};
#endif //_UI_EXT_H
