//
// Created by Jung, DaeCheon on 25/04/2019.
//

#include "ui_wizard.h"
#include "ui_progressbar.h"
#include "ui_roulette.h"
#include "ui_effect.h"
#include "ui_icon.h"
#include "ui_ext.h"
#include "ui_button.h"
#include "library/pch.h"

#define POINT_CHAR   "P"
#define POINT_COLOR  "YELLOW"

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
    this->span = Vec2::ZERO;
    
    if(p.HasMember("id") && !p["id"].IsNull())
        this->id = p["id"].GetInt();
    
    CCLOG("WIZARD::_Object::load id=%d", id);
    
    if(p.HasMember("component") && !p["component"].IsNull()) {
        this->component = p["component"].GetString();
//        CCLOG("WIZARD::_Object::load component = %s", this->component.c_str());
    }
    
//    CCLOG("WIZARD::_Object::load position");
	this->position.x = p["position"][rapidjson::SizeType(0)].GetFloat();
	this->position.y = p["position"][rapidjson::SizeType(1)].GetFloat();
    
    if(p.HasMember("span") && !p["span"].IsNull()) {
        this->span.x = p["span"][rapidjson::SizeType(0)].GetFloat();
        this->span.y = p["span"][rapidjson::SizeType(1)].GetFloat();
//        CCLOG("WIZARD::_Object::load span");
    }
    
    this->alignment = ALIGNMENT_CENTER;
    if(p.HasMember("alignment") && !p["alignment"].IsNull()) {
        const string szAlignment = p["alignment"].GetString();
        if (szAlignment.compare("none") == 0) {
            this->alignment = ALIGNMENT_NONE;
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
        
//        CCLOG("WIZARD::_Object::load alignment %s", szAlignment.c_str());
    }
    
    
//    CCLOG("WIZARD::_Object::load type");
	this->type = (OBJECT_TYPE)getObjectType(p["type"].GetString());
//    CCLOG("Start WIZARD::_Object::load link");
	this->link = ( !p.HasMember("link") || p["link"].IsNull()) ? NULL_INT_VALUE : p["link"].GetInt();
    
//    CCLOG("WIZARD::_Object::load text");
    this->text = (!p.HasMember("text") || p["text"].IsNull()) ? NULL_STRING_VALUE : p["text"].GetString();
//    CCLOG("WIZARD::_Object::load fontSize");
    this->fontSize = (!p.HasMember("fontSize") || p["fontSize"].IsNull()) ? 0 : p["fontSize"].GetFloat();
//    CCLOG("WIZARD::_Object::load visible");
    this->visible = (!p.HasMember("visible") || p["visible"].IsNull()) ? true : p["visible"].GetBool();
	
//    CCLOG("WIZARD::_Object::load img");
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
    
//    CCLOG("WIZARD::_Object::load color");
    if (p.HasMember("color") && !p["color"].IsNull()) {
        //COLOR_RGB color1, color2;
        getColorFromJson(p["color"], &color1, &color2);
        this->color = color1.getColor3B();
        this->opacity = color1.getA();
        if(color2.isValidColor) {
            this->color_second = color2.getColor3B();
            this->opacity_second = color2.getA();
        }
    }
    
//    CCLOG("WIZARD::_Object::load bgColor");
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
    else if (type.compare("button_rectangle_circle_shadow_1") == 0)
        return OBJECT_TYPE_BUTTON_RECT_CIRCLE_SHADOW_1;
    else if (type.compare("button_rectangle_circle_shadow_2") == 0)
        return OBJECT_TYPE_BUTTON_RECT_CIRCLE_SHADOW_2;
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
    else if (type.compare("progressbar_FLAT") == 0)
        return OBJECT_TYPE_PROGRESSBAR_FLAT;
    else if (type.compare("progressbar") == 0)
        return OBJECT_TYPE_PROGRESSBAR;
    else if (type.compare("checkbox") == 0)
        return OBJECT_TYPE_CHECKBOX;
    else if (type.compare("roulette") == 0)
        return OBJECT_TYPE_ROULETTE;
    else if (type.compare("lighting") == 0)
        return OBJECT_TYPE_LIGHTING;
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
    else if (type.compare("line") == 0)
        return OBJECT_TYPE_LINE;
    else if (type.compare("icon_circle") == 0)
        return OBJECT_TYPE_ICON_CIRCLE;
    else if (type.compare("icon_heart") == 0)
        return OBJECT_TYPE_ICON_HEART;
    else if (type.compare("icon_point") == 0)
        return OBJECT_TYPE_ICON_POINT;
    else if (type.compare("icon_circle2") == 0)
        return OBJECT_TYPE_ICON_CIRCLE2;
    else if (type.compare("icon_heart2") == 0)
        return OBJECT_TYPE_ICON_HEART2;
    else if (type.compare("icon_point2") == 0)
        return OBJECT_TYPE_ICON_POINT2;
    else if (type.compare("component") == 0)
        return OBJECT_TYPE_COMPONENT;
    else if (type.compare("layer") == 0)
        return OBJECT_TYPE_LAYER;
    
	return OBJECT_TYPE_LABEL;
}
// _Node -------------------------------------------------------------------------------------------
bool WIZARD::_Node::load(rapidjson::Value & pValue)
{
    CCLOG("Start WIZARD::_Node::load");
    this->visible = true;
    this->isScrollView = false;
    this->id = -1;
    this->link = -1;
    this->img = NULL_STRING_VALUE;
    
    if(pValue.HasMember("id") && !pValue["id"].IsNull())
        this->id = pValue["id"].GetInt();
	
    CCLOG("WIZARD::_Node::load id=%d", id);
    
    rapidjson::Value & p = (pValue.HasMember("include")) ? getJsonValue(pValue["include"]["path"].GetString())[pValue["include"]["key"].GetString()] : pValue;
    
    if(p.HasMember("component") && !p["component"].IsNull()) {
        this->component = p["component"].GetString();
//        CCLOG("WIZARD::_Node::load component = %s", this->component.c_str());
        return true;
    }
    
    if(p.HasMember("link") && !p["link"].IsNull()) {
        this->link = p["link"].GetInt();
//        CCLOG("WIZARD::_Node::load link = %d", this->link);
    }
    
//    CCLOG("WIZARD::_Node::load dimension");
    this->dimensionStart.x = p["dimension"][rapidjson::SizeType(0)].GetFloat();
	this->dimensionStart.y = p["dimension"][rapidjson::SizeType(1)].GetFloat();
	this->dimensionEnd.x = p["dimension"][rapidjson::SizeType(2)].GetFloat();
	this->dimensionEnd.y = p["dimension"][rapidjson::SizeType(3)].GetFloat();
    
    if(p.HasMember("dimensionInner") && !p["dimensionInner"].IsNull()) {
//        CCLOG("Start WIZARD::_Node::load dimensionInner");
        this->dimensionInnerStart.x = p["dimensionInner"][rapidjson::SizeType(0)].GetFloat();
        this->dimensionInnerStart.y = p["dimensionInner"][rapidjson::SizeType(1)].GetFloat();
        this->dimensionInnerEnd.x = p["dimensionInner"][rapidjson::SizeType(2)].GetFloat();
        this->dimensionInnerEnd.y = p["dimensionInner"][rapidjson::SizeType(3)].GetFloat();
        
        this->isScrollView = true;
    }
    
//    CCLOG("WIZARD::_Node::load margin");
	this->margin.x = p["margin"][rapidjson::SizeType(0)].GetFloat();
	this->margin.y = p["margin"][rapidjson::SizeType(1)].GetFloat();
    
//    CCLOG("WIZARD::_Node::load innerMargin");
    this->innerMargin.x = p["innerMargin"][rapidjson::SizeType(0)].GetFloat();
    this->innerMargin.y = p["innerMargin"][rapidjson::SizeType(1)].GetFloat();
    
//    CCLOG("WIZARD::_Node::load gridSize");
	this->gridSize.x = p["gridSize"][rapidjson::SizeType(0)].GetFloat();
	this->gridSize.y = p["gridSize"][rapidjson::SizeType(1)].GetFloat();
    
    
    if(p.HasMember("img") && !p["img"].IsNull()) {
        this->img = p["img"].GetString();
//        CCLOG("WIZARD::_Node::load img %s", this->img.c_str());
    }
    
//    CCLOG("WIZARD::_Node::load color");
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
//        CCLOG("WIZARD::_Node::load tile");
        COLOR_RGB color1;
        getColorFromJson(p["tile"]["color"], &color1);
        this->colorTile.set(color1);
        this->tileNum = Vec2(p["tile"]["num"][rapidjson::SizeType(0)].GetInt()
                             , p["tile"]["num"][rapidjson::SizeType(1)].GetInt());
    }

