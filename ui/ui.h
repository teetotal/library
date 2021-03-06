//
// Created by daejung on 2018-07-24.
//

#ifndef PROJ_ANDROID_GRID_H
#define PROJ_ANDROID_GRID_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#define GRID_X 9
#define GRID_Y 7
#define GRID_DEFAULT_FONT_SIZE 14
#define GRID_MARGIN 10
#define GRID_INNER_MARGIN 0
#define GRID_INVALID_VALUE -1
#define INVALID_VALUE -1
#define DEFAULT_OPACITY 150

#define DEFAULT_LAYER_SIZE Size(420, 200)

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;

enum ALIGNMENT{
    ALIGNMENT_NONE = 0,
    ALIGNMENT_CENTER,
    ALIGNMENT_LEFT,
    ALIGNMENT_RIGHT,
    ALIGNMENT_CENTER_TOP,
    ALIGNMENT_CENTER_BOTTOM,
    ALIGNMENT_LEFT_TOP,
    ALIGNMENT_LEFT_BOTTOM,
    ALIGNMENT_RIGHT_TOP,
    ALIGNMENT_RIGHT_BOTTOM
};

//레벨에 따른 이미지 출력을 위한 구조체
struct IMG_LEVEL {
	const string img;
	float level;
};

typedef std::vector<IMG_LEVEL> IMG_LEVEL_VECTOR;

#define TOUCH_INIT(__TYPE__) \
    auto listener = EventListenerTouchOneByOne::create();\
    listener->setSwallowTouches(true);\
    listener->onTouchBegan = CC_CALLBACK_2(__TYPE__::onTouchBegan, this);\
    listener->onTouchEnded = CC_CALLBACK_2(__TYPE__::onTouchEnded, this);\
    listener->onTouchMoved = CC_CALLBACK_2(__TYPE__::onTouchMoved, this);\
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

#define MULTITOUCH_INIT(__TYPE__) \
    auto listener = EventListenerTouchAllAtOnce::create();\
    listener->onTouchesBegan = CC_CALLBACK_2(__TYPE__::onTouchesBegan, this);\
    listener->onTouchesEnded = CC_CALLBACK_2(__TYPE__::onTouchesEnded, this);\
    listener->onTouchesMoved = CC_CALLBACK_2(__TYPE__::onTouchesMoved, this);\
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


