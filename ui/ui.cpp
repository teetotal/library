//
// Created by daejung on 2018-07-24.
//

#include "ui.h"

gui * gui::hInstance = NULL;

void gui::init(const char* font, int fontSize, Color4F bgColor, bool useSpriteCache) {
	if (mIsInitialized)
		return;
	mIsInitialized = true;
    
    Rect rect = Director::getInstance()->getSafeAreaRect();
    /*
     XS: origin [26, 61.5], size [427, 209]
     6s: origin [0, 25.0], size [480, 269.8]
     */
    mVisibleSize = rect.size;
    mOrigin = rect.origin;
    
/*
    auto visibleSize = Director::getInstance()->getVisibleSize();
    mVisibleSize = visibleSize;
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    mOrigin = origin;
 */
    mResolution = Director::getInstance()->getWinSizeInPixels();


    mOriginX = mOrigin.x;
    mOriginY = mOrigin.y;

    mVisibleX = mVisibleSize.width;
    mVisibleY = mVisibleSize.height;

    mDefaultFont = font;
    auto labelHeight = Label::createWithTTF("j", mDefaultFont, 10);
    auto labelWidth = Label::createWithTTF("M", mDefaultFont, 10);
    mDefaultFontLabelSize.width = labelWidth->getContentSize().width;
    mDefaultFontLabelSize.height = labelHeight->getContentSize().height;
    
    mDefaultFontSize = fontSize;

    MenuItemFont::setFontName(font);
    MenuItemFont::setFontSize(fontSize);

    Director::getInstance()->setClearColor(bgColor);

	mUseSpriteCache = useSpriteCache;
}
// about pixel --------------------------------------------------------------------------------
float gui::getRealPixel(float x){
    return mResolution.width * x / mVisibleX;
}

float gui::getSizeFromRealPixel(float x){

    return mVisibleX * x / mResolution.width;
}
// Get Point --------------------------------------------------------------------------------
bool gui::getPoint(int x, int y, float &pointX, float &pointY, ALIGNMENT align
        , Size dimension
        , Vec2 grid
        , Vec2 origin
        , Vec2 margin
        , Vec2 innerMargin
    ){

    int gridX = grid.x == INVALID_VALUE ? GRID_X : grid.x;
    int gridY = grid.y == INVALID_VALUE ? GRID_Y : grid.y;

    float originX = origin.x == INVALID_VALUE ? mOriginX : origin.x;
    float originY = origin.y == INVALID_VALUE ? mOriginY : origin.y;

    float marginX = margin.x == INVALID_VALUE ? GRID_MARGIN : margin.x;
    float marginY = margin.y == INVALID_VALUE ? GRID_MARGIN : margin.y;
    
    float innerMarginX = innerMargin.x == INVALID_VALUE ? GRID_INNER_MARGIN : innerMargin.x;
    float innerMarginY = innerMargin.y == INVALID_VALUE ? GRID_INNER_MARGIN : innerMargin.y;

    float dimensionX = dimension.width == INVALID_VALUE ? mVisibleX : dimension.width - (marginX * 2.f);
    float dimensionY = dimension.height == INVALID_VALUE ? mVisibleY : dimension.height - (marginY * 2.f);

    float gridWidth = dimensionX / gridX;
    float gridHeight = dimensionY / gridY;


    pointX = (gridWidth * (float)x) + originX + marginX;
    pointY = originY + marginY + dimensionY -  (gridHeight * (float)y) ;

    if(align == ALIGNMENT_NONE)
        return true;
    
    switch(align){
        case ALIGNMENT_CENTER:
            pointX += gridWidth / 2.f;
            pointY -= gridHeight/ 2.f;
            break;
        case ALIGNMENT_CENTER_TOP:
            pointX += gridWidth / 2.f;
            pointY -= innerMarginY;
            break;
        case ALIGNMENT_CENTER_BOTTOM:
            pointX += gridWidth / 2.f;
            pointY -= gridHeight - innerMarginY;
            break;
        case ALIGNMENT_LEFT:
            pointX += innerMarginX;
            pointY -= gridHeight/ 2.f;
            break;
        case ALIGNMENT_LEFT_TOP:
            pointX += innerMarginX;
            pointY -= innerMarginY;
            break;
        case ALIGNMENT_LEFT_BOTTOM:
            pointX += innerMarginX;
            pointY -= gridHeight - innerMarginY;
            break;
        case ALIGNMENT_RIGHT:
            pointX += gridWidth;
            pointX -= innerMarginX;
            pointY -= gridHeight/ 2.f;
            break;
        case ALIGNMENT_RIGHT_TOP:
            pointX += gridWidth;
            pointX -= innerMarginX;
            pointY -= innerMarginY;
            break;
        case ALIGNMENT_RIGHT_BOTTOM:
            pointX += gridWidth;
            pointX -= innerMarginX;
            pointY -= gridHeight - innerMarginY;
            break;
        default:
            break;
    }
    return true;
}

