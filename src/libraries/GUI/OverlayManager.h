
#ifndef OVERLAYMANAGER_H_
#define OVERLAYMANAGER_H_

class Overlaymanager : public Singleton<Overlaymanager>, Subject{
	friend class Singleton<Overlaymanager>;

private:
	/** \brief constructor
	 *
	 */
	Overlaymanager();
public:
	/** \brief destructor
	 *
	 */
    ~Overlaymanager();
};
#endif /* OVERLAYMANAGER_H_ */
