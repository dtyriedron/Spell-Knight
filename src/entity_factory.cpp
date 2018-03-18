#include "entity_factory.h"
#include "components/cmp_player_physics.h"
#include "components/cmp_player_animated_sprite.h"
#include "components/cmp_animated_sprite.h"
#include "components/cmp_enemy_ai.h"
#include "components/cmp_hurt_player.h"
#include "components/cmp_enemy_animated_sprite.h"
#include "components/cmp_player_lives.h"
#include "components/cmp_player_bullet.h"
#include "components/cmp_enemy_physics.h"
#include "components/cmp_physics.h"
#include "../engine/lib_tile_level_loader/LevelSystem.h"
#include "../engine/lib_texture_manager/TextureManager.h"
#include "components/cmp_pickup.h"
#include "components/cmp_score.h"

using namespace sf;

/*
* Factory class for easier creation of entities.
*/

//creates the player at position pos in Scene scene
std::shared_ptr<Entity> EntityFactory::makePlayer(Scene* scene, const Vector2f& pos) {
    auto player = scene->makeEntity();
    player->setPosition(pos);
    player->addTag("player");
  
    player->addComponent<PlayerAnimatedSpriteComponent>(64, 64);
    player->addComponent<PlayerPhysicsComponent>(Vector2f(27.f, 62.f));
    player->addComponent<PlayerBulletComponent>();
    player->addComponent<PlayerLivesComponent>(3);
    player->addComponent<PlayerScoreComponent>();

    return player;
}

//creates a snake enemy at position pos in Scene scene
std::shared_ptr<Entity> EntityFactory::makeSlime(Scene* scene, const Vector2f& pos) {
    auto slime = scene->makeEntity();
    slime->addTag("enemy");
    // set position
    slime->setPosition(pos);
    auto anim = slime->addComponent<AnimatedSpriteComponent>(32, 32);
    anim->setSpritesheet(TextureManager::getTexture("slime.png"));
    anim->setNumberOfFrames(4);
    // Add HurtComponent
    slime->addComponent<HurtComponent>();
    // Add EnemyAIComponent
    //slime->addComponent<EnemyAIComponent>();
	//slime->addComponent<EnemyPhysicsComponent>(Vector2f(32.f, 32.f), false);
    auto physics = slime->addComponent<PhysicsComponent>(true, Vector2f(32.f, 32.f));
    physics->setLinearVelocity(Vector2f(10.f, 0.f));

    return slime;
}

//creates an eye demon enemy at position pos in Scene scene
std::shared_ptr<Entity> EntityFactory::makeEyeDemon(Scene* scene, const sf::Vector2f& pos) {
    auto eyeDemon = scene->makeEntity();
    eyeDemon->addTag("enemy");
    eyeDemon->setPosition(pos);
    auto anim = eyeDemon->addComponent<AnimatedSpriteComponent>(64, 37);
    anim->setSpritesheet(TextureManager::getTexture("sheet_eye_flyer.png"));
    anim->setNumberOfFrames(5);
    eyeDemon->addComponent<HurtComponent>();
    //eyeDemon->addComponent<EnemyAIComponent>();
    eyeDemon->addComponent<EnemyPhysicsComponent>(Vector2f(64.f, 37.f), true);

    return eyeDemon;
}

//creates the physics colliders for the tiles in the currently loaded level in Scene scene
void EntityFactory::makeWalls(Scene* scene) {
    auto walls = (ls::getGroundTiles());
    for (auto w : walls) {  
        auto pos = ls::getTilePosition(w);
        pos += Vector2f(16.f, 16.f); //offset to center
        
        auto e = scene->makeEntity();
        e->setPosition(pos);
        e->addComponent<PhysicsComponent>(false, Vector2f(32.f, 32.f));
  }
}

//makes a collectible in Scene scene at position pos
std::shared_ptr<Entity> EntityFactory::makePowerUp(Scene* scene, sf::Vector2f& pos) {
    auto pu = scene->makeEntity();
    pu->setPosition(pos);
    pu->addComponent<PickUpComponent>();

    auto anim = pu->addComponent<AnimatedSpriteComponent>(32, 32);
    anim->setSpritesheet(TextureManager::getTexture("flame.png"));
    anim->setNumberOfFrames(4);
    anim->setFrameTime(0.1f);

    return pu;
}