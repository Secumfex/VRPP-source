#ifndef APPLICATIONCONTEXT_H
#define APPLICATIONCONTEXT_H

#include "Patterns/Context.h"
#include "ApplicationStates.h"

class ApplicationContext : public Context {
	public:
	void setState(ApplicationState* state);
};

#endif