#define POPUP_LIST(_PARENT_NODE, _GRID_SIZE, _NEWLINE, _START_VEC2, _END_VEC2, _MARGIN, _NODE_MARGIN, _NODE_SIZE, _FOR, _CONTINUE, _IMG, _CALLBACK, _SZ0, _SZ1, _SZ2, _SZ3, _SZ4, _IMG_POINTER) \
    Color3B fontColor0 = Color3B::BLACK; \
    Color3B fontColor1 = Color3B::BLACK; \
    Color3B fontColor2 = Color3B::BLACK; \
    Color3B fontColor3 = Color3B::BLACK; \
    Color3B fontColor4 = Color3B::BLACK; \
    bool isEnable = true; \
	int nCnt = 0; \
	for _FOR { \
		_CONTINUE \
		nCnt++; \
	} \
	Size __nodeSize = _NODE_SIZE; \
	Size sizeOfScrollView = gui::inst()->getScrollViewSize(_START_VEC2, _END_VEC2, _PARENT_NODE->getContentSize(), Size(-1,-1), Size::ZERO, _MARGIN); \
	if(_NEWLINE > 0) { \
		__nodeSize.width = (sizeOfScrollView.width  - (float)((_NEWLINE + 1) * _NODE_MARGIN)) / (float)_NEWLINE; \
	} else { \
		__nodeSize.height = sizeOfScrollView.height; \
	} \
	Size innerSize = (_NEWLINE > 0) ? Size(sizeOfScrollView.width, ((nCnt / _NEWLINE) + 1) * (__nodeSize.height + _NODE_MARGIN)) : Size((__nodeSize.width  + _NODE_MARGIN) * nCnt, __nodeSize.height + _NODE_MARGIN);\
    ScrollView * sv = gui::inst()->addScrollView(_START_VEC2, _END_VEC2, _PARENT_NODE->getContentSize(), Size(-1,-1), Size::ZERO, _MARGIN, "", innerSize); \
	for _FOR { \
		_CONTINUE \
		Layout* l = gui::inst()->createLayout(__nodeSize, "", true, Color3B::WHITE); \
		l->setOpacity(192); \
		int heightIdx = 0; \
		LayerColor * colorLayer = _IMG_POINTER; \
        if(colorLayer != NULL){ \
            Vec2 pos = gui::inst()->getPointVec2(0, 2, ALIGNMENT_CENTER, l->getContentSize(), _GRID_SIZE, Size::ZERO, Size::ZERO);\
            pos.x -= 10;\
            pos.y -= 10;\
            colorLayer->setPosition(pos); \
            l->addChild(colorLayer);\
        } else{ \
            if(_IMG.compare(gui::inst()->EmptyString) != 0) { \
                Menu * pSpriteMenu; \
                auto pMenuSprite = gui::inst()->addSpriteButtonRaw(pSpriteMenu, 0, 2, _IMG, _IMG, l, _CALLBACK, ALIGNMENT_CENTER, l->getContentSize(), _GRID_SIZE, Size::ZERO, Size::ZERO); \
                gui::inst()->setScale(pMenuSprite, 20); \
            } \
        } \
        gui::inst()->addTextButtonAutoDimension(0, 1, _SZ0, l, _CALLBACK, 10, ALIGNMENT_CENTER, fontColor0, _GRID_SIZE, Size::ZERO, Size::ZERO); \
		heightIdx = 1;\
        auto btn1 = gui::inst()->addTextButtonAutoDimension(1, heightIdx++, _SZ1, l, _CALLBACK, 12, ALIGNMENT_NONE, fontColor1, _GRID_SIZE, Size::ZERO, Size::ZERO); \
		auto btn2 = gui::inst()->addTextButtonAutoDimension(1, heightIdx++, _SZ2, l, _CALLBACK, 12, ALIGNMENT_NONE, fontColor2, _GRID_SIZE, Size::ZERO, Size::ZERO); \
		auto btn3 = gui::inst()->addTextButtonAutoDimension(1, heightIdx++, _SZ3, l, _CALLBACK, 12, ALIGNMENT_NONE, fontColor3, _GRID_SIZE, Size::ZERO, Size::ZERO); \
		auto btn4 = gui::inst()->addTextButtonAutoDimension(1, heightIdx++, _SZ4, l, _CALLBACK, 12, ALIGNMENT_NONE, fontColor4, _GRID_SIZE, Size::ZERO, Size::ZERO); \
        if(!isEnable) { \
            btn1->setEnabled(isEnable); \
            btn2->setEnabled(isEnable); \
            btn3->setEnabled(isEnable); \
            btn4->setEnabled(isEnable); \
        } \
		gui::inst()->addLayoutToScrollView(sv, l, _NODE_MARGIN, _NEWLINE); \
	} \
    _PARENT_NODE->removeChildByTag(99, true); \
    _PARENT_NODE->addChild(sv, 1, 99); 

class gui {
public:
    gui() : mIsInitialized(false) {};
    ~gui(){
        //hInstance = NULL;
    };
    static gui * inst(){
        if (hInstance == NULL) {
            hInstance = new gui();
            hInstance->EmptyString = " ";
        }
        return hInstance;
    };
    void init(const char* font = "fonts/arial.ttf"
            , int fontSize = GRID_DEFAULT_FONT_SIZE
            , Color4F bgColor = Color4F::WHITE
			, bool useSpriteCache = false
    );
    
    void initDefaultWithSpriteCache(const char* font = "fonts/arial.ttf") {
        init(font, GRID_DEFAULT_FONT_SIZE, Color4F::WHITE, true);
    };
    // get sprite  --------------------------------------------------------------------------------
    SpriteFrame * getSpriteFrame(const string img) {
        if(mUseSpriteCache) {
            if (SpriteFrameCache::getInstance()->getSpriteFrameByName(img) == NULL)
                SpriteFrameCache::getInstance()->addSpriteFrame(Sprite::create(img)->getSpriteFrame(), img);
            
            return SpriteFrameCache::getInstance()->getSpriteFrameByName(img);
        }
        return Sprite::create(img)->getSpriteFrame();
    };
    