Vec2 gui::getPointVec2(int x
                       , int y
                       , ALIGNMENT align
                       , Size dimension
                       , Vec2 grid
                       , Vec2 origin
                       , Vec2 margin
                       , Vec2 innerMargin
                       , Vec2 span)
{
    if(span.x == 0 && span.y ==0) {
        Vec2 p;
        getPoint(x, y, p, align, dimension, grid, origin, margin, innerMargin);
        return p;
    }
    
    Size gridSizeNoMargin = getGridSize(dimension, grid, margin, Vec2::ZERO);
    Vec2 posNoMargin;
    getPoint(x, y, posNoMargin, align, dimension, grid, origin, margin, Vec2::ZERO);

    float moveX = 0.f, moveY = 0.f;
    
    if(span.x > 0) {
        switch (align) {
            case ALIGNMENT_CENTER:
            case ALIGNMENT_CENTER_TOP:
            case ALIGNMENT_CENTER_BOTTOM:
                moveX = 0.5f;
                break;
            case ALIGNMENT_RIGHT:
            case ALIGNMENT_RIGHT_TOP:
            case ALIGNMENT_RIGHT_BOTTOM:
                moveX = 1.f;
                break;
            default:
                break;
        }
    }
    
    if(span.y > 0) {
        switch (align) {
            case ALIGNMENT_CENTER:
            case ALIGNMENT_LEFT:
            case ALIGNMENT_RIGHT:
                moveY = 0.5f;
                break;
            case ALIGNMENT_CENTER_BOTTOM:
            case ALIGNMENT_LEFT_BOTTOM:
            case ALIGNMENT_RIGHT_BOTTOM:
                moveY = 1.f;
                break;
            default:
                break;
        }
    }
    posNoMargin.x += (gridSizeNoMargin.width * moveX * span.x);
    posNoMargin.y -= (gridSizeNoMargin.height * moveY * span.y);
    
    switch(align){
        case ALIGNMENT_CENTER_TOP:
            posNoMargin.y -= innerMargin.y;
            break;
        case ALIGNMENT_CENTER_BOTTOM:
            posNoMargin.y += innerMargin.y;
            break;
        case ALIGNMENT_LEFT:
            posNoMargin.x += innerMargin.x;
            break;
        case ALIGNMENT_LEFT_TOP:
            posNoMargin.x += innerMargin.x;
            posNoMargin.y -= innerMargin.y;
            break;
        case ALIGNMENT_LEFT_BOTTOM:
            posNoMargin.x += innerMargin.x;
            posNoMargin.y += innerMargin.y;
            break;
        case ALIGNMENT_RIGHT:
            posNoMargin.x -= innerMargin.x;
            break;
        case ALIGNMENT_RIGHT_TOP:
            posNoMargin.x -= innerMargin.x;
            posNoMargin.y -= innerMargin.y;
            break;
        case ALIGNMENT_RIGHT_BOTTOM:
            posNoMargin.x -= innerMargin.x;
            posNoMargin.y += innerMargin.y;
            break;
        default:
            break;
    }
    return posNoMargin;
};
// setAnchorPoint --------------------------------------------------------------------------------
void gui::setAnchorPoint(Node * p, ALIGNMENT align) {
    switch(align) {
        case ALIGNMENT_CENTER:
            p->setAnchorPoint(Vec2(0.5, 0.5));
            break;
        case ALIGNMENT_CENTER_TOP:
            p->setAnchorPoint(Vec2(0.5, 1));
            break;
        case ALIGNMENT_CENTER_BOTTOM:
            p->setAnchorPoint(Vec2(0.5, 0));
            break;
        case ALIGNMENT_LEFT:
            p->setAnchorPoint(Vec2(0, 0.5));
            break;
        case ALIGNMENT_LEFT_TOP:
            p->setAnchorPoint(Vec2(0, 1));
            break;
        case ALIGNMENT_LEFT_BOTTOM:
            p->setAnchorPoint(Vec2(0, 0));
            break;
        case ALIGNMENT_RIGHT:
            p->setAnchorPoint(Vec2(1, 0.5));
            break;
        case ALIGNMENT_RIGHT_TOP:
            p->setAnchorPoint(Vec2(1, 1));
            break;
        case ALIGNMENT_RIGHT_BOTTOM:
            p->setAnchorPoint(Vec2(1, 0));
            break;
        default:
            break;
    }
};
// drawGrid --------------------------------------------------------------------------------
bool gui::drawGrid(Node * p, Size dimension, Vec2 grid, Vec2 origin, Vec2 margin, Color4F color){
    int gridX = grid.x == INVALID_VALUE ? GRID_X : grid.x;
    int gridY = grid.y == INVALID_VALUE ? GRID_Y : grid.y;

    for(int x = 0; x <= gridX; x++){
        auto draw = DrawNode::create();
        float startX, startY, endX, endY;
        getPoint(x
                 ,0
                 , startX
                 , startY
                 , ALIGNMENT_NONE
                 , dimension
                 , grid
                 , origin
                 , margin
                 , Vec2::ZERO
                 );
        getPoint(x, gridY, endX, endY, ALIGNMENT_NONE, dimension
                , grid
                , origin
                , margin);
        draw->drawLine(Point(startX, startY), Point(endX, endY), color);
        p->addChild(draw);
    }

    for(int y=0; y<=gridY; y++){
        auto draw = DrawNode::create();
        float startX, startY, endX, endY;
        getPoint(0,y, startX, startY, ALIGNMENT_NONE, dimension
                , grid
                , origin
                , margin);
        getPoint(gridX, y, endX, endY, ALIGNMENT_NONE, dimension
                , grid
                , origin
                , margin);
        draw->drawLine(Point(startX, startY), Point(endX, endY), color);
        p->addChild(draw);
    }

    return true;
}

