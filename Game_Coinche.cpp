#include "Game_Coinche.h"

using namespace std;
Game_Coinche::Game_Coinche()
{
    //ctor
}

Game_Coinche::Game_Coinche(SDL_Surface* screen,Uint16 screenWidth, Uint16 screenHeight):
    Quit()
    ,_infos()
    ,_pScreen(screen)
    ,_backSide("images/tapis_moyen_2.jpg")
    ,_begin(&_backSide,_event,screenWidth,screenHeight)
    ,_end(&_backSide,_event,screenWidth,screenHeight,"Merci d'avoir jou� !")
    ,_error(&_backSide,_event,screenWidth,screenHeight,"An unexpected error occurred :-(")
    ,_deck(_event,_pScreen,screenWidth,screenHeight)
    ,_currentPhase(BEGINNING)
    ,_bid(array<Player*,4>(),_event,_pScreen,&_deck)
    ,_timeNextAction(0)
    ,_trick(&_deck,array<Player*,4>(),screenWidth,screenHeight,_event,_pScreen)
    ,_endGame(_event,_pScreen,screenWidth,screenHeight)
    ,_saveGame()
{
    PositionGraphic pos(0,0,TOP_LEFT);
    _backSide.SetPosition(pos);
    POSITION_PLAYER posPlayer[4] = {PLAYER0,PLAYER1,PLAYER2,PLAYER3};
    _players[0] = static_cast<Player*>(new Player_Human(posPlayer[0],screenWidth,screenHeight,_event,&_backSide,_pScreen));
//    _players[0] = static_cast<Player*>(new Player_AI(posPlayer[0],screenWidth,screenHeight,_event,&_backSide,_pScreen));
    for (Uint i = 1; i < 4; i++)
    {
        //<AITakeBasic,AIPlayRandom>
        _players[i] =  static_cast<Player*>(new Player_AI<AITakeBasic,AIPlayRandom>(posPlayer[i],screenWidth,screenHeight,_event,&_backSide,_pScreen));
    }
    _bid.SetPlayers(_players);
    _trick.SetPlayers(_players);
}

