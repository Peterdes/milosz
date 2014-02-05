#ifndef RANDENGINE_H
#define RANDENGINE_H
#include <random>

/*
 * Generator liczb losowych.
 */

class RandEngine
{
private:
	std::mt19937 engine;
public:
	RandEngine();
	RandEngine(const RandEngine&) = delete;
	RandEngine& operator=(const RandEngine&) = delete;
	/*
	 * Zwraca wynik losowania na podstawie zadanej dystrybucji.
	 * Dystrybucja ma działać tak jak te w STL, standard C++11.
	 */
	template<class Dist> auto operator() (Dist distrib) -> decltype(distrib(engine))
	{
		return distrib(engine);
	}

};

#endif // RANDENGINE_H