    Sprite * getSprite(const string img) {
        if(mUseSpriteCache) {
            if (SpriteFrameCache::getInstance()->getSpriteFrameByName(img) == NULL)
                SpriteFrameCache::getInstance()->addSpriteFrame(Sprite::create(img)->getSpriteFrame(), img);
            
            return Sprite::createWithSpriteFrameName(img);
        }
        
        return Sprite::create(img);
    };
    // about pixel --------------------------------------------------------------------------------
    float getRealPixel(float x);
    float getSizeFromRealPixel(float x);
    // Get Point --------------------------------------------------------------------------------
    bool getPoint(int x, int y, float &pointX, float &pointY, ALIGNMENT align = ALIGNMENT_NONE
                  , Size dimension = Size(INVALID_VALUE, INVALID_VALUE)
                  , Vec2 grid = Vec2(INVALID_VALUE, INVALID_VALUE)
                  , Vec2 origin = Vec2(INVALID_VALUE, INVALID_VALUE)
                  , Vec2 margin = Vec2(INVALID_VALUE, INVALID_VALUE)
                  , Vec2 innerMargin = Vec2(INVALID_VALUE, INVALID_VALUE)
                  );
    
    bool getPoint(int x, int y, Vec2 &point, ALIGNMENT align = ALIGNMENT_NONE
                    , Size dimension = Size(INVALID_VALUE, INVALID_VALUE)
                    , Vec2 grid = Size(INVALID_VALUE, INVALID_VALUE)
                    , Vec2 origin = Size(INVALID_VALUE,INVALID_VALUE)
                    , Vec2 margin = Size(INVALID_VALUE, INVALID_VALUE)
                    , Vec2 innerMargin = Size(INVALID_VALUE, INVALID_VALUE)
                  ) {
        return getPoint(x, y, point.x, point.y, align, dimension, grid, origin, margin, innerMargin);
    }
    /*
    Vec2 getPointVec2(int x, int y, ALIGNMENT align = ALIGNMENT_CENTER
                      , Size dimension = Size(INVALID_VALUE, INVALID_VALUE)
                      , Size grid = Size(INVALID_VALUE, INVALID_VALUE)
                      , Size origin = Size(INVALID_VALUE,INVALID_VALUE)
                      , Size margin = Size(INVALID_VALUE, INVALID_VALUE)
                      , Size innerMargin = Size(INVALID_VALUE, INVALID_VALUE)) {
		Vec2 p;
		getPoint(x, y, p, align, dimension, grid, origin, margin, innerMargin);
		return p;
	};
    */
    Vec2 getPointVec2(int x, int y, ALIGNMENT align = ALIGNMENT_CENTER
                      , Size dimension = Size(INVALID_VALUE, INVALID_VALUE)
                      , Vec2 grid = Vec2(INVALID_VALUE, INVALID_VALUE)
                      , Vec2 origin = Vec2(INVALID_VALUE,INVALID_VALUE)
                      , Vec2 margin = Vec2(INVALID_VALUE, INVALID_VALUE)
                      , Vec2 innerMargin = Vec2(INVALID_VALUE, INVALID_VALUE)
                      , Vec2 span = Vec2::ZERO);
    // setAnchorPoint --------------------------------------------------------------------------------
    void setAnchorPoint(Node * p, ALIGNMENT align);
    // drawGrid --------------------------------------------------------------------------------
    bool drawGrid(Node * p
                  , Size dimension = Size(INVALID_VALUE, INVALID_VALUE)
                  , Vec2 grid = Vec2(INVALID_VALUE, INVALID_VALUE)
                  , Vec2 origin = Vec2(INVALID_VALUE,INVALID_VALUE)
                  , Vec2 margin = Vec2(INVALID_VALUE, INVALID_VALUE)
                  , Color4F color = Color4F::GRAY
    );
    bool drawPoint(Node * p);
    // addBG --------------------------------------------------------------------------------
    Sprite * addBG(const string bgImg, Node * parent, bool isOnLayer = false /* Scene이 아닌 layer에 이미지 올릴때 true */);
    // Label --------------------------------------------------------------------------------
    Label * createLabel(int x
                        , int y
                        , const string text
                        , float fontSize = 0.f
                        , ALIGNMENT align = ALIGNMENT_CENTER
                        , const Color3B color = Color3B::BLACK
                        , Size dimension = Size(GRID_INVALID_VALUE, GRID_INVALID_VALUE)
                        , Vec2 grid = Vec2(INVALID_VALUE, INVALID_VALUE)
                        , Vec2 origin = Vec2(INVALID_VALUE,INVALID_VALUE)
                        , Vec2 margin = Vec2(INVALID_VALUE,INVALID_VALUE)
                        , Vec2 innerMargin = Vec2(INVALID_VALUE,INVALID_VALUE)
                        , Vec2 span = Vec2::ZERO);

