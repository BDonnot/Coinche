#include "Trick_Basic.h"

using namespace::std;

Trick_Basic::Trick_Basic(Cards_Deck* pDeck,const std::array<Player*,4>& players):
_players(players),
//_currentTrick(),
_previousTrick(),
_oldFirstPlayer(GHOST),
_pDeck(pDeck)
{
    _currentTrick = {nullptr,nullptr,nullptr,nullptr};
    _previousTrick = {nullptr,nullptr,nullptr,nullptr};
    _posTrick = {FIRST,SECOND,THIRD,FOURTH};
}

Trick_Basic::~Trick_Basic()
{
    for(Uint i = 0;i < 4; ++i)
    {
        delete _currentTrick[i];
        delete _previousTrick[i];
    }
}

string Trick_Basic::GetString() const
{
    string res = "<trick : ";
    res += IntToString(_number_cards_play);
    res += ">";
    Uint first = _oldFirstPlayer;
    Uint counter = 0;
    for(Uint i = first; i < first+4; ++i, ++counter)
    {
        res += _players[i%4]->GetString(_currentTrick[counter]->GetString());
    }
    res += "<\\trick>";
    return res;
}

void Trick_Basic::WinnerTakeCards()
{
    for(Uint i = 0; i < 4; ++i)
    {
        if(_previousTrick[i] == nullptr) break; //TO DO : exception here !
        _pDeck->GetCardBack(_previousTrick[i]);
    }
    if(_trickMemory.TrickNumber()==8)
    {
        for(Uint i = 0; i < 4; ++i)
        {
            if(_currentTrick[i] == nullptr) break; //TO DO : exception here !
            _pDeck->GetCardBack(_currentTrick[i]);
        }
    }
    _previousTrick = _currentTrick;
    _currentTrick = {nullptr,nullptr,nullptr,nullptr};
}

/*
POSITION_TRICK Trick_Basic::whoWinTrick()
{
    POSITION_TRICK res = FIRST;
    for(Uint i = 1; i <4; i++)
    {
        if(_currentTrick[i]==nullptr) break; //TO DO : exception here !
        if(_currentTrick[i]->GetColour()==_currentTrick[res]->GetColour())
        {
            if(_currentTrick[i]->Win(_currentTrick[res]->GetHeight())) res = _posTrick[i];
        }
        else
        {
            if(_currentTrick[i]->GetColour()==_info.TrumpColor()) res = _posTrick[i];
        }
    }
    return res;
}
*/

bool Trick_Basic::Play() // TO DO code the same way as Bidding.cpp
{
    Uint i = _infos.PosPlayerToInt(_to_play);
    if (_cardsPlayed == 0 && (trickFinished()) ) //the trick is over
    {
        terminatecurrentTrick(i);
        return true;
    }
    Cards * pcard = _players[i]->PlayCard(static_cast<TrickBasic_Memory&>(*this));
    if(pcard == nullptr) { return false; }
    _currentTrick[_cardsPlayed] = pcard;
    playerPlayed();
    //graphics bellow
    animateIfGraphic(pcard,i);
    return false;
    /*
    //Uint first = _info.FirstPlayer();
    Cards* pcard = nullptr;
    Uint counter = 0;
    for (Uint i = first; i < first+4; ++i, ++counter)
    {
        if(_currentTrick[counter] != nullptr) continue;
        pcard = _players[i%4]->PlayCard(_currentTrick);
        if(pcard == nullptr) break; //the player has not chosen yet
        _currentTrick[counter] = pcard;

        //graphics bellow
        animateIfGraphic(pcard,i);

        //POSITION_TRICK winner = whoWinTrick();
        //_info.SetHigherCard(winner); //TO DO
        //_info.SetNumberCardsPlayed(); //TO DO
        break;

    }
    //graphic here (in trick finished)
    if((_currentTrick.back() != nullptr)&&(trickFinished()))
    {
        terminatecurrentTrick(first,counter);
        return true;
    }
    return false;
    */

}

void Trick_Basic::terminatecurrentTrick(Uint first)
{
    for (Uint i = first; i < first+4; ++i)
    {
        _players[i%4]->UpdateEndTrick(static_cast<TrickBasic_Memory&>(*this),_infos.IntToPosTrick(i));
    }
    //_oldFirstPlayer = _info.FirstPlayer();
    //POSITION_TRICK winner = whoWinTrick();

/*
    array<Uint,4> values; //TO DO
    for (Uint i = 0; i < 4; ++i)
    {
        values[i] = _currentTrick[i]->Value();
    }
    //if (_info.TrickNumber() == 8) values[0] += 10;
    //_info.SetScores(winner,values);
    */
}

void Trick_Basic::SetPlayers(const array<Player*,4>& players)
{
    _players = players;
}
