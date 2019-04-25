//
// Created by Jung, DaeCheon on 25/04/2019.
//

#ifndef PROJ_ANDROID_UI_WIZARD_H
#define PROJ_ANDROID_UI_WIZARD_H

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

using namespace cocos2d;
using namespace std;
using namespace rapidjson;

interface ui_wizard_business {
	virtual const string get(int id) = 0;
};

class ui_wizard : public Scene {
public:
	
protected:
	bool loadFromJson(const string path, ui_wizard_business * pBusinessClass);

private:
	enum OBJECT_TYPE {
		OBJECT_TYPE_LABEL = 0,
		OBJECT_TYPE_BUTTON
	};
#define NULL_INT_VALUE -1
#define NULL_STRING_VALUE ""

	ui_wizard_business * mBusinessClass;

	struct _Object {
		int id;
		Vec2 position;
		OBJECT_TYPE type;
		int link;
		string img;
		Color3B bgColor, color;
		string text;
		float fontSize;

		bool load(rapidjson::Value &p);
		int getObjectType(const string type);
	};
	struct _Node {
		int id;
		Vec2 dimensionStart;
		Vec2 dimensionEnd;
		Size margin;
		Size gridSize;	
		string img;
		Color3B color;
		vector<_Object> mObjects;

		bool load(rapidjson::Value &p);
	};

	vector<_Node> mNodes;

	void drawNode(_Node &node);
};


#endif //PROJ_ANDROID_UI_WIZARD_H