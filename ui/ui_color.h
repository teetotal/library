//
// Created by Jung, DaeCheon on 19/10/2018.
//

#ifndef _UI_COLOR_H
#define _UI_COLOR_H

#include "ui.h"
enum COLOR_RGB_TYPE {
    COLOR_RGB_TYPE_NORMAL = 0,
    COLOR_RGB_TYPE_WARM,
    COLOR_RGB_TYPE_COOL,
    COLOR_RGB_TYPE_DARK,
    COLOR_RGB_TYPE_LIGHT
};
struct COLOR_RGB{
    int R;
    int G;
    int B;
    int A;
    bool isValidColor;
    
    COLOR_RGB() : R(-1) , G(-1), B(-1), A(255), isValidColor(false) { };
    COLOR_RGB(int r, int g, int b, int a) : R(r) , G(g), B(b), A(a), isValidColor(true) { };
    void set(int r, int g, int b, int a);
    void set(COLOR_RGB& p);
    void set(const Color3B & color, int a = 255);
    
    COLOR_RGB getColor(COLOR_RGB_TYPE type = COLOR_RGB_TYPE_NORMAL, int level = 30);
    Color3B getColor3B(COLOR_RGB_TYPE type = COLOR_RGB_TYPE_NORMAL, int level = 30);
    Color4F getColor4F(COLOR_RGB_TYPE type = COLOR_RGB_TYPE_NORMAL, int level = 30);
    Color4B getColor4B(COLOR_RGB_TYPE type = COLOR_RGB_TYPE_NORMAL, int level = 30);
    
    COLOR_RGB getColorWarm(int level = 30);
    COLOR_RGB getColorCool(int level = 30);
    COLOR_RGB getColorDark(int level = 50);
    COLOR_RGB getColorLight(int level = 50);
    
    GLubyte getA() {
        return (GLubyte)this->A;
    }
};

class ui_color {
public:
    ui_color() {
    };
    virtual ~ui_color(){
    };
    
    static ui_color * inst(){
        if(hInst == NULL){
            hInst = new ui_color();
        }
        
        return hInst;
    };
    
    void set(const string& name, int r, int g, int b, int a) {
        if(!hasColor(name)) mMap[name] = COLOR_RGB(r, g, b, a);
    };
    void set(const string& name, COLOR_RGB& color) {
        if(!hasColor(name)) {
            mMap[name] = COLOR_RGB(color);
        }
    };
    
    COLOR_RGB getColor(const string& name);

    Color3B getColor3B(const string& name);
    Color4F getColor4F(const string& name);
    Color4B getColor4B(const string& name);
    
    typedef map<string, COLOR_RGB> COLOR_MAP;
    COLOR_MAP mMap;
    
private:
    static ui_color * hInst;
    bool hasColor(const string& name);
};


#endif //_UI_COLOR_H