    Label * addLabel(Node *p
                     , int x
                     , int y
                     , const string text
                     , float fontSize = 0.f
                     , ALIGNMENT align = ALIGNMENT_CENTER
                     , const Color3B color = Color3B::BLACK
                     , Size dimension = Size(INVALID_VALUE, INVALID_VALUE)
                     , Vec2 grid = Vec2(INVALID_VALUE, INVALID_VALUE)
                     , Vec2 origin = Vec2(INVALID_VALUE, INVALID_VALUE)
                     , Vec2 margin = Vec2(INVALID_VALUE, INVALID_VALUE)
                     , Vec2 innerMargin = Vec2(INVALID_VALUE, INVALID_VALUE)
                     , Vec2 span = Vec2::ZERO
                     , const string img = ""
                     , bool isBGImg = true
                     );
    
    Label * addLabelAutoDimension(int x
                                  , int y
                                  , const string text
                                  , Node *p
                                  , float fontSize = 0.f
                                  , ALIGNMENT align = ALIGNMENT_CENTER
                                  , const Color3B color = Color3B::BLACK
                                  , Vec2 grid = Vec2(INVALID_VALUE, INVALID_VALUE)
                                  , Vec2 origin = Vec2(INVALID_VALUE,INVALID_VALUE)
                                  , Vec2 margin = Vec2(INVALID_VALUE,INVALID_VALUE)
                                  , Vec2 innerMargin = Vec2(INVALID_VALUE,INVALID_VALUE)
                                  , Vec2 span = Vec2::ZERO
                                  , const string img = ""
                                  , bool isBGImg = true) {
        return  addLabel(p
                         , x
                         , y
                         , text
                         , fontSize
                         , align
                         , color
                         , p->getContentSize()
                         , grid
                         , origin
                         , margin
                         , innerMargin
                         , span
                         , img
                         , isBGImg
                         );
    };
    // Text Button --------------------------------------------------------------------------------
    MenuItemLabel* addTextButtonRaw(
                                    Menu* &pMenu
                                    , int x
                                    , int y
                                    , const string text
                                    , Node* p
                                    , const ccMenuCallback& callback
                                    , float fontSize = 0.f
                                    , ALIGNMENT align = ALIGNMENT_CENTER
                                    , const Color3B color = Color3B::BLACK
                                    , Size dimension    = Size(INVALID_VALUE, INVALID_VALUE)
                                    , Vec2 grid         = Vec2(INVALID_VALUE, INVALID_VALUE)
                                    , Vec2 origin       = Vec2(INVALID_VALUE, INVALID_VALUE)
                                    , Vec2 margin       = Vec2(INVALID_VALUE, INVALID_VALUE)
                                    , Vec2 innerMargin  = Vec2(INVALID_VALUE, INVALID_VALUE)
                                    , Vec2 span         = Vec2::ZERO
                                    , const string img = ""
                                    , bool isBGImg = true
                                    , bool isAttachParent = true
                                    , Vec2 specificPos = Vec2(INVALID_VALUE, INVALID_VALUE)
                                    );
    
    MenuItemLabel * addTextButton(int x
                                  , int y
                                  , const string text
                                  , Node* p
                                  , const ccMenuCallback& callback
                                  , float fontSize = 0.f
                                  , ALIGNMENT align = ALIGNMENT_CENTER
                                  , const Color3B color = Color3B::BLACK
                                  , Size dimension    = Size(INVALID_VALUE, INVALID_VALUE)
                                  , Vec2 grid         = Vec2(INVALID_VALUE, INVALID_VALUE)
                                  , Vec2 origin       = Vec2(INVALID_VALUE, INVALID_VALUE)
                                  , Vec2 margin       = Vec2(INVALID_VALUE, INVALID_VALUE)
                                  , Vec2 innerMargin  = Vec2(INVALID_VALUE, INVALID_VALUE)
                                  , Vec2 span = Vec2::ZERO
                                  , const string img = ""
                                  , bool isBGImg = true)
    {
        Menu * pMenu = NULL;
        return addTextButtonRaw(pMenu, x, y, text, p, callback, fontSize, align, color, dimension, grid, origin, margin, innerMargin, span, img, isBGImg);
    };
    
