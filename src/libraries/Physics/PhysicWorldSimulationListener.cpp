#include "PhysicWorldSimulationListener.h"
#include "PhysicWorld.h"
#include <iostream>

using namespace std;

PhysicWorldSimulationListener::PhysicWorldSimulationListener(float* delta_time_source		){
	if (delta_time_source != 0){
		this->delta_time_source = delta_time_source;
	}
	else{
		this->delta_time_source = 0;
	}
}

void PhysicWorldSimulationListener::update(){

	PhysicWorld* physicWorld = PhysicWorld::getInstance();
	if (delta_time_source != 0){
		physicWorld->dynamicsWorld->stepSimulation(*delta_time_source,10);	//werte muessen noch auf entsprechende framerate angepasst werden
	}
	else{
		physicWorld->dynamicsWorld->stepSimulation(1/120.f,10);	//werte muessen noch auf entsprechende framerate angepasst werden
	}
}
