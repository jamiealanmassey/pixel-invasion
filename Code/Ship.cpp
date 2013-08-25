#include "Ship.h"
#include "Feanwork/Game.h"
#include "Feanwork/Random.h"
#include "Enemy.h"
#include "Timer.h"

Ship::Ship(int _resourceID, float _xPos, float _yPos, Object* _timer, Object* _visual) :
	Object(_resourceID, _xPos, _yPos, true)
{
	mSpawnTime = .0f;
	mTimer	   = _timer;
	mVisual	   = _visual;
}

Ship::~Ship()
{
}

bool Ship::update(Game* _game)
{
	if(mSpawnTime < 7.2f && mSpawnTime > 6.8f)
		static_cast<Timer*>(mTimer)->reset();
	if(mSpawnTime >= 10.f)
		spawn(4, _game);
	else
		mSpawnTime += _game->getDelta();

	Object::update(_game);
	return true;
}

bool Ship::render(Game* _game)
{
	Object::render(_game);
	return true;
}

void Ship::collisionCallback(sf::Vector2f _depth, sf::Vector2f _normal, Object* _collision, Game* _game)
{
}

std::vector<Object*> Ship::spawn(int _amount, Game* _game)
{
	mSpawnTime = .0f;
	std::vector<Object*> objects;
	for(unsigned i = 0; i < _amount; i++)
	{
		Random* random = Random::get_singleton();
		float xRand = random->rand_range(-0.2f, 0.2f);
		float yRand = random->rand_range(0.3f, 0.4f);

		Enemy* newEnemy = new Enemy(2, mX + 196, mY + 193, xRand, yRand, 100, mVisual);
		newEnemy->setUniqueType("Enemy");
		newEnemy->ignore(_game->getPlayer());
		_game->pushObject(newEnemy);
		_game->getPlayer()->ignore(newEnemy);
		_game->addCollisionCheck(newEnemy);
		objects.push_back(newEnemy);
	}

	std::cout << "Spawn"; // Spawn stuff
	return objects;
}