    MenuItemLabel* addTextButtonAutoDimension(int x
                                              , int y
                                              , const string text
                                              , Node* p
                                              , const ccMenuCallback& callback
                                              , float fontSize = 0.f
                                              , ALIGNMENT align = ALIGNMENT_CENTER
                                              , const Color3B color = Color3B::BLACK
                                              , Vec2 grid         = Vec2(INVALID_VALUE, INVALID_VALUE)
                                              , Vec2 origin       = Vec2(INVALID_VALUE, INVALID_VALUE)
                                              , Vec2 margin       = Vec2(INVALID_VALUE, INVALID_VALUE)
                                              , Vec2 innerMargin  = Vec2(INVALID_VALUE, INVALID_VALUE)
                                              , Vec2 span = Vec2::ZERO
                                              , const string img = ""
                                              , bool isBGImg = true)
    {
        return addTextButton(x, y, text, p, callback, fontSize, align, color, p->getContentSize(), grid, origin, margin, innerMargin, span, img, isBGImg);
    }
    
    // Sprite Button --------------------------------------------------------------------------------
    MenuItemImage * addSpriteButtonRaw(Menu* &pMenu
                                       , int x
                                       , int y
                                       , const string normalImg
                                       , const string selectImg
                                       , Node *p
                                       , const ccMenuCallback &callback
                                       , ALIGNMENT align = ALIGNMENT_CENTER
                                       , Size dimension    = Size(GRID_INVALID_VALUE, GRID_INVALID_VALUE)
                                       , Vec2 grid         = Vec2(INVALID_VALUE, INVALID_VALUE)
                                       , Vec2 origin       = Vec2(INVALID_VALUE, INVALID_VALUE)
                                       , Vec2 margin       = Vec2(INVALID_VALUE, INVALID_VALUE)
                                       , Vec2 innerMargin  = Vec2(INVALID_VALUE, INVALID_VALUE)
                                       , Vec2 span = Vec2::ZERO
                                       , Vec2 specificPos  = Vec2(INVALID_VALUE, INVALID_VALUE));
    
	MenuItemImage * addSpriteButton(int x
                                    , int y
                                    , const string normalImg
                                    , const string selectImg
                                    , Node *p
                                    , const ccMenuCallback &callback
                                    , ALIGNMENT align = ALIGNMENT_CENTER
                                    , Size dimension = Size(GRID_INVALID_VALUE, GRID_INVALID_VALUE)
                                    , Vec2 grid         = Vec2(INVALID_VALUE, INVALID_VALUE)
                                    , Vec2 origin       = Vec2(INVALID_VALUE, INVALID_VALUE)
                                    , Vec2 margin       = Vec2(INVALID_VALUE, INVALID_VALUE)
                                    , Vec2 innerMargin  = Vec2(INVALID_VALUE, INVALID_VALUE)
                                    , Vec2 span = Vec2::ZERO)
    {
		Menu * pMenu = NULL;
		return addSpriteButtonRaw(pMenu, x, y, normalImg, selectImg, p, callback, align, dimension, grid, origin, margin, innerMargin, span);
	};
    
    // Sprite --------------------------------------------------------------------------------
    Sprite* addSprite(int x
                      , int y
                      , const string img
                      , Node* p
                      , ALIGNMENT align = ALIGNMENT_CENTER
                      , Size dimension = Size(INVALID_VALUE, INVALID_VALUE)
                      , Vec2 grid = Vec2(INVALID_VALUE, INVALID_VALUE)
                      , Vec2 origin = Vec2(INVALID_VALUE, INVALID_VALUE)
                      , Vec2 margin = Vec2(INVALID_VALUE, INVALID_VALUE)
                      , Vec2 innerMargin = Vec2(INVALID_VALUE, INVALID_VALUE)
                      , Vec2 span = Vec2::ZERO
                      , const Size &spriteSize = Size(INVALID_VALUE, INVALID_VALUE)
    );

