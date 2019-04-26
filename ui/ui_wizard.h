//
// Created by Jung, DaeCheon on 25/04/2019.
//

#ifndef PROJ_ANDROID_UI_WIZARD_H
#define PROJ_ANDROID_UI_WIZARD_H

#include "cocos2d.h"
#include "ui/ui.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

using namespace cocos2d;
using namespace std;
using namespace rapidjson;

namespace WIZARD {
	enum OBJECT_TYPE {
		OBJECT_TYPE_LABEL = 0,
		OBJECT_TYPE_BUTTON
	};

	struct _Object {
		int id;
		Vec2 position;
		ALIGNMENT alignment;
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

	typedef vector<WIZARD::_Node> VEC_NODES;
};

interface ui_wizard_business {
public:
	virtual void setCallerScene(Scene * p) = 0;
	virtual const string getText(const string& defaultString, int id) = 0;
	virtual void call(int link) = 0;
};

class ui_wizard_share {
public:
	ui_wizard_share() {

	};
	~ui_wizard_share() {

	};
	static ui_wizard_share * inst() {
		if (hInstance == NULL) {
			hInstance = new ui_wizard_share;
		}
		return hInstance;
	};
	void finalize() {
		mSharedNodes.clear();
		delete hInstance;
	};
	void addNode(const string id, WIZARD::_Node& node) {
		mSharedNodes[id].push_back(node);
	};
	
	WIZARD::VEC_NODES getNodes(const string& id) {
		return mSharedNodes[id];
	};

	bool hasNode(const string& id) {
		if (mSharedNodes.find(id) == mSharedNodes.end()) {
			return false;
		}
		return true;
	};
private:
	static ui_wizard_share * hInstance;
	map<string, WIZARD::VEC_NODES> mSharedNodes;
};

class ui_wizard : public Scene {
public:
	
protected:
	bool loadFromJson(const string& sceneName, const string& path, ui_wizard_business * pBusinessClass);
	void callback(cocos2d::Ref* pSender, int from, int link);

private:
	
#define NULL_INT_VALUE -1
#define NULL_STRING_VALUE ""

	ui_wizard_business * mBusinessClass;
	void drawNode(WIZARD::_Node &node);
};


#endif //PROJ_ANDROID_UI_WIZARD_H