bool gui::drawPoint(Node *p) {
    for(int x =0; x < GRID_X; x ++){
        for(int y=0; y < GRID_Y; y++){
            std::string sz = std::to_string(x);
            sz += ",";
            sz += std::to_string(y);

            auto labelPoint = Label::createWithTTF(sz, mDefaultFont, 14);
            if(labelPoint == NULL)
                return false;
            labelPoint->setColor(Color3B::GRAY);
            float labelX, labelY;
            getPoint(x,y, labelX, labelY, ALIGNMENT_CENTER);
            labelPoint->setPosition(Vec2(labelX, labelY));
            //labelPoint->setAnchorPoint(Vec2(0,1));
            p->addChild(labelPoint, 1);
        }
    }
    return true;
}
// addBG --------------------------------------------------------------------------------
Sprite * gui::addBG(const string bgImg, Node * parent, bool isOnLayer) {
    auto bg = (mUseSpriteCache == false) ? Sprite::create(bgImg) : Sprite::createWithSpriteFrameName(bgImg);
    bg->setContentSize(Director::getInstance()->getVisibleSize());
    if(!isOnLayer)
        bg->setPosition(getCenter());
    else {
        bg->setPosition(Vec2(parent->getContentSize().width / 2, parent->getContentSize().height / 2));
    }
    parent->addChild(bg);
    
    return bg;
}
// Label --------------------------------------------------------------------------------
Label * gui::createLabel(int x
                         , int y
                         , const string text
                         , float fontSize
                         , ALIGNMENT align
                         , const Color3B color
                         , Size dimension
                         , Vec2 grid
                         , Vec2 origin
                         , Vec2 margin
                         , Vec2 innerMargin
                         , Vec2 span) {
    switch((int)fontSize) {
        case 0:
            fontSize = gui::getFontSize(getGridSize(dimension, grid, margin, innerMargin, span));
            break;
        case -1:
            fontSize = gui::getFontSize(getGridSize(dimension, grid, margin, innerMargin, span), 0.75f);
            break;
        case -2:
            fontSize = gui::getFontSize(getGridSize(dimension, grid, margin, innerMargin, span), 0.5f);
            break;
        case -3:
            fontSize = gui::getFontSize(getGridSize(dimension, grid, margin, innerMargin, span), 0.25f);
            break;
        default:
            break;
    }
    
    Label * label = Label::createWithTTF(text, mDefaultFont, fontSize);
    label->setColor(color);
    label->setPosition(getPointVec2(x, y, align, dimension, grid, origin, margin, innerMargin, span));
    setAnchorPoint(label, align);
    
    return label;
}

