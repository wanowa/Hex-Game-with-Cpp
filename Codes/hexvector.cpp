#include <iostream>
#include<string>
#include<fstream>
#include <vector>
#include <deque>
#include <cstdlib>
#include<exception>
#include<stdexcept>
#include "abstracthex.h"
#include "hexvector.h"

using namespace std;
using namespace AbstractHexAltun;

void HexVector::reset(){
	int i,j;
	Cell c;
	c.setInside('.');
	vector<Cell> v;			//Burada da vectorCells'in tüm hücrelerine '.' atıyorum.
	for(i=0;i<26;i++){
		for(j=0;j<26;j++){
			v.push_back(c);	//26*26'lık Cell vektörü oluşturuyorum
		}
		vectorCells.push_back(v);
	}
}

void HexVector::play(int row,int column){
	
	if(turn%2==0){					
		vectorCells[row][column].setInside(pl1);	//turn%2==0 ise tahtaya pl1'i, yani 'x'i yaz. 
	}
	else if(turn%2==1){
		vectorCells[row][column].setInside(pl2);	//turn%2==1 ise tahtaya pl2'i, yani 'o'yu yaz. 
	}
}