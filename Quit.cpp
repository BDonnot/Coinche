#include "Quit.h"

Quit::Quit()
{
    _keystates = SDL_GetKeyState( NULL );
    _event = new SDL_Event;
    _destruct = true;
}
Quit::Quit(SDL_Event* pevent)
{
    _event = pevent;
    _keystates = SDL_GetKeyState( NULL );
    _destruct = false;
}
Quit::~Quit()
{
    if (_destruct) delete(_event);
}
bool Quit::KeepLooping()
{
    bool continuer = true;
    if (_event->type == SDL_QUIT) continuer = false;
    if (_event->type == SDL_KEYDOWN)
    {
        switch( _event->key.keysym.sym )
        {
            case SDLK_ESCAPE:
                continuer = false;
                break;
            case SDLK_a:
                if (_keystates[SDLK_LCTRL]||_keystates[SDLK_RCTRL]) continuer = false;
            break;
            case SDLK_F4 :
                if (_keystates[SDLK_LALT]) continuer = false;
            break;
            default : break;
        }
    }
    return continuer;
}