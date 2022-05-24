#pragma once

using namespace std;
using namespace AbstractHexAltun;

class HexArray1D:public AbstractHex{	//AbstractHex constructorını çağırıyorum, gerekli değişkenler initialize ediliyor.
public:
	//BIG THREE IS NOT NEEDED.
	HexArray1D():AbstractHex(){	}
	virtual void reset();
	virtual void play(int row,int column);
	virtual char operator()(int row,int column) const{	return hexCells[row*boardsize+column].getInside();	}
	virtual void operator()(int row,int column,char inside){	hexCells[row*boardsize+column].setInside(inside);	}
private:
	Cell hexCells[676];	//Bir boyutlu Cell arrayim
};