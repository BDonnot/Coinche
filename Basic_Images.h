#ifndef BASIC_IMAGES_H
#define BASIC_IMAGES_H

/**
** This class is the basic (and basis) of all the
** User Interface, concerning the graphics.
** It uses Smart pointers (unique_ptr) delete the surface.
** For reason of safety, it is then forbidden to copy / assign
** these surface.
**/
#include <string>
#include <array>
#include <memory>

#include "Definitions.h"

#if COMPLETE_GAME > 0
#if defined(__GNUC__)
	#include "SDL/SDL.h"
	#include "SDL/SDL_image.h"
#elif defined(_MSC_VER)
	#include <SDL.h>
	#include <SDL_image.h>
#endif //SDL include
#endif //COMPLETE_GAME

#include "Basic_Game_Info.h"
#include "PositionGraphic.h"


#if COMPLETE_GAME > 0
	class DeleteSurface
	{
	public:
		DeleteSurface() {}
		void operator()(SDL_Surface* surface)
		{
			SDL_FreeSurface(surface);
		}
	};
	typedef std::unique_ptr<SDL_Surface, DeleteSurface> SMARTSurface;
#endif //#if COMPLETE_GAME > 0

	class Basic_Images
	{
	protected:
		const Basic_Game_Info _info;
		int _height; //height
		int _width; //width
		PositionGraphic _pos;
#if COMPLETE_GAME > 0
		SMARTSurface _surface; //the surface
#endif // #if COMPLETE_GAME > 0

	public:
		Basic_Images();
		Basic_Images(std::string path);
		virtual ~Basic_Images() {}
		virtual void SetPosition(PositionGraphic& pos); //to set the position of the image
#if COMPLETE_GAME > 0
		void Display(SDL_Surface* destination); //to display the image on the screen
		const SDL_Surface* Get_Surface() const { return _surface.get(); }
#endif //#if COMPLETE_GAME > 0
		void Display() {}
		const PositionGraphic& GetPosition() const { return _pos; }
		std::array<Uint, 2> GetSize();

	protected:
#if COMPLETE_GAME > 0
		SDL_Surface* load_image(const std::string& filename); //to load a surface from an image
		void apply_surface(const Uint& x, const Uint& y, const SMARTSurface& source, SDL_Surface* destination); //to apply a surface on the screen
#endif //#if COMPLETE_GAME > 0
		void apply_surface(const Uint& x, const Uint& y) {} //to apply a surface on the screen
		virtual void act() {} //the action : will be overrode in the derivate classes (for example changing the position if the image is moving)

	private:
		Basic_Images(const Basic_Images& other) {} //to prevent copy
		Basic_Images& operator=(const Basic_Images& other) { return *this; } //to prevent assignment
	};

#endif // BASIC_IMAGES_H
