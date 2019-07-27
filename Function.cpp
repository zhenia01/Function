// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Function.h"
#include <cmath>
#include <string>

Function::Function(sf::Font& font) :
	_window{ sf::VideoMode{ 1200, 1000 }, "Function", sf::Style::Close | sf::Style::Titlebar },
	_font(font)
{
	_texture.create(1200, 1000);

	sf::View view{ initView() };
	_texture.setView(view);

	sf::Text text{ initFuncLabel() };

	sf::VertexArray pointArray = mainGraph();
	std::vector<sf::VertexArray> axisArray = initLines();
	std::vector<sf::Text> stepArray = initSteps();
	std::vector<ThickLine> strokeArray = initStrokes();

	strokeArray.push_back(ThickLine({ 0.f * _zoom, -1.5f* _zoom - 2.5f }, {0.f * _zoom, 1.5f * _zoom + 2.5f}, 5.f, sf::Color::Black)); // vertical bold metrics line
	strokeArray.push_back(ThickLine({ 1.8f * _zoom, 0.f * _zoom }, {-1.8f * _zoom, 0.f * _zoom}, 5.f, sf::Color::Black)); // horisontal bold metrics line

	//drawing texture
	_texture.clear(sf::Color::White);

	for (const auto i : axisArray) {
		_texture.draw(i);
	}
	for (const auto i : stepArray) {
		_texture.draw(i);
	}
	for (const auto i : strokeArray) {
		_texture.draw(i);
	}
	_texture.draw(pointArray);

	_texture.draw(text);
	_texture.display();

	_picture.setTexture(_texture.getTexture());
}

std::pair<float, float> Function::func(float x) {

	float _1 = std::pow(x, 2.f / 3.f); // x^(2/3)
	float _2 = std::pow(x, 4.f / 3.f); // x^(4/3)
	float _3 = 4.f * (1.f - x * x); // 4(1-x^2)
	float _4 = std::sqrt(_2 + _3); // sqrt(x^(4/3) + 4(1-x^2))

	float _plus = _1 + _4; // x^(2/3) + sqrt(x^(4/3) + 4(1-x^2))
	_plus *= 0.5f; //  1/2 (x^(2/3) + sqrt(x^(4/3) + 4(1-x^2)))

	float _minus = _1 - _4; //  x^(2/3) - sqrt(x^(4/3) + 4(1-x^2))
	_minus *= 0.5f; // 1/2 (x^(2/3) + sqrt(x^(4/3) + 4(1-x^2)))

	return std::pair<float, float>(_minus, _plus);
}

