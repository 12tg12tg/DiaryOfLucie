#pragma once


//======================================================
//					singleton
//======================================================
/*
	싱글톤 패턴은 static member로 하나의 인스턴스만
	생성된다. 프로그램 안에서 전역적 접근이 가능하다.
	전역변수를 선언해도 하나의 인스턴스를 유지할 수 있긴하지만,
	싱글톤 패턴을 사용하면 클래스 자신이 자기의 유일한 인스턴스로
	접근하는 방법을 캡슐화하여 관리가 가능하다.
	상속, 객체생성, 소멸, 인스턴스 갯수 제어 등 활용에 유리하다.

	자기 스스로가 자기의 유일한 인스턴스로 접근하는 방법을
	자체적으로 관리하는게 좋다.
	다른 인스턴스가 생성되지 않도록 처리할 수 있고, 
	접근방법 또한 제한을 둘 수 있다.
*/
template<typename T>
class Singleton
{
protected:
	//싱글톤 인스턴스 선언
	static T* singleton;

	Singleton() {}
	~Singleton() {}

public :
	static T* getSingleton();
	void releaseSingleton();

};

//싱글톤 인스턴스 선언
template<typename T>
T* Singleton<T>::singleton = nullptr;


//싱글톤 객체를 가져오자.
template<typename T>
T* Singleton<T>::getSingleton()
{
	//싱글톤 객체가 없으면 새로 만들자
	if (!singleton) singleton = new T;
	return singleton;
}

template<typename T>
void Singleton<T>::releaseSingleton()
{
	if (singleton)
	{
		delete singleton;
		singleton = nullptr;
	}
}
