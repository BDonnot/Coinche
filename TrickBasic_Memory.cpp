#include "TrickBasic_Memory.h"
using namespace std;

void TrickBasic_Memory::Reset()
{
    _trickNumber = 0;
    _cardsPlayed = 0;
    _to_play = _infos.Giver();
    _oldFirstPlayer = GHOST;
    _winner = Position_Trick(UNKNOWN);
    _scores.first = 0;
    _scores.second = 0;
    _colorAsked = Card_Color(NOT_CHOSEN);
    _colorMaster = Card_Color(NOT_CHOSEN);
    _heightMaster = Card_Height(UNINTIALIZED);
    _trickFinished = false;
}

void TrickBasic_Memory::updateWinner()
{
    if(_cardsPlayed == 0)
    {
        _colorAsked = _currentTrick[0]->GetColour();
        _colorMaster = _colorAsked;
        _heightMaster = _currentTrick[0]->GetHeight();
        _winner = Position_Trick(FIRST);
        _printf("color asked : %d, trump color : %d\n",_colorAsked.ToInt(),_infos.TrumpColor().ToInt());
        return ;
    }
    Card_Color colorTrump = _infos.TrumpColor();
    Card_Color color = _currentTrick[_cardsPlayed]->GetColour();
    _printf("color asked : %d, trump color : %d, color played : %d\n",_colorAsked.ToInt(),_infos.TrumpColor().ToInt(),color.ToInt());

    bool needUpdate = false; //do the last cards played is master
    if(color == colorTrump)
    {
        if(_colorMaster == colorTrump) needUpdate = _currentTrick[_cardsPlayed]->Win(_heightMaster);
        else needUpdate = true;
    }
    else
    {
        if(_colorMaster == colorTrump) needUpdate = false;
        else
        {
            if(color != _colorAsked) needUpdate = false;
            else needUpdate = _currentTrick[_cardsPlayed]->Win(_heightMaster);
        }
    }
    if(needUpdate)
    {
        _colorMaster = _currentTrick[_cardsPlayed]->GetColour();
        _heightMaster = _currentTrick[_cardsPlayed]->GetHeight();
        _winner = Position_Trick(_cardsPlayed);
    }
    _printf("after player %d played, the winner is %d \n",_cardsPlayed,_winner.Position());
}

void TrickBasic_Memory::finishTrick()
{
    _printf("le pli %d est fini\n",_trickNumber);
    Uint pointsInTheTrick = 0;
    for(auto pcards : _currentTrick) { pointsInTheTrick += pcards->Value(); }
    if(_trickNumber == 8) pointsInTheTrick += 10;
    updateToPlay();
    updateScores(pointsInTheTrick);
}

void TrickBasic_Memory::updateToPlay()
{
    _printf("updateToPlay : first player is %d \n",_to_play.ID());
    _oldFirstPlayer = _to_play;
    switch(_winner.Position()) //TO DO better to do here !
    {
    case FIRST :
        break;
    case SECOND :
        _to_play.Next();
        break;
    case THIRD :
        _to_play.Next();
        _to_play.Next();
        break;
    case FOURTH :
        _to_play.Next();
        _to_play.Next();
        _to_play.Next();
        break;
    default : //TO DO exception here
        _to_play = Player_ID(GHOST);
        break;
    }
}

void TrickBasic_Memory::updateScores(Uint pointsInTheTrick)
{

    switch(_to_play.ID())
    {
    case PLAYER0 : case PLAYER2 :
        _scores.first += pointsInTheTrick;
        break;
    case PLAYER1 : case PLAYER3 :
        _scores.second += pointsInTheTrick;
        break;
    default : //TO DO exception here
        break;
    }
    updateBasicGameInfo(); //this class does not update it
}

void TrickBasic_Memory::trickOver()
{
    _trickFinished = false;
    _cardsPlayed = 0;
    _trickNumber++;
    finishTrick();
    _winner = Position_Trick(UNKNOWN);
}

void TrickBasic_Memory::playerPlayed()
{
    updateWinner();
    _to_play.Next();
    _cardsPlayed++;
}

bool TrickBasic_Memory::IsFallen(const Card_Color& color, const Card_Height& height) const
{
    Cards* temp;
    for(Uint i = 0; i < _cardsPlayed; ++i)
    {
        temp = _currentTrick[i];
        if(temp->GetColour() == color && temp->GetHeight() == height) return true;
    }
    return false;
}

void TrickBasic_Memory::PutCard(Cards* card)
{
    _currentTrick[_cardsPlayed] = card;
    playerPlayed();
}
void TrickBasic_Memory::NextToPlay()
{
    trickFinished();
    if (_cardsPlayed == 4 && _trickFinished) //the trick is over
    {
        trickOver();
    }
}