//    CCLOG("WIZARD::_Node::load objects");
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
    
//    CCLOG("WIZARD::_Node::load visible");
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
    
    //grid
    if(p.HasMember("grid") && !p["grid"].IsNull()) {
        this->grid = Vec2(p["grid"][rapidjson::SizeType(0)].GetInt(), p["grid"][rapidjson::SizeType(1)].GetInt());
    } else {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        this->grid = Vec2(GRID_X, GRID_Y);
        if(visibleSize.width < visibleSize.height)
            this->grid = Vec2(GRID_Y, GRID_X);
    }

    this->isDrawGrid = false;
    //bgColor
//    CCLOG("WIZARD::_Background::load bgColor");
	if (!p["bgColor"].IsNull()) {
        COLOR_RGB color1, color2;
        getColorFromJson(p["bgColor"], &color1, &color2);
        this->bgColor.set(color1);
        if(color2.isValidColor) {
            this->bgColor_second.set(color2);
        }
	}
    //tile
//    CCLOG("WIZARD::_Background::load tile");
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
//    CCLOG("WIZARD::_Background::load isDrawGrid");
    if(!p["isDrawGrid"].IsNull())
        this->isDrawGrid = p["isDrawGrid"].GetBool();
    
	return true;
}
//
//rapidjson::Document WIZARD::getJsonValue(const string& path) {
//    string fullpath = FileUtils::getInstance()->fullPathForFilename(path);
//    string sz = FileUtils::getInstance()->getStringFromFile(fullpath);
//    
//    rapidjson::Document d;
//    d.Parse(sz.c_str());
//    if (d.HasParseError()) {
//        CCLOG("loadFromJson Failure. ErrorCode: %d, ErrorOffset: %zu", d.GetParseError(), d.GetErrorOffset());
//        //return false;
//    }
//    return d;
//}

