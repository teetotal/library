//
// Created by Jung, DaeCheon on 19/10/2018.
//

#include "ui_color.h"

ui_color * ui_color::hInst = NULL;

ui_color::COLOR_RGB ui_color::getColor(const string& name) {
    if(hasColor(name))
        return mMap[name];
    
    return COLOR_RGB();
}

Color3B ui_color::getColor3B(const string& name){
    COLOR_RGB color = getColor(name);
    return Color3B(color.R, color.G, color.B);
}

Color4B ui_color::getColor4B(const string& name) {
    COLOR_RGB color = getColor(name);
    return Color4B(color.R, color.G, color.B, color.A);
}

Color4F ui_color::getColor4F(const string& name){
    COLOR_RGB color = getColor(name);
    return Color4F(((float)color.R) / 255.f
                   , ((float)color.G) / 255.f
                   , ((float)color.B) / 255.f
                   , ((float)color.A) / 255.f);
}

bool ui_color::hasColor(const string& name) {
    if(mMap.find(name) == mMap.end()) {
        return false;
    }
    return true;
}
