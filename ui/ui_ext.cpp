#include "ui_ext.h"

#define _OPACITY    0.05f
/*
 drawCircleForPhysics
 */
DrawNode * guiExt::drawCircleForPhysics(Node * p, Vec2 pos, float radius, COLOR_RGB color){
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
DrawNode * guiExt::drawRectForPhysics(Node * p, Vec2 pos, Size size, COLOR_RGB color, bool isSolid, float thick){
    auto draw = DrawNode::create();
    if(isSolid) {
        draw->drawSolidRect(Vec2::ZERO, size, color.getColor4F());
        
        Color4F line = color.getColorDark().getColor4F();
        
        for(float n=0; n < thick; n = n + 0.1f) {
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
DrawNode * guiExt::drawRectRoundShadow (Node * p, Vec2 pos, Size size, COLOR_RGB& color) {
    Color4F colorShadow = color.getColorLight().getColor4F();
    Color4F colorMain = color.getColor4F();
    
    gui::inst()->drawRectRound(p, Vec2(pos.x, pos.y), size, colorShadow);
    return gui::inst()->drawRectRound(p, pos, Size(size.width - 2.f, size.height - 2.f), colorMain);
}

/*
 addRoulette
 */
ui_roulette * guiExt::addRoulette(Node * p, Size size, Vec2 center, COLOR_RGB& color, COLOR_RGB& bg, const string sz) {
    auto roulette = ui_roulette::create(size, center, color, bg, sz);
    if(p)
        p->addChild(roulette);
    return roulette;
}

/*
 addIconCircle
 */
//Layout * guiExt::addIconCircle (Node * p, Vec2 pos, ALIGNMENT align, float radius, const string sz, COLOR_RGB color, const string szText, COLOR_RGB colorText) {
//
//    Size sizeCircle = Size(radius * 2.f, radius * 2.f);
//    Size size = sizeCircle;
//
//    Color4F colorOut, colorInner, colorOutline;
//    Color3B colorSymbol;
//    colorOut = color.getColorDark().getColor4F();
//    colorInner = color.getColor4F();
//    colorOutline = color.getColorDark().getColorDark().getColor4F();
//    colorSymbol = color.getColorDark().getColorDark().getColor3B();
//
//    auto draw = DrawNode::create();
//    Vec2 centerInner = Vec2(radius, radius);
//
//    //outline
////    draw->drawDot(centerInner, radius, colorOutline);
//
//    //outcircle
//    draw->drawDot(centerInner, radius - .1, colorOut);
//
//    //inner circle
//    draw->drawDot(centerInner, radius * 0.8f, colorInner);
//
//    //circle text
//    float fontSize = gui::inst()->getFontSizeDefine(sizeCircle, -1);
//    auto label = Label::createWithSystemFont(sz, SYSTEM_FONT_NAME, fontSize);
//    label->setColor(colorSymbol);
//    gui::inst()->setAnchorPoint(label, ALIGNMENT_CENTER);
//    label->setPosition(centerInner);
//
//    Label * labelText = NULL;
//    //text
//    if(szText.size() > 0) {
//        float fontSizeText = gui::inst()->getFontSizeDefine(sizeCircle, 0);
//        labelText = Label::createWithTTF(szText, gui::inst()->mDefaultFont, fontSizeText);
//        labelText->setColor(colorText.getColor3B());
//        gui::inst()->setAnchorPoint(labelText, ALIGNMENT_LEFT_BOTTOM);
//        labelText->setPosition(Vec2(sizeCircle.width, 0));
//
//        size.width += labelText->getContentSize().width;
//    }
//
//    auto layer = Layout::create();
////    layer->setBackGroundColor(Color3B::MAGENTA);
////    layer->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
//    layer->setContentSize(size);
//
//    layer->addChild(draw);
//    layer->addChild(label);
//
//    if(labelText)
//        layer->addChild(labelText);
//
//    layer->setPosition(pos);
//    gui::inst()->setAnchorPoint(layer, align);
//
//
//    p->addChild(layer);
//    return layer;
//}
 /*
  addIconHeart
  */
//Layout * guiExt::addIconHeart (Node * p, Vec2 pos, ALIGNMENT align, float fontSize, COLOR_RGB color, const string sz) {
//    auto layer = Layout::create();
//    auto labelHeart = Label::createWithSystemFont("♥", SYSTEM_FONT_NAME, fontSize);
//    gui::inst()->setAnchorPoint(labelHeart, ALIGNMENT_LEFT_BOTTOM);
//    labelHeart->setPosition(Vec2::ZERO);
//    Size size = labelHeart->getContentSize();
//
//    if(sz.size() > 0) {
//        auto label = Label::createWithTTF(sz, gui::inst()->mDefaultFont, fontSize);
//        label->setColor(color.getColor3B());
//        gui::inst()->setAnchorPoint(label, ALIGNMENT_LEFT_BOTTOM);
//        label->setPosition(Vec2(size.width, 0));
//
//        size.width += label->getContentSize().width;
//        layer->setContentSize(size);
//
//
//        layer->addChild(labelHeart);
//        layer->addChild(label);
//    } else {
//        layer->setContentSize(size);
//        layer->addChild(labelHeart);
//    }
//
//    layer->setPosition(pos);
//    gui::inst()->setAnchorPoint(layer, align);
//
////    label->enableGlow(color.getColorDark().getColor4B());
//
//    p->addChild(layer);
//    return layer;
//}

Node * guiExt::addMovingEffect(Node * p
                               , COLOR_RGB bgColor
                               , const string img
                               , const string text
                               , COLOR_RGB fontColor
                               , bool toRight
                               , float speed
                               , CallFunc * pCallFunc
                               , CallFunc * pCallFuncInter) {
    auto layer = gui::inst()->createLayout(Size(p->getContentSize().width, p->getContentSize().height / 3), "", true, bgColor.getColor3B());
    gui::inst()->setAnchorPoint(layer, ALIGNMENT_LEFT);
    layer->setPosition(
                       Vec2(p->getContentSize().width * ((toRight) ? -1.f : 1.f), p->getContentSize().height / 2.f)
                       );
    layer->setOpacity(bgColor.getA());
    
    auto center = EaseBackIn::create(MoveTo::create(.4f * speed, Vec2(0, p->getContentSize().height / 2.f)));
    auto left = EaseBackOut::create(MoveTo::create(.4f * speed, Vec2(p->getContentSize().width * -1.f, p->getContentSize().height / 2.f)));
    auto right = EaseBackOut::create(MoveTo::create(.4f * speed, Vec2(p->getContentSize().width * 1.f, p->getContentSize().height / 2.f)));
    
    Vector<FiniteTimeAction*> arr;
    arr.pushBack(center);
    arr.pushBack(DelayTime::create(.4f * speed));
    if(pCallFuncInter)
        arr.pushBack(pCallFuncInter);
    arr.pushBack(toRight ? right : left);
    arr.pushBack(RemoveSelf::create());
    if(pCallFunc)
        arr.pushBack(pCallFunc);
    
    layer->runAction(Sequence::create( arr ));
    Vec2 gridText = Vec2(1,1);
    int posText = 0;
    int fontSize = -2;
    
    if(img.length() > 0) {
        auto sprite = gui::inst()->getSprite(img);
        gui::inst()->setScaleByHeight(sprite, layer->getContentSize().height / 2.f);
        sprite->setPosition(gui::inst()->getCenter(layer));
        sprite->runAction(Sequence::create(DelayTime::create(0.4f * speed)
                                           , ScaleBy::create(.2f * speed, 1.5)
                                           , ScaleBy::create(.2f * speed, 1 / 1.5)
                                           , NULL));
        layer->addChild(sprite);
        gridText = Vec2(1,2);
        posText = 1;
        fontSize = -2;
    }
    
    if(text.length() > 0) {
        auto txt = gui::inst()->addLabelAutoDimension(0, posText, text, layer, fontSize, ALIGNMENT_CENTER, fontColor.getColor3B(), gridText, Vec2::ZERO, Vec2::ZERO, Vec2::ZERO);
        txt->enableGlow(Color4B::BLACK);
        if(img.length() == 0) {
             
            txt->runAction(Sequence::create(DelayTime::create(.4f * speed)
                                            ,ScaleBy::create(.2f * speed, 1.5)
                                            , ScaleBy::create(.2f * speed, 1 / 1.5)
                                            , NULL));
         } else {
             txt->setOpacity(fontColor.getA());
         }
    }
    
    p->addChild(layer);
    
    return layer;
}

void guiExt::addVibrateEffect(Node * p, CallFunc * pCallFunc, float duration, float width) {
    Vec2 pos = p->getPosition();
    p->runAction(Sequence::create( MoveTo::create(duration, Vec2(pos.x - width, pos.y - width))
                                      , MoveTo::create(duration, Vec2(pos.x + width, pos.y + width))
                                      , MoveTo::create(duration, Vec2(pos.x - width, pos.y))
                                      , MoveTo::create(duration, Vec2(pos.x + width, pos.y))
                                      , MoveTo::create(duration, pos)
                                      , pCallFunc
                                      , NULL));
}

void guiExt::addScaleEffect(Node * p
                            , const string img
                            , const string text
                            , COLOR_RGB fontColor
                            , CallFunc * pCallFunc
                            , float duration
                            , float sizeRatio
                            , Vec2 specificPosition
                            , GLubyte opacity
                            ) {
    Size size = p->getContentSize();
    size.width *= sizeRatio;
    size.height *= sizeRatio;
    
    float min = fmin(size.width, size.height);
    
    auto layer = gui::inst()->createLayout(size);
    gui::inst()->setAnchorPoint(layer, ALIGNMENT_CENTER);
    
    Vec2 pos;
    if(specificPosition.x == -1 && specificPosition.y == -1)
        pos = gui::inst()->getCenter(p);
    else
        pos = specificPosition;
    
    layer->setPosition(pos);
    
    Vec2 grid = Vec2(1, 1);
    Vec2 position = Vec2::ZERO;
    float fontSize = -1;
    
    if(img.size() > 0) {
        auto pImg = gui::inst()->getSprite(img);
        gui::inst()->setScale(pImg, min);
        pImg->setPosition(gui::inst()->getCenter(layer));
        pImg->setOpacity(opacity);
        
        layer->addChild(pImg);
        grid.y++;
        position.y++;
        fontSize--;
    }
    
    if(text.size() > 0) {
        auto label = gui::inst()->addLabelAutoDimension(position.x, position.y, text, layer, fontSize, ALIGNMENT_CENTER, fontColor.getColor3B(), grid, Vec2::ZERO, Vec2::ZERO, Vec2::ZERO);
        label->enableGlow(Color4B::BLACK);
        label->setOpacity(fontColor.getA());
    }
    
    runScaleEffect(layer, pCallFunc, duration, true);
    
    p->addChild(layer);
}

void guiExt::runScaleEffect(Node * p, CallFunc * pCallFunc, float duration, bool isRemoveSelf) {
    Vector<FiniteTimeAction *> actions;
    float origin = p->getScale();
    actions.pushBack(EaseBackIn::create(ScaleBy::create(duration, 1.2f)));
    actions.pushBack(EaseBackOut::create(ScaleTo::create(duration, origin)));
    if(isRemoveSelf)
        actions.pushBack(RemoveSelf::create());
    if(pCallFunc)
        actions.pushBack(pCallFunc);
    
    Sequence * seq = Sequence::create(actions);
    p->runAction(seq);
    
//    p->runAction(Sequence::create(
//                                  EaseBackIn::create(ScaleTo::create(duration, 1.5f))
//                                  , EaseBackOut::create(ScaleTo::create(duration, 1.f))
//                                  , RemoveSelf::create()
//                                  , pCallFunc
//                                  , NULL));
  
}

void guiExt::runFlyEffect(Node * p, CallFunc * pCallFunc, float duration, bool isDown) {
    Vec2 direction = Vec2(p->getContentSize().width / 2.f, p->getContentSize().height * 1.5f);
    if(isDown) {
        direction.x *= -1.f;
        direction.y *= -1.f;
    }
    
    Spawn * spawn = Spawn::create(MoveBy::create(duration, direction)
                                  , FadeOut::create(duration)
                                  , NULL
                                  );
    Sequence * seq = Sequence::create(spawn, RemoveSelf::create(), pCallFunc, NULL);
    p->runAction(seq);
}

DrawNode * guiExt::drawRectCircleButton(Node * p, Vec2 pos, Size size, COLOR_RGB colorFront, COLOR_RGB colorBack) {
    DrawNode * draw;
    Size innerSize;
    if(colorBack.isValidColor) {
        draw = gui::inst()->drawRectCircle(p, pos, size, colorBack.getColor4F());
        float innerMargin = size.height * 0.1f;
        innerSize = Size(size.width - innerMargin, size.height - innerMargin);
        draw = gui::inst()->drawRectCircle(NULL, Vec2(pos.x, pos.y), innerSize, colorFront.getColorDark().getColor4F(), draw);
    } else {
        draw = gui::inst()->drawRectCircle(p, pos, size, colorFront.getColorDark().getColor4F());
        innerSize = size;
    }
    
    float shadowMargin = innerSize.height * 0.1f;
    draw = gui::inst()->drawRectCircle(NULL, Vec2(pos.x, pos.y + (shadowMargin / 2.f)), Size(innerSize.width, innerSize.height - shadowMargin), colorFront.getColor4F(), draw);
    
    return draw;
}
