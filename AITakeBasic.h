#ifndef AITAKEBASIC_H
#define AITAKEBASIC_H

#include <list>

#include "Definitions.h"
#include "Cards.h"
#include "Basic_Game_Info.h"
#include "Player_Bid.h"
#include "Random.h"
#include "BetsMemory.h"
/**
The class to compute a basic bidding for the AI players.
The first player of the team take at 80/90 if he has (Jack or 9)/(Jack and 9) in a color.
The  second player increase the bidding by its numbers of non trump aces.
**/
//TO DO implement this strategy.
class AITakeBasic
{
    protected :
        Basic_Game_Info _basic_info;
        bool _alreadyBid;
    public:
        AITakeBasic():_basic_info(),_alreadyBid(false){}
        virtual ~AITakeBasic(){}
        void Bid(Player_Bid& bid,const std::list<Cards*>& hand,Random& rand,const BetsMemory& bets);
        void Reset(){_alreadyBid = false;}
    protected:
        void iChoose(Player_Bid& bid,const std::list<Cards*>& hand);
        void iFollow(Player_Bid& bid,const std::list<Cards*>& hand,const Player_Bid& bidTeammate);
    private:
};

#endif // AITAKEBASIC_H