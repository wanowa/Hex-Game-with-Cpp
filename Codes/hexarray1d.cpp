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

using namespace std;
using namespace AbstractHexAltun;

void HexArray1D::reset(){
	int row,column;
	for(row=0;row<26;row++){				//Burada da hexCells'in tüm hücrelerine '.' atayıp
		for(column=0;column<26;column++){	//path'ımın tüm hücrelerini 0 ile dolduruyorum.
			hexCells[row*26+column].setInside(dot);
			path[row][column]=0;			//Path arrayimi kazananı belirlemede kullanıyorum
		}
	}
}

void HexArray1D::play(int row,int column){
	
	if(turn%2==0){					
		hexCells[row*boardsize+column].setInside(pl1);	//turn%2==0 ise tahtaya pl1'i, yani 'x'i yaz. 
	}
	else if(turn%2==1){
		hexCells[row*boardsize+column].setInside(pl2);	//turn%2==1 ise tahtaya pl2'i, yani 'o'yu yaz. 
	}
}