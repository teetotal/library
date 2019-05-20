#include "ui_ext.h"

#define _OPACITY    0.05f
/*
 drawCircleForPhysics
 */
DrawNode * guiExt::drawCircleForPhysics(Node * p, Vec2 pos, float radius, COLOR_RGB& color){
    auto draw = DrawNode::create();
    draw->drawDot(Vec2(radius, radius), radius, color.getColor4F());
    
//    Color4F centerCircleColor = color.getColor4F();
//    float opacity = (_OPACITY * 8) / ((radius - .1f) * 10);
//    centerCircleColor.a = 1;
//    for(float n = radius - .1f; n > .1f; n = n - 0.1f) {
//        centerCircleColor.r = std::fmin(1.f, centerCircleColor.r + opacity);
//        centerCircleColor.g = std::fmin(1.f, centerCircleColor.g + opacity);
//        centerCircleColor.b = std::fmin(1.f, centerCircleColor.b + opacity);
//        draw->drawDot(Vec2(radius, radius), n, centerCircleColor);
//    }
    
    draw->setContentSize(Size(radius * 2.f, radius * 2.f));
    draw->setPosition(Vec2(pos.x - radius, pos.y - radius));
    
    if(p)
        p->addChild(draw);
    
    return draw;
}

/*
 drawRectForPhysics
 */
DrawNode * guiExt::drawRectForPhysics(Node * p, Vec2 pos, Size size, COLOR_RGB& color, bool isSolid, float thick){
    auto draw = DrawNode::create();
    if(isSolid) {
        draw->drawSolidRect(Vec2::ZERO, size, color.getColor4F());
        
        Color4F line = color.getColorDark().getColor4F();
        
        for(float n=0; n < thick; n = n+ 0.1) {
            draw->drawLine(Vec2(size.width, size.height - n), Vec2(0, size.height - n), line);
            draw->drawLine(Vec2(n, size.height), Vec2(n, 0.f), line);
            
            draw->drawLine(Vec2(size.width - n, size.height), Vec2(size.width - n, 0.f), line);
            draw->drawLine(Vec2(size.width, n), Vec2(0.f, n), line);
        }
    }
    else
        draw->drawRect(Vec2::ZERO, size, color.getColor4F());
    
    draw->setContentSize(size);
    //physics를 적용하면 anchorpoint가 0,0 이되는 현상이 있다.
    draw->setPosition(Vec2(pos.x - size.width / 2.f, pos.y - size.height / 2.f));
    
    if(p)
        p->addChild(draw);
    
    return draw;
}

/*
 drawRectRoundShadow
 */
DrawNode * guiExt::drawRectRoundShadow (Node * p, Vec2 pos, Size size, COLOR_RGB& color){
    Color4F colorShadow = color.getColorLight().getColor4F();
    Color4F colorMain = color.getColor4F();
    
    gui::inst()->drawRectRound(p, Vec2(pos.x, pos.y), size, colorShadow);
    return gui::inst()->drawRectRound(p, pos, Size(size.width - 2.f, size.height - 2.f), colorMain);
}

