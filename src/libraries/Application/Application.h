#ifndef APPLICATION_H
#define APPLICATION_H

#include "ApplicationContext.h"
#include "Patterns/Singleton.h"

//Application is a Singleton State Machine (ApplicationContext) 
class Application : public Singleton<Application>, public ApplicationContext{
friend class Singleton<Application>;

Application();

};

#endif
