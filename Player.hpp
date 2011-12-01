#ifndef _Player_hpp
#define _Player_hpp
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
class Player{
	public:
	bool human;
	int pieceVal;
	string name;
	int wins;
	void init(bool _human, int _pieceVal, string _name);
	int placePiece(int (*Board)[3], int x, int y);
	int doMove(int (*Board)[3]);
	void aiLogic(int (*Board)[3]);
};
#endif
