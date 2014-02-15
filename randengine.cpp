#include "randengine.h"
#include <chrono>

RandEngine::RandEngine()
	: engine(std::chrono::system_clock::now().time_since_epoch().count())
{
}

RandEngine::~RandEngine() {}
