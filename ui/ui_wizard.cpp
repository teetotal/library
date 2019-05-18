//
// Created by Jung, DaeCheon on 25/04/2019.
//

#include "ui_wizard.h"
#include "ui_progressbar.h"

ui_wizard_share * ui_wizard_share::hInstance = NULL;

// _base -------------------------------------------------------------------------------------------
void WIZARD::_base::getColorFromJson(rapidjson::Value &p, COLOR_RGB * color) {
    if (p.IsInt()) {
        color->set(0, 0, 0, p.GetInt());
    }
    else if (p.IsString()) {
        COLOR_RGB c = ui_wizard_share::inst()->getPalette()->getColor(p.GetString());
        color->set(c);
    }
    else {
        color->set(p[rapidjson::SizeType(0)].GetInt()
                   , p[rapidjson::SizeType(1)].GetInt()
                   , p[rapidjson::SizeType(2)].GetInt()
                   , (p.GetArray().Size() == 4) ? p[rapidjson::SizeType(3)].GetInt() : 255);
    }
}

void WIZARD::_base::getColorFromJson(rapidjson::Value &p, COLOR_RGB * color1, COLOR_RGB * color2) {
    if (p.IsArray() && p.GetArray().Size() == 2) {
        getColorFromJson(p[rapidjson::SizeType(0)], color1);
        getColorFromJson(p[rapidjson::SizeType(1)], color2);
    } else {
        getColorFromJson(p, color1);
    }
}
// _Object -------------------------------------------------------------------------------------------
bool WIZARD::_Object::load(rapidjson::Value & p)
{
    CCLOG("Start WIZARD::_Object::load");
    this->opacity = (GLubyte)0xFF;
    this->opacity_second = (GLubyte)0xFF;
    this->id = -1;
    this->link = -1;
    
    if(p.HasMember("id") && !p["id"].IsNull())
        this->id = p["id"].GetInt();
    
    CCLOG("WIZARD::_Object::load id=%d", id);
    
    CCLOG("WIZARD::_Object::load position");
	this->position.x = p["position"][rapidjson::SizeType(0)].GetFloat();
	this->position.y = p["position"][rapidjson::SizeType(1)].GetFloat();
    
    CCLOG("WIZARD::_Object::load alignment");
	const string szAlignment = p["alignment"].GetString();
	if (szAlignment.compare("none") == 0) {
		this->alignment = ALIGNMENT_NONE;
	}
	else if (szAlignment.compare("center") == 0){
		this->alignment = ALIGNMENT_CENTER;
    }
    else if (szAlignment.compare("center_top") == 0){
        this->alignment = ALIGNMENT_CENTER_TOP;
    }
    else if (szAlignment.compare("center_bottom") == 0){
        this->alignment = ALIGNMENT_CENTER_BOTTOM;
    }
    else if (szAlignment.compare("left") == 0){
        this->alignment = ALIGNMENT_LEFT;
    }
    else if (szAlignment.compare("left_top") == 0){
        this->alignment = ALIGNMENT_LEFT_TOP;
    }
    else if (szAlignment.compare("left_bottom") == 0){
        this->alignment = ALIGNMENT_LEFT_BOTTOM;
    }
    else if (szAlignment.compare("right") == 0){
        this->alignment = ALIGNMENT_RIGHT;
    }
    else if (szAlignment.compare("right_top") == 0){
        this->alignment = ALIGNMENT_RIGHT_TOP;
    }
    else if (szAlignment.compare("right_bottom") == 0){
        this->alignment = ALIGNMENT_RIGHT_BOTTOM;
    }
    
    CCLOG("WIZARD::_Object::load type");
	this->type = (OBJECT_TYPE)getObjectType(p["type"].GetString());
    CCLOG("Start WIZARD::_Object::load link");
	this->link = ( !p.HasMember("link") || p["link"].IsNull()) ? NULL_INT_VALUE : p["link"].GetInt();
    
    CCLOG("WIZARD::_Object::load text");
    this->text = (!p.HasMember("text") || p["text"].IsNull()) ? NULL_STRING_VALUE : p["text"].GetString();
    CCLOG("WIZARD::_Object::load fontSize");
    this->fontSize = (!p.HasMember("fontSize") || p["fontSize"].IsNull()) ? 0 : p["fontSize"].GetFloat();
    CCLOG("WIZARD::_Object::load visible");
    this->visible = (!p.HasMember("visible") || p["visible"].IsNull()) ? true : p["visible"].GetBool();
	
    CCLOG("WIZARD::_Object::load img");
    if (!p.HasMember("img") || p["img"].IsNull()) {
		this->img = NULL_STRING_VALUE;
        this->img_selected = NULL_STRING_VALUE;
    }
	else {
        if(p["img"].IsArray()) {
            this->img = p["img"][rapidjson::SizeType(0)].GetString();
            if (SpriteFrameCache::getInstance()->getSpriteFrameByName(this->img) == NULL)
                SpriteFrameCache::getInstance()->addSpriteFrame(Sprite::create(this->img)->getSpriteFrame(), this->img);
            this->img_selected = p["img"][rapidjson::SizeType(1)].GetString();
            if (SpriteFrameCache::getInstance()->getSpriteFrameByName(this->img_selected) == NULL)
                SpriteFrameCache::getInstance()->addSpriteFrame(Sprite::create(this->img_selected)->getSpriteFrame(), this->img_selected);
            
        } else {
            this->img = p["img"].GetString();
            this->img_selected = this->img;
            if (SpriteFrameCache::getInstance()->getSpriteFrameByName(this->img) == NULL)
                SpriteFrameCache::getInstance()->addSpriteFrame(Sprite::create(this->img)->getSpriteFrame(), this->img);
        }
		//SpriteFrameCache::getInstance()->removeSpriteFrameByName("btn_bg");	
	}
    
    CCLOG("WIZARD::_Object::load color");
    if (p.HasMember("color") && !p["color"].IsNull()) {
        COLOR_RGB color1, color2;
        getColorFromJson(p["color"], &color1, &color2);
        this->color = color1.getColor3B();
        this->opacity = color1.getA();
        if(color2.isValidColor) {
            this->color_second = color2.getColor3B();
            this->opacity_second = color2.getA();
        }
    }
    
    CCLOG("WIZARD::_Object::load bgColor");
    if (p.HasMember("bgColor") && !p["bgColor"].IsNull()) {
        COLOR_RGB color1, color2;
        getColorFromJson(p["bgColor"], &color1, &color2);
        this->bgColor.set(color1);
        if(color2.isValidColor) {
            this->bgColor_second.set(color2);
        }
    }
    
	return true;
}

