#ifndef UPLOADUNIFORMLISTENERS_H_
#define UPLOADUNIFORMLISTENERS_H_

class UploadUniformModelMatrixListener : public Listener{

 	public:
 	 	void update();
 };

 class UploadUniformViewMatrixListener : public Listener{

 	public:
 	 	void update();
 };

 class UploadUniformProjectionMatrixListener : public Listener{

 	public:
 	 	void update();
 };

 class UploadUniformInverseModelViewMatrixListener : public Listener{

 	public:
 	 	void update();
 };

 class UploadUniformPositionMapListener : public Listener{

 	public:
 	 	void update();
 };

 class UploadUniformNormalMapListener : public Listener{

 	public:
 	 	void update();
 };

 class UploadUniformColorMapListener : public Listener{

 	public:
 	 	void update();
 };

 class UploadUniformDepthMapListener : public Listener{

 	public:
 	 	void update();
 };

 class UploadUniformDiffuseMapListener : public Listener{

  	public:
  	 	void update();
  };

 class UploadUniformBumpMapListener : public Listener{

  	public:
  	 	void update();
  };


#endif /* UPLOADUNIFORMLISTENERS_H_ */
