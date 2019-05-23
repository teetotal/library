#include "ui_roulette.h"

#define STEP 100
#define STEP_DEGREE 0.45f
#define STEP_DEGREE_TEXT 0.225f

void ui_roulette::init(Size size
                       , Vec2 center
                       , COLOR_RGB& color
                       , COLOR_RGB& colorBG
                       , const string szStart)
{
    mThis = this;
    mItemsIdx = 0;
    mEnable = true;
    mColor = color;
    mStartString = szStart;
    
    mLayer = gui::inst()->createLayout(size, "", false, Color3B::BLACK);
    gui::inst()->setAnchorPoint(mLayer, ALIGNMENT_CENTER);
    mLayer->setPosition(center);
    
    mRadius = (size.width > size.height) ? size.height: size.width;
    
    mLayerSquare = gui::inst()->createLayout(Size(mRadius, mRadius), "", false, Color3B::WHITE);
    gui::inst()->setAnchorPoint(mLayerSquare, ALIGNMENT_CENTER);
    mLayerSquare->setPosition(Vec2(size.width / 2.f, size.height / 2.f));
    mLayer->addChild(mLayerSquare);
    
    mRadius /= 2.f;
    float len = mRadius * 0.1f;
    Vec2 l,r,c;
    c = Vec2(center.x, center.y * 2.f - len * 2.f);
    l = Vec2(center.x - len, center.y * 2.f);
    r = Vec2(center.x + len, center.y * 2.f);
    
    mCenter = Vec2(mRadius, mRadius);
    
    //outline
    COLOR_RGB colorOutCircle = colorBG.getColorDark();
    gui::inst()->drawCircle(mLayerSquare, mCenter, mRadius, colorOutCircle.getColor4F());
    gui::inst()->drawCircle(mLayerSquare, mCenter, mRadius * 0.92, colorOutCircle.getColorDark().getColor4F());
    
    mRadius -= mRadius * 0.1f;
    
    for(int n=0; n < 8; n++) {
        Color4F c = (n % 2==0) ? colorBG.getColor4F(): Color4F::WHITE;
        drawArc(45*n, 45*(n+1), c);
    }
    
    gui::inst()->drawCircle(mLayer, center, mRadius * 0.32, colorBG.getColor4F());
    gui::inst()->drawCircle(mLayer, center, mRadius * 0.3, Color4F::WHITE);
    
    gui::inst()->drawTriangle(mLayer, l, r, c, color.getColorDark().getColor4F());
}

bool ui_roulette::run(const ccMenuCallback& callback) {
    if(mEnable == false) {
        CCLOG("ui_roulette disabled");
        return false;
    }

    mLayerSquare->setRotation(0);
    
    mEnable = false;
    // 2: 360 = d: mValue
    auto ease = EaseIn::create(RotateBy::create(4, 360 * 3 + mValue), 0.6);
//    auto seq = Sequence::create(RotateBy::create(1, 360)
//                                , RotateBy::create(1.2, 360)
//                                , RotateBy::create(1.5, 360)
//                                , RotateBy::create(mValue * 2 / 360, mValue)
//                                , CallFunc::create(callback)
//                                , NULL);
    auto seq = Sequence::create(ease
                                , CallFunc::create([=](){ callback(this); })
                                , NULL);

    mLayerSquare->runAction(seq);
    
    return true;
}
void ui_roulette::drawArc(float fromDegree, float toDegree, const Color4F color) {
    DrawNode * arc = DrawNode::create();
    vector<Vec2> vecs;
    vecs.push_back(mCenter);
    for(int n=0; n <= (int)STEP; n++) {
        Vec2 pos;
        // cos =   x / mRadius
        // sin =   y / mRadius
        pos.x = mCenter.x + std::cosf(CC_DEGREES_TO_RADIANS(fromDegree + (n * STEP_DEGREE))) * mRadius;
        pos.y = mCenter.y + std::sinf(CC_DEGREES_TO_RADIANS(fromDegree + (n * STEP_DEGREE))) * mRadius;
        
        vecs.push_back(pos);
    }
    //vecs.push_back(mCenter);
    arc->drawSolidPoly(vecs.data(), (unsigned int)vecs.size(), color);
    mLayerSquare->addChild(arc);
}

bool ui_roulette::setValue(float val, const ccMenuCallback& callback) {
    if(mItemsIdx != 8)
        return false;
    
    mValue = val;
    
    Vec2 pos;
    float degree;
    for(int n=0; n < mItemsIdx; n++) {
        degree = 22.5 + 45 * n;
        
        pos.x = mCenter.x + (std::cosf(CC_DEGREES_TO_RADIANS(degree)) * mRadius) * 0.75;
        pos.y = mCenter.y + (std::sinf(CC_DEGREES_TO_RADIANS(degree)) * mRadius) * 0.75;
        
        mItems[n]->setRotation(90 - degree);
        mItems[n]->setPosition(pos);
        gui::inst()->setScale(mItems[n], mRadius * 0.25);
        mLayerSquare->addChild(mItems[n]);
    }
    
    float width = mRadius * 0.3 * 2;
    
    float fontSize = gui::inst()->getFontSize(Size(width, width), 0.75f);
    auto button = gui::inst()->addTextButton(0
                               , 0
                               , mStartString
                               , mLayer
                               , [=](Ref* pRef) {
                                   this->run(callback);
                               }
                               , fontSize
                               , ALIGNMENT_CENTER
                               , mColor.getColor3B()
                               , mLayer->getContentSize()
                               , Vec2(1,1)
                               , Vec2::ZERO
                               , Vec2::ZERO
                               , Vec2::ZERO
                               , Vec2::ZERO );
    if(button->getContentSize().width > width * 0.75f) {
        gui::inst()->setScale(button, width * 0.75f);
    }
    
    return true;
}