    Sprite* addSpriteAutoDimension(int x
                                   , int y
                                   , const string img
                                   , Node* p
                                   , ALIGNMENT align = ALIGNMENT_CENTER
                                   , Vec2 grid = Vec2(INVALID_VALUE, INVALID_VALUE)
                                   , Vec2 origin = Vec2(INVALID_VALUE, INVALID_VALUE)
                                   , Vec2 margin = Vec2(INVALID_VALUE, INVALID_VALUE)
                                   , Vec2 innerMargin = Vec2(INVALID_VALUE, INVALID_VALUE)
                                   , Vec2 span = Vec2::ZERO
                                   , const Size &spriteSize = Size(INVALID_VALUE, INVALID_VALUE))
    {
        return addSprite(x, y, img, p, align, p->getContentSize(), grid, origin, margin, innerMargin, span, spriteSize);
    };
    
    // addProgressBar --------------------------------------------------------------------------------
    LoadingBar * addProgressBar(int x
                                , int y
                                , const string img
                                , Node * p
                                , Vec2 scaleSize
                                , float defaultVal = 0.f
                                , Size dimension = Size(GRID_INVALID_VALUE, GRID_INVALID_VALUE)
                                , Vec2 grid = Vec2(INVALID_VALUE, INVALID_VALUE)
                                , Vec2 origin = Vec2(INVALID_VALUE, INVALID_VALUE)
                                , Vec2 margin = Vec2(INVALID_VALUE, INVALID_VALUE)
                                , Vec2 innerMargin = Vec2(INVALID_VALUE, INVALID_VALUE)
                                , LoadingBar::Direction direction = LoadingBar::Direction::LEFT
                                );
    
    Sprite * getfittedSprite(const string sz, Node * node) {
        Sprite * sprite = Sprite::create(sz);
        sprite->setPosition(Vec2(node->getContentSize().width / 2, node->getContentSize().height / 2));
        sprite->setContentSize(node->getContentSize());
        return sprite;
    };
    
    // draws --------------------------------------------------------------------------------
    DrawNode * drawLine             (Node * p, Vec2 start,  Vec2 end,       Color4F color = Color4F::GRAY, GLfloat width = 3.f);
    DrawNode * drawCircle           (Node * p, Vec2 pos,    float radius,   Color4F color);
    DrawNode * drawTriangle         (Node * p, Vec2 a,      Vec2 b,         Vec2 c,     Color4F color);
    DrawNode * drawRect             (Node * p, Vec2 pos,    Size size,      Color4F color,  bool isSolid = true, DrawNode * pDraw = NULL);
    DrawNode * drawRect             (Node * p, Vec2 pos1,   Vec2 pos2,      Vec2 pos3,  Vec2 pos4, Color4F color, bool isSolid = false);
    DrawNode * drawRectRound        (Node * p, Vec2 pos,    Size size,      Color4F color, DrawNode * pDraw = NULL);
    DrawNode * drawRectCircle       (Node * p, Vec2 pos,    Size size,      Color4F color, DrawNode * draw = NULL);
    DrawNode * drawDiamond          (Node * p, Vec2 pos,    Size size,      Color4F color);
    float drawDiamond               (Node * p, Vec2 center, float h,        float degrees,  Color4F color);
    void drawDiamondTile            (Node * p, Vec2 counts, Color4F color);

    // set modal  --------------------------------------------------------------------------------
    void setModal(Node * layer);
    
    // createLayout  --------------------------------------------------------------------------------
    Layout * createLayout(Size size, const string bgImg = "", bool hasBGColor = false, Color3B bgColor = Color3B::WHITE);
    
    // addScrollView  --------------------------------------------------------------------------------
    ScrollView * addScrollView(Size size, Size innerSize, Vec2 position, Node * parent);
    
    // get fontSize  --------------------------------------------------------------------------------
    /*
         10: mDefaultFontLabelSize = x : size
         x = 10 * size / mDefaultFontLabelSize
     */
    float getFontSize(Size size, float scale = 1.f) {
        return ( 10.f * size.height / mDefaultFontLabelSize.height ) * scale;
    }
    
    inline const float getScaleDefine(int code) {
        switch(code) {
            case 0:
                return 1.f;
            case -1:
                return 0.75f;
            case -2:
                return 0.5f;
            case -3:
                return 0.25f;
            default:
                return 0;
        }
    };
    
    inline float getFontSizeDefine(Size size, float sizeCode) {
        float scale = getScaleDefine(sizeCode);
        if(scale > 0) {
            return ( 10.f * size.height / mDefaultFontLabelSize.height ) * scale;
        } else {
            return sizeCode;
        }
    };
    
