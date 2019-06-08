#pragma once
#include <SFML/Graphics.hpp>
class IGameObject {
public:
	virtual void gameTick() = 0;
	virtual void position( const sf::Vector2f& pos ) = 0;
	virtual const sf::Vector2f& position() const = 0;
	virtual const sf::Sprite& sprite() const = 0;
};