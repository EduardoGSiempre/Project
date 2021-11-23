#pragma once

#include<SFML/Graphics.hpp>
#include "Rigidbody.hh"
#include "Character.hh"

class Enemy : public GameObject
{
private:
  float moveSpeed{};
  void Move();
  void FlipSprite();
  sf::Vector2f player;

public:
  Enemy(const char* textureUrl, int col, int row, float width, float height, float scale, float moveSpeed,
  sf::Vector2f* position, sf::RenderWindow*& window, b2World*& world);
  ~Enemy();

  void Update(float& deltaTime) override;
  void Draw() override;

  sf::Sprite* GetSprite() const;
  void PlayerPos(const sf::Vector2f& resource);
  
    

};