sf::VertexArray Function::mainGraph() {

	sf::VertexArray pointArray(sf::Points, 72000);

	for (int i = 0; i <= 1100; i += 1) { // [0, 1.1], ->0.001

		float x = i / 1000.f;

		auto y = func(x);
		pointArray.append(sf::Vertex(sf::Vector2f(x * _zoom, -y.first * _zoom), sf::Color::Red));
		pointArray.append(sf::Vertex(sf::Vector2f(x * _zoom, -y.second * _zoom), sf::Color::Red));
		pointArray.append(sf::Vertex(sf::Vector2f(-x * _zoom, -y.first * _zoom), sf::Color::Red));
		pointArray.append(sf::Vertex(sf::Vector2f(-x * _zoom, -y.second * _zoom), sf::Color::Red));

		//thickness
		pointArray.append(sf::Vertex(sf::Vector2f(x * _zoom + 0.004f, -y.first * _zoom + 0.004f), sf::Color::Red));
		pointArray.append(sf::Vertex(sf::Vector2f(x * _zoom + 0.004f, -y.second * _zoom + 0.004f), sf::Color::Red));
		pointArray.append(sf::Vertex(sf::Vector2f(-x * _zoom + 0.004f, -y.first * _zoom + 0.004f), sf::Color::Red));
		pointArray.append(sf::Vertex(sf::Vector2f(-x * _zoom + 0.004f, -y.second * _zoom + 0.004f), sf::Color::Red));

		pointArray.append(sf::Vertex(sf::Vector2f(x * _zoom - 0.004f, -y.first * _zoom - 0.004f), sf::Color::Red));
		pointArray.append(sf::Vertex(sf::Vector2f(x * _zoom - 0.004f, -y.second * _zoom - 0.004f), sf::Color::Red));
		pointArray.append(sf::Vertex(sf::Vector2f(-x * _zoom - 0.004f, -y.first * _zoom - 0.004f), sf::Color::Red));
		pointArray.append(sf::Vertex(sf::Vector2f(-x * _zoom - 0.004f, -y.second * _zoom - 0.004f), sf::Color::Red));
	}

	float x_interval = 1.139028f;
	for (int i = 1'100'000; i <= x_interval * 1'000'000; i += 4) { // [1.1 ; 1.139..], ->0.000004

		float x = i / 1'000'000.f;

		auto y = func(x);
		pointArray.append(sf::Vertex(sf::Vector2f(x * _zoom, -y.first * _zoom), sf::Color::Red));
		pointArray.append(sf::Vertex(sf::Vector2f(x * _zoom, -y.second * _zoom), sf::Color::Red));
		pointArray.append(sf::Vertex(sf::Vector2f(-x * _zoom, -y.first * _zoom), sf::Color::Red));
		pointArray.append(sf::Vertex(sf::Vector2f(-x * _zoom, -y.second * _zoom), sf::Color::Red));

		//thickness
		pointArray.append(sf::Vertex(sf::Vector2f(x * _zoom + 0.004f, -y.first * _zoom + 0.004f), sf::Color::Red));
		pointArray.append(sf::Vertex(sf::Vector2f(x * _zoom + 0.004f, -y.second * _zoom + 0.004f), sf::Color::Red));
		pointArray.append(sf::Vertex(sf::Vector2f(-x * _zoom + 0.004f, -y.first * _zoom + 0.004f), sf::Color::Red));
		pointArray.append(sf::Vertex(sf::Vector2f(-x * _zoom + 0.004f, -y.second * _zoom + 0.004f), sf::Color::Red));

		pointArray.append(sf::Vertex(sf::Vector2f(x * _zoom - 0.004f, -y.first * _zoom - 0.004f), sf::Color::Red));
		pointArray.append(sf::Vertex(sf::Vector2f(x * _zoom - 0.004f, -y.second * _zoom - 0.004f), sf::Color::Red));
		pointArray.append(sf::Vertex(sf::Vector2f(-x * _zoom - 0.004f, -y.first * _zoom - 0.004f), sf::Color::Red));
		pointArray.append(sf::Vertex(sf::Vector2f(-x * _zoom - 0.004f, -y.second * _zoom - 0.004f), sf::Color::Red));
	}

	return pointArray;
}

sf::Text Function::initFuncLabel() {
	sf::Text text(L"(x² + y² - 1)³ - x²y³ = 0", _font, 70);
	text.setFillColor(sf::Color::Black);
	text.setPosition(-text.getGlobalBounds().width / 2.f, -475);
	text.setStyle(sf::Text::Bold);

	return text;
}

sf::View Function::initView() {
	sf::View view(sf::FloatRect(0.f, 0.f, _window.getSize().x, _window.getSize().y));
	view.setCenter(0.f, 0.f);
	return view;
}

std::vector<sf::VertexArray> Function::initLines() {

	std::vector<sf::VertexArray> axisArray;

	// horisontal lines
	for (int i = -15; i <= 10; i += 5) { // [-1.5 ; 1.0], ->0.5

		float y = i / 10.f;

		sf::VertexArray line(sf::Lines, 2);

		line[0].position = sf::Vector2f(-1.8f * _zoom, y * _zoom);
		line[0].color = sf::Color::Black;
		line[1].position = sf::Vector2f(1.8f * _zoom, y * _zoom);
		line[1].color = sf::Color::Black;
		axisArray.push_back(line);
	}

	// vertical lines
	for (int i = -15; i <= 15; i += 5) { // [-1.5 ; 1.5], ->0.5

		float x = i / 10.f;

		sf::VertexArray line(sf::Lines, 2);
		line[0].position = sf::Vector2f(x * _zoom, -1.5f * _zoom);
		line[0].color = sf::Color::Black;
		line[1].position = sf::Vector2f(x * _zoom, 1.5f * _zoom);
		line[1].color = sf::Color::Black;
		axisArray.push_back(line);
	}

	return axisArray;
}

