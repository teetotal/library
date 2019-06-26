//
// Created by daejung on 2018-07-24.
//

#ifndef _UI_EXT_H
#define _UI_EXT_H

#include "cocos2d.h"
#include "ui_color.h"
#include "ui_roulette.h"

#define SYSTEM_FONT_NAME "Helvetica"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;

class guiExt {
public:
    static DrawNode * drawCircleForPhysics (Node * p, Vec2 center, float radius, COLOR_RGB color);
    static DrawNode * drawRectForPhysics(Node * p, Vec2 pos, Size size, COLOR_RGB color, bool isSolid = true, float thick = .1f);
    static DrawNode * drawRectRoundShadow  (Node * p, Vec2 pos, Size size, COLOR_RGB& color);
    static DrawNode * drawRectCircleButton (Node * p, Vec2 pos, Size size, COLOR_RGB colorFront, COLOR_RGB colorBack = COLOR_RGB());
    
    static ui_roulette * addRoulette(Node * p, Size size, Vec2 center, COLOR_RGB& color, COLOR_RGB& bg, const string sz);
//    static Layout * addIconCircle (Node * p, Vec2 pos, ALIGNMENT align, float radius, const string sz, COLOR_RGB color, const string szText = "", COLOR_RGB colorText = COLOR_RGB());
//    static Layout * addIconHeart (Node * p, Vec2 pos, ALIGNMENT align, float fontSize, COLOR_RGB color, const string sz = "");
    static Node * addMovingEffect(Node * p
                                  , COLOR_RGB bgColor
                                  , const string img
                                  , const string text = ""              //img가 없으면 중앙에서 효과
                                  , COLOR_RGB fontColor = COLOR_RGB()
                                  , bool toRight = false
                                  , float speed = 1.f                   //default speed를 얼마나 빠르고 느리게 하는가
                                  , CallFunc * pCallFunc = NULL         // 효과 이후 콜백을 받기 위해
                                  , CallFunc * pCallFuncInter = NULL    //중간 효과에서 콜백
                                  );
    static void addVibrateEffect(Node * p, CallFunc * pCallFunc = NULL, float duration = 0.1f, float width = 5.f);
    static void addScaleEffect(Node * p, const string img, const string text = "", COLOR_RGB fontColor = COLOR_RGB(), CallFunc * pCallFunc = NULL, float duration = 0.4f, float sizePerWidth = .4f, Vec2 specificPosition = Vec2(-1, -1), GLubyte opacity = 255);
    static void runScaleEffect(Node * p, CallFunc * pCallFunc = NULL, float duration = 0.3f, bool isRemoveSelf = false);
    static void runFlyEffect(Node * p, CallFunc * pCallFunc = NULL, float duration = 1.f, bool isDown = false);
};
#endif //_UI_EXT_H
