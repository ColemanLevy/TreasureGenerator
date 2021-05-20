//The header file that contains the class which handles the Text component for all entities
#pragma once

#include "Texture.h"

//The Text Component class
class TextComponent : public Component
{
private:
	//The rectangles used to create and draw the text for the renderer
	SDL_Rect srcRect, destRect;
	//The texture used for the render to draw the text on screen
	SDL_Texture *texture;
	//The position and size of the entity this component is attached to. Used to calculate
	//the size and position of the text shown by this component
	TransformComponent *transform;

public:
	//The default initializer for the Text Component
	TextComponent() = default;
	//The constuctor that takes in a message, line length, and color for constructing a
	//text component with a preset message
	TextComponent(const char* message, int line, SDL_Color color)
	{
		setTex(message, line, color);
	}
	//The deconstructor of the text, deletes the text from the entity
	~TextComponent()
	{
		SDL_DestroyTexture(texture);
	}
	//A small function that sets the message that the entity will show. Accepts the message,
	//line length (which is used to determine where the text message should have line breaks),
	//and the color that the text will be
	void setTex(const char* message, int line, SDL_Color color)
	{
		texture = Texture::loadMessage(message, line, color);
	}
	//Sets the position and the source rectangles for the text. Currently, source rectangle with
	//is set to 1000 to allow it to load almost any length of message
	void init() override
	{
		//Sets the position of the text to the position of the entity
		transform = &entity->getComponent<TransformComponent>();
		//Indicates how large the text used is and how it should be offset
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = 1000;
		srcRect.h = 100;
	}
	//Small function the draw the text to where the entity is and at the size given
	void update() override
	{
		//Position of the entity (comes with an offset to center the text)
		destRect.x = (int)transform->position.x + (transform->width * 45 / 256);
		destRect.y = (int)transform->position.y + (transform->height * 10 / 128);
		//Size of the texture (comes with an offset to center the text)
		destRect.w = transform->width  - (transform->width * 80 / 256);
		destRect.h = transform->height  - (transform->height * 30 / 128);
	}
	//Override that draws the text
	void draw() override
	{
		Texture::Draw(texture, srcRect, destRect);
	}
};
