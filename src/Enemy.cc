#include "Enemy.hh"
#include "Animation.hh"
#include "Character.hh"

Animation* EnemyAnimation{new Animation()};

Enemy::Enemy(const char* textureUrl, int col, int row, float width, float height, float scale, float moveSpeed,
sf::Vector2f* position, sf::RenderWindow*& window, b2World*& world) :
GameObject(textureUrl, col, row, width, height, scale, position, b2BodyType::b2_dynamicBody, window, world)
{
  this->moveSpeed = moveSpeed;
  rigidbody->SetRotationFreeze(true);

  EnemyAnimation = new Animation(0, 10, drawable, 0.1f, 0);
}

Enemy::~Enemy()
{
}

void Enemy::Draw()
{
  GameObject::Draw();
}

void Enemy::Update(float& deltaTime)
{
  GameObject::Update(deltaTime);
  FlipSprite();
  Move();
  EnemyAnimation->Play(deltaTime);
}

void Enemy::FlipSprite()
{
    drawable->GetSprite()->setScale(this->GetPosition().x < player.x ? scale :
    this->GetPosition().x > player.x ? -scale :
    drawable->GetSprite()->getScale().x, drawable->GetSprite()->getScale().y);
}

void Enemy::Move()
{
    if(this->GetPosition().x < player.x){
      if(this->GetPosition().y < player.y)
        rigidbody->Move(b2Vec2(1 * moveSpeed, 1 * moveSpeed));
      else
        rigidbody->Move(b2Vec2(1 * moveSpeed, -1 * moveSpeed));
    }
    else{
      if(this->GetPosition().y < player.y)
        rigidbody->Move(b2Vec2(-1 * moveSpeed, 1 * moveSpeed));
      else
        rigidbody->Move(b2Vec2(-1 * moveSpeed, -1 * moveSpeed));
    }
}

sf::Sprite* Enemy::GetSprite() const
{
  return drawable->GetSprite();
}

void Enemy::PlayerPos(const sf::Vector2f& resource){

    this->player = resource;
}




