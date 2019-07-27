// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "ThickLine.h"

ThickLine::ThickLine() :
	_line(sf::Quads, 4),
	_thickness(0.f),
	_begin(),
	_end() {
	setColor(sf::Color::Black);
	updateLine();
}

ThickLine::ThickLine(const sf::Vector2f& begin,const sf::Vector2f& end, const float thickness, sf::Color color) :
	_begin(begin), _end(end), _thickness(thickness), _line(sf::Quads, 4) {
	setColor(color);
	updateLine();
}

void ThickLine::setBegin(const sf::Vector2f& begin) {
	_begin = begin;
	updateLine();
}

void ThickLine::setEnd(const sf::Vector2f& end) {
	_end = end;
	updateLine();
}

void ThickLine::setThickness(const float thickness) {
	_thickness = thickness;
	updateLine();
}

void ThickLine::setColor(const sf::Color& color) {
	_line[0].color = color;
	_line[1].color = color;
	_line[2].color = color;
	_line[3].color = color;
}

void ThickLine::updateLine() {
	const sf::Vector2f midLine = _end - _begin;									// vector between points
	const float length =																				// midLine's length
		std::sqrtf(midLine.x * midLine.x + midLine.y*midLine.y);
	sf::Vector2f normal = midLine / length;											// normal vector
	sf::Vector2f turn{ -normal.y, normal.x };										// normal, turned 90 degrees
	sf::Vector2f vector{ turn * _thickness / 2.f };							// half of a thickness
	
	// drawing Quad clockwise
	_line[0].position = _begin + vector;
	_line[1].position = _end + vector;
	_line[2].position = _end - vector;
	_line[3].position = _begin - vector;
}

void ThickLine::draw(sf::RenderTarget& target, sf::RenderStates) const {
	target.draw(_line);
}


