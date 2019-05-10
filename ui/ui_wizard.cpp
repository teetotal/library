//
// Created by Jung, DaeCheon on 25/04/2019.
//

#include "ui_wizard.h"

ui_wizard_share * ui_wizard_share::hInstance = NULL;

bool WIZARD::_Object::load(rapidjson::Value & p)
{
    this->opacity = (GLubyte)0xFF;
    this->opacity_second = (GLubyte)0xFF;
    
	this->id = p["id"].GetInt();
	this->position.x = p["position"][rapidjson::SizeType(0)].GetFloat();
	this->position.y = p["position"][rapidjson::SizeType(1)].GetFloat();
    
	const string szAlignment = p["alignment"].GetString();
	if (szAlignment.compare("none") == 0) {
		this->alignment = ALIGNMENT_NONE;
	}
	else if (szAlignment.compare("center") == 0){
		this->alignment = ALIGNMENT_CENTER;
	}
    else if (szAlignment.compare("left") == 0){
        this->alignment = ALIGNMENT_LEFT;
    }
    else if (szAlignment.compare("right") == 0){
        this->alignment = ALIGNMENT_RIGHT;
    }
    
	this->type = (OBJECT_TYPE)getObjectType(p["type"].GetString());
	this->link = p["link"].IsNull() ? NULL_INT_VALUE : p["link"].GetInt();
	
    if (p["img"].IsNull()) {
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
    
    if (!p["color"].IsNull()) {
        if (p["color"].IsArray() && p["color"][rapidjson::SizeType(0)].IsArray()) {
            this->color = Color3B(
                                  p["color"][rapidjson::SizeType(0)][rapidjson::SizeType(0)].GetInt()
                                  , p["color"][rapidjson::SizeType(0)][rapidjson::SizeType(1)].GetInt()
                                  , p["color"][rapidjson::SizeType(0)][rapidjson::SizeType(2)].GetInt()
                                  );
            this->opacity = (p["color"][rapidjson::SizeType(0)].GetArray().Size() == 4) ?
            (GLubyte)p["color"][rapidjson::SizeType(0)][rapidjson::SizeType(3)].GetInt() : (GLubyte)0xFF;
            
            if (p["color"].GetArray().Size() == rapidjson::SizeType(2)) {
                this->color_second = Color3B(
                                          p["color"][rapidjson::SizeType(1)][rapidjson::SizeType(0)].GetInt()
                                          , p["color"][rapidjson::SizeType(1)][rapidjson::SizeType(1)].GetInt()
                                          , p["color"][rapidjson::SizeType(1)][rapidjson::SizeType(2)].GetInt()
                                          );
                this->opacity_second = (p["color"][rapidjson::SizeType(1)].GetArray().Size() == 4) ?
                (GLubyte)p["color"][rapidjson::SizeType(1)][rapidjson::SizeType(3)].GetInt() : (GLubyte)0xFF;
            }
        }
        else {
            if (p["color"].IsInt()) {
                this->opacity = (GLubyte)p["color"].GetInt();
            }
            else {
                this->color = Color3B(
                                      p["color"][rapidjson::SizeType(0)].GetInt()
                                      , p["color"][rapidjson::SizeType(1)].GetInt()
                                      , p["color"][rapidjson::SizeType(2)].GetInt()
                                      );
                
                this->opacity = (p["color"].GetArray().Size() == 4) ? (GLubyte)p["color"][rapidjson::SizeType(3)].GetInt() : (GLubyte)0xFF;
            }
        }
    }
    
	this->text = p["text"].IsNull() ? NULL_STRING_VALUE : p["text"].GetString();
	this->fontSize = p["fontSize"].GetFloat();

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
    else if (type.compare("rectangle_round") == 0)
        return OBJECT_TYPE_RECT_ROUND;
    else if (type.compare("rectangle_round_shadow") == 0)
        return OBJECT_TYPE_RECT_ROUND_SHADOW;
    
	return OBJECT_TYPE_LABEL;
}

bool WIZARD::_Node::load(rapidjson::Value & pValue)
{
	this->isGradient = false;
    this->visible = true;
    
	this->id = pValue["id"].GetInt();
    rapidjson::Value & p = (pValue.HasMember("include")) ? getJsonValue(pValue["include"]["path"].GetString())[pValue["include"]["key"].GetString()] : pValue;
    
    this->dimensionStart.x = p["dimension"][rapidjson::SizeType(0)].GetFloat();
	this->dimensionStart.y = p["dimension"][rapidjson::SizeType(1)].GetFloat();
	this->dimensionEnd.x = p["dimension"][rapidjson::SizeType(2)].GetFloat();
	this->dimensionEnd.y = p["dimension"][rapidjson::SizeType(3)].GetFloat();
	this->margin.width = p["margin"][rapidjson::SizeType(0)].GetFloat();
	this->margin.height = p["margin"][rapidjson::SizeType(1)].GetFloat();
    this->innerMargin.width = p["innerMargin"][rapidjson::SizeType(0)].GetFloat();
    this->innerMargin.height = p["innerMargin"][rapidjson::SizeType(1)].GetFloat();
	this->gridSize.width = p["gridSize"][rapidjson::SizeType(0)].GetFloat();
	this->gridSize.height = p["gridSize"][rapidjson::SizeType(1)].GetFloat();
	this->img = p["img"].IsNull() ? NULL_STRING_VALUE : p["img"].GetString();
	if (!p["color"].IsNull()) {
		if (p["color"].IsArray() && p["color"][rapidjson::SizeType(0)].IsArray()) {
			this->color = Color3B(
				p["color"][rapidjson::SizeType(0)][rapidjson::SizeType(0)].GetInt()
				, p["color"][rapidjson::SizeType(0)][rapidjson::SizeType(1)].GetInt()
				, p["color"][rapidjson::SizeType(0)][rapidjson::SizeType(2)].GetInt()
			);
			this->opacity = (p["color"][rapidjson::SizeType(0)].GetArray().Size() == 4) ? 
				(GLubyte)p["color"][rapidjson::SizeType(0)][rapidjson::SizeType(3)].GetInt() : (GLubyte)0xFF;
			
			if (p["color"].GetArray().Size() == rapidjson::SizeType(2)) {
				this->color_end = Color3B(
					p["color"][rapidjson::SizeType(1)][rapidjson::SizeType(0)].GetInt()
					, p["color"][rapidjson::SizeType(1)][rapidjson::SizeType(1)].GetInt()
					, p["color"][rapidjson::SizeType(1)][rapidjson::SizeType(2)].GetInt()
				);
				this->opacity_end = (p["color"][rapidjson::SizeType(1)].GetArray().Size() == 4) ?
					(GLubyte)p["color"][rapidjson::SizeType(1)][rapidjson::SizeType(3)].GetInt() : (GLubyte)0xFF;

				this->isGradient = true;
			}
		}
		else {
			if (p["color"].IsInt()) {
				this->opacity = (GLubyte)p["color"].GetInt();
			}
			else {
				this->color = Color3B(
					p["color"][rapidjson::SizeType(0)].GetInt()
					, p["color"][rapidjson::SizeType(1)].GetInt()
					, p["color"][rapidjson::SizeType(2)].GetInt()
				);

				this->opacity = (p["color"].GetArray().Size() == 4) ? (GLubyte)p["color"][rapidjson::SizeType(3)].GetInt() : (GLubyte)0xFF;
			}
		}
	}

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
    
    if(p.HasMember("visible")) {
        this->visible = p["visible"].GetBool();
    }
	
	return true;
}

bool WIZARD::_Background::load(rapidjson::Value & pValue)
{
    this->id = pValue["id"].GetInt();
    
    rapidjson::Value & p = (pValue.HasMember("include")) ? getJsonValue(pValue["include"]["path"].GetString())[pValue["include"]["key"].GetString()] : pValue;
    
	if (p["img"].IsNull())
		this->img = NULL_STRING_VALUE;
	else {
		this->img = p["img"].GetString();
		if(SpriteFrameCache::getInstance()->getSpriteFrameByName(this->img) == NULL)
			SpriteFrameCache::getInstance()->addSpriteFrame(Sprite::create(this->img)->getSpriteFrame(), this->img);
	}

	this->isGradient = false;
    this->hasTile = false;
    this->isDrawGrid = false;
    //bgColor
	if (!p["bgColor"].IsNull()) {
		if (p["bgColor"][rapidjson::SizeType(0)].IsArray()) {
			this->bgColor = Color4B(
				p["bgColor"][rapidjson::SizeType(0)][rapidjson::SizeType(0)].GetInt()
				, p["bgColor"][rapidjson::SizeType(0)][rapidjson::SizeType(1)].GetInt()
				, p["bgColor"][rapidjson::SizeType(0)][rapidjson::SizeType(2)].GetInt()
				, p["bgColor"][rapidjson::SizeType(0)][rapidjson::SizeType(3)].GetInt()
			);

			if (p["bgColor"].GetArray().Size() == rapidjson::SizeType(2)) {
				this->bgColor_end = Color4B(
					p["bgColor"][rapidjson::SizeType(1)][rapidjson::SizeType(0)].GetInt()
					, p["bgColor"][rapidjson::SizeType(1)][rapidjson::SizeType(1)].GetInt()
					, p["bgColor"][rapidjson::SizeType(1)][rapidjson::SizeType(2)].GetInt()
					, p["bgColor"][rapidjson::SizeType(1)][rapidjson::SizeType(3)].GetInt()
				);
				this->isGradient = true;
			}
		}
		else {
			this->bgColor = Color4B(
				p["bgColor"][rapidjson::SizeType(0)].GetInt()
				, p["bgColor"][rapidjson::SizeType(1)].GetInt()
				, p["bgColor"][rapidjson::SizeType(2)].GetInt()
				, p["bgColor"][rapidjson::SizeType(3)].GetInt()
			);
		}
	}
    //tile
    if (!p["tile"].IsNull()) {
        this->tileColor = Color4F(Color4B(p["tile"]["color"][rapidjson::SizeType(0)].GetInt()
                                          , p["tile"]["color"][rapidjson::SizeType(1)].GetInt()
                                          , p["tile"]["color"][rapidjson::SizeType(2)].GetInt()
                                          , p["tile"]["color"][rapidjson::SizeType(3)].GetInt()));
        this->tileNum = Vec2(
                             p["tile"]["num"][rapidjson::SizeType(0)].GetInt()
                             , p["tile"]["num"][rapidjson::SizeType(1)].GetInt()
        );
        this->hasTile = true;
    }
    
    //isDrawGrid
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


bool ui_wizard::loadFromJson(const string& sceneName, const string& path)
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
    
    rapidjson::Document d = WIZARD::getJsonValue(path);
    /*
    // parse from json file
	string fullpath = FileUtils::getInstance()->fullPathForFilename(path);
	string sz = FileUtils::getInstance()->getStringFromFile(fullpath);

	rapidjson::Document d;	
	d.Parse(sz.c_str());
	if (d.HasParseError()) {		
		CCLOG("loadFromJson Failure. ErrorCode: %d, ErrorOffset: %zu", d.GetParseError(), d.GetErrorOffset());		
		return false;
	}
    */
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
    mIsDrawGrid = bg.isDrawGrid;
	auto p = (bg.isGradient) ? LayerGradient::create(bg.bgColor, bg.bgColor_end) : LayerColor::create(bg.bgColor);
	p->setContentSize(Director::getInstance()->getVisibleSize());
	p->setAnchorPoint(Vec2(0, 0));
	p->setPosition(Director::getInstance()->getVisibleOrigin());
	this->addChild(p);

	if (bg.img.compare(NULL_STRING_VALUE) != 0) {
		gui::inst()->addBG(bg.img, p, true);
	}
    
    mNodeMap[bg.id] = p;
    
    if(bg.hasTile) {
        gui::inst()->drawDiamondTile(p, bg.tileNum, bg.tileColor);
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
    Size sizeColored = Size(size.width - (node.margin.width * 2.f), size.height - (node.margin.height * 2.f));
    Size sizePerGrid = Size((sizeColored.width / node.gridSize.width) - (node.innerMargin.width * 2.f)
                            , (sizeColored.height / node.gridSize.height) - (node.innerMargin.height * 2.f) 
                            );
    float min = (sizePerGrid.width > sizePerGrid.height) ? sizePerGrid.height : sizePerGrid.width;
    
	//background colored layer
    Node * layoutBG;
    if (node.img.length() > 0 || !node.isGradient) {
        layoutBG = gui::inst()->createLayout(sizeColored, node.img, true, node.color);
    }
    else {
        Color4B gradientStart = Color4B(node.color);
        gradientStart.a = node.opacity;

        Color4B gradientEnd = Color4B(node.color_end);
        gradientEnd.a = node.opacity_end;

        layoutBG = LayerGradient::create(gradientStart, gradientEnd);
        layoutBG->setContentSize(sizeColored);
    }
    layoutBG->setPosition(Vec2(start.x + node.margin.width, end.y + node.margin.height));
    layoutBG->setOpacity(node.opacity);
    
    if(node.id >= 0)
        mNodeMap[node.id] = layoutBG;
    
	//draw grid line
    if(mIsDrawGrid) {
        gui::inst()->drawGrid(layoutBG, layoutBG->getContentSize(), node.gridSize, Size::ZERO, Size::ZERO, (seq % 2 == 1) ? Color4F::MAGENTA : Color4F::GREEN);
    }
    
	for (size_t n = 0; n < node.mObjects.size(); n++) {
		WIZARD::_Object obj = node.mObjects[n];
		string sz = getText(obj.text, obj.id);
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
                
                Menu * pMenu;
                pObj = gui::inst()->addTextButtonRaw(pMenu
                                                     , 0
                                                     , 0
                                                     , sz
                                                     , layoutBG
                                                     , CC_CALLBACK_1(ui_wizard::callback, this, obj.id, obj.link)
                                                     , obj.fontSize
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
		
		if(obj.id > 0)
			mNodeMap[obj.id] = pObj;
	}
    layoutBG->setVisible(node.visible);
	this->addChild(layoutBG);
}

