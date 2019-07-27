// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Function.h"
#include <SFML/Graphics.hpp>
#include <exception>

int main() {

	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		throw std::runtime_error("arial.ttf couldn't be loaded");
	}

	Function function(font);
	function.run();
	
	return 0;
}