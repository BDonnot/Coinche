#ifndef PLAYER_NAME_H
#define PLAYER_NAME_H

/**
** This class display the name of the player.
** It is also charged to handle the changing of the name
** at the beginning of game.
** The names can be changed by clicking on the image of the player.
**/

#include <string>

#include "Basic_Game_Info.h"
#include "Text_Typing.h"
#include "Images_Text.h"
#include "Images_Click.h"
#include "Images_Button.h"
#include "Quit.h"


class Player_Name:public Quit //contains the name, the question, and the image of a player
{
    protected:
        Text_Typing _name; //the name we can enter
		Text_Typing _name_display; //the name  displayed under the image
		Images_Text _what_name; //the question above the name
		Basic_Images* _fond; //tapis of the game
		Images_Click _image; //the image of the player
        Uint16 _width;
        Uint16 _height;
        std::string _name_origin;
#if COMPLETE_GAME > 0
        SDL_Event _current_event;
#endif
        Uint8* _keystates; //state of the key : pressed / not pressed
		Images_Button _ok;
		Images_Button _return;

    public:
        Player_Name(){}
		Player_Name(Basic_Images* fond
			, std::string name
			, std::string path_image
			, Uint width
			, Uint height
			, PositionGraphic& pos);
		Player_Name(std::string name
			, std::string path_image
			, Uint width
			, Uint height
			, PositionGraphic& pos);
#if COMPLETE_GAME > 0
        Player_Name(Basic_Images* fond
			,std::string name
			,std::string path_image
			,SDL_Event* pevent
			,Uint width
			,Uint height
			,PositionGraphic& pos);
		bool WhatName(SDL_Surface* screen);
		void Display(SDL_Surface* destination, bool choose_name);
#else
		bool WhatName() { return false; }
		void Display(bool choose_name) {}
#endif //#if COMPLETE_GAME > 0
        virtual ~Player_Name(){}

        void Update(GAME_PHASES currentPhase);
        void ResetClick();
        const std::string& Name() const;
    private:
};

#endif // PLAYER_NAME_H
