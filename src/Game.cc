#include "Game.hh"
#include "Constants.hh"
#include "Collider.hh"
#include "InputsSystem.hh"
#include "Animation.hh"
#include "Rigidbody.hh"
#include "Character.hh"
#include "Enemy.hh"
#include<iostream>
#include "TileGroup.hh"
#include "ContactEventManager.hh"

Collider* collider{new Collider(100, 100, 100, 100, sf::Color::Green, 5.f)};
sf::View view1(sf::Vector2(415.0f, 350.0f), sf::Vector2(830.0f, 700.0f));

sf::Clock* timer{new sf::Clock()};
float deltaTime{};
const float playerSpeed{600.f};
const float playerScale{4.f};

Character* character1{};
Enemy* enemy{};
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
  windowWin = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME);
  event = new sf::Event();

  //gravity = new b2Vec2(0.f, -9.8f);
  gravity = new b2Vec2(0.f, 0.f);
  world = new b2World(*gravity);
  drawPhysics = new DrawPhysics(window);
  deleteList = new std::vector<GameObject*>();
  contactEventManager = new ContactEventManager(deleteList);
  gameObjects = new std::vector<GameObject*>();

  character1 = new Character("assets/sprites.png", 0, 1, 20.f, 20.f,
  playerScale, playerSpeed, new sf::Vector2f(1245, 1750), window, world);

  character1->SetTagName("Player");
  gameObjects->push_back(character1);

  enemy = new Enemy("assets/sprites.png", 0, 0, 20.f, 20.f,
  playerScale, playerSpeed-400, new sf::Vector2f(1245, 950), window, world);

  enemy->SetTagName("Enemy");
  gameObjects->push_back(enemy);

  Walls();
  Objects();
  tileGroup = new TileGroup(window, 39, 33, "assets/t.png", "assets/maps/full.tg", 16, 16, 4.f); 
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
  for(auto& gameObject : *deleteList){
    gameObjects->erase(std::remove(gameObjects->begin(), gameObjects->end(), gameObject), gameObjects->end());
    delete gameObject;
  }
  deleteList->clear();
  window->clear(sf::Color(0, 0, 0, 255));
  Draw();
  window->display();
  
}
void Game::Init()
{
  world->SetDebugDraw(drawPhysics);
  drawPhysics->SetFlags(b2Draw::e_shapeBit);
  world->SetContactListener(contactEventManager);
  windowWin->setVisible(false);
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
    enemy->PlayerPos(sf::Vector2f(character1->GetPosition()));
    //std::cout << "enemigo X: " << enemy->GetPosition().x << " enemigo Y: " << enemy->GetPosition().y << std::endl;
    window->setView(view1);

    if(contactEventManager->GetScore() == 5)
    {
      sf::Texture* gameWin {new sf::Texture()};
      gameWin->loadFromFile("assets/win.png");
      sf::Sprite* fondoGameWin {new sf::Sprite(*gameWin)};
      window->setVisible(false);
      window->setActive(false);
      windowWin->setVisible(true);

      while (windowWin->isOpen())
      {
         while (windowWin->pollEvent(*event))
          {
            if (event->type == sf::Event::Closed)
            {
              windowWin->close();
            }
          }
            windowWin->clear(sf::Color(0, 0, 0, 255));           
            windowWin->draw(*fondoGameWin);                  
            windowWin->display();
        }
    }

    if(contactEventManager->Status())
    {
      sf::Texture* gameLose {new sf::Texture()};
      gameLose->loadFromFile("assets/lose.png");
      sf::Sprite* fondoGameLose {new sf::Sprite(*gameLose)};
      window->setVisible(false);
      window->setActive(false);
      windowWin->setVisible(true);

      while (windowWin->isOpen())
      {
         while (windowWin->pollEvent(*event))
          {
            if (event->type == sf::Event::Closed)
            {
              windowWin->close();
            }
          }
            windowWin->clear(sf::Color(0, 0, 0, 255));           
            windowWin->draw(*fondoGameLose);                  
            windowWin->display();
        }
    }

  }

  delete window;
  delete event;
}