Label * gui::addLabel(Node *p
                      , int x
                      , int y
                      , const string text
                      , float fontSize
                      , ALIGNMENT align
                      , const Color3B color
                      , Size dimension
                      , Vec2 grid
                      , Vec2 origin
                      , Vec2 margin
                      , Vec2 innerMargin
                      , Vec2 span
                      , const string img
                      , bool isBGImg)
{

    Label * label = createLabel(x, y, text, fontSize, align, color, dimension, grid, origin, margin, innerMargin, span);

    if(img.compare("") != 0) {
        Size sizePerGrid = getGridSize(p->getContentSize(), grid, margin, innerMargin, span);
        
        auto sprite = (mUseSpriteCache == false) ? Sprite::create(img) : Sprite::createWithSpriteFrameName(img);
        if(sizePerGrid.width > sizePerGrid.height)
            setScaleByHeight(sprite, sizePerGrid.height);
        else
            setScale(sprite, sizePerGrid.width);
        //bg
        if(isBGImg){
            sprite->setPosition(getPointVec2(x, y, ALIGNMENT_CENTER, dimension, grid, origin, margin, innerMargin, span));
            setAnchorPoint(sprite, ALIGNMENT_CENTER);
            p->addChild(sprite);
            p->addChild(label);

        } else {
            float spriteWidth = sprite->getContentSize().width * sprite->getScale();
            float labelWidth = label->getContentSize().width;
            setAnchorPoint(sprite, ALIGNMENT_LEFT);
            setAnchorPoint(label, ALIGNMENT_LEFT);
            sprite->setPosition(Vec2(0, sizePerGrid.height / 2.f));
            label->setPosition(Vec2(spriteWidth, sprite->getPosition().y));
            
            auto layer = createLayout(Size(spriteWidth + labelWidth, sizePerGrid.height));
            layer->addChild(sprite);
            layer->addChild(label);
            
            layer->setPosition(getPointVec2(x, y, align, dimension, grid, origin, margin, innerMargin, span));
            setAnchorPoint(layer, align);
            p->addChild(layer);
        }
    } else {
        p->addChild(label);
    }

    return label;
}
// Text Button --------------------------------------------------------------------------------
MenuItemLabel * gui::addTextButtonRaw(Menu* &pMenu
                                      , int x
                                      , int y
                                      , const string text
                                      , Node *p
                                      , const ccMenuCallback &callback
                                      , float fontSize
                                      , ALIGNMENT align
                                      , const Color3B color
                                      , Size dimension
                                      , Vec2 grid
                                      , Vec2 origin
                                      , Vec2 margin
                                      , Vec2 innerMargin
                                      , Vec2 span
                                      , const string img
                                      , bool isBGImg
                                      , bool isAttachParent
                                      , Vec2 specificPos)
{
    switch((int)fontSize) {
        case 0:
            fontSize = gui::getFontSize(getGridSize(dimension, grid, margin, innerMargin, span));
            break;
        case -1:
            fontSize = gui::getFontSize(getGridSize(dimension, grid, margin, innerMargin, span), 0.75f);
            break;
        case -2:
            fontSize = gui::getFontSize(getGridSize(dimension, grid, margin, innerMargin, span), 0.5f);
            break;
        case -3:
            fontSize = gui::getFontSize(getGridSize(dimension, grid, margin, innerMargin, span), 0.25f);
            break;
        default:
            break;
    }
    
    auto label = Label::createWithTTF(text, mDefaultFont, fontSize);
    label->setColor(color);
    
    auto pItem = MenuItemLabel::create(label, callback);
    Node * child = NULL;
    pMenu = Menu::create(pItem, NULL);
    child = pMenu;

    
    if(img.compare("") != 0) {
        Size sizePerGrid = getGridSize(p->getContentSize(), grid, margin, innerMargin, span);
        
        auto sprite = (mUseSpriteCache == false) ? Sprite::create(img) : Sprite::createWithSpriteFrameName(img);
        if(sizePerGrid.width > sizePerGrid.height)
            setScaleByHeight(sprite, sizePerGrid.height);
        else
            setScale(sprite, sizePerGrid.width);
        //bg
        if(isBGImg){
            sprite->setPosition(getPointVec2(x, y, ALIGNMENT_CENTER, dimension, grid, origin, margin, innerMargin, span));
            setAnchorPoint(sprite, ALIGNMENT_CENTER);
            p->addChild(sprite);
            setAnchorPoint(pItem, align);
            pMenu->setPosition(getPointVec2(x, y, align, dimension, grid, origin, margin, innerMargin, span));
            
        } else{
            float spriteWidth = sprite->getContentSize().width * sprite->getScale();
            float labelWidth = label->getContentSize().width;
            setAnchorPoint(sprite, ALIGNMENT_LEFT);
            setAnchorPoint(pItem, ALIGNMENT_LEFT);
            sprite->setPosition(Vec2(0.f, sizePerGrid.height / 2.f));
            pMenu->setPosition(Vec2(spriteWidth, sprite->getPosition().y));
            
            auto layer = createLayout(Size(spriteWidth + labelWidth, sizePerGrid.height));
            layer->addChild(sprite);
            layer->addChild(pMenu);
            
            layer->setPosition(getPointVec2(x, y, align, dimension, grid, origin, margin, innerMargin, span));
            setAnchorPoint(layer, align);
            
            child = layer;
        }
    } else{
        setAnchorPoint(pItem, align);
    }
    
    if(specificPos.x != GRID_INVALID_VALUE && specificPos.y != GRID_INVALID_VALUE) {
        child->setPosition(specificPos);
    } else {
        child->setPosition(getPointVec2(x, y, align, dimension, grid, origin, margin, innerMargin, span));
    }
    
    if(isAttachParent)
        p->addChild(child);
    
    return pItem;
}
// Sprite Button --------------------------------------------------------------------------------
MenuItemImage * gui::addSpriteButtonRaw(Menu* &pMenu
                                        , int x
                                        , int y
                                        , const string normalImg
                                        , const string selectImg
                                        , Node *p
                                        , const ccMenuCallback &callback
                                        , ALIGNMENT align
                                        , Size dimension
                                        , Vec2 grid
                                        , Vec2 origin
                                        , Vec2 margin
                                        , Vec2 innerMargin
                                        , Vec2 span
                                        , Vec2 specificPos)
{
    auto pItem = MenuItemImage::create(normalImg, selectImg, callback);
    pMenu = Menu::create(pItem, NULL);
    
    setAnchorPoint(pItem, align);
    if(specificPos.x != INVALID_VALUE && specificPos.y != INVALID_VALUE) {
        pMenu->setPosition(specificPos);
    } else {
        pMenu->setPosition(getPointVec2(x, y, align, dimension, grid, origin, margin, innerMargin, span));
    }
    
    p->addChild(pMenu);
    
    return pItem;
}
// Sprite --------------------------------------------------------------------------------
Sprite * gui::addSprite(int x
                        , int y
                        , const string img
                        , Node *p
                        , ALIGNMENT align
                        , Size dimension
                        , Vec2 grid
                        , Vec2 origin
                        , Vec2 margin
                        , Vec2 innerMargin
                        , Vec2 span
                        , const Size &spriteSize)
{
    Sprite * sprite = (mUseSpriteCache == false) ? Sprite::create(img) : Sprite::createWithSpriteFrameName(img);
    if(spriteSize.width != INVALID_VALUE && spriteSize.height != INVALID_VALUE) {
        sprite->setScale(spriteSize.width / sprite->getContentSize().width, spriteSize.height / sprite->getContentSize().height);
    }
    setAnchorPoint(sprite, align);
    sprite->setPosition(getPointVec2(x, y, align, dimension, grid, origin, margin, innerMargin, span));
    p->addChild(sprite);
    return sprite;
}
// addProgressBar --------------------------------------------------------------------------------
LoadingBar * gui::addProgressBar(int x
                                 , int y
                                 , const string img
                                 , Node * p
                                 , Vec2 scaleSize
                                 , float defaultVal
                                 , Size dimension
                                 , Vec2 grid
                                 , Vec2 origin
                                 , Vec2 margin
                                 , Vec2 innerMargin
                                 , LoadingBar::Direction direction)
{
    
    Vec2 point = getPointVec2(x, y, ALIGNMENT_LEFT, dimension, grid, origin, margin, innerMargin);
    
    LoadingBar * loadingBar = LoadingBar::create(img);
    setAnchorPoint(loadingBar, ALIGNMENT_LEFT);
    loadingBar->setDirection(direction);
    loadingBar->setPosition(point);
    loadingBar->setPercent(defaultVal);
    loadingBar->setScale(scaleSize.x / loadingBar->getContentSize().width, scaleSize.y / loadingBar->getContentSize().height);
    
    //progress backgroung image
    auto bgProgress = (mUseSpriteCache == false) ? Sprite::create(img) : Sprite::createWithSpriteFrameName(img);
    setAnchorPoint(bgProgress, ALIGNMENT_LEFT);
    bgProgress->setOpacity(50);
    bgProgress->setPosition(point);
    bgProgress->setScale(scaleSize.x / bgProgress->getContentSize().width, scaleSize.y / bgProgress->getContentSize().height);
    
    p->addChild(bgProgress);
    p->addChild(loadingBar);
    
    return loadingBar;
}

