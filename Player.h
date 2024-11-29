#pragma once
#include<string>
#include"utility.h"
using namespace std;
class Player
{
	string name;
	color C;
public:
	Player(string _n, color _C);
	string getname();
	color getcolor();
};

