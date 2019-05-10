//
// Created by Jung, DaeCheon on 25/04/2019.
//

#ifndef PROJ_ANDROID_UI_WIZARD_H
#define PROJ_ANDROID_UI_WIZARD_H

#include "library/PhysicsScene.h"
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
        OBJECT_TYPE_LABEL_SPRITE,
        
		OBJECT_TYPE_BUTTON,
        OBJECT_TYPE_BUTTON_SPRITE,
        OBJECT_TYPE_BUTTON_CIRCLE,
        OBJECT_TYPE_BUTTON_RECT_ROUND_SHADOW,
        
		OBJECT_TYPE_SPRITE,
		OBJECT_TYPE_SPRITE_BUTTON,
        OBJECT_TYPE_SPRITE_BUTTON_CIRCLE,
        
		OBJECT_TYPE_LOADINGBAR,
        
		OBJECT_TYPE_CIRCLE,
        
        OBJECT_TYPE_RECT,
        OBJECT_TYPE_RECT_ROUND,
        OBJECT_TYPE_RECT_ROUND_SHADOW,
	};

	struct _Object {
		int id;
		Vec2 position;
		ALIGNMENT alignment;
		OBJECT_TYPE type;
		int link;
		string img;
        string img_selected;
		Color3B color, color_second;
		GLubyte opacity, opacity_second;
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
        Size innerMargin;
		Size gridSize;
		string img;
		Color3B color, color_end;
        GLubyte opacity, opacity_end;
		bool isGradient;
        bool visible;
		vector<_Object> mObjects;

		bool load(rapidjson::Value &p);
	};

	struct _Background {
        int id;
		string img;
		Color4B bgColor, bgColor_end;
        Color4F tileColor;
		bool isGradient, hasTile;
        Vec2 tileNum;
        bool isDrawGrid;
        
		bool load(rapidjson::Value &p);
	};

	typedef vector<WIZARD::_Node> VEC_NODES;
    
    rapidjson::Document getJsonValue(const string& path);
};
/* ===============================================
	ui_wizard_share
 
 
 #ifndef __SCENES_H__
 #define __SCENES_H__
 
 #include "ui/ui_wizard.h"
 USING_NS_CC;
 
 class SceneMain : public ui_wizard
 {
 public:
 static Scene* createScene() { return SceneMain::create(); };
 virtual bool init();
 CREATE_FUNC(SceneMain);
 
 protected:
 virtual void callback(Ref* pSender, int from, int link);
 virtual const string getText(const string& defaultString, int id);
 };
 
 #endif // __SCENES_H__
 
================================================== */
class ui_wizard_share {
public:
	ui_wizard_share() {};
	~ui_wizard_share() {};
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
	void addNode(const string& id, WIZARD::_Node& node) {
		mSharedNodes[id].push_back(node);
	};
	void setBackground(const string& id, WIZARD::_Background& bg) {
		mSharedBackgounds[id] = bg;
	};
	
	WIZARD::VEC_NODES getNodes(const string& id) {
		return mSharedNodes[id];
	};

	WIZARD::_Background getBackgound(const string& id) {
		return mSharedBackgounds[id];
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
	map<string, WIZARD::_Background> mSharedBackgounds;
};

/* ===============================================
	ui_wizard
================================================== */
class ui_wizard : public PhysicsScene {	
protected:
	bool loadFromJson(const string& sceneName, const string& path);
	Node * getNodeById(int id);
	void pushScene(Scene * pScene) {
		Director::getInstance()->pushScene(pScene);
	};
	void replaceScene(Scene * pScene) {
		Director::getInstance()->replaceScene(pScene);
	};
	void popScene() {
		Director::getInstance()->popScene();
	};
	void closeScene() {
		Director::getInstance()->end();
	};
	virtual void callback(cocos2d::Ref* pSender, int from, int link) = 0;
	virtual const string getText(const string& defaultString, int id) = 0;	
private:	
#define NULL_INT_VALUE -1
#define NULL_STRING_VALUE ""
	map<int, Node*> mNodeMap;

	void drawBackground(WIZARD::_Background &bg);
	void drawNode(WIZARD::_Node &node, int seq);
    
    bool mIsDrawGrid;
    Size mGrid;
};

#endif //PROJ_ANDROID_UI_WIZARD_H