// ui_wizard -------------------------------------------------------------------------------------------
bool ui_wizard::loadFromJson(const string& sceneName, const string& path)
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    mGrid = Vec2(GRID_X, GRID_Y);
//    if(visibleSize.width < visibleSize.height)
//        mGrid = Vec2(GRID_Y, GRID_X);
    //Draw from memory --------------------------------------------------------------------------------------
	if (ui_wizard_share::inst()->hasNode(sceneName)) {
        WIZARD::_Background bg = ui_wizard_share::inst()->getBackgound(sceneName);
        mGrid = bg.grid;
		this->drawBackground(bg);

		WIZARD::VEC_NODES nodes = ui_wizard_share::inst()->getNodes(sceneName);
		for (size_t n = 0; n < nodes.size(); n++) {
			WIZARD::_Node p = nodes[n];
			drawNode(p);
		}
		return true;
	}
    
    //Parse & Draw --------------------------------------------------------------------------------------
    rapidjson::Document d = getJsonValue(path);
    
    //component

    //background
	WIZARD::_Background bg;
	bg.load(d["background"]);
    mGrid = bg.grid;
	ui_wizard_share::inst()->setBackground(sceneName, bg);
	this->drawBackground(bg);

    //_Node
	const rapidjson::Value& nodes = d["nodes"];
	for (rapidjson::SizeType i = 0; i < nodes.Size(); i++)
	{	
		WIZARD::_Node p;
		if (!p.load(d["nodes"][rapidjson::SizeType(i)]))
			return false;
		
		ui_wizard_share::inst()->addNode(sceneName, p);
		drawNode(p);
	}

	return true;
}

//Palette --------------------------------------------------------------------------------------
bool ui_wizard_share::loadPaletteFromJson(const string& pathPalette) {
    
    if(pathPalette.compare("") != 0 && ui_wizard_share::inst()->insertPalettePath(pathPalette)) {
        rapidjson::Document dPalette = getJsonValue(pathPalette);
        int brightness = dPalette["brightness"].GetInt();
        int tone = dPalette["tone"].GetInt();
        
        for (auto& m : dPalette.GetObject())
        {
            string name = m.name.GetString();
            if(name.compare("brightness") == 0 || name.compare("tone") == 0)
                continue;
            
            int rgba[4];
            for(int n=0; n < 4; n++) rgba[n] = m.value[n].GetInt();
            COLOR_RGB color = COLOR_RGB(rgba[0], rgba[1], rgba[2], rgba[3]);
            COLOR_RGB colorWarm = color.getColorWarm(tone);
            COLOR_RGB colorCool = color.getColorCool(tone);
            COLOR_RGB colorDark = color.getColorDark(brightness);
            COLOR_RGB colorLight = color.getColorLight(brightness);
            
            //color
            ui_wizard_share::inst()->getPalette()->set(name, color);
            //warm
            ui_wizard_share::inst()->getPalette()->set(name + "_WARM", colorWarm);
            //warm
            ui_wizard_share::inst()->getPalette()->set(name + "_COOL", colorCool);
            //warm
            ui_wizard_share::inst()->getPalette()->set(name + "_DARK", colorDark);
            //warm
            ui_wizard_share::inst()->getPalette()->set(name + "_LIGHT", colorLight);
        }
        
        ui_color::COLOR_MAP::iterator it;
        for (it = ui_wizard_share::inst()->getPalette()->mMap.begin(); it != ui_wizard_share::inst()->getPalette()->mMap.end(); ++it) {
            CCLOG("Insert Palette %s\t[ %d, %d, %d, %d ]"
                  , it->first.c_str()
                  , it->second.R
                  , it->second.G
                  , it->second.B
                  , it->second.A
                  );
        }
        return true;
    }
    return false;
}

bool ui_wizard_share::loadComponentFromJson(const string& path) {
    if(path.compare("") != 0) {
        rapidjson::Document d = getJsonValue(path);
        for (auto& m : d.GetObject())
        {
            string name = m.name.GetString();
            WIZARD::_Node componet;
            componet.load(m.value);
            setComponent(name, componet);
        }
        return true;
    }
    return false;
}

Node * ui_wizard::getNodeById(int id)
{
	if (mNodeMap.find(id) == mNodeMap.end())
		return nullptr;
    Node * p = mNodeMap[id];
	return p;
}

