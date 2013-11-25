#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>
using namespace std;


template <typename C>
 class Singleton
 {
 public:
    static C* getInstance (); //static Method to get the only instance
    virtual ~Singleton ();    //virtual destroyer in case there is other stuff to destroy
 private:
    static C* _instance;      //static variable containing a pointer to itself
 protected:
    Singleton ();
 };

 template <typename C> C* Singleton <C>::_instance = 0; // generic template

////////////////////////////////////////////////////////////////
 //Beispielklasse die Singleton implementiert
class ConcreteSingleton : public Singleton <ConcreteSingleton>
 {
//nötig damit Singleton Zugriff auf private und protected Membervariablen von ConcreteSingleton hat
 friend class Singleton <ConcreteSingleton>;

 public:
    ~ConcreteSingleton ();
    void helloWorld ();
 protected:
    ConcreteSingleton ();
 };

 #endif
