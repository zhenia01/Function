#pragma once

#include <SFML/Graphics.hpp>
#include "ThickLine.h"

// Main class, encapsulates "game loop"

class Function {
public:
	Function(sf::Font& font);
	void run();

private:
	void processEvents();
	void render();

	sf::VertexArray mainGraph();							// heart of vertexes
	sf::Text initFuncLabel();									// function label on the top
	sf::View initView();											// centering coordinates
	std::vector<sf::VertexArray> initLines(); // vertical and horisontal lines
	std::vector<sf::Text> initStepsx();				// step labels
	std::vector<ThickLine> initStrokes();			// step strokes
	std::pair<float, float> func(float x);		// function

private:
	sf::RenderWindow _window;									
	sf::Sprite _picture;											// calculated scene
	sf::RenderTexture _texture;								// needed for _picture
	sf::Font _font;

	const float _zoom = 250.f;
};

