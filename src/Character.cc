#include "Character.hh"
#include "InputsSystem.hh"
#include "Animation.hh"

Animation* idleAnimation{new Animation()};
Animation* runAnimation{new Animation()};

Character::Character(const char* textureUrl, int col, int row, float width, float height, float scale, float moveSpeed,
sf::Vector2f* position, sf::RenderWindow*& window, b2World*& world) :
GameObject(textureUrl, col, row, width, height, scale, position, b2BodyType::b2_dynamicBody, window, world)
{
  this->moveSpeed = moveSpeed;

  rigidbody->SetRotationFreeze(true);

  idleAnimation = new Animation(0, 5, drawable, 0.05f, 5);
  runAnimation = new Animation(0, 5, drawable, 0.08f, 6);
}

Character::~Character()
{
}

void Character::Draw()
{
  GameObject::Draw();
}

void Character::Update(float& deltaTime)
{
  GameObject::Update(deltaTime);

  FlipSprite();
  Move();

  if(std::abs(InputsSystem::GetAxis().x) || std::abs(InputsSystem::GetAxis().y))
  {
    runAnimation->Play(deltaTime);
  }
  else
  {
    idleAnimation->Play(deltaTime);
  }
}

void Character::FlipSprite()
{
    drawable->GetSprite()->setScale(InputsSystem::GetAxis().x > 0 ? scale :
    InputsSystem::GetAxis().x < 0 ? -scale :
    drawable->GetSprite()->getScale().x, drawable->GetSprite()->getScale().y);
}

void Character::Move()
{
  rigidbody->Move(b2Vec2(InputsSystem::GetAxis().x * moveSpeed, InputsSystem::GetAxis().y * moveSpeed));
}

sf::Sprite* Character::GetSprite() const
{
  return drawable->GetSprite();
}
