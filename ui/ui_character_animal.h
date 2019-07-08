//
//  ui_character_animal.h
//
//  Created by Jung, DaeCheon on 27/06/2019.
//

#ifndef ui_character_animal_h
#define ui_character_animal_h

#include "ui.h"
#include "ui_color.h"

class ui_character_animal : public Layout
{
public:
    static ui_character_animal * create() {
        ui_character_animal * ret = new (std::nothrow) ui_character_animal;
        if (ret)
        {
            ret->autorelease();
        } else {
            CC_SAFE_DELETE(ret);
        }
        
        return ret;
    };
    void addRectangle(Size size, Color3B colorBG, Color4F colorSkin, Color4F colorFeatures, Color4F colorPoint);
    void addCircle(Size size, Color3B colorBG, Color4F colorSkin, Color4F colorFeatures, Color4F colorPoint);

private:
    enum ID_LAYOUT {
        ID_LAYOUT_EARS = 0,
        ID_LAYOUT_FACE,
        ID_LAYOUT_EYEBROW,
        ID_LAYOUT_EYES,
        ID_LAYOUT_MOUTH,
        ID_LAYOUT_NOSE,
        ID_LAYOUT_POINT,
        ID_LAYOUT_MAX
    };
    
    enum TYPE {
        TYPE_RECTANGLE,
    };
    Layout * mLayout[ID_LAYOUT_MAX];
    Color4F mColorSkin, mColorFeatures, mColorPoint;
    TYPE mType;
    
    #define GRID Vec2(4,4)
    #define GRID2 Vec2(8,8)
    Vec2 getPositionOnGrid(int x, int y, ALIGNMENT align = ALIGNMENT_CENTER, Vec2 grid = GRID);
    Vec2 getPositionOnGrid2(int x, int y, ALIGNMENT align = ALIGNMENT_CENTER, Vec2 grid = GRID2){
        return getPositionOnGrid(x, y, align, grid);
    };
    void drawEars(int i);
    void drawFace(int i);
    void drawEyebrow(int i);
    void drawEyes(int i);
    void drawMouth(int i);
    void drawNose(int i);
    void drawPoint(int i);
};

#endif /* ui_character_animal_h */
