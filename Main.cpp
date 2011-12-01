#include <iostream>
#include <string>
#include "Player.hpp"
using namespace std;
void clearBoard(int (*Board)[3]){
	for(int j = 0; j < 3; j++)
		for(int k = 0; k < 3; k++)
			Board[j][k]=0;
}
void dispBoard(int (*Board)[3]){
	cout<<"============================="<<endl;
	for(int k = 0; k < 3; k++){
		for(int j = 0; j < 3; j++){
			if(Board[j][k]==1)
				cout<<"X";
			if(Board[j][k]==-1)
				cout<<"O";
			if(Board[j][k]==0)
				cout<<" ";
			if(j!=2){
				cout<<"|";
			}			
		}
		cout<<endl;
		if(k!=2)
			cout<<"------"<<endl;
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
			if((x==0 && y ==2) || (x==1&&y==1)||(x==2&&y==0))
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
	bool play = true;
	int Board[3][3];
	bool ended = false;
	Player * P1 = new Player;
	Player * P2 = new Player;
	string stmp;
	int itmp;
	cout<<"Player 1's name: ";
	cin >>stmp;
	cout<<"Is "<<stmp<<" a human? (1 for yes, 0 for no): ";
	cin >> itmp;
	P1->init(itmp,1, stmp);
	stmp="";
	cout<<"Player 2's name: ";
	cin >>stmp;
	cout<<"Is "<<stmp<<" a human? (1 for yes, 0 for no): ";
	cin >> itmp;
	P2->init(itmp,-1, stmp);
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
		cout<<"----Scores----"<<endl;
		cout<<P1->name<<": "<<P1->wins<<endl;
		cout<<P2->name<<": "<<P2->wins<<endl;
		clearBoard(Board);
		int t;
		cout<<"1 for play again, 2 for quit: ";
		cin >>t;
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
}