// draws --------------------------------------------------------------------------------
DrawNode * gui::drawLine(Node * p, Vec2 start, Vec2 end, Color4F color, GLfloat width)
{
    auto draw = DrawNode::create();
    draw->setLineWidth(width);
    draw->drawLine(start, end, color);
    
    p->addChild(draw);
    return draw;
}

DrawNode * gui::drawCircle(Node * p, Vec2 center, float radius, Color4F color){
    auto draw = DrawNode::create();
    draw->drawDot(center, radius, color);
    draw->setContentSize(Size(radius * 2, radius * 2));
    p->addChild(draw);
    return draw;
}

DrawNode * gui::drawTriangle(Node * p, Vec2 a, Vec2 b, Vec2 c, Color4F color){
    auto draw = DrawNode::create();
    draw->drawTriangle(a, b, c, color);
    
    p->addChild(draw);
    return draw;
}

DrawNode * gui::drawRect(Node * p, Vec2 pos1, Vec2 pos2, Vec2 pos3, Vec2 pos4, Color4F color){
    auto draw = DrawNode::create();
    
    draw->drawRect(pos1, pos2, pos3, pos4, color);
    
    p->addChild(draw);
    return draw;
}

DrawNode * gui::drawRect(Node * p, Vec2 pos, Size size, Color4F color, bool isSolid){
    auto draw = DrawNode::create();
    
    Vec2 origin = Vec2(pos.x - size.width / 2, pos.y - size.height / 2);
    Vec2 dest = Vec2(pos.x + size.width / 2, pos.y + size.height / 2);
    if(isSolid)
        draw->drawSolidRect(origin, dest, color);
    else
        draw->drawRect(origin, dest, color);
    
    p->addChild(draw);
    return draw;
}

DrawNode * gui::drawRectRound (Node * p, Vec2 pos, Size size, Color4F color){
    auto draw = DrawNode::create();
   
    Vec2 origin = Vec2(pos.x - size.width / 2.f, pos.y - size.height / 2.f);
    Vec2 dest = Vec2(pos.x + size.width / 2.f, pos.y + size.height / 2.f);
    
//    float ratio = 0.04f / 2.f;
//    Vec2 marignBound = Vec2(size.width * ratio, size.height * ratio);
//    float margin = (marignBound.x > marignBound.y) ? marignBound.x : marignBound.y;
    
    float margin = 1.f;
    
    Vec2 poli[9] = {
        Vec2(origin.x + margin    , origin.y)
        , Vec2(dest.x - margin  , origin.y)
        , Vec2(dest.x           , origin.y + margin)
        , Vec2(dest.x           , dest.y - margin)
        , Vec2(dest.x - margin  , dest.y)
        , Vec2(origin.x + margin, dest.y)
        , Vec2(origin.x         , dest.y - margin)
        , Vec2(origin.x         , origin.y + margin)
        , Vec2(origin.x + margin, origin.y)
    };
    
    draw->drawSolidPoly(poli, 9, color);
    p->addChild(draw);
    
    return draw;
}

DrawNode * gui::drawDiamond(Node * p, Vec2 pos, Size size, Color4F color){
    auto draw = DrawNode::create();
    
    Vec2 vLeft = Vec2(pos.x - size.width / 2, pos.y);
    Vec2 vRight = Vec2(pos.x + size.width / 2, pos.y);
    Vec2 vTop = Vec2(pos.x, pos.y + size.height / 2);
    Vec2 vBottom = Vec2(pos.x, pos.y - size.height / 2);
    
    draw->drawTriangle(vLeft, vRight, vTop, color);
    draw->drawTriangle(vLeft, vRight, vBottom, color);
    
    p->addChild(draw);
    
    return draw;
}

float gui::drawDiamond(cocos2d::Node *p, Vec2 center, float h, float degrees, cocos2d::Color4F color) {
    double xLen = getTanLen(h, degrees);
    Vec2 vLeft = Vec2(center.x - xLen, center.y);
    Vec2 vRight = Vec2(center.x + xLen, center.y);
    
    Vec2 vTop = Vec2(center.x, center.y + h);
    Vec2 vBottom = Vec2(center.x, center.y - h);
    
    auto draw = DrawNode::create();
    
    draw->drawTriangle(vLeft, vRight, vTop, color);
    draw->drawTriangle(vLeft, vRight, vBottom, color);
    
    p->addChild(draw);
    
    return xLen;
}

void gui::drawDiamondTile(Node * p, Vec2 counts, Color4F color) {
    Vec2 grid = Vec2(p->getContentSize().width / counts.x, p->getContentSize().height / counts.y);
    for(int x=0; x < counts.x; x++ ) {
        for(int y=0; y < counts.y; y++ ) {
            Vec2 pos = Vec2(x * grid.x + (grid.x / 2.f), y * grid.y + (grid.y / 2.f));
            drawDiamond(p, pos, Size(grid), color);
        }
    }
}

// set modal  --------------------------------------------------------------------------------
void gui::setModal(Node * layer) {
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [this](Touch *touch,Event*event)->bool {
        return true;
    };
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, layer);
}

