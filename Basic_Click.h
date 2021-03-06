#ifndef BASIC_CLICK_H
#define BASIC_CLICK_H


/**
** Basis class for a button (for example)
** Knowing if the mouse is over the "surface concerned"
** and the previous actions done (click, move, etc.)
** it will compute if the "surface concerned"
** has been clicked on or not (for example)
**/

#include "Definitions.h"

#if COMPLETE_GAME > 0
#if defined (__GNUC__)
	#include "SDL/SDL.h"
#elif defined (_MSC_VER)
	#include <SDL.h>
#endif //SDL include
#endif //COMPLETE_GAME


class Basic_Click
{
protected:
	bool _on_it; //if the mouse is over
	bool _click_on_short; //if we click on
	bool _click_on_long; //if we have clicked on, and we still don't have clicked somewhere else
#if COMPLETE_GAME > 0
	SDL_Event* _pEvent; //pointer to the current event
#endif //#if COMPLETE_GAME > 0
public:
	Basic_Click() {}
#if COMPLETE_GAME > 0
	Basic_Click(SDL_Event* event);
	SDL_Event* GetEvent() { return _pEvent; }
#endif //#if COMPLETE_GAME > 0
	virtual ~Basic_Click() {}

	bool Mouse_Over() const { return _on_it; } //true if the mouse is over the images
	bool Click(bool Short); //return true if we click short /long on the image
	virtual void Update_on_it(); //update the position of the mouse and the click
	void Reset_Click();
protected:
	void Set_click_on_long(); //we 'long click' on a surface if we clicked on it once, and we doesn't click anywhere else in the mean time
	void Set_click_on_short(); //we 'short click' on a surface if we just cicked on it
private:
};
#endif // BASIC_CLICK_H
