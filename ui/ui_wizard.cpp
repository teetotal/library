//
// Created by Jung, DaeCheon on 25/04/2019.
//

#include "ui_wizard.h"

ui_wizard_share * ui_wizard_share::hInstance = NULL;

bool WIZARD::_Object::load(rapidjson::Value & p)
{
	this->id = p["id"].GetInt();
	this->position.x = p["position"][rapidjson::SizeType(0)].GetFloat();
	this->position.y = p["position"][rapidjson::SizeType(1)].GetFloat();
	const string szAlignment = p["alignment"].GetString();
	if (szAlignment.compare("none") == 0) {
		this->alignment = ALIGNMENT_NONE;
	}
	else {
		this->alignment = ALIGNMENT_CENTER;
	}
	this->type = (OBJECT_TYPE)getObjectType(p["type"].GetString());
	this->link = p["link"].IsNull() ? NULL_INT_VALUE : p["link"].GetInt();
	
	if (p["img"].IsNull())
		this->img = NULL_STRING_VALUE;
	else {		
		this->img = p["img"].GetString();
		if (SpriteFrameCache::getInstance()->getSpriteFrameByName(this->img) == NULL)
			SpriteFrameCache::getInstance()->addSpriteFrame(Sprite::create(this->img)->getSpriteFrame(), this->img);
		//SpriteFrameCache::getInstance()->removeSpriteFrameByName("btn_bg");	
	}
	if (!p["bgColor"].IsNull()) {
		this->bgColor = Color3B(
			p["bgColor"][rapidjson::SizeType(0)].GetInt()
			, p["bgColor"][rapidjson::SizeType(1)].GetInt()
			, p["bgColor"][rapidjson::SizeType(2)].GetInt()
		);
	}	
	if (!p["color"].IsNull()) {
		this->color = Color3B(
			p["color"][rapidjson::SizeType(0)].GetInt()
			, p["color"][rapidjson::SizeType(1)].GetInt()
			, p["color"][rapidjson::SizeType(2)].GetInt()
		);
	}
	this->text = p["text"].IsNull() ? NULL_STRING_VALUE : p["text"].GetString();
	this->fontSize = p["fontSize"].GetFloat();

	return true;
}

int WIZARD::_Object::getObjectType(const string type)
{
	if (type.compare("button") == 0)
		return OBJECT_TYPE_BUTTON;
	else if (type.compare("sprite") == 0)
		return OBJECT_TYPE_SPRITE;
	else if (type.compare("sprite_button") == 0)
		return OBJECT_TYPE_SPRITE_BUTTON;

	return OBJECT_TYPE_LABEL;
}

