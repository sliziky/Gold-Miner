#pragma once

#include <SFML/Graphics.hpp>
#include "IGameObject.h"

class Block : public IGameObject {
public:
	Block( const std::string& file, const sf::Vector2f& pos );
	const sf::Sprite& sprite() const override;
	sf::Sprite& sprite() { return m_sprite; }
	void gameTick() override;
	void position( const sf::Vector2f& pos );
	const sf::Vector2f& position() const;
private:
	sf::Vector2f m_position;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};