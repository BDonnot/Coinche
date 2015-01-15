#include "Trump_Image.h"
using namespace::std;

Trump_Image::Trump_Image()
{
    //ctor
}
Trump_Image::Trump_Image(SDL_Event* event):Images_Sprite<4>("images/sprite_trunk.png"),Basic_Click(event)
{
//    vector<int> coord_x = {0,150,0,150};
//    vector<int> coord_y = {0,0,150,150};
//    vector<int> dimension_w = {100,100,100,100};
//    Set_dimension_sprite(coord_x,coord_y,dimension_w,dimension_w);
    array<Uint,4> coord_x = {0,150,0,150};
    array<Uint,4> coord_y = {0,0,150,150};
    array<Uint,4> dimension_w = {100,100,100,100};
    SetDimensionSprite(coord_x,coord_y,dimension_w,dimension_w);
}

Trump_Image::~Trump_Image()
{
    //dtor
}

Trump_Image::Trump_Image(const Trump_Image& other)
{
    //copy ctor
}

Trump_Image& Trump_Image::operator=(const Trump_Image& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

void Trump_Image::Update_on_it()
{
    if( _pEvent->type == SDL_MOUSEMOTION )
    {
        Uint pos_mouse_x = _pEvent->motion.x;
        Uint pos_mouse_y = _pEvent->motion.y;
        const Uint& _pos_x = _pos.Getx();
        const Uint& _pos_y = _pos.Gety();
        if (_on_it&&!((pos_mouse_x>_pos_x)&&( pos_mouse_x < _pos_x+_width)&&( pos_mouse_y > _pos_y)&&(pos_mouse_y < _pos_y+_height))) _on_it = false;
        else
        {
            if (!_on_it&&((pos_mouse_x>_pos_x)&&( pos_mouse_x<_pos_x+_width)&&(pos_mouse_y >_pos_y)&&(pos_mouse_y<_pos_y+_height))) _on_it = true;
        }
    }
    Set_click_on_long();
    Set_click_on_short();
}
void Trump_Image::Set_Taker(int taker)
{
    ChangeSprite(taker);
}