bool WIZARD::_Node::load(rapidjson::Value & p)
{
	this->id = p["id"].GetInt();
	this->dimensionStart.x = p["dimension"][rapidjson::SizeType(0)].GetFloat();
	this->dimensionStart.y = p["dimension"][rapidjson::SizeType(1)].GetFloat();
	this->dimensionEnd.x = p["dimension"][rapidjson::SizeType(2)].GetFloat();
	this->dimensionEnd.y = p["dimension"][rapidjson::SizeType(3)].GetFloat();
	this->margin.width = p["margin"][rapidjson::SizeType(0)].GetFloat();
	this->margin.height = p["margin"][rapidjson::SizeType(1)].GetFloat();
	this->gridSize.width = p["gridSize"][rapidjson::SizeType(0)].GetFloat();
	this->gridSize.height = p["gridSize"][rapidjson::SizeType(1)].GetFloat();
	this->img = p["img"].IsNull() ? NULL_STRING_VALUE : p["img"].GetString();
	if (!p["color"].IsNull()) {
		this->color = Color3B(
			p["color"][rapidjson::SizeType(0)].GetInt()
			, p["color"][rapidjson::SizeType(1)].GetInt()
			, p["color"][rapidjson::SizeType(2)].GetInt()
		);
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
	
	return true;
}

bool WIZARD::_Background::load(rapidjson::Value & p)
{	
	if (p["img"].IsNull())
		this->img = NULL_STRING_VALUE;
	else {
		this->img = p["img"].GetString();
		if(SpriteFrameCache::getInstance()->getSpriteFrameByName(this->img) == NULL)
			SpriteFrameCache::getInstance()->addSpriteFrame(Sprite::create(this->img)->getSpriteFrame(), this->img);
	}

	if (!p["bgColor"].IsNull()) {
		this->bgColor = Color4B(
			p["bgColor"][rapidjson::SizeType(0)].GetInt()
			, p["bgColor"][rapidjson::SizeType(1)].GetInt()
			, p["bgColor"][rapidjson::SizeType(2)].GetInt()
			, p["bgColor"][rapidjson::SizeType(3)].GetInt()
		);
	}
	return true;
}

bool ui_wizard::loadFromJson(const string& sceneName, const string& path)
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
	if (ui_wizard_share::inst()->hasNode(sceneName)) {
        WIZARD::_Background bg = ui_wizard_share::inst()->getBackgound(sceneName);
		this->drawBackground(bg);

		WIZARD::VEC_NODES nodes = ui_wizard_share::inst()->getNodes(sceneName);
		for (size_t n = 0; n < nodes.size(); n++) {
			WIZARD::_Node p = nodes[n];
			drawNode(p);
		}
		return true;
	}

	string fullpath = FileUtils::getInstance()->fullPathForFilename(path);
	string sz = FileUtils::getInstance()->getStringFromFile(fullpath);

	rapidjson::Document d;	
	d.Parse(sz.c_str());
	if (d.HasParseError()) {		
		CCLOG("loadFromJson Failure. ErrorCode: %d, ErrorOffset: %zu", d.GetParseError(), d.GetErrorOffset());		
		return false;
	}

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
		drawNode(p);
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
	auto p = LayerColor::create(bg.bgColor);
	p->setContentSize(Director::getInstance()->getVisibleSize());
	p->setAnchorPoint(Vec2(0, 0));
	p->setPosition(Director::getInstance()->getVisibleOrigin());
	this->addChild(p);

	if (bg.img.compare(NULL_STRING_VALUE) != 0) {
		gui::inst()->addBG(bg.img, this);
	}
}
void ui_wizard::drawNode(WIZARD::_Node &node)
{
	Vec2 start= gui::inst()->getPointVec2(node.dimensionStart.x, node.dimensionStart.y, ALIGNMENT_NONE);
	Vec2 end = gui::inst()->getPointVec2(node.dimensionEnd.x, node.dimensionEnd.y, ALIGNMENT_NONE);
	Size size = Size(end.x - start.x, start.y - end.y);
	Size sizePerGrid = Size((size.width / node.gridSize.width) - node.margin.width, (size.height / node.gridSize.height) - node.margin.height);
	
	auto layout = gui::inst()->createLayout(size, node.img, true, node.color);
	//layout->setTag(node.id);
	layout->setPosition(Vec2(start.x, end.y));
	mNodeMap[node.id] = layout;

	for (size_t n = 0; n < node.mObjects.size(); n++) {
		WIZARD::_Object obj = node.mObjects[n];
		string sz = getText(obj.text, obj.id);

		Node * pObj;
		switch(obj.type) {
		case WIZARD::OBJECT_TYPE_LABEL:
			pObj = gui::inst()->addLabelAutoDimension(obj.position.x, obj.position.y
				, sz
				, layout
				, obj.fontSize
				, obj.alignment
				, obj.color
				, node.gridSize
				, Size::ZERO
				, node.margin
				, obj.img
			);			
			break;

		case WIZARD::OBJECT_TYPE_BUTTON:
			pObj = gui::inst()->addTextButtonAutoDimension(obj.position.x, obj.position.y
				, sz
				, layout
				, CC_CALLBACK_1(ui_wizard::callback, this, obj.id, obj.link)
				, obj.fontSize
				, obj.alignment
				, obj.color
				, node.gridSize
				, Size::ZERO
				, node.margin
				, obj.img);
			break;
		case WIZARD::OBJECT_TYPE_SPRITE:			
			pObj = gui::inst()->addSpriteAutoDimension(obj.position.x, obj.position.y, obj.img, layout, obj.alignment, node.gridSize, Size::ZERO, node.margin);
			if (sizePerGrid.width > sizePerGrid.height) {
				gui::inst()->setScaleByHeight(pObj, sizePerGrid.height);				
			}
			else {
				gui::inst()->setScaleByHeight(pObj, sizePerGrid.width);
			} 
			break;
		case WIZARD::OBJECT_TYPE_SPRITE_BUTTON:
			pObj = gui::inst()->addSpriteButton(obj.position.x
				, obj.position.y
				, obj.img
				, obj.img
				,layout
				, CC_CALLBACK_1(ui_wizard::callback, this, obj.id, obj.link)
				, obj.alignment
				, layout->getContentSize()
				, node.gridSize
				, Size::ZERO
				, node.margin);

			if (sizePerGrid.width > sizePerGrid.height) {
				gui::inst()->setScaleByHeight(pObj, sizePerGrid.height);
			}
			else {
				gui::inst()->setScaleByHeight(pObj, sizePerGrid.width);
			}
			break;
		default:
			break;
		}
		//pObj->setTag(obj.id);
		mNodeMap[obj.id] = pObj;
	}
	
	this->addChild(layout);
}

