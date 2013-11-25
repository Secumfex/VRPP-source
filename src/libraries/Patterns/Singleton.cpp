#include "Singleton.h"

C* Singleton::getInstance ()
    {
       if (!_instance)
          _instance = new C ();
       return _instance;
    }

Singleton::Singleton(){}
Singleton::~Singleton()
    {
       _instance = 0;
    }


void ConcreteSingleton::helloWorld(){
 cout<<"Hallo Welt, Ich bin die einzige Instanz von ConcreteSingleton!"<<endl;
}

ConcreteSingleton::ConcreteSingleton(){}
ConcreteSingleton::~ConcreteSingleton(){}

