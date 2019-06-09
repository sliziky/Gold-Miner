#include <vector>
#include <memory>
#include "IGameObject.h"
#include "Player.h"



bool collision_detection( Player& player, std::vector< std::vector< std::unique_ptr< IGameObject > > >& map ) {
	auto& player_sprite = player.animations().animated_sprite();
	for ( const auto& row : map ) {
		for ( const auto& block : row ) {
			if ( block->sprite().getGlobalBounds().intersects( player_sprite.getGlobalBounds() ) ) {
				return true;
			}
		}
	}
	return false;
}

