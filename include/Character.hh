#pragma once

#include<SFML/Graphics.hpp>
#include "Rigidbody.hh"
#include "GameObject.hh"

class Character : public GameObject
{
private:
  float moveSpeed{};

  void Move();
  void FlipSprite();
public:
  Character(const char* textureUrl, int col, int row, float width, float height, float scale, float moveSpeed,
  sf::Vector2f* position, sf::RenderWindow*& window, b2World*& world);
  ~Character();

  void Update(float& deltaTime) override;
  void Draw() override;

  sf::Sprite* GetSprite() const;
};