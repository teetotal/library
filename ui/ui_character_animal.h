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
    
    void init(Size size);

private:
    #define GRID Vec2(4,4)
    Vec2 getPositionOnGrid(int x, int y, ALIGNMENT align = ALIGNMENT_CENTER, Vec2 grid = GRID);
    
};

#endif /* ui_character_animal_h */
