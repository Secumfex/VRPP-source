#ifndef UPLOADUNIFORMLISTENERS_H_
#define UPLOADUNIFORMLISTENERS_H_

#include "Patterns/Listener.h"

class UploadUniformModelMatrixListener : public Listener{

 	public:
 		UploadUniformModelMatrixListener(std::string name);
 	 	void update();
 };

 class UploadUniformViewMatrixListener : public Listener{

 	public:
 		UploadUniformViewMatrixListener(std::string name);
 	 	void update();
 };

 class UploadUniformProjectionMatrixListener : public Listener{

 	public:
 		UploadUniformProjectionMatrixListener(std::string name);
 	 	void update();
 };

 class UploadUniformInverseModelViewMatrixListener : public Listener{

 	public:
 		UploadUniformInverseModelViewMatrixListener(std::string name);
 	 	void update();
 };

 class UploadUniformPositionMapListener : public Listener{

 	public:
 		UploadUniformPositionMapListener(std::string name);
 	 	void update();
 };

 class UploadUniformNormalMapListener : public Listener{

 	public:
 		UploadUniformNormalMapListener(std::string name);
 	 	void update();
 };

 class UploadUniformColorMapListener : public Listener{

 	public:
 		UploadUniformColorMapListener(std::string name);
 	 	void update();
 };

 class UploadUniformDepthMapListener : public Listener{

 	public:
	 UploadUniformDepthMapListener(std::string name);
 	 	void update();
 };

 class UploadUniformDiffuseMapListener : public Listener{

  	public:
	 UploadUniformDiffuseMapListener(std::string name);
  	 	void update();
  };

 class UploadUniformBumpMapListener : public Listener{

  	public:
	 UploadUniformBumpMapListener(std::string name);
  	 	void update();
  };

 class UploadUniformShininessListener : public Listener{

  	public:
	 UploadUniformShininessListener(std::string name);
  	 	void update();
  };

 class UploadUniformDiffuseColorListener : public Listener{

  	public:
	 UploadUniformDiffuseColorListener(std::string name);
  	 	void update();
  };

 class UploadUniformAmbientColorListener : public Listener{

  	public:
	 UploadUniformAmbientColorListener(std::string name);
  	 	void update();
  };

 class UploadUniformSpecularColorListener : public Listener{

  	public:
	 UploadUniformSpecularColorListener(std::string name);
  	 	void update();
  };

#endif /* UPLOADUNIFORMLISTENERS_H_ */