// createLayout  --------------------------------------------------------------------------------
Layout * gui::createLayout(Size size, const string bgImg, bool hasBGColor, Color3B bgColor){
    Layout* l = Layout::create();
    l->setContentSize(size);
    if(hasBGColor){
        l->setBackGroundColor(bgColor);
        l->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
    }
    
    if(bgImg.compare("") != 0){
        //l->setBackGroundImage(bgImg);
        //l->setBackGroundImageScale9Enabled(true);
        auto img = Sprite::create(bgImg);
//        float min = (l->getContentSize().width > l->getContentSize().height) ? l->getContentSize().height : l->getContentSize().width;
        img->setScaleX(size.width / img->getContentSize().width);
        img->setScaleY(size.height / img->getContentSize().height);
        img->setPosition(Vec2(size.width / 2.f, size.height / 2.f));
        l->addChild(img);
    }
    
    
    
    return l;
}

// addScrollView  --------------------------------------------------------------------------------
ScrollView * gui::addScrollView(Size size, Size innerSize, Vec2 position, Node * parent) {
    ScrollView * sv = ScrollView::create();
    sv->setContentSize(size);
    sv->setPosition(position);
    sv->setInnerContainerSize(innerSize);
    ScrollView::Direction d = ScrollView::Direction::NONE;
    
    if(size.width < innerSize.width && size.height < innerSize.height) {
        d = ScrollView::Direction::BOTH;
    }
    else if(size.width < innerSize.width) {
        d = ScrollView::Direction::HORIZONTAL;
    }
    else if(size.height < innerSize.height) {
        d = ScrollView::Direction::VERTICAL;
    }
    
    sv->setDirection(d);
    sv->setScrollBarPositionFromCorner(Vec2::ZERO);
    
    if (parent != NULL)
        parent->addChild(sv);
    
    return sv;
}

// getGridSize  --------------------------------------------------------------------------------
Size gui::getGridSize(Size dimension, Vec2 grid, Vec2 margin, Vec2 innerMargin, Vec2 span) {
    Size size;
    size.width  = ((dimension.width -(margin.x * 2.f)) / grid.x);
    size.height = ((dimension.height - (margin.y * 2.f)) / grid.y);
    
    size.width += size.width * span.x;
    size.height += size.height * span.y;
    
    size.width  -= (innerMargin.x * 2.f);
    size.height -= (innerMargin.y * 2.f);
    
    return size;
}

LayerColor * gui::createModalLayer(LayerColor * &layerBG, Size size, const string bgImg, Color4B bgColor) {
	mModalTouchCnt = 0;
    //layerBG = LayerColor::create(Color4B::BLACK);
    layerBG = new (std::nothrow) LayerColor();
    layerBG->initWithColor(Color4B::BLACK);

    layerBG->setContentSize(Size(mVisibleX, mVisibleY));

    layerBG->setPosition(Vec2(mOriginX, mOriginY));
    layerBG->setOpacity(DEFAULT_OPACITY);

    //LayerColor * layer = cocos2d::LayerColor::create(bgColor);
    LayerColor * layer = new (std::nothrow) LayerColor();
    layer->initWithColor(bgColor);

    layer->setContentSize(size);
    layer->setPosition(Vec2(mVisibleX / 2 - (size.width / 2),
                            (mVisibleY / 2) - (size.height / 2)
                       )
    );

    //drawGrid(layer, size, Size(GRID_INVALID_VALUE, GRID_INVALID_VALUE), Size::ZERO, Size::ZERO);

    if(bgImg.compare("") != 0){
        auto sprite = (mUseSpriteCache == false) ? Sprite::create(bgImg) : Sprite::createWithSpriteFrameName(bgImg); 
        sprite->setContentSize(size);
        sprite->setPosition(Vec2::ZERO);
        sprite->setAnchorPoint(Vec2::ZERO);
        layer->addChild(sprite);
    }

    layerBG->addChild(layer);

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [this](Touch *touch,Event*event)->bool {
        CCLOG("x %f, y: %f"
        , touch->getLocation().x
        , touch->getLocation().y
        );
		mModalTouchCnt++;
        return true;
    };

    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, layerBG);

    return layer;
}

LayerColor * gui::addPopup(LayerColor * &layerBG, Node * p, Size size, const string bgImg, Color4B bgColor){

    Vec2 start = getPointVec2(0, 6);
    Vec2 end = getPointVec2(8, 0);
    Size sizeLayer = Size(end.x - start.x, end.y - start.y);
    LayerColor * layer = createModalLayer(layerBG, sizeLayer, bgImg, bgColor);
    p->addChild(layerBG);
    return layer;
}

void gui::addLayoutToScrollView(ScrollView * p, Layout * e, float margin, int newlineInterval){
    ssize_t nCount = p->getChildrenCount();
    float x, y;

    if(newlineInterval == 0) {
        x = nCount * (e->getContentSize().width + margin) + (margin);
		y = (p->getInnerContainerSize().height / 2) + (e->getContentSize().height / 2);
    } else {
        x = (nCount % newlineInterval) * (e->getContentSize().width + margin) + (margin);
        y = (p->getInnerContainerSize().height) - (nCount / newlineInterval) * (e->getContentSize().height + margin);

    }
    e->setAnchorPoint(Vec2(0, 1));
    e->setPosition(Vec2(x, y));
    p->addChild(e);
}

Size gui::getScrollViewSize(Vec2 p1, Vec2 p2, Size size, Size grid, Size origin, Size margin) {
//    if (size.width <= 0) size = Director::getInstance()->getVisibleSize();

	float svX1, svY1, svX2, svY2;
	getPoint(p1.x, p1.y, svX1, svY1, ALIGNMENT_NONE, size, grid, origin, margin);
	getPoint(p2.x, p2.y, svX2, svY2, ALIGNMENT_NONE, size, grid, origin, margin);

	return Size(svX2 - svX1, std::max(svY1, svY2) - std::min(svY1, svY2));
}


