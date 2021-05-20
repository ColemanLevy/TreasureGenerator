//Cpp file that contains the functions for what the TextureManager does
#include "Headers/Texture.h"

//Loads texture from sprite pointer
SDL_Texture* Texture::loadTexture(const char* texture)
{
	//Load image from file path saved at pointer
	SDL_Surface* tempSurface = IMG_Load(texture);
	//Turn image into a texture
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	//Open up tempSurface for later use
	SDL_FreeSurface(tempSurface);
	//Return the newly created texture
	return tex;
}

//Loads text from a parsed message. The color of the text is taken from the passed color
//and it contains line breaks based on the size of the passed line length
SDL_Texture* Texture::loadMessage(const char* message, int line, SDL_Color color)
{
	//Creates the text's font and size using a ttf file
	TTF_Font* font = TTF_OpenFont("Ubuntu.ttf", 12);
	//Creates a surface that renders the text as a texture on the given surface
	SDL_Surface* surMessage = TTF_RenderText_Blended_Wrapped(font, message, color, line);
	//Then loads that created texture into the texture used by the text component
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Game::renderer, surMessage);
	//Frees up the Message Surface for later use
	SDL_FreeSurface(surMessage);
	//Returns the texture to be used by the text component
	return Message;
}

//Small function that draws out the texture the renderer is meant to render
void Texture::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}