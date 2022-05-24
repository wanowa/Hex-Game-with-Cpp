/*#include <iostream>
#include<string>
#include<fstream>
#include <vector>
#include <deque>
#include <cstdlib>
#include<exception>
#include<stdexcept>
#include "abstracthex.h"
#include "hexadapter.h"

using namespace std;
using namespace AbstractHexAltun;




template<template<typename...> class T>
void HexAdapter<T>::reset(){
	int i,j;
	Cell c;
	c.setInside('.');
	T<Cell> t;

	for(i=0;i<26;i++){
		for(j=0;j<26;j++){
			t.push_back(c);
		}
		adapterCells.push_back(t);
	}
}

template<template<typename...> class T>
void HexAdapter<T>::play(int row,int column){
	if(turn%2==0){					//tahtaya yerleştiriyorum.
		adapterCells[row][column].setInside(pl1);	//turn%2==0 ise tahtaya pl1'i, yani 'x'i yaz. 
	}
	else if(turn%2==1){
		adapterCells[row][column].setInside(pl2);	//turn%2==1 ise tahtaya pl2'i, yani 'o'yu yaz. 
	}	
}*/