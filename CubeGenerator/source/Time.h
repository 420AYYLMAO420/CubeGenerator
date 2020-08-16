#pragma once

class Time {

public:
	Time();
	~Time();

	//assigns a time point value to StartTime
	void Start();

	//retrieves the duration between the time that this function is called and StartTime
	float GetTimeSinceStart() const;
	//returns the approximate time between eacch frame
	float GetDeltaTime();

private:
	//variables used for GetDeltaTime()
	float CurrentTime;
	float DeltaTime = 0.0f;	
	float PrevTime = 0.0f; 
};