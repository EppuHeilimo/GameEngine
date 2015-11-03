#pragma once
#include "DisplayManager.h"
class GameTime
{
public:
	GameTime(DisplayManager *display,
		float day,
		float night,
		float evening,
		float morning );
	~GameTime();
	float getGametime(){ return gametime; }
	float getDay(){ return day; }
	float getNight(){ return night; }
	float getEvening(){ return evening; }
	float getMorning(){ return morning; }
	void updateTime();
	float clock();
	float skyBoxCalc();
private:
	DisplayManager *display;
	float gametime;
	float day;
	float night;
	float evening;
	float morning;
	float sum;
};

