#include <iostream>
#include<string>
#include<fstream>
#include <vector>
#include <deque>
#include <cstdlib>
#include<exception>
#include<stdexcept>
#include "abstracthex.h"
#include "hexarray1d.h"
#include "hexvector.h"
#include "hexadapter.h"

using namespace std;
using namespace AbstractHexAltun;

/////////////////////////////////////////////////////////////////////////////////////////

bool isValid(const AbstractHex* game);


int main(){
	vector<AbstractHex*> games(5);
	int index;
	string str1,str2;
	int i,j,num,check=1,sira,row=0,column=0,size,var,turnVar=0;
	bool win;
	games[0]=new HexArray1D();	//1. oyunda hexarray1d objesi var
	games[1]=new HexVector();	//2. oyunda hexvector objesi var
	games[2]=new HexAdapter<vector>();	//3. oyunda vector alan template hexadapter objesi var
	games[3]=new HexAdapter<deque>();	//4. oyunda deque alan template hexadapter objesi var
	games[4]=new HexArray1D();	//5. oyunda hexarray1d objesi var

	while(!AbstractHex::getEnd()){		//End flag'ı false iken devam et
		
		num=AbstractHex::getGameNum();	//Güncel oyunun numarasını alıyorum. Default olarak 0.
		if(games[num]->getInit()==0){	//Oyun initialize edilmemişse initialize ediyorum
			games[num]->reset();		//Tahtayı reset'liyorum
			games[num]->startBoard();
			games[num]->setInit(1);		//ve initialize flag'ımı 1 yapıyorum
		}

		games[num]->setTurn(games[num]->getTurn()+1);	//while'ın her döngüsünde turn değişkeni bir artacak
		games[num]->print();						//Böylelikle her seferinde sıra değişecek.
													//turn%2==0 ise sıra user1'de, turn%2==1 ise sıra user2'de
		games[num]->player_move();		//Kullanıcıdan input aldım		

		win=games[num]->winCheck();			//galibiyet durumunu kontrol ettim

		if(win){		//eğer biri kazandı ise kullanıcıya hangi oyuna devam etmek
			while(check==1){	//istediğini soruyorum.
				check=0;
				cout<<"Which Game do you want to continue?(1 to 5) :";
				cin>>var;
				if(var<1||var>5){
					cerr<<"\nWrong entered, please try again.";
					check=1;
				}
				else{
					var--;
					AbstractHex::setGameNum(var);	//Yeni oyunun numarasını güncel oyun numarasına atıyorum.
				}
			}
		}
	}
}

bool isValid(const AbstractHex* game){	//AbstractHex pointer'ı alıp tahtalarda invalid karakter var mı kontrol ediyorum.
	int row,column,check=1,i,j;
	char c;
	for(i=0;i<5;i++){
		for(row=0;row<game[i].getSize();row++){
			for(column=0;column<game[i].getSize();column++){
				c=game[i].operator()(row,column);
				if(c!='.'||c!='x'||c!='o'){
					cout<<i+1<<". Game contains invalid character!";
					return false;
				}
			}
		}
	}
	return true;
}