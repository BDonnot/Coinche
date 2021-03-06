#include "Quit.h"


#if COMPLETE_GAME > 0
Quit::Quit(SDL_Event* pevent):_destruct(false)
{
    _event = pevent;
    _keystates = SDL_GetKeyState( NULL );
}
bool Quit::KeepLooping()
{
	bool continuer = true;
	if (_event->type == SDL_QUIT) continuer = false;
	if (_event->type == SDL_KEYDOWN)
	{
		switch (_event->key.keysym.sym)
		{
		case SDLK_ESCAPE:
			continuer = false;
			break;
		case SDLK_a:
			if (_keystates[SDLK_LCTRL] || _keystates[SDLK_RCTRL]) continuer = false;
			break;
		case SDLK_F4:
			if (_keystates[SDLK_LALT]) continuer = false;
			break;
		default: break;
		}
	}
	return continuer;
}
Quit::Quit() :_destruct(true)
{
	_keystates = SDL_GetKeyState(NULL);
	_event = new SDL_Event;
}
Quit::~Quit()
{
	if (_destruct) delete(_event);
}
#else
bool Quit::KeepLooping() { return false; }
Quit::Quit() :_destruct(false) {}
Quit::~Quit() {}
#endif //#if COMPLETE_GAME > 0



