#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>
using namespace std;


template <typename C>
 class Singleton
 {
 public:
    static C* instance ()
    {
       if (!_instance)
          _instance = new C ();
       return _instance;
    }
    virtual
    ~Singleton ()
    {
       _instance = 0;
    }
 private:
    static C* _instance;
 protected:
    Singleton () { }
 };

 template <typename C> C* Singleton <C>::_instance = 0;



 //Beispielklasse die Singleton implementiert
class ConcreteSingleton : public Singleton <ConcreteSingleton>
 {
//nötig damit Singleton Zugriff auf private und protected Membervariablen von ConcreteSingleton hat
 friend class Singleton <ConcreteSingleton>;

 public:
    ~ConcreteSingleton () { }
    void helloWorld () {cout<<"Isch bins, ein Singleton!"<<endl; }
 protected:
    ConcreteSingleton () { }
 };

 #endif
