#include "panel.h"
#include "../../engine/src/system_renderer.h"
#include "../../engine/src/system_resources.h"
#include "../Log.h"
#include "../config.h"
#include <codecvt>
#include <engine.h>

using namespace sf;

/*
* A panel which displays a rectangle with a string centered in it.
*/

//initialise everything needed
Panel::Panel(const Vector2f& pos, const Vector2f& size)
	: _size(size)
	, _position(pos)
{
	_font = Resources::get<sf::Font>(Config::getDefaultFont());
	_text.setFont(*_font);
	_text.setCharacterSize(32);
	_text.setFillColor(Color::Black);
	_text.setString("----");
	_text.setPosition(pos);
	_rect = RectangleShape(size);
	_rect.setPosition(pos);
	//_rect.setOrigin(_size/2.f);
	_rect.setFillColor(sf::Color(255, 255, 255, 128));
	_isGUI = true;
}

void Panel::update(double dt) { }

//render the panel and the text
void Panel::render()
{
	if(_isGUI)
	{
		//using a view seems to work better for GUI stuff
		_currView = Engine::getCurrentView();
		View v = View(FloatRect(_currView.getViewport().left,
								_currView.getViewport().top,
								_currView.getSize().x,
								_currView.getSize().y));
		Renderer::setView(v);
		Engine::GetWindow().draw(_rect);
		Engine::GetWindow().draw(_text);
		Renderer::setView(_currView);
	}
	else
	{
		Engine::GetWindow().draw(_rect);
		Engine::GetWindow().draw(_text);
	}
}

//repositions the text so it is in the centre of the panel
void Panel::recentreText()
{
	auto txtbounds = _text.getLocalBounds();
	auto textSize = Vector2f(txtbounds.width, txtbounds.height);
	_text.setPosition(_rect.getPosition() + (_size / 2.f) - textSize / 2.f -
					  Vector2f(0, txtbounds.top));
}

//------ SETTERS ------
//sets the text displayed in the panel
void Panel::setText(const std::string& text)
{
	_renderString = text;
	_text.setString(_renderString);
	//make sure the text is centered
	recentreText();
}

//sets non english string as the text
void Panel::setTextLocalised(const std::string& text)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	//convert to a wide string
	std::wstring wide = converter.from_bytes(text);

	_text.setString(wide);
	recentreText();
}

//sets the colour of the panel
void Panel::setPanelColour(const Color& colour) { _rect.setFillColor(colour); }

//sets the colour of the text
void Panel::setTextColour(const Color& colour) { _text.setFillColor(colour); }

//sets the position of the panel
void Panel::setPosition(const Vector2f& pos)
{
	_rect.setPosition(pos);
	recentreText();
}

//position the panel's centre without changing the origin as that may break every other panel
void Panel::setPositionOfCentre(const Vector2f& pos)
{
	auto newPos = pos - _rect.getSize() / 2.f;
	_rect.setPosition(newPos);
	recentreText();
}

//sets the size of the text
void Panel::setTextSize(int size) { _text.setCharacterSize(size); }

//sets whether the panel is a GUI panel or not
//if a panel is a GUI panel, then it "moves" with the view, i.e. it is always at a constant position within the view (e.g. the player HP)
//the enemy health bars are not GUI and they follow the enemies
void Panel::setGUI(bool value) { _isGUI = value; }

FloatRect Panel::getBoundingBox() const { return _rect.getGlobalBounds(); }

void Panel::setBorder(const float& thickness, const sf::Color& colour)
{
	_rect.setOutlineThickness(thickness);
	_rect.setOutlineColor(colour);
}

const sf::Vector2f& Panel::getPosition() const { return _position; }

const sf::Vector2f Panel::getPositionOfCentre() const
{
	auto newPos = _rect.getPosition() - _rect.getSize() / 2.f;
	return newPos;
}
