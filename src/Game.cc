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
sf::View view1(sf::Vector2(415.0f, 350.0f), sf::Vector2(830.0f, 700.0f));

sf::Clock* timer{new sf::Clock()};
float deltaTime{};
const float playerSpeed{600.f};
const float playerScale{4.f};

Character* character1{};
GameObject* tv{};
GameObject* chair_living1{};
GameObject* box1{};
GameObject* heart{};
GameObject* bookshelf{};
GameObject* table{};
GameObject* bed{};
GameObject* wc{};
GameObject* lavamanos{};
GameObject* wall{};

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
  playerScale, playerSpeed, new sf::Vector2f(1245, 1750), window, world);

  //walls

  //pared izquierda completa
  wall = new GameObject("assets/t.png", 0, 0, 16, 160, playerScale,
  new sf::Vector2f(30, 160+1600), b2BodyType::b2_staticBody, window, world);

  wall = new GameObject("assets/t.png", 0, 0, 16, 160, playerScale,
  new sf::Vector2f(30+830, 360), b2BodyType::b2_staticBody, window, world);

  wall = new GameObject("assets/t.png", 0, 0, 16, 160, playerScale,
  new sf::Vector2f(30, 1050), b2BodyType::b2_staticBody, window, world);
  
  //pared derecha completa

  wall = new GameObject("assets/t.png", 0, 0, 16, 160, playerScale,
  new sf::Vector2f(800+830, 360), b2BodyType::b2_staticBody, window, world);

  wall = new GameObject("assets/t.png", 0, 0, 16, 160, playerScale,
  new sf::Vector2f(802+1660, 1050), b2BodyType::b2_staticBody, window, world);

  wall = new GameObject("assets/t.png", 0, 0, 16, 160, playerScale,
  new sf::Vector2f(802+1660, 1720), b2BodyType::b2_staticBody, window, world);

  //puerta abajo
  wall = new GameObject("assets/t.png", 0, 0, 32, 80, playerScale,
  new sf::Vector2f(825, 1950), b2BodyType::b2_staticBody, window, world);

  wall = new GameObject("assets/t.png", 0, 0, 32, 80, playerScale,
  new sf::Vector2f(825+833, 1950), b2BodyType::b2_staticBody, window, world);

  wall = new GameObject("assets/t.png", 0, 0, 32, 80, playerScale,
  new sf::Vector2f(825, 1250), b2BodyType::b2_staticBody, window, world);

  wall = new GameObject("assets/t.png", 0, 0, 32, 80, playerScale,
  new sf::Vector2f(825+833, 1250), b2BodyType::b2_staticBody, window, world);

  //puerta arriba
  wall = new GameObject("assets/t.png", 0, 0, 32, 64, playerScale,
  new sf::Vector2f(828, 1535), b2BodyType::b2_staticBody, window, world);

  wall = new GameObject("assets/t.png", 0, 0, 32, 64, playerScale,
  new sf::Vector2f(828+833, 1535), b2BodyType::b2_staticBody, window, world);

  wall = new GameObject("assets/t.png", 0, 0, 32, 64, playerScale,
  new sf::Vector2f(828, 835), b2BodyType::b2_staticBody, window, world);

  wall = new GameObject("assets/t.png", 0, 0, 32, 64, playerScale,
  new sf::Vector2f(828+833, 835), b2BodyType::b2_staticBody, window, world);


  //puerta izquierda
  wall = new GameObject("assets/t.png", 0, 0, 64, 48, playerScale,
  new sf::Vector2f(195+830, 730+710), b2BodyType::b2_staticBody, window, world);

  wall = new GameObject("assets/t.png", 0, 0, 64, 48, playerScale,
  new sf::Vector2f(195+830, 732), b2BodyType::b2_staticBody, window, world);

  //puerta derecha

  wall = new GameObject("assets/t.png", 0, 0, 64, 48, playerScale,
  new sf::Vector2f(642+830, 730+710), b2BodyType::b2_staticBody, window, world);

  wall = new GameObject("assets/t.png", 0, 0, 64, 48, playerScale,
  new sf::Vector2f(642+830, 732), b2BodyType::b2_staticBody, window, world);

  //parte de abajo completa
  wall = new GameObject("assets/t.png", 0, 0, 176, 16, playerScale,
  new sf::Vector2f(410, 670+1420), b2BodyType::b2_staticBody, window, world);

  wall = new GameObject("assets/t.png", 0, 0, 176, 16, playerScale,
  new sf::Vector2f(410+830, 670+1420), b2BodyType::b2_staticBody, window, world);

  wall = new GameObject("assets/t.png", 0, 0, 176, 16, playerScale,
  new sf::Vector2f(410+1660, 670+1420), b2BodyType::b2_staticBody, window, world);

  //parte arriba completa 
  wall = new GameObject("assets/t.png", 0, 0, 176, 16, playerScale,
  new sf::Vector2f(415+830, 90), b2BodyType::b2_staticBody, window, world);

  wall = new GameObject("assets/t.png", 0, 0, 176, 16, playerScale,
  new sf::Vector2f(415, 90+710), b2BodyType::b2_staticBody, window, world);

  wall = new GameObject("assets/t.png", 0, 0, 176, 16, playerScale,
  new sf::Vector2f(415+1660, 90+710), b2BodyType::b2_staticBody, window, world);

  wall = new GameObject("assets/t.png", 0, 0, 176, 48, playerScale,
  new sf::Vector2f(415, 88+1350), b2BodyType::b2_staticBody, window, world);

  wall = new GameObject("assets/t.png", 0, 0, 176, 48, playerScale,
  new sf::Vector2f(415+1660, 90+1350), b2BodyType::b2_staticBody, window, world);     


  //living room
  tv = new GameObject("assets/t.png", 2, 5, 32, 32, playerScale,
  new sf::Vector2f(390, 270+1400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(tv);

  chair_living1 = new GameObject("assets/t.png", 15, 14, 16, 8, playerScale,
  new sf::Vector2f(500, 440+1400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(chair_living1);

  chair_living1 = new GameObject("assets/t.png", 15, 15, 16, 8, playerScale,
  new sf::Vector2f(500, 470+1400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(chair_living1);

  chair_living1 = new GameObject("assets/t.png", 15, 14, 16, 8, playerScale,
  new sf::Vector2f(200, 500+1400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(chair_living1);

  chair_living1 = new GameObject("assets/t.png", 15, 15, 16, 8, playerScale,
  new sf::Vector2f(200, 530+1400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(chair_living1);

  box1 = new GameObject("assets/t.png", 2, 5, 16, 16, playerScale,
  new sf::Vector2f(180, 160+1400), b2BodyType::b2_staticBody, window, world);

   gameObjects->push_back(box1);

  heart = new GameObject("assets/t.png", 0, 0, 16, 16, playerScale,
  new sf::Vector2f(100, 160+1400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(heart);

  //library
  //1
  bookshelf = new GameObject("assets/t.png", 13, 5, 16, 16, playerScale,
  new sf::Vector2f(350+830, 300), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);

  bookshelf = new GameObject("assets/t.png", 14, 5, 16, 16, playerScale,
  new sf::Vector2f(415+830, 300), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);

  bookshelf = new GameObject("assets/t.png", 13, 6, 16, 16, playerScale,
  new sf::Vector2f(350+830, 365), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);

  bookshelf = new GameObject("assets/t.png", 14, 6, 16, 16, playerScale,
  new sf::Vector2f(415+830, 365), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);

  bookshelf = new GameObject("assets/t.png", 13, 7, 16, 16, playerScale,
  new sf::Vector2f(350+830, 430), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);

  bookshelf = new GameObject("assets/t.png", 14, 7, 16, 16, playerScale,
  new sf::Vector2f(415+830, 430), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);

  bookshelf = new GameObject("assets/t.png", 13, 16, 16, 8, playerScale,
  new sf::Vector2f(350+830, 485), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);

  bookshelf = new GameObject("assets/t.png", 14, 16, 16, 8, playerScale,
  new sf::Vector2f(415+830, 485), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);

  heart = new GameObject("assets/t.png", 0, 0, 16, 16, playerScale,
  new sf::Vector2f(380+830, 200), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(heart);

  //kitchen
  //1
  table = new GameObject("assets/t.png", 13, 3, 16, 16, playerScale,
  new sf::Vector2f(200+1660, 450+1400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(table);

  table = new GameObject("assets/t.png", 14, 3, 16, 16, playerScale,
  new sf::Vector2f(265+1660, 450+1400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(table);

  table = new GameObject("assets/t.png", 15, 3, 16, 16, playerScale,
  new sf::Vector2f(330+1660, 450+1400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(table);

  //2
  table = new GameObject("assets/t.png", 13, 3, 16, 16, playerScale,
  new sf::Vector2f(500+1660, 450+1400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(table);

  table = new GameObject("assets/t.png", 14, 3, 16, 16, playerScale,
  new sf::Vector2f(565+1660, 450+1400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(table);

  table = new GameObject("assets/t.png", 15, 3, 16, 16, playerScale,
  new sf::Vector2f(630+1660, 450+1400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(table);

  heart = new GameObject("assets/t.png", 0, 0, 16, 16, playerScale,
  new sf::Vector2f(730+1660, 600+1400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(heart);

  //room 1
  bed = new GameObject("assets/t.png", 14, 0, 16, 16, playerScale,
  new sf::Vector2f(590+1660, 170+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bed);

  bed = new GameObject("assets/t.png", 15, 0, 16, 16, playerScale,
  new sf::Vector2f(655+1660, 170+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bed);

  bed = new GameObject("assets/t.png", 14, 1, 16, 16, playerScale,
  new sf::Vector2f(590+1660, 235+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bed);

  bed = new GameObject("assets/t.png", 15, 1, 16, 16, playerScale,
  new sf::Vector2f(655+1660, 235+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bed);

  bed = new GameObject("assets/t.png", 14, 2, 16, 16, playerScale,
  new sf::Vector2f(590+1660, 300+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bed);

  bed = new GameObject("assets/t.png", 15, 2, 16, 16, playerScale,
  new sf::Vector2f(655+1660, 300+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bed);

  box1 = new GameObject("assets/t.png", 2, 5, 16, 16, playerScale,
  new sf::Vector2f(300+1660, 400+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(box1);

  box1 = new GameObject("assets/t.png", 2, 5, 16, 16, playerScale,
  new sf::Vector2f(300+1660, 465+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(box1);

  heart = new GameObject("assets/t.png", 0, 0, 16, 16, playerScale,
  new sf::Vector2f(730+1660, 170+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(heart);

 //bathroom
  wc = new GameObject("assets/t.png", 0, 6, 16, 32, playerScale,
  new sf::Vector2f(150, 150+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(wc);

  lavamanos = new GameObject("assets/t.png", 1, 15, 16, 16, playerScale,
  new sf::Vector2f(260, 190+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(lavamanos);

  lavamanos = new GameObject("assets/t.png", 2, 15, 16, 16, playerScale,
  new sf::Vector2f(325, 190+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(lavamanos);

  lavamanos = new GameObject("assets/t.png", 1, 29, 16, 8, playerScale,
  new sf::Vector2f(260, 140+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(lavamanos);

  lavamanos = new GameObject("assets/t.png", 2, 29, 16, 8, playerScale,
  new sf::Vector2f(325, 140+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(lavamanos);

  heart = new GameObject("assets/t.png", 0, 0, 16, 16, playerScale,
  new sf::Vector2f(730, 170+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(heart);

  tileGroup = new TileGroup(window, 39, 33, "assets/t.png", "assets/maps/full.tg", 16, 16, 4.f);

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

    view1.setCenter(character1->GetPosition());
    window->setView(view1);

  }

  delete window;
  delete event;
}