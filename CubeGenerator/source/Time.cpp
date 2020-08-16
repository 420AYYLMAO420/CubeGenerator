#include "Time.h"
#include <chrono>

using namespace std::chrono;

steady_clock::time_point StartTime;

Time::Time()
{

}

Time::~Time()
{

}

void Time::Start()
{
	StartTime = steady_clock::now();
}

float Time::GetTimeSinceStart() const
{
	//gets the duration in seconds
	return duration<float>(steady_clock::now() - StartTime).count();
}

float Time::GetDeltaTime() {
	CurrentTime = GetTimeSinceStart();
	DeltaTime = CurrentTime - PrevTime;
	PrevTime = CurrentTime;

	return DeltaTime;
}
