#include "ContactEventManager.hh"
#include "GameObject.hh"
#include<iostream>

ContactEventManager::ContactEventManager(std::vector<GameObject*>*& deleteList)
{
    this->deleteList = deleteList;
    this->cont = 0;
}

ContactEventManager::~ContactEventManager()
{
}

void ContactEventManager::BeginContact(b2Contact *contact)
{
  GameObject* actorA{(GameObject*)contact->GetFixtureA()->GetBody()->GetUserData().pointer};
  GameObject* actorB{(GameObject*)contact->GetFixtureB()->GetBody()->GetUserData().pointer};

  std::string objeto = actorB->GetTagName();

  if(actorA && actorB)
  {
    std::cout << "collision: " << actorA->GetTagName() << ", " << actorB->GetTagName() << std::endl;

    if(objeto == "Heart"){
        cont=cont+1;
        std::cout << "agarraste corazón :" << cont << std::endl;
        deleteList->push_back(actorB);
      }

    if(objeto == "Enemy"){
        std::cout << "Inserte pantalla de derrota :" << cont << std::endl;
      }  
  }
    
    if(cont==5){
        std::cout << "inserte pantalla de victoria " << std::endl;
    }
}
void ContactEventManager::EndContact(b2Contact *contact)
{

}