    float getFontSize(Size dimension, Vec2 grid, Vec2 margin, Vec2 innerMargin, Vec2 span, float scale) {
        return getFontSize(getGridSize(dimension, grid, margin, innerMargin, span), scale);
    }
    // getGridSize  --------------------------------------------------------------------------------
    Size getGridSize(Size dimension, Vec2 grid, Vec2 margin, Vec2 innerMargin, Vec2 span = Vec2::ZERO);
    
    // getColor4F  --------------------------------------------------------------------------------
    static Color4F getColor4F(int r, int g, int b, int a = 255) {
        return Color4F((float)r / 255.f, (float)g / 255.f, (float)b / 255.f, (float)a / 255.f);
    };
    
    LayerColor * addPopup(LayerColor * &pBG
            , Node * p
            , Size size
            , const string bgImg = ""
            , Color4B bgColor = Color4B::WHITE
    );
    LayerColor * createModalLayer(LayerColor * &pBG
            , Size size
            , const string bgImg = ""
            , Color4B bgColor = Color4B::WHITE
    );

    void addLayoutToScrollView(ScrollView * p
            , Layout * e
            , float margin
            , int newlineInterval = 0
    );

	Size getScrollViewSize(Vec2 p1, Vec2 p2, Size size, Size grid, Size origin, Size margin);

    ScrollView * addScrollView(Vec2 p1
            , Vec2 p2
            , Size size, Size grid, Size origin, Size margin
            , const string bgImg = ""
            , Size innerSize = Size(0, 0)
			, Node * parent = NULL
                               );

	Sequence * createActionFocus() { 
		float raiseDuration = 0.3f;
		float returnDuration = 0.1f;
		float scale = 1.5f;

		return Sequence::create(
			ScaleTo::create(raiseDuration, scale), ScaleTo::create(returnDuration, 1), NULL
		);
	};

	RepeatForever * createActionBlink() {
		return RepeatForever::create(Sequence::create(ScaleTo::create(0.3f, 1.2f), ScaleTo::create(0.3f, 1.0f), NULL));
	}

	void actionHarvest(Node * p, string img, int cnt, Vec2 from, Vec2 to, Size size) {		
		for (int n = 0; n < cnt; n++) {

			auto sprite = Sprite::create(img);
			sprite->setPosition(from);
			sprite->setContentSize(size);
			p->addChild(sprite);

			auto delay1 = DelayTime::create(n * 0.03);
			auto delay2 = delay1->clone();
			auto seq1 = Sequence::create(delay1, MoveTo::create(0.5f, to), RemoveSelf::create(), NULL);
			auto seq2 = Sequence::create(delay2, ScaleTo::create(0.2f, 1.5f), ScaleTo::create(0.3f, 0.5f), NULL);

			sprite->runAction(Spawn::create(seq1, seq2, NULL));
		}
	}


	//수량 UI Layer
	Layout * addQuantityLayer(Node * p, Size size, Size margin
		, Sprite* &sprite, Label * &label, Label * &labelQuantity, Label* &labelPrice
		, const string szSubmit
		, const ccMenuCallback& callbackDec
		, const ccMenuCallback& callbackInc
		, const ccMenuCallback& callbackSubmit);

    float getScale(Node * p, float targetWidth){
        return targetWidth / p->getContentSize().width;
    };
    float getScaleByHeight(Node * p, float targetHeight){
        return targetHeight / p->getContentSize().height;
    };
    //set Scale
    void setScaleAuto(Node * p, float targetSize) {
      if(p->getContentSize().width > p->getContentSize().height)
          return setScale(p, targetSize);
        
        return setScaleByHeight(p, targetSize);
    };
	void setScale(Node * p, float targetWidth) {
		//float ratio = targetWidth / p->getContentSize().width;
		p->setScale(getScale(p, targetWidth));
	};
    void setScaleByHeight(Node * p, float targetHeight) {
        p->setScale(getScaleByHeight(p, targetHeight));
    };

	//정 중앙 포인트 가져오기
	Vec2 getCenterFromSize(Size size) {
		return Vec2(size.width / 2, size.height / 2);
	};
	Vec2 getCenter() {
		Size size = Director::getInstance()->getVisibleSize();
		Vec2 point = Vec2(size.width / 2, size.height / 2);
		point.x += Director::getInstance()->getVisibleOrigin().x;
		point.y += Director::getInstance()->getVisibleOrigin().y;
		return point;
	};
    
