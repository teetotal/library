//
//  ui_effect.cpp
//
//  Created by Jung, DaeCheon on 17/07/2019.
//

#include "ui_effect.h"

#define STEP 100
#define STEP_DEGREE 0.15f

void ui_effect::addBG(Node * parent, COLOR_RGB color, bool isRunRotate) {
    this->setContentSize(parent->getContentSize());
    float radius = fmax(parent->getContentSize().width, parent->getContentSize().height);
    
    mBGLayer = Layout::create();
    mBGLayer->setContentSize(Size(radius, radius));
    
    Color4F c1 = color.getColor4F();
    Color4F c2 = color.getColorLight().getColor4F();
    int cnt = 0;
    const float interval = STEP_DEGREE * 100;
    for(int n=0; n < 360 / interval; n++) {
        drawArc(mBGLayer, radius, (n*interval), (n + 1) * interval, (cnt % 2) == 0 ? c1 : c2);
        cnt++;
    }
    
    Color4B color1 = Color4B(0, 0, 0, 0);
    Color4B color2 = color.getColorDark().getColor4B();
    mBGGradientLayer = LayerRadialGradient::create( color1
                                                    , color2
                                                    , radius
                                                    , gui::inst()->getCenter(parent)
                                                    , 0.3f);
    
    mBGGradientLayer->setContentSize(this->getContentSize());
    
    
    gui::inst()->setAnchorPoint(mBGLayer, ALIGNMENT_CENTER);
    mBGLayer->setPosition(gui::inst()->getCenter(parent));
    
    this->addChild(mBGLayer);
    this->addChild(mBGGradientLayer);
    parent->addChild(this);
}

void ui_effect::drawArc(Node * layer, float radius, float fromDegree, float toDegree, const Color4F color) {
    DrawNode * arc = DrawNode::create();
    vector<Vec2> vecs;
    Vec2 center = gui::inst()->getCenter(layer);
    vecs.push_back(center);
    for(int n=0; n <= (int)STEP; n++) {
        Vec2 pos;
        // cos =   x / mRadius
        // sin =   y / mRadius
        pos.x = center.x + std::cosf(CC_DEGREES_TO_RADIANS(fromDegree + (n * STEP_DEGREE))) * radius;
        pos.y = center.y + std::sinf(CC_DEGREES_TO_RADIANS(fromDegree + (n * STEP_DEGREE))) * radius;
        
        vecs.push_back(pos);
    }
    //vecs.push_back(mCenter);
    arc->drawSolidPoly(vecs.data(), (unsigned int)vecs.size(), color);
    layer->addChild(arc);
}

void ui_effect::runBGRotate(float duration) {
    auto seq = Sequence::create(RotateBy::create(duration, 360), RotateTo::create(0.01, 0), NULL);
    mBGLayer->runAction(RepeatForever::create(seq));
}
void ui_effect::stopRotate() {
    mBGLayer->stopAllActions();
}