int WIZARD::_Object::getObjectType(const string type)
{
	if (type.compare("button") == 0)
		return OBJECT_TYPE_BUTTON;
    else if (type.compare("button_sprite") == 0)
        return OBJECT_TYPE_BUTTON_SPRITE;
    else if (type.compare("button_circle") == 0)
        return OBJECT_TYPE_BUTTON_CIRCLE;
    else if (type.compare("button_rectangle_round_shadow") == 0)
        return OBJECT_TYPE_BUTTON_RECT_ROUND_SHADOW;
	else if (type.compare("sprite") == 0)
		return OBJECT_TYPE_SPRITE;
	else if (type.compare("label_sprite") == 0)
		return OBJECT_TYPE_LABEL_SPRITE;
	else if (type.compare("sprite_button") == 0)
		return OBJECT_TYPE_SPRITE_BUTTON;
    else if (type.compare("sprite_button_circle") == 0)
        return OBJECT_TYPE_SPRITE_BUTTON_CIRCLE;
	else if (type.compare("loadingbar") == 0)
		return OBJECT_TYPE_LOADINGBAR;
	else if (type.compare("circle") == 0)
		return OBJECT_TYPE_CIRCLE;
    else if (type.compare("rectangle") == 0)
        return OBJECT_TYPE_RECT;
    else if (type.compare("rectangle_line") == 0)
        return OBJECT_TYPE_RECT_LINE;
    else if (type.compare("rectangle_round") == 0)
        return OBJECT_TYPE_RECT_ROUND;
    else if (type.compare("rectangle_round_shadow") == 0)
        return OBJECT_TYPE_RECT_ROUND_SHADOW;
    
	return OBJECT_TYPE_LABEL;
}
// _Node -------------------------------------------------------------------------------------------
bool WIZARD::_Node::load(rapidjson::Value & pValue)
{
    CCLOG("Start WIZARD::_Node::load");
    this->visible = true;
    this->isScrollView = false;
    this->id = -1;
    
    if(pValue.HasMember("id") && !pValue["id"].IsNull())
        this->id = pValue["id"].GetInt();
	
    CCLOG("WIZARD::_Node::load id=%d", id);
    
    CCLOG("WIZARD::_Node::load include");
    rapidjson::Value & p = (pValue.HasMember("include")) ? getJsonValue(pValue["include"]["path"].GetString())[pValue["include"]["key"].GetString()] : pValue;
    
    CCLOG("WIZARD::_Node::load dimension");
    this->dimensionStart.x = p["dimension"][rapidjson::SizeType(0)].GetFloat();
	this->dimensionStart.y = p["dimension"][rapidjson::SizeType(1)].GetFloat();
	this->dimensionEnd.x = p["dimension"][rapidjson::SizeType(2)].GetFloat();
	this->dimensionEnd.y = p["dimension"][rapidjson::SizeType(3)].GetFloat();
    
    if(p.HasMember("dimensionInner") && !p["dimensionInner"].IsNull()) {
        CCLOG("Start WIZARD::_Node::load dimensionInner");
        this->dimensionInnerStart.x = p["dimensionInner"][rapidjson::SizeType(0)].GetFloat();
        this->dimensionInnerStart.y = p["dimensionInner"][rapidjson::SizeType(1)].GetFloat();
        this->dimensionInnerEnd.x = p["dimensionInner"][rapidjson::SizeType(2)].GetFloat();
        this->dimensionInnerEnd.y = p["dimensionInner"][rapidjson::SizeType(3)].GetFloat();
        
        this->isScrollView = true;
    }
    
    CCLOG("WIZARD::_Node::load margin");
	this->margin.width = p["margin"][rapidjson::SizeType(0)].GetFloat();
	this->margin.height = p["margin"][rapidjson::SizeType(1)].GetFloat();
    
    CCLOG("WIZARD::_Node::load innerMargin");
    this->innerMargin.width = p["innerMargin"][rapidjson::SizeType(0)].GetFloat();
    this->innerMargin.height = p["innerMargin"][rapidjson::SizeType(1)].GetFloat();
    
    CCLOG("WIZARD::_Node::load gridSize");
	this->gridSize.width = p["gridSize"][rapidjson::SizeType(0)].GetFloat();
	this->gridSize.height = p["gridSize"][rapidjson::SizeType(1)].GetFloat();
    
    CCLOG("WIZARD::_Node::load img");
	this->img = p["img"].IsNull() ? NULL_STRING_VALUE : p["img"].GetString();
    
    CCLOG("WIZARD::_Node::load color");
    if (p.HasMember("color") && !p["color"].IsNull()) {
        COLOR_RGB color1, color2;
        getColorFromJson(p["color"], &color1, &color2);
        this->color.set(color1);
        if(color2.isValidColor) {
            this->color_second.set(color2);
        }
    }
    //tile
    if (p.HasMember("tile") && !p["tile"].IsNull()) {
        CCLOG("WIZARD::_Node::load tile");
        COLOR_RGB color1;
        getColorFromJson(p["tile"]["color"], &color1);
        this->colorTile.set(color1);
        this->tileNum = Vec2(p["tile"]["num"][rapidjson::SizeType(0)].GetInt()
                             , p["tile"]["num"][rapidjson::SizeType(1)].GetInt());
    }

    CCLOG("WIZARD::_Node::load objects");
	if (p.HasMember("objects")) {
		const rapidjson::Value& objects = p["objects"];
		for (rapidjson::SizeType i = 0; i < objects.Size(); i++)
		{
			_Object object;
			if (!object.load(p["objects"][rapidjson::SizeType(i)]))
				return false;

			this->mObjects.push_back(object);
		}
	}
    
    CCLOG("WIZARD::_Node::load visible");
    if(p.HasMember("visible")) {
        this->visible = p["visible"].GetBool();
    }
	
	return true;
}
// _Background -------------------------------------------------------------------------------------------
bool WIZARD::_Background::load(rapidjson::Value & pValue)
{
    CCLOG("Start WIZARD::_Background::load");
    this->id = (pValue.HasMember("id") && !pValue["id"].IsNull()) ? pValue["id"].GetInt() : -1;
    CCLOG("WIZARD::_Background::load id=%d", id);
    
    CCLOG("WIZARD::_Background::load include");
    rapidjson::Value & p = (pValue.HasMember("include")) ? getJsonValue(pValue["include"]["path"].GetString())[pValue["include"]["key"].GetString()] : pValue;
    CCLOG("WIZARD::_Background::load img");
	if (p["img"].IsNull())
		this->img = NULL_STRING_VALUE;
	else {
		this->img = p["img"].GetString();
		if(SpriteFrameCache::getInstance()->getSpriteFrameByName(this->img) == NULL)
			SpriteFrameCache::getInstance()->addSpriteFrame(Sprite::create(this->img)->getSpriteFrame(), this->img);
	}

    this->isDrawGrid = false;
    //bgColor
    CCLOG("WIZARD::_Background::load bgColor");
	if (!p["bgColor"].IsNull()) {
        COLOR_RGB color1, color2;
        getColorFromJson(p["bgColor"], &color1, &color2);
        this->bgColor.set(color1);
        if(color2.isValidColor) {
            this->bgColor_second.set(color2);
        }
	}
    //tile
    CCLOG("WIZARD::_Background::load tile");
    if (p.HasMember("tile") && !p["tile"].IsNull()) {
        COLOR_RGB color1;
        getColorFromJson(p["tile"]["color"], &color1);
        this->tileColor.set(color1);
        this->tileNum = Vec2(
                             p["tile"]["num"][rapidjson::SizeType(0)].GetInt()
                             , p["tile"]["num"][rapidjson::SizeType(1)].GetInt()
        );
    }
    
    //isDrawGrid
    CCLOG("WIZARD::_Background::load isDrawGrid");
    if(!p["isDrawGrid"].IsNull())
        this->isDrawGrid = p["isDrawGrid"].GetBool();
    
	return true;
}

