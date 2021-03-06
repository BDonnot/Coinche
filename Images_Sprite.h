#ifndef IMAGES_SPRITE_H
#define IMAGES_SPRITE_H

/**
** This class define an specific type of image :
** an image that can be displayed with "numberOfSprite"
** different faces.
**/

#include <array>

#if COMPLETE_GAME > 0
#if defined(__GNUC__)
	#include "SDL/SDL.h"
	#include "SDL/SDL_image.h"
#elif defined(_MSC_VER)
	#include <SDL.h>
	#include <SDL_image.h>
#endif //SDL include
#endif //#if COMPLETE_GAME > 0

#include "Basic_Images.h"

	template<Uint numberOfSprite>
	class Images_Sprite : public Basic_Images
	{
	protected:
#if COMPLETE_GAME > 0
		SDL_Rect _clip[numberOfSprite];
#endif //#if COMPLETE_GAME > 0
		Uint _sprite_number; //number of the sprite in the sheet currently used

	public:
		Images_Sprite();
		Images_Sprite(std::string path);
		virtual ~Images_Sprite() {}
#if COMPLETE_GAME > 0
		virtual void Display(SDL_Surface* destination);
		void apply_surface(Uint x, Uint y, const SMARTSurface& source, SDL_Surface* destination, SDL_Rect* clip); 
		//overriding of the method for applying the right surface on the screen
#else
		virtual void Display(){}
		void apply_surface(Uint x, Uint y) {}
#endif //#if COMPLETE_GAME > 0
		virtual void SetPosition(PositionGraphic& pos);
		void ChangeSprite(Uint sprite_number, PositionGraphic& pos); //to change the sprite displayed, and ajust its position on the screen
		void ChangeSprite(Uint sprite_number); //change the sprite currently used
		void SetDimensionSprite(const std::array<Uint, numberOfSprite>& coord_x
			, const std::array<Uint, numberOfSprite>& coord_y
			, const std::array<Uint, numberOfSprite>& dimension_w
			, const std::array<Uint, numberOfSprite>& dimension_h); //set the dimension of the sprite sheet

		Uint GetSpriteNumber() { return _sprite_number; }
	private:
	};

	template<Uint numberOfSprite>
	Images_Sprite<numberOfSprite>::Images_Sprite(std::string path) :
		Basic_Images(path)
		, _sprite_number(0)
	{

	}

	template<Uint numberOfSprite>
	Images_Sprite<numberOfSprite>::Images_Sprite() :
		_sprite_number(0)
	{

	}
#if COMPLETE_GAME > 0
	template<Uint numberOfSprite>
	void Images_Sprite<numberOfSprite>::Display(SDL_Surface* destination)
	{
		act();
		if (_surface != nullptr) apply_surface(_pos.Getx(), _pos.Gety(), _surface, destination, &(_clip[_sprite_number]));
	}

	template<Uint numberOfSprite>
	void Images_Sprite<numberOfSprite>::SetDimensionSprite(const std::array<Uint, numberOfSprite>& coord_x
		, const std::array<Uint, numberOfSprite>& coord_y
		, const std::array<Uint, numberOfSprite>& dimension_w
		, const std::array<Uint, numberOfSprite>& dimension_h)
	{
		for (int i = 0; i < numberOfSprite; i++)
		{
			_clip[i].x = coord_x[i];
			_clip[i].y = coord_y[i];
			_clip[i].w = dimension_w[i];
			_clip[i].h = dimension_h[i];
		}
	}

	template<Uint numberOfSprite>
	void Images_Sprite<numberOfSprite>::apply_surface(Uint x, Uint y, const SMARTSurface& source, SDL_Surface* destination, SDL_Rect* clip)
	{
		SDL_Rect offset;
		offset.x = x;
		offset.y = y;
		SDL_BlitSurface(source.get(), clip, destination, &offset);
	}
	template<Uint numberOfSprite>
	void Images_Sprite<numberOfSprite>::ChangeSprite(Uint sprite_number)
	{
		_sprite_number = sprite_number;
		_height = _clip[_sprite_number].h;
		_width = _clip[_sprite_number].w;
	}

	template<Uint numberOfSprite>
	void Images_Sprite<numberOfSprite>::SetPosition(PositionGraphic& pos)
	{
		_height = _clip[_sprite_number].h;
		_width = _clip[_sprite_number].w;
		pos.SetProperPosition(_width, _height);
		_pos = pos;
	}
#else
	template<Uint numberOfSprite>
	void Images_Sprite<numberOfSprite>::SetDimensionSprite(const std::array<Uint, numberOfSprite>& coord_x
		, const std::array<Uint, numberOfSprite>& coord_y
		, const std::array<Uint, numberOfSprite>& dimension_w
		, const std::array<Uint, numberOfSprite>& dimension_h) {}

	template<Uint numberOfSprite>
	void Images_Sprite<numberOfSprite>::ChangeSprite(Uint sprite_number) {}

	template<Uint numberOfSprite>
	void Images_Sprite<numberOfSprite>::SetPosition(PositionGraphic& pos) {}
#endif //#if COMPLETE_GAME > 0
	template<Uint numberOfSprite>
	void Images_Sprite<numberOfSprite>::ChangeSprite(Uint sprite_number, PositionGraphic& pos)
	{
		_sprite_number = sprite_number;
		SetPosition(pos);
	}


#endif // IMAGES_SPRITE_H