void gui::addBGScrolling(const string img, Node * p, float duration){
    auto sprite1 = (mUseSpriteCache == false) ? Sprite::create(img) : Sprite::createWithSpriteFrameName(img);
    auto sprite2 = (mUseSpriteCache == false) ? Sprite::create(img) : Sprite::createWithSpriteFrameName(img);
    auto sprite3 = (mUseSpriteCache == false) ? Sprite::create(img) : Sprite::createWithSpriteFrameName(img); // 카메라 전환시 빈공간 메꿔주기 위해 추가

    Vec2 point = Vec2(mVisibleX / 2 + mOriginX, mVisibleY / 2 + mOriginY);
    sprite1->setContentSize(Size(mVisibleX, mVisibleY));
    sprite1->setAnchorPoint(Vec2(0.5, 0.5));
    sprite1->setPosition(point);

    Vec2 point2 = Vec2(point.x + sprite1->getContentSize().width , point.y);
    sprite2->setContentSize(Size(mVisibleX, mVisibleY));
    sprite2->setAnchorPoint(Vec2(0.5, 0.5));
    sprite2->setPosition(point2);


    Vec2 point3 = Vec2(point.x + sprite1->getContentSize().width *2, point.y);
    sprite3->setContentSize(Size(mVisibleX, mVisibleY));
    sprite3->setAnchorPoint(Vec2(0.5, 0.5));
    sprite3->setPosition(point3);


    Vec2 finishPoint = Vec2(point.x * -1, point.y);
	if (duration > 0) {
		auto seq1 = RepeatForever::create(Sequence::create(
			MoveTo::create(duration, finishPoint)
			, Place::create(point)
			, NULL
		));

		auto seq2 = RepeatForever::create(Sequence::create(
			MoveTo::create(duration, point)
			, Place::create(point2)
			, NULL
		));

		auto seq3 = RepeatForever::create(Sequence::create(
			MoveTo::create(duration, point2)
			, Place::create(point3)
			, NULL
		));

		sprite1->runAction(seq1);
		sprite2->runAction(seq2);
		sprite3->runAction(seq3);
	}
    p->addChild(sprite1);
    p->addChild(sprite2);
    p->addChild(sprite3);
}

Layout * gui::addQuantityLayer(Node * p, Size size, Size margin
	, Sprite* &sprite, Label * &label, Label * &labelQuantity, Label* &labelPrice
	, const string szSubmit
	, const ccMenuCallback& callbackDec
	, const ccMenuCallback& callbackInc
	, const ccMenuCallback& callbackSubmit
) {
	//quantity
	Vec2 s, e;
	gui::inst()->getPoint(7, 7, s, ALIGNMENT_NONE, size, Size(GRID_INVALID_VALUE, GRID_INVALID_VALUE), Size::ZERO, margin);
	gui::inst()->getPoint(9, 1, e, ALIGNMENT_NONE, size, Size(GRID_INVALID_VALUE, GRID_INVALID_VALUE), Size::ZERO, margin);

	Size sizeQunatity = Size(e.x - s.x, e.y - s.y);
	Layout * layerQunatity = gui::inst()->createLayout(sizeQunatity, "", true);
	layerQunatity->setOpacity(192);

	Size gridQuantity = Size(5, 6);
	sprite = gui::inst()->addSpriteAutoDimension(2, 1, "blank.png", layerQunatity, ALIGNMENT_CENTER, gridQuantity, Size::ZERO, Size::ZERO);
	sprite->setContentSize(Size(20, 20));

	label = gui::inst()->addLabelAutoDimension(1, 2, " ", layerQunatity, 10, ALIGNMENT_NONE, Color3B::BLACK, gridQuantity, Size::ZERO, Size::ZERO);
	gui::inst()->addTextButtonAutoDimension(0, 3, "-", layerQunatity, callbackDec, 24, ALIGNMENT_CENTER, Color3B::BLACK, gridQuantity, Size::ZERO, Size::ZERO);
	labelQuantity = gui::inst()->addLabelAutoDimension(2, 3, "  ", layerQunatity, 14, ALIGNMENT_CENTER, Color3B::BLACK, gridQuantity, Size::ZERO, Size::ZERO);
	gui::inst()->addTextButtonAutoDimension(4, 3, "+", layerQunatity, callbackInc, 24, ALIGNMENT_CENTER, Color3B::BLACK, gridQuantity, Size::ZERO, Size::ZERO);
	labelPrice = gui::inst()->addLabelAutoDimension(2, 4, "           ", layerQunatity, 14, ALIGNMENT_CENTER, Color3B::BLACK, gridQuantity, Size::ZERO, Size::ZERO);
	gui::inst()->addTextButtonAutoDimension(2, 5, szSubmit, layerQunatity, callbackSubmit, 14, ALIGNMENT_CENTER, Color3B::BLUE, gridQuantity, Size::ZERO, Size::ZERO);

	layerQunatity->setAnchorPoint(Vec2(0, 0));
	layerQunatity->setPosition(s);

	p->addChild(layerQunatity);
    
    return layerQunatity;
}


