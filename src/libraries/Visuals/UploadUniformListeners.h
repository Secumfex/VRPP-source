#ifndef UPLOADUNIFORMLISTENERS_H_
#define UPLOADUNIFORMLISTENERS_H_

class UploadUniformModelMatrixListener : public Listener{
 	private:
 		RenderManager* rm;
 	public:
 	 	void update();
 };

 class UploadUniformViewMatrixListener : public Listener{
 	private:
 		RenderManager* rm;
 	public:
 	 	void update();
 };

 class UploadUniformProjectionMatrixListener : public Listener{
 	private:
 		RenderManager* rm;
 	public:
 	 	void update();
 };

 class UploadUniformInverseModelViewMatrixListener : public Listener{
 	private:
 		RenderManager* rm;
 	public:
 	 	void update();
 };

 class UploadUniformPositionMapListener : public Listener{
 	private:
 		RenderManager* rm;
 	public:
 	 	void update();
 };

 class UploadUniformNormalMapListener : public Listener{
 	private:
 		RenderManager* rm;
 	public:
 	 	void update();
 };

 class UploadUniformColorMapListener : public Listener{
 	private:
 		RenderManager* rm;
 	public:
 	 	void update();
 };


#endif /* UPLOADUNIFORMLISTENERS_H_ */
