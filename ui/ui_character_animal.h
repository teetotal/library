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
    enum ID_EARS {
        ID_EARS_1 = 0,
        ID_EARS_MAX
    };
    
    enum ID_FACE {
        ID_FACE_1 = 0,
        ID_FACE_2,
        ID_FACE_MAX
    };
    
    enum ID_EYES {
        ID_EYES_1 = 0,
        ID_EYES_2,
        ID_EYES_MAX
    };
    
    enum ID_MOUTH {
        ID_MOUTH_1 = 0,
        ID_MOUTH_2,
        ID_MOUTH_MAX
    };
    
    enum ID_NOSE {
        ID_NOSE_1 = 0,
        ID_NOSE_MAX
    };
    
    enum ID_POINT {
        ID_POINT_1 = 0,
        ID_POINT_MAX
    };
    
    static ui_character_animal * create(Node * parent
                                        , Size size
                                        , Vec2 position
                                        , ALIGNMENT align
                                        , COLOR_RGB colorSkin
                                        , COLOR_RGB colorFeatures
                                        , COLOR_RGB colorPoint
                                        , COLOR_RGB colorBG) {
        ui_character_animal * ret = new (std::nothrow) ui_character_animal;
        if (ret)
        {
            ret->init(parent
                      , size
                      , position
                      , align
                      , colorSkin
                      , colorFeatures
                      , colorPoint
                      , colorBG
            );
            ret->autorelease();
        } else {
            CC_SAFE_DELETE(ret);
        }
        
        return ret;
    };
    void init(Node * parent
              , Size size
              , Vec2 position
              , ALIGNMENT align
              , COLOR_RGB colorSkin
              , COLOR_RGB colorFeatures
              , COLOR_RGB colorPoint
              , COLOR_RGB colorBG);
    
    void addRectangle(ID_EARS nEars = ID_EARS_1
                      , ID_FACE nFace = ID_FACE_1
                      , ID_EYES nEyes = ID_EYES_1
                      , ID_MOUTH nMouth = ID_MOUTH_1
                      , ID_NOSE nNose = ID_NOSE_1
                      , ID_POINT nPoint = ID_POINT_1);
    
    void addCircle(Size size
                   , Color3B colorBG
                   , Color4F colorSkin
                   , Color4F colorFeatures
                   , Color4F colorPoint
                   );

private:
    enum ID_LAYOUT {
        ID_LAYOUT_EARS = 0,
        ID_LAYOUT_FACE,
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
    Node * mParent;
    COLOR_RGB mColorSkin, mColorFeatures, mColorPoint;
    TYPE mType;
    
    #define GRID Vec2(4,4)
    #define GRID2 Vec2(8,8)
    Vec2 getPositionOnGrid(int x, int y, ALIGNMENT align = ALIGNMENT_CENTER, Vec2 grid = GRID);
    Vec2 getPositionOnGrid2(int x, int y, ALIGNMENT align = ALIGNMENT_CENTER, Vec2 grid = GRID2){
        return getPositionOnGrid(x, y, align, grid);
    };
    void drawEars(ID_EARS i);
    void drawFace(ID_FACE i);
    void drawEyes(ID_EYES i);
    void drawMouth(ID_MOUTH i);
    void drawNose(ID_NOSE i);
    void drawPoint(ID_POINT i);
};

#endif /* ui_character_animal_h */