std::vector<sf::Text> Function::initSteps() {
	std::vector<sf::Text> stepArray;

	// horisontal steps
	for (int i = 15; i >= -15; i -= 5) { // [1.5 ; -1.5], -> -0.5

		float x = i / 10.f;

		std::string str = std::to_string(x);
		if (str[0] == '-') {
			str = str.substr(0, 4);
		} else {
			str = str.substr(0, 3);
		}
		if (str[str.length() - 1] == '0') {
			if (str[0] == '-') {
				str = str.substr(0, 2);
			} else {
				str = str.substr(0, 1);
			}
		}
		
		sf::Text step(str, _font, 30);
		step.setFillColor(sf::Color::Black);
		sf::Vector2f place{ -1.8f * _zoom, -x * _zoom };
		auto size = step.getGlobalBounds();
		step.setPosition(place - sf::Vector2f(size.width + 10, size.height));
		stepArray.push_back(step);
	}

	// vertical steps
	for (int i = -15; i <= 15; i += 5) { // [-1.5 ; 1.5], ->0.5

		float y = i / 10.f;

		std::string str = std::to_string(y);
		if (str[0] == '-') {
			str = str.substr(0, 4);
		} else {
			str = str.substr(0, 3);
		}
		if (str[str.length() - 1] == '0') {
			if (str[0] == '-') {
				str = str.substr(0, 2);
			} else {
				str = str.substr(0, 1);
			}
		}

		sf::Text step(str, _font, 30);
		step.setFillColor(sf::Color::Black);
		sf::Vector2f place{ y * _zoom, 1.5f * _zoom };
		step.setPosition(place + sf::Vector2f{ step.getGlobalBounds().width / -2.f, 5 });
		stepArray.push_back(step);
	}

	sf::Vector2f tempPos{ 0.f * _zoom, -1.5f * _zoom };
	sf::Text yAxis;
	yAxis.setFont(_font);
	yAxis.setPosition(tempPos + sf::Vector2f{ 5, 5 });
	yAxis.setFillColor(sf::Color::Black);
	yAxis.setString("y");
	stepArray.push_back(yAxis);

	tempPos = { 1.8f * _zoom, 0.f * _zoom };
	sf::Text xAxis;
	xAxis.setFont(_font);
	xAxis.setPosition(tempPos + sf::Vector2f{ -10, 5 });
	xAxis.setFillColor(sf::Color::Black);
	xAxis.setString("x");
	stepArray.push_back(xAxis);

	return stepArray;

}

std::vector<ThickLine> Function::initStrokes() {
	
	std::vector<ThickLine> strokeArray;

	// horisontal strokes
	for (int i = -10; i <= 10; i += 5) { // [-1.5 ; 1.0], ->0.5

		float x = i / 10.f;

		sf::Vector2f place{ 0.f * _zoom, x * _zoom };
	
		ThickLine stroke(place - sf::Vector2f(10.f, 0.f), place + sf::Vector2f(10.f, 0.f), 5.f, sf::Color::Black);
		strokeArray.push_back(stroke);
	}

	sf::Vector2f tempPos{ 0.f * _zoom, -1.5f * _zoom };

	ThickLine tempStroke(tempPos, tempPos + sf::Vector2f(10.f, 10.f), 5.f, sf::Color::Black);
	strokeArray.push_back(tempStroke);

	tempStroke = { tempPos, tempPos + sf::Vector2f(-10.f, 10.f), 5.f, sf::Color::Black };
	strokeArray.push_back(tempStroke);

	// vertical strokes
	for (int i = -15; i <= 15; i += 5) { // [-1.5 ; 1.5], ->0.5

		float y = i / 10.f;

		sf::Vector2f place{ y * _zoom, 0.f * _zoom };

		ThickLine stroke(place - sf::Vector2f(0.f, 10.f), place + sf::Vector2f(0.f, 10.f), 5.f, sf::Color::Black);
		strokeArray.push_back(stroke);
	}

	tempPos = { 1.8f * _zoom, 0.f * _zoom };

	tempStroke = { tempPos, tempPos + sf::Vector2f(-10.f, -10.f), 5.f, sf::Color::Black };
	strokeArray.push_back(tempStroke);

	tempStroke = { tempPos, tempPos + sf::Vector2f(-10.f, 10.f), 5.f, sf::Color::Black };
	strokeArray.push_back(tempStroke);

	return strokeArray;
}

void Function::run() {
	
	while (_window.isOpen()) {
		processEvents();
		render();
	}
}

void Function::processEvents() {
	sf::Event event;
	while (_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			_picture.getTexture()->copyToImage().saveToFile("graph.jpg");
			_window.close();
		}
	}
}

void Function::render() {

	_window.clear(sf::Color::White);

	_window.draw(_picture);

	_window.display();

}

