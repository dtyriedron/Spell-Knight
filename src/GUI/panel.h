#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>
#include <memory>

class Panel
{
protected:
	sf::Vector2f _size;
	sf::Vector2f _position;
	std::string _renderString;
	sf::RectangleShape _rect;
	sf::Text _text;
	std::shared_ptr<sf::Font> _font;
	bool _isGUI;
	sf::View _currView;

	void recentreText();

public:
	Panel() = default;
	Panel(const sf::Vector2f& pos, const sf::Vector2f& size);
	~Panel() = default;

	void update(double dt);
	void render();

	void setText(const std::string& text);
	void setPanelColour(const sf::Color& colour);
	void setTextColour(const sf::Color& colour);
	void setPosition(const sf::Vector2f& pos);
	void setBorder(const float& thickness, const sf::Color& colour);
	void setTextSize(int size);
	void setGUI(bool value);
	sf::FloatRect getBoundingBox() const;
	void setTextLocalised(const std::string& text);
	void setPositionOfCentre(const sf::Vector2f& pos);

	const sf::Vector2f& getPosition() const;
	const sf::Vector2f getPositionOfCentre() const;
};