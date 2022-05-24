#pragma once

using namespace std;
using namespace AbstractHexAltun;

class HexVector:public AbstractHex{
public:
	//BIG THREE IS NOT NEEDED.
	HexVector():AbstractHex(){	}	//AbstractHex constructorını çağırıyorum, gerekli değişkenler initialize ediliyor.
	virtual void reset();
	virtual void play(int row,int column);
	virtual char operator()(int row,int column) const{	return vectorCells[row][column].getInside();	}
	virtual void operator()(int row,int column,char inside){	vectorCells[row][column].setInside(inside);	}	
private:
	vector<vector<Cell> > vectorCells;	// 2d vektör arrayim
};