rapidjson::Document WIZARD::getJsonValue(const string& path) {
    string fullpath = FileUtils::getInstance()->fullPathForFilename(path);
    string sz = FileUtils::getInstance()->getStringFromFile(fullpath);
    
    rapidjson::Document d;
    d.Parse(sz.c_str());
    if (d.HasParseError()) {
        CCLOG("loadFromJson Failure. ErrorCode: %d, ErrorOffset: %zu", d.GetParseError(), d.GetErrorOffset());
        //return false;
    }
    return d;
}

// ui_wizard -------------------------------------------------------------------------------------------
bool ui_wizard::loadFromJson(const string& sceneName, const string& path, const string& pathPalette)
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    mGrid = Size(GRID_X, GRID_Y);
    if(visibleSize.width < visibleSize.height)
        mGrid = Size(GRID_Y, GRID_X);
    
	if (ui_wizard_share::inst()->hasNode(sceneName)) {
        WIZARD::_Background bg = ui_wizard_share::inst()->getBackgound(sceneName);
		this->drawBackground(bg);

		WIZARD::VEC_NODES nodes = ui_wizard_share::inst()->getNodes(sceneName);
		for (size_t n = 0; n < nodes.size(); n++) {
			WIZARD::_Node p = nodes[n];
			drawNode(p, (int)n);
		}
		return true;
	}
    
    if(pathPalette.compare("") != 0 && ui_wizard_share::inst()->insertPalettePath(pathPalette)) {
        rapidjson::Document dPalette = WIZARD::getJsonValue(pathPalette);
        
        for (auto& m : dPalette.GetObject())
        {
            int rgba[4];
            for(int n=0; n < 4; n++) rgba[n] = m.value[n].GetInt();
            
            ui_wizard_share::inst()->getPalette()->set(m.name.GetString()
                                                       , rgba[0]
                                                       , rgba[1]
                                                       , rgba[2]
                                                       , rgba[3]);
            
            CCLOG("Insert Palette %s\t[ %d, %d, %d, %d ]"
                  , m.name.GetString()
                  , rgba[0]
                  , rgba[1]
                  , rgba[2]
                  , rgba[3]
                  );
        }
    }
    
    rapidjson::Document d = WIZARD::getJsonValue(path);
    
    
	WIZARD::_Background bg;
	bg.load(d["background"]);
	ui_wizard_share::inst()->setBackground(sceneName, bg);
	this->drawBackground(bg);

	const rapidjson::Value& nodes = d["nodes"];
	for (rapidjson::SizeType i = 0; i < nodes.Size(); i++)
	{	
		WIZARD::_Node p;
		if (!p.load(d["nodes"][rapidjson::SizeType(i)]))
			return false;
		
		ui_wizard_share::inst()->addNode(sceneName, p);
		drawNode(p, (int)i);
	}

	return true;
}

