#include "Images_Click.h"

Images_Click::Images_Click()
{
    //ctor
}

Images_Click::~Images_Click()
{
    //dtor
}
Images_Click::Images_Click(std::string path,SDL_Event* event):Basic_Images(path),Basic_Click(event)
{

}
void Images_Click::Update_on_it()
{
    if( _pEvent->type == SDL_MOUSEMOTION )
    {
        Uint pos_mouse_x = _pEvent->motion.x;
        Uint pos_mouse_y = _pEvent->motion.y;
        const Uint& _pos_x = _pos.Getx();
        const Uint& _pos_y = _pos.Gety();
        //pos_mouse_x = _pEvent->motion.x;
        //pos_mouse_y = _pEvent->motion.y;
        if (_on_it&&!((pos_mouse_x>_pos_x)&&( pos_mouse_x < _pos_x+_width)&&( pos_mouse_y > _pos_y)&&(pos_mouse_y < _pos_y+_height))) _on_it = false;
        else
        {
            if (!_on_it&&((pos_mouse_x>_pos_x)&&( pos_mouse_x<_pos_x+_width)&&(pos_mouse_y >_pos_y)&&(pos_mouse_y<_pos_y+_height))) _on_it = true;
        }
    }
    Set_click_on_long();
    Set_click_on_short();
}