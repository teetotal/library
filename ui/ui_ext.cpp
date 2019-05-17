#include "ui_ext.h"

#define _OPACITY    0.05f
/*
 drawCircleForPhysics
 */
DrawNode * guiExt::drawCircleForPhysics(Node * p, Vec2 pos, float radius, Color4F color){
    auto draw = DrawNode::create();
    
    Color4F centerCircleColor = color;
    float opacity = (_OPACITY * 2) / ((radius - .1f) * 10);
    centerCircleColor.a = 1;
//
//    draw->drawDot(Vec2(radius, radius), radius, bg);
//    draw->drawDot(Vec2(radius, radius), radius * 0.9f, color);
    draw->drawDot(Vec2(radius, radius), radius, color);
    
    for(float n = radius - .1f; n > .1f; n = n - 0.1f) {
        centerCircleColor.r = std::fmin(1.f, centerCircleColor.r + opacity);
        centerCircleColor.g = std::fmin(1.f, centerCircleColor.g + opacity);
        centerCircleColor.b = std::fmin(1.f, centerCircleColor.b + opacity);
        draw->drawDot(Vec2(radius, radius), n, centerCircleColor);
    }
    
    draw->setContentSize(Size(radius * 2.f, radius * 2.f));
    draw->setPosition(Vec2(pos.x - radius, pos.y - radius));
    
    if(p)
        p->addChild(draw);
    
    return draw;
}

/*
 drawRectForPhysics
 */
DrawNode * guiExt::drawRectForPhysics(Node * p, Vec2 pos, Size size, Color4F color, bool isSolid, float thick){
    auto draw = DrawNode::create();
    if(isSolid) {
        draw->drawSolidRect(Vec2::ZERO, size, color);
        
        Color4F line1 = color;
        line1.r = std::fmin(1.f, line1.r + _OPACITY);
        line1.g = std::fmin(1.f, line1.g + _OPACITY);
        line1.b = std::fmin(1.f, line1.b + _OPACITY);
        
        Color4F line2 = color;
        line2.r = std::fmax(0.f, line2.r - _OPACITY);
        line2.g = std::fmax(0.f, line2.g - _OPACITY);
        line2.b = std::fmax(0.f, line2.b - _OPACITY);
        
        for(float n=0; n < thick; n = n+ 0.1) {
            draw->drawLine(Vec2(size.width - thick, size.height - n), Vec2(0, size.height - n), line1);
            draw->drawLine(Vec2(n, size.height), Vec2(n, thick), line1);
            
            draw->drawLine(Vec2(size.width - n, size.height), Vec2(size.width - n, 0), line2);
            draw->drawLine(Vec2(size.width, n), Vec2(0, n), line2);
        }
    }
    else
        draw->drawRect(Vec2::ZERO, size, color);
    
    draw->setContentSize(size);
    //physics를 적용하면 anchorpoint가 0,0 이되는 현상이 있다.
    draw->setPosition(Vec2(pos.x - size.width / 2.f, pos.y - size.height / 2.f));
    
    if(p)
        p->addChild(draw);
    
    return draw;
}