Node * ui_wizard::getNodeById(int id)
{
	if (mNodeMap.find(id) == mNodeMap.end())
		return nullptr;
	return mNodeMap[id];
}

void ui_wizard::drawBackground(WIZARD::_Background & bg)
{
    Size size = Director::getInstance()->getVisibleSize();
    mIsDrawGrid = bg.isDrawGrid;
//    auto p = (bg.bgColor_second.isValidColor) ? LayerGradient::create(bg.bgColor.getColor4B(), bg.bgColor_second.getColor4B()) : LayerColor::create(bg.bgColor.getColor4B());
    auto p = LayerColor::create(bg.bgColor.getColor4B());
	p->setContentSize(size);
    p->setAnchorPoint(Vec2::ZERO);
	p->setPosition(Director::getInstance()->getVisibleOrigin());
	this->addChild(p);
    
    if (bg.bgColor_second.isValidColor) {
        
        auto gradient = LayerRadialGradient::create( bg.bgColor_second.getColor4B() //node.color.getColor4B()
                                                    , bg.bgColor.getColor4B()
                                                    , size.width / 1.5f
                                                    , Vec2(size.width / 2.f, size.height / 4.f) //Vec2(sizeColored.width / 2.f, sizeColored.height / 2.f)
                                                    , 0.0f);
        
        gradient->setContentSize(size);
        p->addChild(gradient);
        
    }

	if (bg.img.compare(NULL_STRING_VALUE) != 0) {
		gui::inst()->addBG(bg.img, p, true);
	}
    
    mNodeMap[bg.id] = p;
    
    if(bg.tileColor.isValidColor) {
        gui::inst()->drawDiamondTile(p, bg.tileNum, bg.tileColor.getColor4F());
    }
    
    if(bg.isDrawGrid)
        gui::inst()->drawGrid(this
                              , Size(GRID_INVALID_VALUE, GRID_INVALID_VALUE)
                              , mGrid
                              , Vec2(INVALID_VALUE, INVALID_VALUE)
                              , Vec2::ZERO
                              , Color4F::GRAY
                              );
}

