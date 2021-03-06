#ifndef TAKEHUMANCOINCHE_H
#define TAKEHUMANCOINCHE_H

/**
** This class allows the human player to
** interact with game, and to choose the color
** and the value of its bet.
**/

#include<string>
#include<ostream>
#include <sstream>

#include "Definitions.h"
#include "Basic_Game_Info.h"
#include "Player_Bid.h"
#include "Images_Button.h"
#include "Images_Text.h"
#include "Player_Bid.h"
#include "Random.h"

#if COMPLETE_GAME > 0
class TakeHumanCoinche
{
    protected :
        Uint16 _windows_width;
        Uint16 _windows_height;
        SDL_Surface* _screen;
        const Basic_Game_Info _info;
		Images_Button _carreau;
		Images_Button _coeur;
		Images_Button _pique;
		Images_Button _trefle;
		Images_Button _tt_atout;
		Images_Button _ss_atout;
		Images_Button _pass;
		Images_Button _ok;
		Images_Button _plus;
		Images_Button _minus;
		Images_Text _score;

        Player_Bid _unconfirmedBid;
        Player_Bid _confirmedBid;

        bool _displayed;
        Uint32 _clock;
        Uint32 _clock_min_before_new_change;
    public:
        TakeHumanCoinche(){};
        TakeHumanCoinche(SDL_Event* event,SDL_Surface* screen,Uint16 windows_width, Uint16 windows_height);
        virtual ~TakeHumanCoinche(){}

        void Display(GAME_PHASES currentPhase);
        void UpdateMouse(GAME_PHASES currentPhase);
        void UpdateClock(Uint32 time);

        const Player_Bid& Has_Taken();
        void Reset(bool reset_unconfirmedBid);
    protected:
        void Update();
        void ChangeText(Uint number);
    private:
};
#endif //#if COMPLETE_GAME > 0

#endif // TAKEHUMANCOINCHE_H
