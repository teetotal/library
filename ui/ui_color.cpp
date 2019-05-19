//
// Created by Jung, DaeCheon on 19/10/2018.
//

#include "ui_color.h"

ui_color * ui_color::hInst = NULL;

//--------------------------------------------------------
void COLOR_RGB::set(int r, int g, int b, int a) {
    this->R = r;
    this->G = g;
    this->B = b;
    this->A = a;
    
    this->isValidColor = true;
}

void COLOR_RGB::set(const COLOR_RGB& p) {
    this->R = p.R;
    this->G = p.G;
    this->B = p.B;
    this->A = p.A;
    
    this->isValidColor = true;
}

void COLOR_RGB::set(const Color3B& color, int a) {
    this->R = color.r;
    this->G = color.g;
    this->B = color.b;
    this->A = a;
    
    this->isValidColor = true;
}

COLOR_RGB COLOR_RGB::getColor(COLOR_RGB_TYPE type, int level) {
    COLOR_RGB color;
    
    switch(type) {
        case COLOR_RGB_TYPE_WARM:
        {
            color = getColorWarm(level);
            break;
        }
        case COLOR_RGB_TYPE_COOL:
        {
            color = getColorCool(level);
            break;
        }
        case COLOR_RGB_TYPE_DARK:
        {
            color = getColorDark(level);
            break;
        }
        case COLOR_RGB_TYPE_LIGHT:
        {
            color = getColorLight(level);
            break;
        }
        default:
            return COLOR_RGB(R, G, B, A);
    }
    
    return color;
}

Color3B COLOR_RGB::getColor3B(COLOR_RGB_TYPE type, int level) {
    COLOR_RGB color = getColor(type, level);
    return Color3B(color.R, color.G, color.B);
}

Color4B COLOR_RGB::getColor4B(COLOR_RGB_TYPE type, int level) {
    COLOR_RGB color = getColor(type, level);
    return Color4B(color.R, color.G, color.B, color.A);
}

Color4F COLOR_RGB::getColor4F(COLOR_RGB_TYPE type, int level){
    COLOR_RGB color = getColor(type, level);
    return Color4F(((float)color.R) / 255.f
                   , ((float)color.G) / 255.f
                   , ((float)color.B) / 255.f
                   , ((float)color.A) / 255.f);
}


COLOR_RGB COLOR_RGB::getColorWarm(int level) {
    COLOR_RGB color = COLOR_RGB(R, G, B, A);
    color.R = std::min(255, color.R + level);
    return color;
}

COLOR_RGB COLOR_RGB::getColorCool(int level) {
    COLOR_RGB color = COLOR_RGB(R, G, B, A);
    color.B = std::min(255, color.B + level);
    return color;
}

COLOR_RGB COLOR_RGB::getColorDark(int level) {
    COLOR_RGB color = COLOR_RGB(R, G, B, A);
    color.R = std::max(0, color.R - level);
    color.G = std::max(0, color.G - level);
    color.B = std::max(0, color.B - level);
    return color;
}

COLOR_RGB COLOR_RGB::getColorLight(int level) {
    COLOR_RGB color = COLOR_RGB(R, G, B, A);
    color.R = std::min(255, color.R + level);
    color.G = std::min(255, color.G + level);
    color.B = std::min(255, color.B + level);
    return color;
}

//--------------------------------------------------------
COLOR_RGB ui_color::getColor(const string& name) {
    if(hasColor(name))
        return mMap[name];
    
    return COLOR_RGB();
}
Color3B ui_color::getColor3B(const string& name){
    return getColor(name).getColor3B();
}

Color4B ui_color::getColor4B(const string& name) {
    return getColor(name).getColor4B();
}

Color4F ui_color::getColor4F(const string& name){
    return getColor(name).getColor4F();
}

bool ui_color::hasColor(const string& name) {
    if(mMap.find(name) == mMap.end()) {
        return false;
    }
    return true;
}
