//
// Created by Jung, DaeCheon on 25/04/2019.
//

#ifndef _UI_WIZARD_H
#define _UI_WIZARD_H

#include "library/PhysicsScene.h"
#include "ui/ui.h"
#include "ui/ui_color.h"
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
        OBJECT_TYPE_BUTTON_RECT_CIRCLE_SHADOW_1, //no outline
        OBJECT_TYPE_BUTTON_RECT_CIRCLE_SHADOW_2, // white outline
        OBJECT_TYPE_BUTTON_RECT_ROUND_SHADOW,
        
		OBJECT_TYPE_SPRITE,
		OBJECT_TYPE_SPRITE_BUTTON,
        OBJECT_TYPE_SPRITE_BUTTON_CIRCLE,
        
		OBJECT_TYPE_LOADINGBAR,
        OBJECT_TYPE_PROGRESSBAR_FLAT,
        OBJECT_TYPE_PROGRESSBAR,
        
        OBJECT_TYPE_CHECKBOX,
        
        OBJECT_TYPE_ROULETTE,
        
		OBJECT_TYPE_CIRCLE,
        
        OBJECT_TYPE_RECT,
        OBJECT_TYPE_RECT_LINE,
        OBJECT_TYPE_RECT_ROUND,
        OBJECT_TYPE_RECT_ROUND_SHADOW,
        OBJECT_TYPE_LINE,
        
        OBJECT_TYPE_ICON_CIRCLE,
        OBJECT_TYPE_ICON_HEART,
        OBJECT_TYPE_ICON_POINT,
        
        OBJECT_TYPE_COMPONENT,
        
        OBJECT_TYPE_LAYER,
	};
    
    struct _base {
        void getColorFromJson(rapidjson::Value &p, COLOR_RGB * color);
        void getColorFromJson(rapidjson::Value &p, COLOR_RGB * color1, COLOR_RGB * color2);
    };

    struct _Object : _base {
		int id;
        string component;
		Vec2 position;
        Vec2 span;
		ALIGNMENT alignment;
		OBJECT_TYPE type;
		int link;
		string img;
        string img_selected;
        
        Color3B color, color_second;
        GLubyte opacity, opacity_second;
        
        COLOR_RGB color1, color2;
        COLOR_RGB bgColor, bgColor_second;
        
		string text;
		float fontSize;
        
        bool visible;

		bool load(rapidjson::Value &p);
		int getObjectType(const string type);
	};
    
    struct _Node : _base {
		int id;
        string component;
        int link;
		Vec2 dimensionStart, dimensionEnd;
		Vec2 dimensionInnerStart, dimensionInnerEnd;
		Vec2 margin;
        Vec2 innerMargin;
		Vec2 gridSize;
		string img;
		COLOR_RGB color, color_second, colorTile;
        Vec2 tileNum;
        bool visible;
        bool isScrollView;
		vector<_Object> mObjects;

        bool load(rapidjson::Value &p);
	};

    struct _Background : _base {
        int id;
		string img;
		COLOR_RGB bgColor, bgColor_second, tileColor;
        Vec2 tileNum;
        bool isDrawGrid;
        Vec2 grid;
        
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
            hInstance->_DRAWLINE_COLOR [0] = Color4F::RED;
            hInstance->_DRAWLINE_COLOR [1] = Color4F::MAGENTA;
            hInstance->_DRAWLINE_COLOR [2] = Color4F::BLUE;
            hInstance->_DRAWLINE_COLOR [3] = Color4F::ORANGE;
            hInstance->_DRAWLINE_COLOR [4] = Color4F::BLACK;
            hInstance->_DRAWLINE_COLOR [5] = Color4F::GREEN;
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
    void setComponent(const string& id, WIZARD::_Node& component) {
        if(mSharedComponent.find(id) == mSharedComponent.end())
            mSharedComponent[id] = component;
    };
	
	WIZARD::VEC_NODES getNodes(const string& id) {
		return mSharedNodes[id];
	};

	WIZARD::_Background getBackgound(const string& id) {
		return mSharedBackgounds[id];
	};
    
    WIZARD::_Node getComponent(const string& id) {
        return mSharedComponent[id];
    }

	bool hasNode(const string& id) {
		if (mSharedNodes.find(id) == mSharedNodes.end()) {
			return false;
		}
		return true;
	};
    
    ui_color * getPalette() {
        return &mPalette;
    }
    bool insertPalettePath(const string& path) {
        if(!hasPalettePath(path)) {
            mPalettePaths.insert(path);
            return true;
        }
        return false;
    }
    
    bool hasPalettePath(const string& path) {
        return  mPalettePaths.find(path) != mPalettePaths.end();
    }
    
    bool loadPaletteFromJson(const string& pathPalette);
    bool loadComponentFromJson(const string& path);
    
    Color4F _DRAWLINE_COLOR[6];
private:
	static ui_wizard_share * hInstance;
	map<string, WIZARD::VEC_NODES> mSharedNodes;
	map<string, WIZARD::_Background> mSharedBackgounds;
    map<string, WIZARD::_Node> mSharedComponent;
    ui_color mPalette;
    set<string> mPalettePaths;
    
};

/* ===============================================
	ui_wizard
================================================== */
class ui_wizard : public PhysicsScene {	
protected:
	bool loadFromJson(const string& sceneName, const string& path);
    
	Node * getNodeById(int id);
    Node ** getNodePointerById(int id) {
        if (mNodeMap.find(id) == mNodeMap.end())
            return NULL;
        return &mNodeMap[id];
    };
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
    void callback2(int from, int link) {
        return callback(this, from, link);
    }
	virtual const string getText(const string& defaultString, int id) = 0;
    virtual const float getProgressValue(int id) = 0;
    
    virtual void cleanup() override {
        mNodeMap.clear();
        Node::cleanup();
    };
    
    Node * mScreen;
    
private:	
#define NULL_INT_VALUE -1
#define NULL_STRING_VALUE ""
	map<int, Node*> mNodeMap;

	void drawBackground(WIZARD::_Background &bg);
	void drawNode(WIZARD::_Node &node);
    Node * createNode(const Size& Dimension, const Vec2& Origin, const Vec2& Grid, WIZARD::_Node &node, int seq);
    
    bool mIsDrawGrid;
    Vec2 mGrid;
};

#endif //_UI_WIZARD_H
