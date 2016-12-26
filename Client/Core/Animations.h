#pragma once
class Animations
{
public:
	Animations() {};
	~Animations() {};

	void GetAnimalAnimation(int modelhash, int movement, std::string *dict, std::string *name);
};