    Vec2 getCenter(Node * p) {
        Vec2 center;
        center.x = p->getContentSize().width / 2;
        center.y = p->getContentSize().height / 2;
        
        return center;
    }

    //이미지 하나를 3배 복제해서 스크롤링, 리턴 없음
    void addBGScrolling(const string img, Node * p, float duration);

	//particle
	ParticleSystemQuad * createParticle(string szParticle, int x, int y) {
		return createParticle(szParticle, getPointVec2(x, y));
	};
	ParticleSystemQuad * createParticle(string szParticle, Vec2 position) {
		auto particle = ParticleSystemQuad::create(szParticle);
		particle->setPosition(position);

		return particle;
	};

	void addToCenter(Node * p, Node * pParent) {
		p->setAnchorPoint(Vec2(0.5, 0.5));
		p->setPosition(getCenter());
		pParent->addChild(p);
	};
    
    
    float getTanLen(float h, float degrees) {
//        const double pi = std::acos(-1);
        //180 X = degree
        //return h / std::tan(degrees * pi / 180);
        
        return h/ tan(CC_DEGREES_TO_RADIANS(degrees));
    }
    void addTiles(Node * p, Rect dimension, vector<Vec2> &vec
                  , Vec2 start
                  , float h
                  , float degrees
                  , bool isBGColor = false
                  , Color4F color1 = Color4F::BLACK
                  , Color4F color2 = Color4F::GRAY
                  , bool isLeft = true
                  , bool isRight = true
                  , Vec2 debugPos = Vec2::ZERO
                  , Vec2 debugPos2 = Vec2::ZERO
                  );
    void addWalls(bool isLeft, Node * p, Rect dimension, vector<Vec2> *vec, Vec2 pos, float h, float len
                  , bool isBGColor = false
                  , Color4F color1 = Color4F::BLACK
                  , Color4F color2 = Color4F::GRAY );
    void drawParallelogram(Node * p, Vec2 top1, Vec2 top2, Vec2 bottom1, Vec2 bottom2, Color4F color);
    
    //벡터 외적. 음수 = false
    bool vectorCross(Vec2 a, Vec2 b, Vec2 c, Vec2 x);
    
    const string getStar(int point){
        //★☆
        /*
         1-25 ☆
         26-40 ★
         41-60 ★☆
         61-75 ★★
         76-90 ★★☆
         91- ★★★
         */
        if(point <=0)
            return " ";
        else if(point > 0 && point <= 25)
            return "☆";
        else if(point > 25 && point <= 40)
            return "★";
        else if(point > 40 && point <= 60)
            return "★☆";
        else if(point > 60 && point <= 75)
            return "★★";
        else if(point > 75 && point <= 90)
            return "★★☆";
        else
            return "★★★";
        
    };
    
    Size getVisibleSize() {
        return mVisibleSize;
    };
    //tile 영역 체크에서 사용
    Rect getResizedRect(const Rect rect, float scale, bool isAlignToCenter = true);
    
	int mModalTouchCnt;
	string EmptyString;

	float mOriginX, mOriginY;
	float mVisibleX, mVisibleY;

    Vec2 mOrigin;
    Size mVisibleSize;
	Size mResolution;
    
    const char* mDefaultFont;
    int mDefaultFontSize;
    Size mDefaultFontLabelSize; // font 10 A에 대한 라벨 크기
	bool mUseSpriteCache;
private:
    static gui * hInstance;
	bool mIsInitialized;
    const Vec2 getNoneAnchorPoint(){
        return Vec2(0,1.75);
    };
/*
    void getPoint(int x, int y
            , float &pointX_Center, float &pointY_Center
            , float &pointX_None, float &pointY_None
            , ALIGNMENT align
            , Size dimension
            , Size grid
            , Size origin
            , Size margin) {
        getPoint(x,y
                 , pointX_Center, pointY_Center
                 , ALIGNMENT_CENTER
                 , dimension
                 , grid
                 , origin
                 , margin
                 );
        
        getPoint(x,y
                 , pointX_None, pointY_None
                 , ALIGNMENT_NONE
                 , dimension
                 , grid
                 , origin
                 , margin
                 );
    };
   */
    bool isExistVec2(vector<Vec2> &vec, Vec2 point);
};


#endif //PROJ_ANDROID_GRID_H
