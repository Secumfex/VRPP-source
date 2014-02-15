#include "PhysicWorldSimulationListener.h"
#include "PhysicWorld.h"
#include <iostream>

using namespace std;

PhysicWorldSimulationListener::PhysicWorldSimulationListener(){

}

void PhysicWorldSimulationListener::update(){

	PhysicWorld* physicWorld = PhysicWorld::getInstance();
	physicWorld->dynamicsWorld->stepSimulation(0.1,5,0.02);
}
