#ifndef RESOURCE_H_
#define RESOURCE_H_

class Resource{
public:
	virtual void streamToVRAM();
};

class Texture : public Resource {

};

class Mesh : public Resource{

};

#endif
