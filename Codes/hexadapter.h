#pragma once

using namespace std;
using namespace AbstractHexAltun;
											//Implementation'ları da bu dosyada yaptım.
template<template<typename...> class T>
class HexAdapter:public AbstractHex{
public:
	//BIG THREE IS NOT NEEDED.
	HexAdapter():AbstractHex(){	}	//AbstractHex constructorını çağırıyorum, gerekli değişkenler initialize ediliyor.
	virtual void reset();
	virtual void play(int row, int column);
	virtual char operator()(int row, int column)const{	return adapterCells[row][column].getInside();	}
	virtual void operator()(int row, int column, char inside){	adapterCells[row][column].setInside(inside);	}
private:
	T <T<Cell> > adapterCells;
};

template<template<typename...> class T>
void HexAdapter<T>::reset(){
	int i,j;
	Cell c;
	c.setInside('.');
	T<Cell> t;

	for(i=0;i<26;i++){
		for(j=0;j<26;j++){
			t.push_back(c);		//26*26'lık template Cell arrayi oluşturuyorum
		}
		adapterCells.push_back(t);
	}
}

template<template<typename...> class T>
void HexAdapter<T>::play(int row,int column){
	if(turn%2==0){					
		adapterCells[row][column].setInside(pl1);	//turn%2==0 ise tahtaya pl1'i, yani 'x'i yaz. 
	}
	else if(turn%2==1){
		adapterCells[row][column].setInside(pl2);	//turn%2==1 ise tahtaya pl2'i, yani 'o'yu yaz. 
	}	
}