#include "GameTime.h"


GameTime::GameTime(DisplayManager *display, float day, float night, float evening, float morning)
{
	this->morning = morning;
	this->day = day;
	this->evening = evening;
	this->night = night;
	this->sum = morning + day + evening + night;
	this->display = display;
	this->gametime = 0;
}


GameTime::~GameTime()
{
}

void GameTime::updateTime(){
	this->gametime += display->getFrameTime();
	if (gametime >= (day + night + evening + morning))
		gametime = 0;
}

float GameTime::skyBoxCalc(){
	float temp = 0.f;
	temp = gametime / night;
	if (gametime < morning)
		return gametime / morning;
	else if (gametime > morning && gametime < day + morning)
		return 0.0f;
	else if (gametime > day + morning && gametime < day + morning + evening)
	{
		return gametime / morning + day;
	}		
	else
		return 1.0f;
	return 0;
}
