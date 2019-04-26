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
	if (type.compare("label") == 0)
		return OBJECT_TYPE_LABEL;

	return OBJECT_TYPE_BUTTON;
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

	const rapidjson::Value& objects = p["objects"];
	for (rapidjson::SizeType i = 0; i < objects.Size(); i++)
	{
		_Object object;
		if (!object.load(p["objects"][rapidjson::SizeType(i)]))
			return false;

		this->mObjects.push_back(object);
	}
	
	return true;
}

bool WIZARD::_Background::load(rapidjson::Value & p)
{	
	if (p["img"].IsNull())
		this->img = NULL_STRING_VALUE;
	else {
		this->img = p["img"].GetString();
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

bool ui_wizard::loadFromJson(const string& sceneName, const string& path, ui_wizard_business * pBusinessClass)
{
	mBusinessClass = pBusinessClass;
	if (mBusinessClass)
		mBusinessClass->setCallerScene(this);

	if (ui_wizard_share::inst()->hasNode(sceneName)) {
		drawBackground(ui_wizard_share::inst()->getBackgound(sceneName));

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
		CCLOG("loadFromJson Failure. ErrorCode: %d, ErrorOffset: %d", d.GetParseError(), d.GetErrorOffset());		
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

void ui_wizard::callback(cocos2d::Ref * pSender, int from, int link)
{
	CCLOG("Callback From %d, To %d", from, link);
	if (mBusinessClass)
		mBusinessClass->call(link);
}
void ui_wizard::drawBackground(WIZARD::_Background & bg)
{
	auto p = LayerColor::create(bg.bgColor);
	p->setContentSize(Director::getInstance()->getVisibleSize());
	p->setAnchorPoint(Vec2(0, 0));
	p->setPosition(Director::getInstance()->getVisibleOrigin());
	this->addChild(p);

	if (bg.img.compare(NULL_STRING_VALUE) != 0) {
		auto p = Sprite::createWithSpriteFrameName(bg.img);
		p->setContentSize(Director::getInstance()->getVisibleSize());
		p->setAnchorPoint(Vec2(0, 0));		
		p->setPosition(Director::getInstance()->getVisibleOrigin());
		this->addChild(p);
	}
}
void ui_wizard::drawNode(WIZARD::_Node &node)
{
	Vec2 start= gui::inst()->getPointVec2(node.dimensionStart.x, node.dimensionStart.y, ALIGNMENT_NONE);
	Vec2 end = gui::inst()->getPointVec2(node.dimensionEnd.x, node.dimensionEnd.y, ALIGNMENT_NONE);
	Size size = Size(end.x - start.x, start.y - end.y);
	auto layout = gui::inst()->createLayout(size, node.img, true, node.color);
	layout->setTag(node.id);
	layout->setPosition(Vec2(start.x, end.y));

	for (size_t n = 0; n < node.mObjects.size(); n++) {
		WIZARD::_Object obj = node.mObjects[n];
		string sz = obj.text;

		if(mBusinessClass)
			sz = mBusinessClass->getText(sz, obj.id);

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

		default:
			break;
		}
		pObj->setTag(obj.id);
	}
	
	this->addChild(layout);
}