void Game::Walls(){
  int posX[] = {30, 30+830, 30, 800+830, 802+1660, 802+1660, 825, 825+833, 825, 825+833, 828, 828+833, 828, 828+833, 195+830, 195+830, 642+830, 642+830, 410, 410+830, 410+1660, 415+830, 415, 415+1660, 415, 415+1660};
  int posY[] = {160+1600, 360, 1050, 360, 1050, 1720, 1950, 1950, 1250, 1250, 1535, 1535, 835, 835, 730+710, 732, 730+710, 732, 670+1420, 670+1420, 670+1420, 90, 90+710, 90+710, 88+1350, 90+1350};
  int weight[] = {16, 16, 16, 16, 16, 16, 32, 32, 32, 32, 32, 32, 32, 32, 64, 64, 64, 64, 176, 176, 176, 176, 176, 176, 176, 176};
  int height[] = {160, 160, 160, 160, 160, 160, 80, 80, 80, 80, 64, 64, 64, 64, 48, 48, 48, 48, 16, 16, 16, 16, 16, 16, 48, 48};

  for (int i = 0; i < sizeof(posX)/sizeof(int); i++)
  {
    wall = new GameObject("assets/t.png", 0, 0, weight[i], height[i], playerScale,
    new sf::Vector2f(posX[i], posY[i]), b2BodyType::b2_staticBody, window, world);

    wall->SetTagName("Wall");    
  }
}

