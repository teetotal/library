//
// Created by Jung, DaeCheon on 25/04/2019.
//

#include "ui_wizard.h"
#include "ui/ui.h"
bool ui_wizard::_Object::load(rapidjson::Value & p)
{
	this->id = p["id"].GetInt();
	this->position.x = p["position"][rapidjson::SizeType(0)].GetFloat();
	this->position.y = p["position"][rapidjson::SizeType(1)].GetFloat();
	this->type = (OBJECT_TYPE)getObjectType(p["type"].GetString());
	this->link = p["link"].IsNull() ? NULL_INT_VALUE : p["link"].GetInt();
	this->img = p["img"].IsNull() ? NULL_STRING_VALUE : p["img"].GetString();
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

int ui_wizard::_Object::getObjectType(const string type)
{
	if (type.compare("label") == 0)
		return OBJECT_TYPE_LABEL;

	return OBJECT_TYPE_BUTTON;
}

bool ui_wizard::_Node::load(rapidjson::Value & p)
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

bool ui_wizard::loadFromJson(const string path, ui_wizard_business * pBusinessClass)
{
	gui::inst()->init();

	string fullpath = FileUtils::getInstance()->fullPathForFilename(path);
	string sz = FileUtils::getInstance()->getStringFromFile(fullpath);

	rapidjson::Document d;	
	d.Parse(sz.c_str());
	if (d.HasParseError()) {		
		CCLOG("loadFromJson Failure. ErrorCode: %d, ErrorOffset: %d", d.GetParseError(), d.GetErrorOffset());		
		return false;
	}	

	const rapidjson::Value& nodes = d["nodes"];
	for (rapidjson::SizeType i = 0; i < nodes.Size(); i++)
	{	
		_Node p;
		if (!p.load(d["nodes"][rapidjson::SizeType(i)]))
			return false;

		mNodes.push_back(p);
		drawNode(p);
	}

	return true;
}

void ui_wizard::drawNode(_Node &node) 
{
	Vec2 start= gui::inst()->getPointVec2(node.dimensionStart.x, node.dimensionStart.y, ALIGNMENT_NONE);
	Vec2 end = gui::inst()->getPointVec2(node.dimensionEnd.x, node.dimensionEnd.y, ALIGNMENT_NONE);
	Size size = Size(end.x - start.x, start.y - end.y);
	auto layout = gui::inst()->createLayout(size, node.img, true, node.color);
	layout->setTag(node.id);
	layout->setPosition(Vec2(start.x, end.y));

	for (int n = 0; n < node.mObjects.size(); n++) {
		_Object obj = node.mObjects[n];
		if (obj.type == OBJECT_TYPE_LABEL) {
			auto label = gui::inst()->addLabelAutoDimension(obj.position.x, obj.position.y, obj.text, layout, obj.fontSize, ALIGNMENT_CENTER, obj.color, node.gridSize, Size::ZERO, node.margin, obj.img);
			label->setTag(obj.id);
		}
	}
	
	this->addChild(layout);
}
