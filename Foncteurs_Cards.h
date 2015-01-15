#ifndef FONCTEURS_CARDS_H_INCLUDED
#define FONCTEURS_CARDS_H_INCLUDED
#include "Cards.h"
//#include "fonctions_annexes.h"

class Sort_Cards
{
    public :
        Sort_Cards(int trump_color):
        _trump_color(trump_color)
        {
            _winColor = {false,true,true,true,false,false,false,true,false,true,false,true,false,false,false,false}; //sort the colours : carreau, pique,coeur,trefle
        }
        bool operator()(Cards* card1,Cards* card2) // says if the card1 must be put at the left of the card2
        {
//            int height1 = card1->GetHeight();
            CARDS_HEIGHT height2 = card2->GetHeight();
            CARDS_COLOR color1 = card1->GetColour();
            CARDS_COLOR color2 = card2->GetColour();
            if (color1 != color2) return _winColor[4*color1+color2];
            return card1->Win(height2);
        }
    private :
        int _trump_color;
        std::array<bool,16> _winColor;

};

class DisplayCardPlayer //handle the positionning of the card in the hand
{
    public :
        DisplayCardPlayer(){};
        DisplayCardPlayer(SDL_Surface* screen,Uint windows_width,Uint windows_height,Uint player_number)
        {
            _screen = screen;
            bool vertical_move = (player_number%2==1);
            if (vertical_move)
            {
                _shift.at(0)= 0;
                _shift.at(1)= 21;
            }
            else
            {
                _shift.at(0)= 27;
                _shift.at(1)= 0;
            }
            Uint& pos_x = _pos_player.Getx();
            Uint& pos_y = _pos_player.Gety();
            switch(player_number)
            {
                case 0 :
                    pos_x = windows_width/2 ;
                    pos_y = windows_height - 150;
                    break;
                case 1 :
                    pos_x = windows_width - 135;
                    pos_y = windows_height/2;
                    break;
                case 2 :
                    pos_x = windows_width/2 ;
                    pos_y = 150;
                    break;
                case 3 :
                    pos_x = 135;
                    pos_y = windows_height/2;
                    break;
                default :
                    pos_x = windows_width/2;
                    pos_y = windows_height/2;
                    break;
            }

        }
        void Reset(unsigned int n)
        {
            _total_card = n;
            _nb_cards = 0;
        }
        void operator()(Cards* pcard)
        {
            _nb_cards++;
            UpdatePosHand(pcard->GetUp());
            pcard->UpdatePositionHand(_pos_hand);
            pcard->Display(_screen);
        }
    private :
        unsigned int _nb_cards;
        unsigned int _total_card;
        PositionGraphic _pos_player;
        PositionGraphic _pos_hand;
        std::array<Uint,2> _shift; //the shift of the card (all the card must be visible)
        SDL_Surface* _screen;
        void UpdatePosHand(bool up)
        {
            Uint shift = 0;
            if (_total_card%2 == 0) shift = _nb_cards - _total_card/2;
            else shift = _nb_cards - (_total_card+1)/2 ;

            _pos_hand.Set(_pos_player.Getx()+ shift*_shift[0]
                            ,_pos_player.Gety()+ shift*_shift[1]
                            ,CENTER);
            if (up)// res.at(1) -= 35;
                _pos_hand.Gety() -= 35;
        }
};
/*
class UpdateCardMouvement
{
    public :
        UpdateCardMouvement(){};
        UpdateCardMouvement(Uint32 current_time):_current_time(current_time){}
        void operator()(Cards* pcard)
        {
            pcard->UpdateMouvement(_current_time);
        }
        void Update(Uint32 current_time)
        {
            _current_time = current_time;
        }
    private :
        Uint32 _current_time;
};
*/
class DisplayCardPile
{
    public :
        DisplayCardPile(){}
        DisplayCardPile(SDL_Surface* screen):_screen(screen){}
        void operator()(Cards* pcard)
        {
            pcard->Display(_screen);
        }
    private :
        SDL_Surface* _screen;

};
class UpdateCardMouse
{
    public :
        UpdateCardMouse():_on_it(true),_number(0),_number_click(255){};
        void operator()(Cards* pcard)
        {
            pcard->Update_on_it();
            if ((pcard->Mouse_Over())&&(_on_it)) //we click on the card, and we didn't click on an other card
            {
                _on_it = false;
                pcard->Up(true);
                if (pcard->Click(true)) _number_click = _number;
            }
            else pcard->Up(false);
            _number++;
        }
        void Reset()
        {
           _on_it = true;
           _number = 0;
           _number_click = 255;
        }
        Uint8 Click()
        {
            return _number_click;
        }
    private :
        bool _on_it;
        Uint8 _number; //the number of card currently updated
        Uint8 _number_click; //the number of the card we have click on

};
#endif // FONCTEURS_CARDS_H_INCLUDED