void Game::Objects(){
  
  tv = new GameObject("assets/t.png", 2, 5, 32, 32, playerScale,
  new sf::Vector2f(390, 270+1400), b2BodyType::b2_staticBody, window, world);

  tv->SetTagName("TV");

  gameObjects->push_back(tv);

  chair_living1 = new GameObject("assets/t.png", 15, 14, 16, 8, playerScale,
  new sf::Vector2f(500, 440+1400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(chair_living1);
  chair_living1->SetTagName("Chair");

  chair_living1 = new GameObject("assets/t.png", 15, 15, 16, 8, playerScale,
  new sf::Vector2f(500, 470+1400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(chair_living1);
  chair_living1->SetTagName("Chair");

  chair_living1 = new GameObject("assets/t.png", 15, 14, 16, 8, playerScale,
  new sf::Vector2f(200, 500+1400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(chair_living1);
  chair_living1->SetTagName("Chair");

  chair_living1 = new GameObject("assets/t.png", 15, 15, 16, 8, playerScale,
  new sf::Vector2f(200, 530+1400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(chair_living1);
  chair_living1->SetTagName("Chair");

  bookshelf = new GameObject("assets/t.png", 13, 5, 16, 16, playerScale,
  new sf::Vector2f(350+830, 300), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);
  bookshelf->SetTagName("Bookshelf");

  bookshelf = new GameObject("assets/t.png", 14, 5, 16, 16, playerScale,
  new sf::Vector2f(415+830, 300), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);
  bookshelf->SetTagName("Bookshelf");

  bookshelf = new GameObject("assets/t.png", 13, 6, 16, 16, playerScale,
  new sf::Vector2f(350+830, 365), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);
  bookshelf->SetTagName("Bookshelf");

  bookshelf = new GameObject("assets/t.png", 14, 6, 16, 16, playerScale,
  new sf::Vector2f(415+830, 365), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);
  bookshelf->SetTagName("Bookshelf");

  bookshelf = new GameObject("assets/t.png", 13, 7, 16, 16, playerScale,
  new sf::Vector2f(350+830, 430), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);
  bookshelf->SetTagName("Bookshelf");

  bookshelf = new GameObject("assets/t.png", 14, 7, 16, 16, playerScale,
  new sf::Vector2f(415+830, 430), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);
  bookshelf->SetTagName("Bookshelf");

  bookshelf = new GameObject("assets/t.png", 13, 16, 16, 8, playerScale,
  new sf::Vector2f(350+830, 485), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);
  bookshelf->SetTagName("Bookshelf");

  bookshelf = new GameObject("assets/t.png", 14, 16, 16, 8, playerScale,
  new sf::Vector2f(415+830, 485), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bookshelf);
  bookshelf->SetTagName("Bookshelf");

  table = new GameObject("assets/t.png", 13, 3, 16, 16, playerScale,
  new sf::Vector2f(200+1660, 450+1400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(table);
  table->SetTagName("Table");

  table = new GameObject("assets/t.png", 14, 3, 16, 16, playerScale,
  new sf::Vector2f(265+1660, 450+1400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(table);
  table->SetTagName("Table");

  table = new GameObject("assets/t.png", 15, 3, 16, 16, playerScale,
  new sf::Vector2f(330+1660, 450+1400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(table);
  table->SetTagName("Table");

  table = new GameObject("assets/t.png", 13, 3, 16, 16, playerScale,
  new sf::Vector2f(500+1660, 450+1400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(table);
  table->SetTagName("Table");

  table = new GameObject("assets/t.png", 14, 3, 16, 16, playerScale,
  new sf::Vector2f(565+1660, 450+1400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(table);
  table->SetTagName("Table");

  table = new GameObject("assets/t.png", 15, 3, 16, 16, playerScale,
  new sf::Vector2f(630+1660, 450+1400), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(table);
  table->SetTagName("Table");

  wc = new GameObject("assets/t.png", 0, 6, 16, 32, playerScale,
  new sf::Vector2f(150, 150+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(wc);
  wc->SetTagName("WC");

  lavamanos = new GameObject("assets/t.png", 1, 15, 16, 16, playerScale,
  new sf::Vector2f(260, 190+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(lavamanos);
  lavamanos->SetTagName("lavamanos");

  lavamanos = new GameObject("assets/t.png", 2, 15, 16, 16, playerScale,
  new sf::Vector2f(325, 190+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(lavamanos);
  lavamanos->SetTagName("lavamanos");

  lavamanos = new GameObject("assets/t.png", 1, 29, 16, 8, playerScale,
  new sf::Vector2f(260, 140+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(lavamanos);
  lavamanos->SetTagName("lavamanos");

  lavamanos = new GameObject("assets/t.png", 2, 29, 16, 8, playerScale,
  new sf::Vector2f(325, 140+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(lavamanos);
  lavamanos->SetTagName("lavamanos");

  bed = new GameObject("assets/t.png", 14, 0, 16, 16, playerScale,
  new sf::Vector2f(590+1660, 170+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bed);
  bed->SetTagName("Bed");

  bed = new GameObject("assets/t.png", 15, 0, 16, 16, playerScale,
  new sf::Vector2f(655+1660, 170+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bed);
  bed->SetTagName("Bed");

  bed = new GameObject("assets/t.png", 14, 1, 16, 16, playerScale,
  new sf::Vector2f(590+1660, 235+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bed);
  bed->SetTagName("Bed");

  bed = new GameObject("assets/t.png", 15, 1, 16, 16, playerScale,
  new sf::Vector2f(655+1660, 235+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bed);
  bed->SetTagName("Bed");

  bed = new GameObject("assets/t.png", 14, 2, 16, 16, playerScale,
  new sf::Vector2f(590+1660, 300+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bed);
  bed->SetTagName("Bed");

  bed = new GameObject("assets/t.png", 15, 2, 16, 16, playerScale,
  new sf::Vector2f(655+1660, 300+700), b2BodyType::b2_staticBody, window, world);

  gameObjects->push_back(bed);
  bed->SetTagName("Bed");

  int posXC[] = {100, 380+830, 730+1660, 730+1660, 730}; 
  int posYC[] = {160+1400, 200, 600+1400, 170+700, 170+700};
  for (int i = 0; i < sizeof(posXC)/sizeof(int); i++)
  {
    heart = new GameObject("assets/t.png", 0, 0, 16, 16, playerScale,
    new sf::Vector2f(posXC[i], posYC[i]), b2BodyType::b2_staticBody, window, world);
    gameObjects->push_back(heart);    
    heart->SetTagName("Heart");
  }

  int posXB[] = {180, 300+1660, 300+1600}; 
  int posYB[] = {160+1400, 400+700, 465+700}; 
  for (int i = 0; i < sizeof(posXB)/sizeof(int); i++)
  {
    box1 = new GameObject("assets/t.png", 2, 5, 16, 16, playerScale,
    new sf::Vector2f(posXB[i], posYB[i]), b2BodyType::b2_staticBody, window, world);
    gameObjects->push_back(box1);    
    box1->SetTagName("Box");
  }    
}