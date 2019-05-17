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

void COLOR_RGB::set(COLOR_RGB& p) {
    this->R = p.R;
    this->G = p.G;
    this->B = p.B;
    this->A = p.A;
    
    this->isValidColor = true;
}

Color3B COLOR_RGB::getColor3B(){
    return Color3B(R, G, B);
}

Color4B COLOR_RGB::getColor4B() {
   return Color4B(R, G, B, A);
}

Color4F COLOR_RGB::getColor4F(){
    return Color4F(((float)R) / 255.f
                   , ((float)G) / 255.f
                   , ((float)B) / 255.f
                   , ((float)A) / 255.f);
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
