#pragma once

using namespace std;

namespace AbstractHexAltun{		//Class'ları Namespace içine aldım
	
	enum statement{pl1 = 'x', pl2 = 'o', dot = '.'};	//enum tipim
	
	class NoMove:public runtime_error{	//Hamle sayısı 0 olduğunda kullandığım exception class'ım
	public:
		NoMove():runtime_error("There is no move on this board."){}
	};

	class FileError:public runtime_error{	//Dosya okumada hata olduğunda kullandığım exception class'ım
	public:
		FileError():runtime_error("File doesn't exist or This file is not accessible."){}
	};


	class AbstractHex{
	public:
		class Cell{		//İçinde birer setter/getter bulunan Cell class'ım
			public:
				Cell(){	inside = dot;	}
				void setInside(char c){	inside=c;	}
				char getInside()const {	return inside;	}
			private:
				char inside='.';	//verilen değere göre '.' 'x','o' olabiliyor. 
		};

		//BIG THREE IS NOT NEEDED.
		
		AbstractHex();
		void print() const;							//Board'ı yazdırıyor
		void readFromFile(string filename);			//Dosya okuyor
		void writeToFile(string filename) const;	//Dosyaya yazıyor
		virtual void play(int row,int column)=0;	//Kullanıcının verdiği koordinatlara hamle yapıyor
		virtual char operator()(int row,int column) const=0;	//[row][column] indeksindeki karakteri döndürüyor
		virtual void operator()(int row,int column,char inside)=0;	//[row][column] indeksindeki hücredeye gönderilen karakteri atıyor.
		//bool operator==(const AbstractHex& other);
		virtual void reset()=0;			//Board'ı reset'liyor
		friend ostream& operator <<(ostream& output, const AbstractHex& object);	//Tahtayı print ederken kullandığım operator<< fonksiyonu
		bool winCheck();	//Her hamleden sonra kazanan var mı diye kontrol ettiğim fonksiyon
		int is_x_win(int row,int column);	//x'in kazanma durumunu kontrol ediyor
		int is_o_win(int row,int column);	//y'nin kazanma durumunu kontrol ediyor
		void player_move();		//Kullanıcıdan input alan fonksiyon
		void startBoard();		//Board için gerekli bilgileri (boardsize, usr1-usr2-pc gibi) kullanıcıdan alan fonksyion

		////////////////	GETTERS				Inline getter fonksiyonlarım
		int getSize()const{	return boardsize;	}
		int getTurn()const{		return turn;	}
		int getVersusconst(){	return versus;	}
		int getInit(){	return initialize;	}
		bool isEnd() const	{	return end;	}	
		string lastMove() const{return last_move;}
		int numberOfMoves()const{return number_of_moves;	}
		static int getEnd(){	return end;	}
		static int getGameNum(){	return AbstractHex::gameNum;	}

		////////////////   SETTERS				Inline setter fonksiyonlarım
		void setSize(int size){boardsize=size;}
		void setTurn(int var){	turn=var;	}
		void setVersus(int var){	versus=var;	}
		void setInit(int var){	initialize=var;	}
		static void setGameNum(int var){	AbstractHex::gameNum=var;	}

	//---------Big Three is not needed------------//

	protected:
		int path[26][26],boardsize,turn=-1,versus,initialize=0,number_of_moves=0;
		char letter='a';	//letter değişkenime 'a' atadım, bir arttıra arttıra tüm alfabeye ulaşabiliyorum
		string last_move = "";	//Son hamlemi atadığım string
		static int gameNum;		//Oynanılan güncel oyun numarasını tutan static data
		static bool end;		//Kullanıcı programı sonlandırırsa true olan flag		
	};	
}