void gui::addTiles(Node * p
                   , Rect dimension
                   , vector<Vec2> &vec
                   , Vec2 start
                   , float h
                   , float degrees
                   , bool isBGColor
                   , Color4F color1
                   , Color4F color2
                   , bool isLeft
                   , bool isRight
                   , Vec2 debugPos
                   , Vec2 debugPos2){
    
    double len = getTanLen(h, degrees);
    
//    if((debugPos2.x == -1 && debugPos2.y == -37)){
//        CCLOG("Parent x= (%f, %f)", debugPos.x, debugPos.y);
//    }
    
    if(!isExistVec2(vec, start)){
        if(isBGColor){
            drawDiamond(p, start, Size(len * 2, h * 2 ), color1);
            //len = drawDiamond(p, start, h, degrees, color1);
//            auto label = Label::create();
//            label->setString(to_string((int)debugPos2.x) + ", " + to_string((int)debugPos2.y));
//            label->setSystemFontSize(8);
//            label->setPosition(start);
//            p->addChild(label);
        }
        vec.push_back(start);
//        CCLOG("Vec(%f, %f) - %d", debugPos2.x, debugPos2.y, (int)vec.size());
    }else{
        return;
    }
    
    Vec2 left = Vec2(start.x - len, start.y - h);
    Vec2 right = Vec2(start.x + len, start.y - h);
    
    if(abs((start.x - len) - dimension.getMinX()) < 0.01 || isExistVec2(vec, left))
        isLeft = false;
    
    if(abs(start.x + len - dimension.getMaxX()) < 0.01 || isExistVec2(vec, right) ||
       vectorCross(
                    Vec2(dimension.getMidX(), dimension.getMinY())
                    , Vec2(dimension.getMaxX(), dimension.getMidY())
                    , Vec2(dimension.getMaxX(), dimension.getMinY())
                    , right
                    )
       )
        isRight = false;
    
//    if(start.y - (h * 2) < dimension.getMinY()) return;

   //left
    if(isLeft)
        addTiles(p, dimension, vec, left, h, degrees, isBGColor, color2, color1, isLeft, isRight, debugPos2, Vec2(debugPos2.x-1, debugPos2.y-1));
    //right
    if(isRight)
        addTiles(p, dimension, vec, right, h, degrees, isBGColor, color2, color1, isLeft, isRight, debugPos2, Vec2(debugPos2.x+1, debugPos2.y-1));
}

void gui::addWalls(bool isLeft, Node * p, Rect dimension, vector<Vec2> *vec, Vec2 pos, float h, float len
              , bool isBGColor
              , Color4F color1
              , Color4F color2){
    
//    Vec2 center = Vec2(pos.x - len, pos.y - h / 2);
    Vec2 rTop, rBottom, lTop, lBottom;
    if(isLeft){
        rTop = pos;
        rBottom = Vec2(rTop.x, rTop.y - h);
        lTop = Vec2(rTop.x - len * 2, rBottom.y);
        lBottom = Vec2(lTop.x, lTop.y - h);
    }else{
        lTop = pos;
        lBottom = Vec2(lTop.x, lTop.y - h);
        rTop = Vec2(lTop.x + len * 2, lBottom.y);
        rBottom = Vec2(rTop.x, rTop.y - h);
    }
    
//    drawRect(p, rTop, rBottom, lBottom, lTop, color1);
    
    if(isLeft){
        if(isBGColor){
            drawTriangle(p, rTop, lTop, Vec2(rTop.x, lTop.y), color1);
            drawTriangle(p, rBottom, lBottom, Vec2(lBottom.x, rBottom.y), color1);
        }
        if(vec)
            vec->push_back(Vec2(rBottom.x, lBottom.y));
        if(lTop.x - len <= dimension.getMinX())
            return;
        addWalls(isLeft, p, dimension, vec, lTop, h, len, isBGColor, color2, color1);
    } else{
        if(isBGColor){
            drawTriangle(p, lTop, rTop, Vec2(lTop.x, rTop.y), color1);
            drawTriangle(p, lBottom, rBottom, Vec2(rBottom.x, lBottom.y), color1);
        }
        if(vec)
            vec->push_back(rBottom);
        if(rTop.x + len >= dimension.getMaxX())
            return;
        addWalls(isLeft, p, dimension, vec, rTop, h, len, isBGColor, color2, color1);
    }
}

void gui::drawParallelogram(Node * p, Vec2 top1, Vec2 top2, Vec2 bottom1, Vec2 bottom2, Color4F color){
    drawTriangle(p, top1, bottom1, top2, color);
    drawTriangle(p, top2, bottom1, bottom2, color);
}


bool gui::isExistVec2(vector<Vec2> &vec, Vec2 point){
    for (size_t n=0; n<vec.size(); n++) {
        if(abs(vec.at(n).x - point.x) < 1 && abs(vec.at(n).y - point.y) < 1)
            return true;
    }
    return false;
}

bool gui::vectorCross(Vec2 a, Vec2 b, Vec2 c, Vec2 x){
    Vec2 ab = Vec2(b.x - a.x, b.y - a.y);
    Vec2 ac = Vec2(c.x - a.x, c.y - a.y);
    Vec2 ax = Vec2(x.x - a.x, x.y - a.y);
    
    float cross1 = (ab.x * ac.y) - (ab.y * ac.x);
    float cross2 = (ab.x * ax.y) - (ab.y * ax.x);
    
    if(cross1 * cross2 < 0)
        return false;
    
    return true;
}

Rect gui::getResizedRect(const Rect rect, float scale, bool isAlignToCenter) {
    float width = (rect.getMaxX() - rect.getMinX()) * scale;
    float height = (rect.getMaxY() - rect.getMinY()) * scale;
    if(isAlignToCenter) {
        return Rect(rect.getMidX() - (width / 2), rect.getMidY() - (height / 2), width, height);
    } else {
        return Rect(rect.getMinX(), rect.getMinY(), width, height);
    }
}
