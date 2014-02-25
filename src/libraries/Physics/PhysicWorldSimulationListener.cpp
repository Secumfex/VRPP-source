#include "PhysicWorldSimulationListener.h"
#include "PhysicWorld.h"
#include <iostream>

using namespace std;

PhysicWorldSimulationListener::PhysicWorldSimulationListener(){

}

void PhysicWorldSimulationListener::update(){

	PhysicWorld* physicWorld = PhysicWorld::getInstance();
	physicWorld->dynamicsWorld->stepSimulation(1/300.f,10);	//werte muessen noch auf entsprechende framerate angepasst werden
}
