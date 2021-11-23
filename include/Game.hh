#pragma once
#include<SFML/Graphics.hpp>
#include<box2d/box2d.h>
#include "DrawPhysics.hh"
#include "GameObject.hh"
#include "ContactEventManager.hh"

class Game
{
private:
  sf::RenderWindow* window{};
  sf::Event* event{};
  b2Vec2* gravity{};
  b2World* world{};
  b2Draw* drawPhysics{};
  std::vector<GameObject*>* gameObjects;
  ContactEventManager* contactEventManager{};
public:
  Game();
  ~Game();

  void UpdatePhysics();
  void Render();
  void Init();
  void Update();
  void Draw();
  void Inputs();
  void Walls();
  void Objects();
};
