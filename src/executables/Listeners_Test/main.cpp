#include <iostream>
#include <string.h>

#include "SomeListeners.h"
#include "Visuals/RenderManager.h"

#include <typeinfo>
void testAnimateClearColor(){
	//RenderManager Pointer via Singleton
	RenderManager* rm = RenderManager::getInstance();

	//AnimateClearColorListener als FrameListener anhängen
	rm->attachFrameListener(new AnimateClearColorListener());

	rm->libInit();
	rm->manageShaderProgram();
	rm->renderLoop();
}

using namespace std;
#include <iostream>

int main() {
int input = 0;
	cout << "Zahl eingeben für testprogramm:"<< endl;
	cout << "	1: Test AnimateClearColorListener (WARNING: may explode)"<< endl;
	cout << "	2: Test simple Listeners"<< endl;
//	cout << "	3: "<<endl;
//	cout << "	4: "<<endl;

	cin >> input;

	switch(input){
		case 1:
			testAnimateClearColor();
			break;
		case 2: 
			cout << "not yet implemented..."<<endl;
	}

	std::cout<<"_____________________________"<<std::endl;

	////////////////////////////////////////////////////////////////////////////////
	/*Endlosschleife, damit das Fenster aufbleibt, wenn man nicht aus Eclipse startet oder so*/
	int terminate;
	std::cout<<"enter any value to terminate."<<std::endl;
	std::cin>>terminate;
};
