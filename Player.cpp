#include "Player.hpp"
using namespace std;
int Player::doMove(int (*Board)[3]){
	char stmp[80];
	printw(this->name.c_str());
	printw("'s Turn:\n");
	if (this->human){
		int x,y;
		bool cont = true;
		while(cont){
			printw("X: ");
			getstr(stmp);
			x = atoi(stmp);
			printw("Y: ");
			getstr(stmp);
			y = atoi(stmp);
			if(x<3&&x>=0&&y<3&&y>=0)
			{
				if (Board[x][y]==0){
					Board[x][y] = this->pieceVal;
					cont = false;
				}
				else{
					printw("Try again, this time, choose one that is not taken\n");
				}
			}
			else{
				printw("X and Y must be < 3 and >= 0\n");
			}
		}		
	}
	else{
		this->aiLogic(Board);		
	}
}
void Player::init(bool _human, int _pieceVal, string _name){
	this->human = _human;
	this->pieceVal=_pieceVal;
	this->name = _name;
	this->wins=0;
	srand( (unsigned)time( NULL ) ); 
}
void Player::aiLogic(int (*Board)[3]){
	int x,y;
	bool cont =true;
	int Rowtot[3];
	int Coltot[3];
	int Diagtot[3];
	for(int i = 0; i < 3; i++){
	Rowtot[i]=0;
	Coltot[i]=0;
	Diagtot[i]=0;
	}
	for(int x = 0; x<3;x++){
		for(int y = 0; y <3; y ++){
			Rowtot[y] += Board[x][y];
			Coltot[x] += Board[x][y];
			if(x==y)
				Diagtot[0] += Board[x][y];
			if(x+y==2)
				Diagtot[1] += Board[x][y];
			
		}
	}
	for(int i = 0; i < 3; i++){
		if (abs(Rowtot[i]) == 2){
			for(int x = 0; x <3; x ++){
				if (Board[x][i]==0){
					Board[x][i] = this->pieceVal;
					return;
				}
			}
		}
	}
	for(int i = 0; i < 3; i++){
		if (abs(Coltot[i]) == 2){
			for(int x = 0; x <3; x ++){
				if (Board[i][x]==0){
					Board[i][x] = this->pieceVal;
					return;
				}
			}
		}
	}
	if(abs(Diagtot[0])==2){
		int y;
		for(int x =0; x < 3; x++){
			y = x;
			if(Board[x][y]==0){
				Board[x][y]= this->pieceVal;
				return;
			}
		}
	}
	if(abs(Diagtot[1])==2){
		for(int x = 0; x < 3; x++)
			if(Board[x][2-x]==0){
				Board[x][2-x]=this->pieceVal;
				return;
			}
	}
	while(cont){
		x = rand()%3;
		y = rand()%3;
		if (Board[x][y]==0){
			Board[x][y] = this->pieceVal;
			cont = false;
			return;
		}
	}
}
