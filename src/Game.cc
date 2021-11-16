#include "Game.hh"
#include "Constants.hh"
#include "Collider.hh"
#include "InputsSystem.hh"
#include "Animation.hh"
#include "Rigidbody.hh"
#include "Character.hh"
#include<iostream>
#include "TileGroup.hh"

Collider* collider{new Collider(100, 100, 100, 100, sf::Color::Green, 5.f)};

sf::Clock* timer{new sf::Clock()};
float deltaTime{};
const float playerSpeed{200.f};
const float playerScale{4.f};

Character* character1{};
GameObject* tv{};
GameObject* chair_living1{};
GameObject* chair_living2{};
GameObject* chair_living3{};
GameObject* chair_living4{};
GameObject* box1{};
GameObject* heart{};
GameObject* bookshelf{};
GameObject* table{};
GameObject* bed{};
GameObject* wc{};
GameObject* lavamanos{};

TileGroup* tileGroup{};

Game::Game()
{
  window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME);
  event = new sf::Event();

  //gravity = new b2Vec2(0.f, -9.8f);
  gravity = new b2Vec2(0.f, 0.f);
  world = new b2World(*gravity);
  drawPhysics = new DrawPhysics(window);
  gameObjects = new std::vector<GameObject*>();

  character1 = new Character("assets/sprites.png", 0, 5, 16.f, 16.f,
  playerScale, playerSpeed, new sf::Vector2f(100, 100), window, world);

  /*living room
  tv = new GameObject("assets/t.png", 2, 5, 32, 32, playerScale,
  new sf::Vector2f(390, 270), b2BodyType::b2_staticBody, window, world);

  chair_living1 = new GameObject("assets/t.png", 15, 14, 16, 8, playerScale,
  new sf::Vector2f(500, 440), b2BodyType::b2_staticBody, window, world);

  chair_living2 = new GameObject("assets/t.png", 15, 15, 16, 8, playerScale,
  new sf::Vector2f(500, 470), b2BodyType::b2_staticBody, window, world);

  chair_living3 = new GameObject("assets/t.png", 15, 14, 16, 8, playerScale,
  new sf::Vector2f(200, 500), b2BodyType::b2_staticBody, window, world);

  chair_living4 = new GameObject("assets/t.png", 15, 15, 16, 8, playerScale,
  new sf::Vector2f(200, 530), b2BodyType::b2_staticBody, window, world);

  box1 = new GameObject("assets/t.png", 2, 5, 16, 16, playerScale,
  new sf::Vector2f(180, 160), b2BodyType::b2_staticBody, window, world);

  heart = new GameObject("assets/t.png", 0, 0, 16, 16, playerScale,
  new sf::Vector2f(100, 160), b2BodyType::b2_staticBody, window, world);*/

  /*
  //library
  //1
  bookshelf = new GameObject("assets/t.png", 13, 5, 16, 16, playerScale,
  new sf::Vector2f(530, 270), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);

  bookshelf = new GameObject("assets/t.png", 14, 5, 16, 16, playerScale,
  new sf::Vector2f(595, 270), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);

  bookshelf = new GameObject("assets/t.png", 13, 6, 16, 16, playerScale,
  new sf::Vector2f(530, 335), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);

  bookshelf = new GameObject("assets/t.png", 14, 6, 16, 16, playerScale,
  new sf::Vector2f(595, 335), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);

  bookshelf = new GameObject("assets/t.png", 13, 7, 16, 16, playerScale,
  new sf::Vector2f(530, 400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);

  bookshelf = new GameObject("assets/t.png", 14, 7, 16, 16, playerScale,
  new sf::Vector2f(595, 400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);

  bookshelf = new GameObject("assets/t.png", 13, 16, 16, 8, playerScale,
  new sf::Vector2f(530, 450), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);

  bookshelf = new GameObject("assets/t.png", 14, 16, 16, 8, playerScale,
  new sf::Vector2f(595, 450), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);

  //2
  bookshelf = new GameObject("assets/t.png", 13, 5, 16, 16, playerScale,
  new sf::Vector2f(170, 270), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);

  bookshelf = new GameObject("assets/t.png", 14, 5, 16, 16, playerScale,
  new sf::Vector2f(235, 270), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);

  bookshelf = new GameObject("assets/t.png", 13, 6, 16, 16, playerScale,
  new sf::Vector2f(170, 335), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);

  bookshelf = new GameObject("assets/t.png", 14, 6, 16, 16, playerScale,
  new sf::Vector2f(235, 335), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);

  bookshelf = new GameObject("assets/t.png", 13, 7, 16, 16, playerScale,
  new sf::Vector2f(170, 400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);

  bookshelf = new GameObject("assets/t.png", 14, 7, 16, 16, playerScale,
  new sf::Vector2f(235, 400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);

  bookshelf = new GameObject("assets/t.png", 13, 16, 16, 8, playerScale,
  new sf::Vector2f(170, 450), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);

  bookshelf = new GameObject("assets/t.png", 14, 16, 16, 8, playerScale,
  new sf::Vector2f(235, 450), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);

  heart = new GameObject("assets/t.png", 0, 0, 16, 16, playerScale,
  new sf::Vector2f(380, 230), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(heart);
  */

  /*
  //kitchen
  //1
  table = new GameObject("assets/t.png", 13, 3, 16, 16, playerScale,
  new sf::Vector2f(200, 450), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(table);

  table = new GameObject("assets/t.png", 14, 3, 16, 16, playerScale,
  new sf::Vector2f(265, 450), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(table);

  table = new GameObject("assets/t.png", 15, 3, 16, 16, playerScale,
  new sf::Vector2f(330, 450), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(table);

  //2
  table = new GameObject("assets/t.png", 13, 3, 16, 16, playerScale,
  new sf::Vector2f(500, 450), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(table);

  table = new GameObject("assets/t.png", 14, 3, 16, 16, playerScale,
  new sf::Vector2f(565, 450), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(table);

  table = new GameObject("assets/t.png", 15, 3, 16, 16, playerScale,
  new sf::Vector2f(630, 450), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(table);

  heart = new GameObject("assets/t.png", 0, 0, 16, 16, playerScale,
  new sf::Vector2f(730, 600), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(heart);
  */

  /*
  //room 1
  bed = new GameObject("assets/t.png", 14, 0, 16, 16, playerScale,
  new sf::Vector2f(590, 170), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bed);

  bed = new GameObject("assets/t.png", 15, 0, 16, 16, playerScale,
  new sf::Vector2f(655, 170), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bed);

  bed = new GameObject("assets/t.png", 14, 1, 16, 16, playerScale,
  new sf::Vector2f(590, 235), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bed);

  bed = new GameObject("assets/t.png", 15, 1, 16, 16, playerScale,
  new sf::Vector2f(655, 235), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bed);

  bed = new GameObject("assets/t.png", 14, 2, 16, 16, playerScale,
  new sf::Vector2f(590, 300), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bed);

  bed = new GameObject("assets/t.png", 15, 2, 16, 16, playerScale,
  new sf::Vector2f(655, 300), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bed);

  box1 = new GameObject("assets/t.png", 2, 5, 16, 16, playerScale,
  new sf::Vector2f(300, 400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(box1);

  box1 = new GameObject("assets/t.png", 2, 5, 16, 16, playerScale,
  new sf::Vector2f(300, 465), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(box1);

  heart = new GameObject("assets/t.png", 0, 0, 16, 16, playerScale,
  new sf::Vector2f(730, 170), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(heart);
  */

  /*
  //room 2
  bed = new GameObject("assets/t.png", 14, 0, 16, 16, playerScale,
  new sf::Vector2f(290, 470), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bed);

  bed = new GameObject("assets/t.png", 15, 0, 16, 16, playerScale,
  new sf::Vector2f(355, 405), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bed);

  bed = new GameObject("assets/t.png", 14, 1, 16, 16, playerScale,
  new sf::Vector2f(290, 405), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bed);

  bed = new GameObject("assets/t.png", 15, 1, 16, 16, playerScale,
  new sf::Vector2f(355, 405), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bed);

  bed = new GameObject("assets/t.png", 14, 2, 16, 16, playerScale,
  new sf::Vector2f(290, 470), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bed);

  bed = new GameObject("assets/t.png", 15, 2, 16, 16, playerScale,
  new sf::Vector2f(355, 470), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bed);
  */

 /*
 //bathroom
  wc = new GameObject("assets/t.png", 0, 6, 16, 32, playerScale,
  new sf::Vector2f(150, 150), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(wc);

  lavamanos = new GameObject("assets/t.png", 1, 15, 16, 16, playerScale,
  new sf::Vector2f(260, 190), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(lavamanos);

  lavamanos = new GameObject("assets/t.png", 2, 15, 16, 16, playerScale,
  new sf::Vector2f(325, 190), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(lavamanos);

  lavamanos = new GameObject("assets/t.png", 1, 29, 16, 8, playerScale,
  new sf::Vector2f(260, 140), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(lavamanos);

  lavamanos = new GameObject("assets/t.png", 2, 29, 16, 8, playerScale,
  new sf::Vector2f(325, 140), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(lavamanos);
  */

  heart = new GameObject("assets/t.png", 0, 0, 16, 16, playerScale,
  new sf::Vector2f(550, 370), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(heart);

  tileGroup = new TileGroup(window, 13, 11, "assets/t.png", "assets/maps/main.tg", 16, 16, 4.f);

  gameObjects->push_back(character1);
  
}

Game::~Game()
{
}

void Game::Inputs()
{

}

void Game::Draw()
{
  tileGroup->Draw();
  for(auto& gameObject : *gameObjects)
  {
    gameObject->Draw();
  }
  world->DebugDraw();
}

void Game::Render()
{
  window->clear(sf::Color(0, 0, 0, 255));
  Draw();
  window->display();
}
void Game::Init()
{
  world->SetDebugDraw(drawPhysics);
  drawPhysics->SetFlags(b2Draw::e_shapeBit);
  Update();
}

void Game::UpdatePhysics()
{
  world->ClearForces();
  world->Step(deltaTime, 8, 8);
  //std::cout << deltaTime << std::endl;
}

void Game::Update()
{
  while (window->isOpen())
  {
    while (window->pollEvent(*event))
    {
      if(event->type == sf::Event::Closed)
      {
        window->close();
      }
    }
    deltaTime = timer->getElapsedTime().asSeconds();
    timer->restart();

    UpdatePhysics();

    Inputs();

    for(auto& gameObject : *gameObjects)
    {
      gameObject->Update(deltaTime);
    }
    Render();
  }

  delete window;
  delete event;
}