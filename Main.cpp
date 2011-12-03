#include <ncurses.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "Player.hpp"
using namespace std;
void clearBoard(int (*Board)[3]){
	for(int j = 0; j < 3; j++)
		for(int k = 0; k < 3; k++)
			Board[j][k]=0;
}
void dispBoard(int (*Board)[3]){
	clear();
	refresh();
	move(0,0);
	int xpos=0, ypos=0;
	for(int k = 0; k < 3; k++){
		for(int j = 0; j < 3; j++){
			if(Board[j][k]==1)
				printw("X");
			if(Board[j][k]==-1)
				printw("O");
			if(Board[j][k]==0)
				printw(" ");
			if(j!=2){
				printw("|");
			}			
		}
		printw("\n");
		if(k!=2)
			printw("------\n");
	}
}
bool WinMa(int (*Board)[3], Player * P1, Player * P2){
	Player * X;
	Player * O;
	if(P1->pieceVal==1){
		X = P1;
		O = P2;		
	}
	else{
		O = P1;
		X = P2;
	}
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
		if(Coltot[i]== 3 || Rowtot[i] == 3){
			X->wins++;
			return true;
		}
		if(Coltot[i]== -3 || Rowtot[i] == -3){
			O->wins++;
			return true;
		}
	}
	for(int i = 0; i < 2; i++){
		if(Diagtot[i]== 3){
			X->wins++;
			return true;
		}
		if(Diagtot[i]== -3){
			O->wins++;
			return true;
		}
	}
	for(int x = 0; x<3;x++){
		for(int y = 0; y <3; y ++){
			if(Board[x][y]==0)
				return false;
		}
	}
	return true;
}
int main(){
	initscr();
	bool play = true;
	int Board[3][3];
	bool ended = false;
	Player * P1 = new Player;
	Player * P2 = new Player;
	char stmp[80];
	int itmp;
	string name;
	printw("Player 1's name: ");
	getstr(stmp);
	name =stmp;
	printw("Is ");
	printw(stmp);
	printw(" a human? (1 for yes, 0 for no): ");
	getstr(stmp);
	itmp=atoi(stmp);
	P1->init(itmp,1, name);
	refresh();
	printw("Player 2's name: ");
	getstr(stmp);
	name =stmp;
	printw("Is ");
	printw(stmp);
	printw(" a human? (1 for yes, 0 for no): ");
	getstr(stmp);
	itmp=atoi(stmp);
	P2->init(itmp,-1, name);
	clearBoard(Board);
	while(play){
		dispBoard(Board);
		while(!ended){
			P1->doMove(Board);
			if(WinMa(Board, P1, P2))
				ended = true;
			dispBoard(Board);
			if(!ended){
				P2->doMove(Board);
				if(WinMa(Board, P1, P2))
					ended = true;
				dispBoard(Board);
			}		
		}
		printw("----Scores----\n");
		printw(P1->name.c_str());
		printw(": ");
		printw("%d\n",P1->wins);
		printw(P2->name.c_str());
		printw(": %d\n",P2->wins);
		clearBoard(Board);
		int t;
		printw("1 for play again, 2 for quit: ");
		getstr(stmp);
		t = atoi(stmp);
		if(t==2)
			play = false;
		else{
			Player * tmp = P1;
			P1 = P2;
			P2 = tmp;
			ended = false;
		}
	}
	delete P1;
	delete P2;
	endwin();
}
