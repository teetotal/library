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
    static DrawNode * drawCircleForPhysics (Node * p, Vec2 center, float radius, COLOR_RGB color);
    static DrawNode * drawRectForPhysics(Node * p, Vec2 pos, Size size, COLOR_RGB color, bool isSolid = true, float thick = .1f);
    static DrawNode * drawRectRoundShadow  (Node * p, Vec2 pos, Size size, COLOR_RGB& color);
    static ui_roulette * addRoulette(Node * p, Size size, Vec2 center, COLOR_RGB& color, COLOR_RGB& bg, const string sz);
    static Layout * addIconCircle (Node * p, Vec2 center, float radius, const string sz, COLOR_RGB& color);
    static Label * addIconHeart (Node * p, Vec2 pos, ALIGNMENT align, float fontSize, COLOR_RGB& color);
    static Node * addMovingEffect(Node * p
                                  , COLOR_RGB bgColor
                                  , const string img
                                  , const string text = ""              //img가 없으면 중앙에서 효과
                                  , COLOR_RGB fontColor = COLOR_RGB()
                                  , bool toRight = false
                                  , float speed = 1.f                   //default speed를 얼마나 빠르고 느리게 하는가
                                  , CallFunc * pCallFunc = NULL         // 효과 이후 콜백을 받기 위해
                                  );
};
#endif //_UI_EXT_H
