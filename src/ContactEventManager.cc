#include "ContactEventManager.hh"
#include "GameObject.hh"
#include<iostream>

ContactEventManager::ContactEventManager(std::vector<GameObject*>*& deleteList)
{
    this->deleteList = deleteList;
    this->cont = 0;
    this->caught = false;
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
    if(objeto == "Heart"){
        cont=cont+1;
        std::cout << "agarraste corazón :" << cont << std::endl;
        deleteList->push_back(actorB);
      }

    if(objeto == "Enemy"){
        caught=true;
      }  
  }
}
void ContactEventManager::EndContact(b2Contact *contact)
{

}

int ContactEventManager::GetScore(){
  return cont;
}

bool ContactEventManager::Status(){
  return caught;
}