Game_Coinche::~Game_Coinche()
{
    for (Uint i = 0; i < 4; i++)
    {
        delete _players[i];
    }
}
void Game_Coinche::updateEvent(bool& keep_playing)
{
    while(SDL_PollEvent(_event))
    {
        _begin.Update();
        _deck.UpdateEvent(_currentPhase);
        _trick.UpdateEvent(_currentPhase);
        for (Uint i = 0; i < 4; i++)
        {
            _players[i]->Update_Mouse(_currentPhase);
        }
        keep_playing = keep_playing && KeepLooping();
        _bid.UpdateEvent(_currentPhase);
        _endGame.UpdateEvent(_currentPhase);
    }
}
bool Game_Coinche::waitForClick()
{
    while(true)
    {
        while(SDL_PollEvent(_event))
        {
            if(_event->type == SDL_KEYDOWN)
            {
                if(_event->key.keysym.sym == SDLK_SPACE) return true;
            }
            if(!KeepLooping())
                return false;
        }
    }
}
void Game_Coinche::updateTime(Uint32 diffTime)
{
    _infos.AddClock(diffTime);
}
void Game_Coinche::Display()
{
     _backSide.Display(_pScreen);
    for (Uint i = 0; i < 4; i++)
    {
        _players[i]->Display(_currentPhase);
    }
    _deck.Display(_currentPhase);
    _bid.Display(_currentPhase);
    _trick.Display(_currentPhase);
    _endGame.Display(_currentPhase);
}
void Game_Coinche::playGame(bool& keep_playing)
{
    if(_infos.Time() < _timeNextAction) return;
    switch (_currentPhase)
    {
    case BEGINNING :
        switch (_begin.Display(_pScreen))
        {
            case QUIT :
                keep_playing = false;
                return;
            case PLAY :
                _currentPhase = (_deck.FirstGame()) ? SELECT_NAMES : GIVING;
                _deck.BeginGame();
                return;
            default :
                return;
        }
        return;
    case SELECT_NAMES : case GIVING :
        if(_deck.Click(_currentPhase))
        {
            _deck.Reset();
//            _deck.GiveCards(_players);
//            _saveGame.SaveHands(_players);
//            _timeNextAction = _infos.Time() + 2000;
            _currentPhase = PREBET;
        }
        return;
        /*
    case GIVING :
        if(_deck.Click(_currentPhase))
        {
            _deck.Reset();
//            _deck.GiveCards(_players);
//            _saveGame.SaveHands(_players);
//            _timeNextAction = _infos.Time() + 2000;
            _currentPhase = PREBET;
        }
        return;
        */
    case PREBET :
        _deck.GiveCards(_players);
        _saveGame.SaveHands(_players);
        _timeNextAction = _infos.Time() + 2000;
        _currentPhase = BIDDING;
        _bid.Reset();
        return;
    case BIDDING :
        if (_bid.Bid(_currentPhase))
        {
            _saveGame.SaveBet(_bid);
            _currentPhase=AFTER_BET;
            _bid.SummarizeBet();
        }
        return;
    case AFTER_BET :
        if (_bid.Click(true))
        {
            _currentPhase = _bid.NextPhase();
            if(_currentPhase == PLAYING)
            {
                _saveGame.SaveTake(_infos.Taker(),_infos.TrumpColor(),_infos.MaxBid());
                _trick.Update();
                ///for(auto it = _players.begin(); it != _players.end();++it)
                ///{
                    ///(*it)->InitMemory();
                ///}
            }
            else _saveGame.EndGame();
        }
        return;
    case PLAYING :
        if(_trick.Play()) _currentPhase = AFTER_TRICK0;
        return;
    case AFTER_TRICK0 :
        _saveGame.SaveTrick(_trick);
        _trick.GatherCards();
        _timeNextAction = _infos.Time() + 600;
        _currentPhase = AFTER_TRICK1;
        return;
    case AFTER_TRICK1 :
         _trick.WinnerTakeCards();
        _currentPhase = PLAYING;
        if(_infos.TrickNumber() == 8)
        {
            _endGame.Update();
            const array<Uint,2>& scores = _infos.FinalScores();
            _saveGame.SaveScores(scores[0],scores[1]);
            _currentPhase = SCORES;
        }
        return;
    case SCORES :
        _currentPhase = _endGame.Next();
        if(_currentPhase!=SCORES) _saveGame.EndGame();
        return;
    default :
        return;
    }
}
void Game_Coinche::Play()
{
    bool keep_playing = true;
    Uint32 startLoop = 0,endLoop = 0;
    double FRAMES_PER_SECOND = 32.;
    Uint32 min_time_loop = static_cast<Uint32>(1000./FRAMES_PER_SECOND);
    _timeNextAction = 0;
    bool error = false;
     while (keep_playing)
    {
        updateTime(endLoop-startLoop);
        try //future feature to be added here, one day... like handling an exception and trying to recover the game from the files saved...
        {
            if(error) throw 0;
            startLoop = SDL_GetTicks();
            updateEvent(keep_playing);
            Display();
            playGame(keep_playing);
            keep_playing = keep_playing && _currentPhase!=EXIT;
        }
        catch(...)
        {
            error = true;
            keep_playing = false;
        }
        if (!keep_playing)
        {
            if(error) _error.Display(_pScreen);
            else _end.Display(_pScreen);
        }
        endLoop = SDL_GetTicks();
        if (endLoop < min_time_loop + startLoop) SDL_Delay( (min_time_loop+ startLoop) - endLoop  );
        SDL_Flip(_pScreen);
        endLoop = SDL_GetTicks();
    }
    _saveGame.Quit();
}