void ui_wizard::drawNode(WIZARD::_Node &node, int seq)
{
    Vec2 start= gui::inst()->getPointVec2(node.dimensionStart.x, node.dimensionStart.y, ALIGNMENT_NONE
		, Size(GRID_INVALID_VALUE, GRID_INVALID_VALUE)
		, mGrid
		, Size(GRID_INVALID_VALUE, GRID_INVALID_VALUE)
		, Size::ZERO
	);
    Vec2 end = gui::inst()->getPointVec2(node.dimensionEnd.x, node.dimensionEnd.y, ALIGNMENT_NONE
		, Size(GRID_INVALID_VALUE, GRID_INVALID_VALUE)
		, mGrid
		, Size(GRID_INVALID_VALUE, GRID_INVALID_VALUE)
		, Size::ZERO
	);
    
    Size size = Size(end.x - start.x, start.y - end.y);
    Size scrollviewSize;
    //margin에 따른 사이즈 수정 필요
    if(node.isScrollView) {
        Vec2 startInner= gui::inst()->getPointVec2(node.dimensionInnerStart.x, node.dimensionInnerStart.y, ALIGNMENT_NONE
                                                   , Size(GRID_INVALID_VALUE, GRID_INVALID_VALUE)
                                                   , mGrid
                                                   , Size(GRID_INVALID_VALUE, GRID_INVALID_VALUE)
                                                   , Size::ZERO
                                                   );
        Vec2 endInner = gui::inst()->getPointVec2(node.dimensionInnerEnd.x, node.dimensionInnerEnd.y, ALIGNMENT_NONE
                                                  , Size(GRID_INVALID_VALUE, GRID_INVALID_VALUE)
                                                  , mGrid
                                                  , Size(GRID_INVALID_VALUE, GRID_INVALID_VALUE)
                                                  , Size::ZERO
                                                  );
        scrollviewSize = Size(size.width - (node.margin.width * 2.f), size.height - (node.margin.height * 2.f));
        size = Size(endInner.x - startInner.x, startInner.y - endInner.y);
        
    }
    
    Size sizeColored = Size(size.width - (node.margin.width * 2.f), size.height - (node.margin.height * 2.f));
    Size sizePerGridNoMargin = Size((sizeColored.width / node.gridSize.width), (sizeColored.height / node.gridSize.height));
    Size sizePerGrid = Size(sizePerGridNoMargin.width - (node.innerMargin.width * 2.f), sizePerGridNoMargin.height - (node.innerMargin.height * 2.f));
    float min, max;
    if(sizePerGrid.width > sizePerGrid.height) {
        min = sizePerGrid.height;
        max = sizePerGrid.width;
    } else {
        max = sizePerGrid.height;
        min = sizePerGrid.width;
    }
    
    float nodeMin, nodeMax;
    if(sizeColored.width > sizeColored.height) {
        nodeMin = sizeColored.height;
        nodeMax = sizeColored.width;
    } else {
        nodeMax = sizeColored.height;
        nodeMin = sizeColored.width;
    }
    
	//background colored layer
    Node * layoutBG = gui::inst()->createLayout(sizeColored, node.img, true, node.color.getColor3B());
    layoutBG->setOpacity(node.color.getA());
    
    ScrollView * sv;
    if (node.color_second.isValidColor) {
        
        auto gradient = LayerRadialGradient::create( node.color_second.getColor4B() //node.color.getColor4B()
                                                    , node.color.getColor4B()
                                                    , nodeMax / 1.5f
                                                    , Vec2(sizeColored.width / 2.f, sizeColored.height / 4.f) //Vec2(sizeColored.width / 2.f, sizeColored.height / 2.f)
                                                    , 0.0f);

        gradient->setContentSize(sizeColored);
        layoutBG->addChild(gradient);
        
    }
   
    
    //tile
    if(node.colorTile.isValidColor) {
        gui::inst()->drawDiamondTile(layoutBG, node.tileNum, node.colorTile.getColor4F());
    }
    
    if(node.isScrollView) {
        layoutBG->setPosition(Vec2::ZERO);
        sv = gui::inst()->addScrollView(scrollviewSize, sizeColored, Vec2(start.x + node.margin.width, end.y + node.margin.height), this);
    } else {
        layoutBG->setPosition(Vec2(start.x + node.margin.width, end.y + node.margin.height));
    }
    
    if(node.id >= 0)
        mNodeMap[node.id] = layoutBG;
    
	//draw grid line
    if(mIsDrawGrid) {
        gui::inst()->drawGrid(layoutBG, layoutBG->getContentSize(), node.gridSize, Size::ZERO, Size::ZERO, (seq % 2 == 1) ? Color4F::MAGENTA : Color4F::GREEN);
    }
    
	for (size_t n = 0; n < node.mObjects.size(); n++) {
		WIZARD::_Object obj = node.mObjects[n];
        
        string sz = obj.text;
        if(obj.id > 0)
            sz = getText(obj.text, obj.id);
        
		Vec2 center = gui::inst()->getPointVec2(obj.position.x
			, obj.position.y
			, ALIGNMENT_CENTER
			, layoutBG->getContentSize()
			, node.gridSize
			, Size::ZERO
			, Size::ZERO
		);
        
        Vec2 position = gui::inst()->getPointVec2(obj.position.x
              , obj.position.y
              , obj.alignment
              , layoutBG->getContentSize()
              , node.gridSize
              , Size::ZERO
              , Size::ZERO//node.innerMargin
        );
        Vec2 circleCenter = position;
        
        //bg color
        if(obj.bgColor.isValidColor) {
            Node * bg;
            if(obj.bgColor_second.isValidColor) {
                bg = LayerGradient::create(obj.bgColor.getColor4B(), obj.bgColor_second.getColor4B());
                bg->setContentSize(sizePerGridNoMargin);
                bg->setPosition(gui::inst()->getPointVec2(obj.position.x, obj.position.y, ALIGNMENT_LEFT_BOTTOM, layoutBG->getContentSize(), node.gridSize, Vec2::ZERO, Vec2::ZERO, Vec2::ZERO));
            } else {
                bg = gui::inst()->createLayout(sizePerGridNoMargin, "", true, obj.bgColor.getColor3B());
                bg->setOpacity(obj.bgColor.getA());
                gui::inst()->setAnchorPoint(bg, ALIGNMENT_CENTER);
                bg->setPosition(gui::inst()->getPointVec2(obj.position.x, obj.position.y, ALIGNMENT_CENTER, layoutBG->getContentSize(), node.gridSize, Vec2::ZERO, Vec2::ZERO, Vec2::ZERO));
            }
            
            layoutBG->addChild(bg);
        }
        
        switch(obj.alignment) {
            case ALIGNMENT_LEFT:
                position.x += node.innerMargin.width;
                circleCenter.x = position.x + (min / 2.f);
            break;
            case ALIGNMENT_RIGHT:
                position.x -= node.innerMargin.width;
                circleCenter.x = position.x - (min / 2.f);
            break;
            default:
            break;
        }
        
        Node * pObj;
        switch(obj.type) {
            case WIZARD::OBJECT_TYPE_LABEL:
                pObj = gui::inst()->addLabelAutoDimension(obj.position.x, obj.position.y
                    , sz
                    , layoutBG
                    , obj.fontSize
                    , obj.alignment
                    , obj.color
                    , node.gridSize
                    , Vec2::ZERO
                    , Vec2::ZERO
                    , node.innerMargin
                    , obj.img
                );
                break;
            case WIZARD::OBJECT_TYPE_LABEL_SPRITE:
                pObj = gui::inst()->addLabelAutoDimension(obj.position.x, obj.position.y
                      , sz
                      , layoutBG
                      , obj.fontSize
                      , obj.alignment
                      , obj.color
                      , node.gridSize
                      , Vec2::ZERO
                      , Vec2::ZERO
                      , node.innerMargin
                      , obj.img
                      , false
                  );
                break;
            case WIZARD::OBJECT_TYPE_BUTTON:
                pObj = gui::inst()->addTextButtonAutoDimension(obj.position.x
                                                               , obj.position.y
                                                               , sz
                                                               , layoutBG
                                                               , CC_CALLBACK_1(ui_wizard::callback, this, obj.id, obj.link)
                                                               , obj.fontSize
                                                               , obj.alignment
                                                               , obj.color
                                                               , node.gridSize
                                                               , Vec2::ZERO
                                                               , Vec2::ZERO
                                                               , node.innerMargin
                                                               , obj.img);
                break;
            case WIZARD::OBJECT_TYPE_BUTTON_SPRITE:
                pObj = gui::inst()->addTextButtonAutoDimension(obj.position.x, obj.position.y
                   , sz
                   , layoutBG
                   , CC_CALLBACK_1(ui_wizard::callback, this, obj.id, obj.link)
                   , obj.fontSize
                   , obj.alignment
                   , obj.color
                   , node.gridSize
                   , Vec2::ZERO
                   , Vec2::ZERO
                   , node.innerMargin
                   , obj.img
                   , false
                );
                break;
            case WIZARD::OBJECT_TYPE_BUTTON_CIRCLE:
            {
                auto p = gui::inst()->drawCircle(layoutBG, circleCenter, min / 2.f, Color4F(obj.color_second));
                p->setOpacity(obj.opacity_second);
                
                float fontSize = gui::inst()->getFontSize(layoutBG->getContentSize(), node.gridSize, node.margin, node.innerMargin, 0.8f);
                
                Menu * pMenu;
                pObj = gui::inst()->addTextButtonRaw(pMenu
                                                     , 0
                                                     , 0
                                                     , sz
                                                     , layoutBG
                                                     , CC_CALLBACK_1(ui_wizard::callback, this, obj.id, obj.link)
                                                     , fontSize
                                                     , ALIGNMENT_CENTER
                                                     , obj.color
                                                     , layoutBG->getContentSize()
                                                     , Vec2(1, 1)
                                                     , Vec2::ZERO
                                                     , Vec2::ZERO
                                                     , node.innerMargin
                                                     , obj.img
                                                     , false
                                                     , true
                                                     , circleCenter
                                                    );
                
            }
                break;
            case WIZARD::OBJECT_TYPE_BUTTON_RECT_ROUND_SHADOW:
            {
                gui::inst()->drawRectRoundShadow(layoutBG, center, sizePerGrid, Color4F(obj.color_second, obj.opacity_second / 255.f));
                float fontSize = gui::inst()->getFontSize(sizePerGrid);
                int fontLength = (int)(sizePerGrid.width / gui::inst()->createLabel(0, 0, "M", fontSize, ALIGNMENT_CENTER)->getContentSize().width);
                string szM = "";
                for(int n = 0; n < fontLength; n++) {
                    szM += "M";
                }
                
                gui::inst()->addTextButtonAutoDimension(obj.position.x
                                                               , obj.position.y
                                                               , szM
                                                               , layoutBG
                                                               , CC_CALLBACK_1(ui_wizard::callback, this, obj.id, obj.link)
                                                               , fontSize
                                                               , obj.alignment
                                                               , Color3B::WHITE
                                                               , node.gridSize
                                                               , Vec2::ZERO
                                                               , Vec2::ZERO
                                                               , node.innerMargin)->setOpacity(0);
                
                pObj = gui::inst()->addTextButtonAutoDimension(obj.position.x
                                                               , obj.position.y
                                                               , sz
                                                               , layoutBG
                                                               , CC_CALLBACK_1(ui_wizard::callback, this, obj.id, obj.link)
                                                               , -1
                                                               , obj.alignment
                                                               , obj.color
                                                               , node.gridSize
                                                               , Vec2::ZERO
                                                               , Vec2::ZERO
                                                               , node.innerMargin
                                                               , obj.img);
            }
                break;
            case WIZARD::OBJECT_TYPE_SPRITE:
                pObj = gui::inst()->addSpriteAutoDimension(obj.position.x
                                                           , obj.position.y
                                                           , obj.img
                                                           , layoutBG
                                                           , obj.alignment
                                                           , node.gridSize
                                                           , Vec2::ZERO
                                                           , Vec2::ZERO
                                                           , node.innerMargin
                                                           );
                if (sizePerGrid.width > sizePerGrid.height)
                    gui::inst()->setScaleByHeight(pObj, sizePerGrid.height);
                else
                    gui::inst()->setScale(pObj, sizePerGrid.width);
                
                break;
            case WIZARD::OBJECT_TYPE_SPRITE_BUTTON:
                pObj = gui::inst()->addSpriteButton(obj.position.x
                                                    , obj.position.y
                                                    , obj.img
                                                    , obj.img_selected
                                                    , layoutBG
                                                    , CC_CALLBACK_1(ui_wizard::callback, this, obj.id, obj.link)
                                                    , obj.alignment
                                                    , layoutBG->getContentSize()
                                                    , node.gridSize
                                                    , Vec2::ZERO
                                                    , Vec2::ZERO
                                                    , node.innerMargin);
                
                if (sizePerGrid.width > sizePerGrid.height)
                    gui::inst()->setScaleByHeight(pObj, sizePerGrid.height);
                else
                    gui::inst()->setScale(pObj, sizePerGrid.width);
                
                break;
            case WIZARD::OBJECT_TYPE_SPRITE_BUTTON_CIRCLE:
            {
                auto p = gui::inst()->drawCircle(layoutBG, circleCenter, min / 2.f, Color4F(obj.color));
                p->setOpacity(obj.opacity);
                
                Menu * pMenu;
                pObj = gui::inst()->addSpriteButtonRaw(pMenu
                                                       , 0
                                                       , 0
                                                       , obj.img
                                                       , obj.img_selected
                                                       , layoutBG
                                                       , CC_CALLBACK_1(ui_wizard::callback, this, obj.id, obj.link)
                                                       , ALIGNMENT_CENTER
                                                       , layoutBG->getContentSize()
                                                       , Vec2(1, 1)
                                                       , Vec2::ZERO
                                                       , Vec2::ZERO
                                                       , node.innerMargin
                                                       , circleCenter
                                                       );
                Size imgSize = sizePerGrid;
                imgSize.width -= node.innerMargin.width * 2.f;
                imgSize.height -= node.innerMargin.height * 2.f;
                
                if (imgSize.width > imgSize.height)
                    gui::inst()->setScaleByHeight(pObj, imgSize.height);
                else
                    gui::inst()->setScale(pObj, imgSize.width);
            }
                break;
            case WIZARD::OBJECT_TYPE_LOADINGBAR:
            {
                COLOR_RGB color, color2;
                color.set(obj.color, obj.opacity);
                color2.set(obj.color_second, obj.opacity_second);
                Vec2 pos = gui::inst()->getPointVec2(obj.position.x
                                                     , obj.position.y
                                                     , ALIGNMENT_LEFT_BOTTOM
                                                     , layoutBG->getContentSize()
                                                     , node.gridSize
                                                     , Vec2::ZERO
                                                     , Vec2::ZERO
                                                     , node.innerMargin );
                pObj= ui_progressbar::create(0.65, pos, sizePerGrid, color, color2, obj.alignment);
                ((ui_progressbar*)pObj)->addParent(layoutBG);
            }
//                pObj = gui::inst()->addProgressBar(obj.position.x
//                                                    , obj.position.y
//                                                    , obj.img
//                                                    , layoutBG
//                                                    , sizePerGrid
//                                                    , 90.f
//                                                    , layoutBG->getContentSize()
//                                                    , node.gridSize
//                                                    , Vec2::ZERO
//                                                    , Vec2::ZERO
//                                                    , node.innerMargin
//                                                );
                break;
            case WIZARD::OBJECT_TYPE_CIRCLE:
                pObj = gui::inst()->drawCircle(layoutBG
                                               , circleCenter
                                               , min / 2.f
                                               , Color4F(obj.color)
                                               );
            
                break;
            case WIZARD::OBJECT_TYPE_RECT:
                pObj = gui::inst()->drawRect(layoutBG, center, sizePerGrid, Color4F(obj.color));
                break;
            case WIZARD::OBJECT_TYPE_RECT_LINE:
                pObj = gui::inst()->drawRect(layoutBG, center, sizePerGrid, Color4F(obj.color), false);
                break;
            case WIZARD::OBJECT_TYPE_RECT_ROUND:
                pObj = gui::inst()->drawRectRound(layoutBG, center, sizePerGrid, Color4F(obj.color));
                break;
            case WIZARD::OBJECT_TYPE_RECT_ROUND_SHADOW:
                pObj = gui::inst()->drawRectRoundShadow(layoutBG, center, sizePerGrid, Color4F(obj.color));
                break;
            default:
                break;
        }
		pObj->setOpacity(obj.opacity);
        pObj->setVisible(obj.visible);
		if(obj.id > 0)
			mNodeMap[obj.id] = pObj;
	}
    
    if(node.isScrollView) {
        sv->setVisible(node.visible);
        sv->addChild(layoutBG);
    } else {
        layoutBG->setVisible(node.visible);
        this->addChild(layoutBG);
    }
}
