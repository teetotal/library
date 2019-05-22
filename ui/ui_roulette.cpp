#include "ui_roulette.h"

void ui_roulette::init(Size size
                       , Vec2 center
                       , COLOR_RGB& colorArrow
                       , COLOR_RGB& colorBG
                       , COLOR_RGB& colorOutCircle)
{
   
    mLayer = gui::inst()->createLayout(size, "", false, Color3B::WHITE);
    
    gui::inst()->setAnchorPoint(mLayer, ALIGNMENT_CENTER);
    mLayer->setPosition(center);
    mCenter = center;
    mRadius = (size.width > size.height) ? size.height: size.width;
    mRadius /= 2.f;
    //outline
    gui::inst()->drawCircle(mLayer, mCenter, mRadius, colorOutCircle.getColor4F());
    
    mRadius -= mRadius * 0.1f;
    
    for(int n=0; n < 8; n++) {
        Color4F c = (n%2==0) ? colorBG.getColor4F(): Color4F::WHITE;
        drawArc(45*n, 45*(n+1), c);
    }
}

void ui_roulette::run(float f) {
    
    mLayer->runAction(RotateTo::create(3, 360 * 3 + 120));
    
}

void ui_roulette::drawArc(float fromDegree, float toDegree, const Color4F color) {
    DrawNode * arc = DrawNode::create();
    vector<Vec2> vecs;
    vecs.push_back(mCenter);
    float STEP = 100;
    float degreeStep = (toDegree - fromDegree) / STEP;
    for(int n=0; n < (int)STEP; n++) {
        Vec2 pos;
        // cos =   x / mRadius
        // sin =   y / mRadius
        pos.x = mCenter.x + std::cosf(CC_DEGREES_TO_RADIANS(fromDegree + (n * degreeStep))) * mRadius;
        pos.y = mCenter.y + std::sinf(CC_DEGREES_TO_RADIANS(fromDegree + (n * degreeStep))) * mRadius;
        
        vecs.push_back(pos);
    }
    //vecs.push_back(mCenter);
    arc->drawSolidPoly(vecs.data(), (unsigned int)vecs.size(), color);
    mLayer->addChild(arc);
}
