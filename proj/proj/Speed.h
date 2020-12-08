#pragma once
class Speed
{
public:
	int getSpeed()
	{
		return speed;
	}

	void changeSpeed()
	{
		if (speed == 1)
		{
			speed = 10;
		}
		else
		{
			speed = 1;
		}
	}
private:
	int speed = 1;
};

