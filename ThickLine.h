#pragma once
#include <SFML/Graphics.hpp>

class ThickLine : 
	public sf::Drawable {

public:
	ThickLine();
	ThickLine(const sf::Vector2f& begin,const sf::Vector2f& end, const float thickness = 1.f, sf::Color = sf::Color::Black);

	void setBegin(const sf::Vector2f& begin);
	void setEnd(const sf::Vector2f& end);
	void setThickness(const float thickness);
	void setColor(const sf::Color& color);

private:
	sf::VertexArray _line;
	sf::Vector2f _begin;
	sf::Vector2f _end;
	float _thickness;
	sf::Color _color;

private:
	void updateLine();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
