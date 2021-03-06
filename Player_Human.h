#ifndef PLAYER_HUMAN_H
#define PLAYER_HUMAN_H

/**
** This class has been done specifically for the human player.
** Now it would be better to have one single class
** player, templated with the method of playing.
** See Player.h and Player_AI.h for more informations.
**/

#include "Player.h"
#include "Take_Human.h"
#include "TakeHumanCoinche.h"
#include "Random.h"
#if COMPLETE_GAME > 0
class Player_Human : public Player
{
    private:
        Take_Human _Take;
        TakeHumanCoinche _TakeCoinche;
		UpdateCardMouse _UpdateCardMouse; //to update if the mouse is over a card or not

    public:
        Player_Human(){}

        Player_Human(const Player_ID& number
			,Uint16 windows_width
			,Uint16 windows_height
			,SDL_Event* pevent
			,Basic_Images* fond
			,SDL_Surface* screen):
            Player(number,windows_width,windows_height,pevent,fond,screen)
            ,_TakeCoinche(pevent,screen,windows_width,windows_height)
            ,_rand(rand()){}
		virtual void Update_Mouse(GAME_PHASES currentPhase);
		virtual void Display(GAME_PHASES currentPhase);
		virtual void ResetBid(bool betFinished);
        virtual ~Player_Human(){}


    protected:
        virtual void updateBid(const BetsMemory& bets);

        virtual Cards* what_card_do_i_play(const TrickBasic_Memory& trick);

    private:
        Player_Human(const Player_Human& other){}
        Player_Human& operator=(const Player_Human& rhs){return *this;}
        Random _rand;
};
#endif //#if COMPLETE_GAME > 0

#endif // PLAYER_HUMAN_H