void ui_wizard::drawBackground(WIZARD::_Background & bg)
{
    Size size = Director::getInstance()->getVisibleSize();
    mIsDrawGrid = bg.isDrawGrid;
//    auto p = (bg.bgColor_second.isValidColor) ? LayerGradient::create(bg.bgColor.getColor4B(), bg.bgColor_second.getColor4B()) : LayerColor::create(bg.bgColor.getColor4B());
    mScreen = LayerColor::create(bg.bgColor.getColor4B());
	mScreen->setContentSize(size);
    mScreen->setAnchorPoint(Vec2::ZERO);
	mScreen->setPosition(Director::getInstance()->getVisibleOrigin());
	this->addChild(mScreen);
    
    if (bg.bgColor_second.isValidColor) {
        
        auto gradient = LayerRadialGradient::create( bg.bgColor_second.getColor4B() //node.color.getColor4B()
                                                    , bg.bgColor.getColor4B()
                                                    , size.width / 1.5f
                                                    , Vec2(size.width / 2.f, size.height / 4.f) //Vec2(sizeColored.width / 2.f, sizeColored.height / 2.f)
                                                    , 0.0f);
        
        gradient->setContentSize(size);
        mScreen->addChild(gradient);
        
    }

	if (bg.img.compare(NULL_STRING_VALUE) != 0) {
		gui::inst()->addBG(bg.img, mScreen, true);
	}
    
    if(bg.id >= 0)
        mNodeMap[bg.id] = mScreen;
    
    if(bg.tileColor.isValidColor) {
        gui::inst()->drawDiamondTile(mScreen, bg.tileNum, bg.tileColor.getColor4F());
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

Node * ui_wizard::createNode(const Size& Dimension, const Vec2& Origin, const Vec2& Grid, WIZARD::_Node &node, int seq)
{
    Vec2 start= gui::inst()->getPointVec2(node.dimensionStart.x, node.dimensionStart.y, ALIGNMENT_NONE
		, Dimension
		, Grid
		, Origin
		, Vec2::ZERO
	);
    Vec2 end = gui::inst()->getPointVec2(node.dimensionEnd.x, node.dimensionEnd.y, ALIGNMENT_NONE
		, Dimension
		, Grid
		, Origin
		, Vec2::ZERO
	);
    
    Size size = Size(end.x - start.x, start.y - end.y);
    Size scrollviewSize;
    //margin에 따른 사이즈 수정 필요
    if(node.isScrollView) {
        Vec2 startInner= gui::inst()->getPointVec2(node.dimensionInnerStart.x, node.dimensionInnerStart.y, ALIGNMENT_NONE
                                                   , Dimension
                                                   , Grid
                                                   , Origin
                                                   , Vec2::ZERO
                                                   );
        Vec2 endInner = gui::inst()->getPointVec2(node.dimensionInnerEnd.x, node.dimensionInnerEnd.y, ALIGNMENT_NONE
                                                  , Dimension
                                                  , Grid
                                                  , Origin
                                                  , Vec2::ZERO
                                                  );
        scrollviewSize = Size(size.width - (node.margin.x * 2.f), size.height - (node.margin.y * 2.f));
        size = Size(endInner.x - startInner.x, startInner.y - endInner.y);
        
    }
    
    Size sizeColored = Size(size.width - (node.margin.x * 2.f), size.height - (node.margin.y * 2.f));
    Size sizePerGridNoMargin = Size((sizeColored.width / node.gridSize.x), (sizeColored.height / node.gridSize.y));
    Size sizePerGrid = Size(sizePerGridNoMargin.width - (node.innerMargin.x * 2.f), sizePerGridNoMargin.height - (node.innerMargin.y * 2.f));
    
    float nodeMin, nodeMax;
    if(sizeColored.width > sizeColored.height) {
        nodeMin = sizeColored.height;
        nodeMax = sizeColored.width;
    } else {
        nodeMax = sizeColored.height;
        nodeMin = sizeColored.width;
    }
    //component
    if(node.component.length() > 0) {
        WIZARD::_Node component =  ui_wizard_share::inst()->getComponent(node.component);
        return createNode(Dimension, Origin, Grid, component, 0);
    }
	//background colored layer
    Node * layoutBG = gui::inst()->createLayout(sizeColored
                                                , node.img
                                                , (node.color.getA() == 0) ? false : true
                                                , node.color.getColor3B());
    if(node.color.getA() > 0)
        layoutBG->setOpacity(node.color.getA());
    
    layoutBG->setPosition(Vec2(start.x + node.margin.x, end.y + node.margin.y));
    ScrollView * sv = NULL;
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
        sv = gui::inst()->addScrollView(scrollviewSize, sizeColored, Vec2(start.x + node.margin.x, end.y + node.margin.y), NULL);
    }
    
    if(node.id >= 0)
        mNodeMap[node.id] = (sv != NULL) ? sv : layoutBG;
    
	//draw grid line
    if(mIsDrawGrid) {
        int idx = getRandValue(6);
        
        Color4F lineColor = ui_wizard_share::inst()->_DRAWLINE_COLOR[idx];
        gui::inst()->drawGrid(layoutBG, layoutBG->getContentSize(), node.gridSize, Size::ZERO, Size::ZERO, lineColor);
    }
    
	for (size_t n = 0; n < node.mObjects.size(); n++) {
		WIZARD::_Object obj = node.mObjects[n];
        
        int objId = obj.id + seq;
        string sz = obj.text;
        if(obj.id > 0)
            sz = getText(obj.text, objId);
        
		Vec2 center = gui::inst()->getPointVec2(obj.position.x
                                                , obj.position.y
                                                , ALIGNMENT_CENTER
                                                , layoutBG->getContentSize()
                                                , node.gridSize
                                                , Size::ZERO
                                                , Size::ZERO
                                                , Size::ZERO
                                                , obj.span
		);
        
        Vec2 position = gui::inst()->getPointVec2(obj.position.x
                                                  , obj.position.y
                                                  , obj.alignment
                                                  , layoutBG->getContentSize()
                                                  , node.gridSize
                                                  , Size::ZERO
                                                  , Size::ZERO
                                                  , Size::ZERO //node.innerMargin
                                                  , obj.span);
        
        Vec2 positionWithInnerMargin = gui::inst()->getPointVec2(obj.position.x
                                                  , obj.position.y
                                                  , obj.alignment
                                                  , layoutBG->getContentSize()
                                                  , node.gridSize
                                                  , Size::ZERO
                                                  , Size::ZERO
                                                  , node.innerMargin
                                                  , obj.span);
        
        Size gridSizeWithSpan = gui::inst()->getGridSize(layoutBG->getContentSize(), node.gridSize, Vec2::ZERO, Vec2::ZERO, obj.span);
        Size gridSizeWithSpanWithMargin = Size(gridSizeWithSpan.width - (node.innerMargin.x * 2.f), gridSizeWithSpan.height - (node.innerMargin.y * 2.f));
        
        float min, max;
        if(gridSizeWithSpanWithMargin.width > gridSizeWithSpanWithMargin.height) {
            min = gridSizeWithSpanWithMargin.height;
            max = gridSizeWithSpanWithMargin.width;
        } else {
            max = gridSizeWithSpanWithMargin.height;
            min = gridSizeWithSpanWithMargin.width;
        }
        
        //bg color
        if(obj.bgColor.isValidColor && obj.visible) {
            Node * bg;
            if(obj.bgColor_second.isValidColor) {
                bg = LayerGradient::create(obj.bgColor.getColor4B(), obj.bgColor_second.getColor4B());
                bg->setContentSize(gridSizeWithSpan);
                bg->setPosition(gui::inst()->getPointVec2(obj.position.x
                                                          , obj.position.y
                                                          , ALIGNMENT_LEFT_BOTTOM
                                                          , layoutBG->getContentSize()
                                                          , node.gridSize
                                                          , Vec2::ZERO
                                                          , Vec2::ZERO
                                                          , Vec2::ZERO
                                                          , obj.span));
            } else {
                bg = gui::inst()->createLayout(gridSizeWithSpan, "", true, obj.bgColor.getColor3B());
                bg->setOpacity(obj.bgColor.getA());
                gui::inst()->setAnchorPoint(bg, ALIGNMENT_CENTER);
                bg->setPosition(gui::inst()->getPointVec2(obj.position.x
                                                          , obj.position.y
                                                          , ALIGNMENT_CENTER
                                                          , layoutBG->getContentSize()
                                                          , node.gridSize
                                                          , Vec2::ZERO
                                                          , Vec2::ZERO
                                                          , Vec2::ZERO
                                                          , obj.span));
            }
            
            layoutBG->addChild(bg);
        }
        
        Vec2 circleCenter = position;
        switch(obj.alignment) {
            case ALIGNMENT_LEFT:
                circleCenter.x += node.innerMargin.x;
                circleCenter.x += (min / 2.f);
            break;
            case ALIGNMENT_RIGHT:
                circleCenter.x -= node.innerMargin.x;
                circleCenter.x -= (min / 2.f);
            break;
            case ALIGNMENT_CENTER_TOP:
                circleCenter.y -= node.innerMargin.x;
                circleCenter.y -= (min / 2.f);
            break;
            case ALIGNMENT_CENTER_BOTTOM:
                circleCenter.y += node.innerMargin.x;
                circleCenter.y += (min / 2.f);
            break;
            default:
            break;
        }
        
//        COLOR_RGB color1, color2;
//        color1.set(obj.color, obj.opacity);
//        color2.set(obj.color_second, obj.opacity_second);
        
        Node * pObj;
        switch(obj.type) {
            case WIZARD::OBJECT_TYPE_LABEL:
                pObj = gui::inst()->addLabelAutoDimension(obj.position.x
                                                          , obj.position.y
                                                          , sz
                                                          , layoutBG
                                                          , obj.fontSize
                                                          , obj.alignment
                                                          , obj.color
                                                          , node.gridSize
                                                          , Vec2::ZERO
                                                          , Vec2::ZERO
                                                          , node.innerMargin
                                                          , obj.span
                                                          , obj.img);
                
                if(obj.color2.isValidColor)
                    ((Label*)pObj)->enableGlow(obj.color2.getColor4B());
                
                break;
            case WIZARD::OBJECT_TYPE_LABEL_SPRITE:
                pObj = gui::inst()->addLabelAutoDimension(obj.position.x
                                                          , obj.position.y
                                                          , sz
                                                          , layoutBG
                                                          , obj.fontSize
                                                          , obj.alignment
                                                          , obj.color
                                                          , node.gridSize
                                                          , Vec2::ZERO
                                                          , Vec2::ZERO
                                                          , node.innerMargin
                                                          , obj.span
                                                          , obj.img
                                                          , false);
                break;
            case WIZARD::OBJECT_TYPE_BUTTON:
                pObj = gui::inst()->addTextButtonAutoDimension(obj.position.x
                                                               , obj.position.y
                                                               , sz
                                                               , layoutBG
                                                               , CC_CALLBACK_1(ui_wizard::callback, this, objId, obj.link)
                                                               , obj.fontSize
                                                               , obj.alignment
                                                               , obj.color
                                                               , node.gridSize
                                                               , Vec2::ZERO
                                                               , Vec2::ZERO
                                                               , node.innerMargin
                                                               , obj.span
                                                               , obj.img);
                break;
            case WIZARD::OBJECT_TYPE_BUTTON_SPRITE:
                pObj = gui::inst()->addTextButtonAutoDimension(obj.position.x, obj.position.y
                   , sz
                   , layoutBG
                   , CC_CALLBACK_1(ui_wizard::callback, this, objId, obj.link)
                   , obj.fontSize
                   , obj.alignment
                   , obj.color
                   , node.gridSize
                   , Vec2::ZERO
                   , Vec2::ZERO
                   , node.innerMargin
                   , obj.span
                   , obj.img
                   , false
                );
                break;
            case WIZARD::OBJECT_TYPE_BUTTON_CIRCLE:
            {
                
                auto p = gui::inst()->drawCircle(layoutBG, circleCenter, min / 2.f, Color4F(obj.color_second));
                p->setOpacity(obj.opacity_second);
                
                float fontSize = gui::inst()->getFontSize(layoutBG->getContentSize(), node.gridSize, node.margin, node.innerMargin, obj.span, 0.8f);
                
                Menu * pMenu;
                pObj = gui::inst()->addTextButtonRaw(pMenu
                                                     , 0
                                                     , 0
                                                     , sz
                                                     , layoutBG
                                                     , CC_CALLBACK_1(ui_wizard::callback, this, objId, obj.link)
                                                     , fontSize
                                                     , ALIGNMENT_CENTER
                                                     , obj.color
                                                     , layoutBG->getContentSize()
                                                     , Vec2(1, 1)
                                                     , Vec2::ZERO
                                                     , Vec2::ZERO
                                                     , node.innerMargin
                                                     , obj.span
                                                     , obj.img
                                                     , false
                                                     , true
                                                     , circleCenter
                                                    );
             
                break;
            }
            case WIZARD::OBJECT_TYPE_BUTTON_RECT_CIRCLE_SHADOW_1: {
                
                pObj = ui_button::create(objId
                                         , obj.link
                                         , sz
                                         , layoutBG
                                         , center
                                         , obj.alignment
                                         , gridSizeWithSpanWithMargin
                                         , ui_button::TYPE_CIRCLE
                                         , std::bind(&ui_wizard::callback2, this, std::placeholders::_1, std::placeholders::_2)
                                         , obj.color2
                                         , obj.color1
                                         , COLOR_RGB()
                                         , obj.img
                                         );
            
                break;
            }
            case WIZARD::OBJECT_TYPE_BUTTON_RECT_CIRCLE_SHADOW_2:
            {
                pObj = ui_button::create(objId
                                         , obj.link
                                         , sz
                                         , layoutBG
                                         , center
                                         , obj.alignment
                                         , gridSizeWithSpanWithMargin
                                         , ui_button::TYPE_CIRCLE
                                         , std::bind(&ui_wizard::callback2, this, std::placeholders::_1, std::placeholders::_2)
                                         , obj.color2
                                         , obj.color1
                                         , ui_wizard_share::inst()->getPalette()->getColor("WHITE")
                                         , obj.img
                                         );
                
                break;
            }
            case WIZARD::OBJECT_TYPE_BUTTON_RECT_ROUND_SHADOW:
            {
                pObj = ui_button::create(objId
                                         , obj.link
                                         , sz
                                         , layoutBG
                                         , center
                                         , obj.alignment
                                         , gridSizeWithSpanWithMargin
                                         , ui_button::TYPE_ROUND
                                         , std::bind(&ui_wizard::callback2, this, std::placeholders::_1, std::placeholders::_2)
                                         , obj.color2
                                         , obj.color1
                                         , COLOR_RGB()
                                         , obj.img
                                         );
                
//                COLOR_RGB color = COLOR_RGB(obj.color_second.r, obj.color_second.g, obj.color_second.b, obj.opacity_second);
//                guiExt::drawRectRoundShadow(layoutBG, center, gridSizeWithSpanWithMargin, color);
//                float fontSize = gui::inst()->getFontSize(gridSizeWithSpanWithMargin);
//                int fontLength = (int)(gridSizeWithSpanWithMargin.width / gui::inst()->createLabel(0, 0, "M", fontSize, ALIGNMENT_CENTER)->getContentSize().width);
//                string szM = "";
//                for(int n = 0; n < fontLength; n++) {
//                    szM += "M";
//                }
//
//                gui::inst()->addTextButtonAutoDimension(obj.position.x
//                                                        , obj.position.y
//                                                        , szM
//                                                        , layoutBG
//                                                        , CC_CALLBACK_1(ui_wizard::callback, this, obj.id, obj.link)
//                                                        , fontSize
//                                                        , obj.alignment
//                                                        , Color3B::WHITE
//                                                        , node.gridSize
//                                                        , Vec2::ZERO
//                                                        , Vec2::ZERO
//                                                        , node.innerMargin
//                                                        , obj.span
//                                                        )->setOpacity(0);
//
//                pObj = gui::inst()->addTextButtonAutoDimension(obj.position.x
//                                                               , obj.position.y
//                                                               , sz
//                                                               , layoutBG
//                                                               , CC_CALLBACK_1(ui_wizard::callback, this, obj.id, obj.link)
//                                                               , -1
//                                                               , obj.alignment
//                                                               , obj.color
//                                                               , node.gridSize
//                                                               , Vec2::ZERO
//                                                               , Vec2::ZERO
//                                                               , node.innerMargin
//                                                               , obj.span
//                                                               , obj.img);
                break;
            }
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
                                                           , obj.span
                                                           );
                if (gridSizeWithSpanWithMargin.width > gridSizeWithSpanWithMargin.height)
                    gui::inst()->setScaleByHeight(pObj, gridSizeWithSpanWithMargin.height);
                else
                    gui::inst()->setScale(pObj, gridSizeWithSpanWithMargin.width);
                
                break;
            case WIZARD::OBJECT_TYPE_SPRITE_BUTTON:
                pObj = gui::inst()->addSpriteButton(obj.position.x
                                                    , obj.position.y
                                                    , obj.img
                                                    , obj.img_selected
                                                    , layoutBG
                                                    , CC_CALLBACK_1(ui_wizard::callback, this, objId, obj.link)
                                                    , obj.alignment
                                                    , layoutBG->getContentSize()
                                                    , node.gridSize
                                                    , Vec2::ZERO
                                                    , Vec2::ZERO
                                                    , node.innerMargin
                                                    , obj.span);
                
                if (gridSizeWithSpanWithMargin.width > gridSizeWithSpanWithMargin.height)
                    gui::inst()->setScaleByHeight(pObj, gridSizeWithSpanWithMargin.height);
                else
                    gui::inst()->setScale(pObj, gridSizeWithSpanWithMargin.width);
                
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
                                                       , CC_CALLBACK_1(ui_wizard::callback, this, objId, obj.link)
                                                       , ALIGNMENT_CENTER
                                                       , layoutBG->getContentSize()
                                                       , Vec2(1, 1)
                                                       , Vec2::ZERO
                                                       , Vec2::ZERO
                                                       , node.innerMargin
                                                       , obj.span
                                                       , circleCenter
                                                       );
                Size imgSize = gridSizeWithSpanWithMargin;
                imgSize.width -= node.innerMargin.x * 2.f;
                imgSize.height -= node.innerMargin.y * 2.f;
                
                if (imgSize.width > imgSize.height)
                    gui::inst()->setScaleByHeight(pObj, imgSize.height);
                else
                    gui::inst()->setScale(pObj, imgSize.width);
            }
                break;
            case WIZARD::OBJECT_TYPE_LOADINGBAR:
                pObj = gui::inst()->addProgressBar(obj.position.x
                                                    , obj.position.y
                                                    , obj.img
                                                    , layoutBG
                                                    , sizePerGrid
                                                    , 90.f
                                                    , layoutBG->getContentSize()
                                                    , node.gridSize
                                                    , Vec2::ZERO
                                                    , Vec2::ZERO
                                                    , node.innerMargin
                                                );
                break;
            case WIZARD::OBJECT_TYPE_PROGRESSBAR_FLAT:
            case WIZARD::OBJECT_TYPE_PROGRESSBAR:
            {
                UI_PROGRESSBAR_TYPE t = (obj.type == WIZARD::OBJECT_TYPE_PROGRESSBAR_FLAT) ? UI_PROGRESSBAR_TYPE_0 : UI_PROGRESSBAR_TYPE_1;
                Vec2 pos = gui::inst()->getPointVec2(obj.position.x
                                                     , obj.position.y
                                                     , ALIGNMENT_LEFT_BOTTOM
                                                     , layoutBG->getContentSize()
                                                     , node.gridSize
                                                     , Vec2::ZERO
                                                     , Vec2::ZERO
                                                     , node.innerMargin
                                                     , obj.span);
                pObj= ui_progressbar::create(t, getProgressValue(objId), pos, gridSizeWithSpanWithMargin, obj.color1, obj.color2, obj.alignment);
                if(sz.size() > 0)
                    ((ui_progressbar*)pObj)->setText(sz);
                
                ((ui_progressbar*)pObj)->addParent(layoutBG);
                break;
            }
            case WIZARD::OBJECT_TYPE_CHECKBOX:
                pObj = ui_checkbox::create(layoutBG
                                           , positionWithInnerMargin
                                           , obj.alignment
                                           , gridSizeWithSpanWithMargin
                                           , (int)obj.fontSize
                                           , sz
                                           , obj.color1
                                           , obj.color2);
                break;
            case WIZARD::OBJECT_TYPE_ROULETTE:
            {
                pObj = guiExt::addRoulette(layoutBG, gridSizeWithSpanWithMargin, center, obj.color1, obj.color2, sz);
                break;
            }
            case WIZARD::OBJECT_TYPE_LIGHTING:
                pObj = ui_effect::create();
                ((ui_effect*)pObj)->addBG(layoutBG, obj.color1);
                break;
            case WIZARD::OBJECT_TYPE_CIRCLE:
                pObj = gui::inst()->drawCircle(layoutBG
                                               , circleCenter
                                               , min / 2.f
                                               , Color4F(obj.color)
                                               );
            
                break;
            case WIZARD::OBJECT_TYPE_RECT:
                pObj = gui::inst()->drawRect(layoutBG, center, gridSizeWithSpanWithMargin, Color4F(obj.color));
                break;
            case WIZARD::OBJECT_TYPE_RECT_LINE:
                pObj = gui::inst()->drawRect(layoutBG, center, gridSizeWithSpan, Color4F(obj.color), false);
                break;
            case WIZARD::OBJECT_TYPE_RECT_ROUND:
                pObj = gui::inst()->drawRectRound(layoutBG, center, gridSizeWithSpanWithMargin, Color4F(obj.color));
                break;
            case WIZARD::OBJECT_TYPE_RECT_ROUND_SHADOW:
            {
                COLOR_RGB color = COLOR_RGB(obj.color.r, obj.color.g, obj.color.b, obj.opacity);
                pObj = guiExt::drawRectRoundShadow(layoutBG, center, gridSizeWithSpanWithMargin, color);
                break;
            }
            case WIZARD::OBJECT_TYPE_LINE:
                pObj = gui::inst()->drawLine(layoutBG
                                             , position
                                             , Vec2(position.x + gridSizeWithSpan.width /* + (node.innerMargin.x * 2.f)*/, position.y)
                                             , Color4F(obj.color));
                break;
            case WIZARD::OBJECT_TYPE_ICON_CIRCLE:
                pObj = ui_icon::create();
                ((ui_icon*)pObj)->addCircle(layoutBG, gridSizeWithSpanWithMargin, positionWithInnerMargin, obj.alignment
                                            , obj.color1
                                            , sz
                                            , obj.img
                                            );
                break;
            case WIZARD::OBJECT_TYPE_ICON_HEART:
                pObj = ui_icon::create();
                ((ui_icon*)pObj)->addHeart(layoutBG, gridSizeWithSpanWithMargin, positionWithInnerMargin, obj.alignment, sz, obj.color1, obj.fontSize);
                break;
            case WIZARD::OBJECT_TYPE_ICON_POINT:
                pObj = ui_icon::create();
                ((ui_icon*)pObj)->addCircle(layoutBG, gridSizeWithSpanWithMargin, positionWithInnerMargin, obj.alignment
                                            , ui_wizard_share::inst()->getPalette()->getColor(POINT_COLOR)
                                            , POINT_CHAR
                                            , ""
                                            , sz
                                            , obj.color1
                                            , obj.fontSize);
                
                break;
            case WIZARD::OBJECT_TYPE_ICON_CIRCLE2:
                pObj = ui_icon::create(false);
                ((ui_icon*)pObj)->addCircle(layoutBG, gridSizeWithSpanWithMargin, positionWithInnerMargin, obj.alignment
                                            , obj.color1
                                            , sz
                                            , obj.img
                                            );
                break;
            case WIZARD::OBJECT_TYPE_ICON_HEART2:
                pObj = ui_icon::create(false);
                ((ui_icon*)pObj)->addHeart(layoutBG, gridSizeWithSpanWithMargin, positionWithInnerMargin, obj.alignment, sz, obj.color1, obj.fontSize);
                break;
            case WIZARD::OBJECT_TYPE_ICON_POINT2:
                pObj = ui_icon::create(false);
                ((ui_icon*)pObj)->addCircle(layoutBG, gridSizeWithSpanWithMargin, positionWithInnerMargin, obj.alignment
                                            , ui_wizard_share::inst()->getPalette()->getColor(POINT_COLOR)
                                            , POINT_CHAR
                                            , ""
                                            , sz
                                            , obj.color1
                                            , obj.fontSize);
                
                break;
            case WIZARD::OBJECT_TYPE_COMPONENT:
            {
                WIZARD::_Node component = ui_wizard_share::inst()->getComponent(obj.component);
                int pSeq = 0;
                if(obj.id >= 0)
                    pSeq = obj.id;
                pObj = createNode(gridSizeWithSpanWithMargin, Vec2::ZERO, Vec2(1.f, 1.f), component, pSeq);
                Vec2 pos = gui::inst()->getPointVec2(obj.position.x
                                                     , obj.position.y
                                                     , ALIGNMENT_LEFT_BOTTOM
                                                     , layoutBG->getContentSize()
                                                     , node.gridSize
                                                     , Vec2::ZERO
                                                     , Vec2::ZERO
                                                     , node.innerMargin
                                                     , obj.span);
                pObj->setPosition(pos);
                layoutBG->addChild(pObj);
                break;
            }
            case WIZARD::OBJECT_TYPE_LAYER:
            {
                bool isBGColor = (obj.color1.isValidColor) ? true : false;
                pObj = gui::inst()->createLayout(gridSizeWithSpanWithMargin, obj.img, isBGColor, obj.color);
                gui::inst()->setAnchorPoint(pObj, ALIGNMENT_LEFT_TOP);
                auto pos = gui::inst()->getPointVec2(obj.position.x, obj.position.y
                                                     , ALIGNMENT_LEFT_TOP
                                                     , layoutBG->getContentSize()
                                                     , node.gridSize
                                                     , Vec2::ZERO
                                                     , Vec2::ZERO
                                                     , node.innerMargin
                                                     , obj.span);
                pObj->setPosition(pos);
                layoutBG->addChild(pObj);
                break;
            }
            default:
                break;
        }
		pObj->setOpacity(obj.opacity);
        pObj->setVisible(obj.visible);
		if(obj.id >= 0 && obj.type != WIZARD::OBJECT_TYPE_COMPONENT)
			mNodeMap[objId] = pObj;
	}
    
    //node link
    if(node.link != -1) {
        gui::inst()->addTextButtonAutoDimension(0
                                                , 0
                                                , "M"
                                                , layoutBG
                                                , CC_CALLBACK_1(ui_wizard::callback, this, node.id, node.link)
                                                , 0
                                                , ALIGNMENT_CENTER
                                                , Color3B::BLACK
                                                , Vec2(1, 1)
                                                , Vec2::ZERO
                                                , Vec2::ZERO
                                                , Vec2::ZERO
                                                , Vec2::ZERO)->setOpacity(0);
    }
    
    if(node.isScrollView) {
        sv->setVisible(node.visible);
        sv->addChild(layoutBG);
        return sv;
    } else {
        layoutBG->setVisible(node.visible);
        return layoutBG;
    }
    return NULL;
}

void ui_wizard::drawNode(WIZARD::_Node &node) {
    Node * p = createNode(Size(INVALID_VALUE, INVALID_VALUE), Vec2(INVALID_VALUE, INVALID_VALUE), mGrid, node, 0);
    if(p)
        this->addChild(p);
}

