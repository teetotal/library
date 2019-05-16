#include "ui_ext.h"


/*
 drawCircleForPhysics
 */
DrawNode * guiExt::drawCircleForPhysics(Node * p, Vec2 pos, float radius, Color4F color){
    auto draw = DrawNode::create();
    
//    float ratioBg = 0.05f;
//    Color4F bg = color;
//    bg.r -= ratioBg;
//    bg.g -= ratioBg;
//    bg.b -= ratioBg;
//
//    draw->drawDot(Vec2(radius, radius), radius, bg);
//    draw->drawDot(Vec2(radius, radius), radius * 0.9f, color);
    draw->drawDot(Vec2(radius, radius), radius, color);
    draw->setContentSize(Size(radius * 2.f, radius * 2.f));
    draw->setPosition(Vec2(pos.x - radius, pos.y - radius));
    
    if(p)
        p->addChild(draw);
    
    return draw;
}

/*
 drawRectForPhysics
 */
DrawNode * guiExt::drawRectForPhysics(Node * p, Vec2 pos, Size size, Color4F color, bool isSolid){
    auto draw = DrawNode::create();
    if(isSolid)
        draw->drawSolidRect(Vec2::ZERO, size, color);
    else
        draw->drawRect(Vec2::ZERO, size, color);
    
    draw->setContentSize(size);
    //physics를 적용하면 anchorpoint가 0,0 이되는 현상이 있다.
    draw->setPosition(Vec2(pos.x - size.width / 2.f, pos.y - size.height / 2.f));
    
    if(p)
        p->addChild(draw);
    
    return draw;
}



