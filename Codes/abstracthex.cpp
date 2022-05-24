#include <iostream>
#include<string>
#include<fstream>
#include <vector>
#include <deque>
#include <cstdlib>
#include<exception>
#include<stdexcept>
#include "abstracthex.h"


using namespace std;

namespace AbstractHexAltun{		//Unique bir namespace oluşturmaya çalıştım.
	int AbstractHex::gameNum=0;			//Static data'larımı initialize ettim
	bool AbstractHex::end = false;

	void AbstractHex::player_move(){
		int check=1,num,column,row;
		string str,str2,substring3,substring4,substring6,substring7;
		cout<<"\n\nInput Format : 'C 11'\n";
		cout<<"\nYour Options:\nEnter Cell Coordinate ('C 11')\n";
		cout<<"LOAD or SAVE the game (LOAD filename.txt)/(SAVE filename.txt)\n";
		cout<<"Switch to another game = SWITCH <game number> (SWITCH 4)\n";
		cout<<"For print Number of Moves = MOVE NUMBER\n";
		cout<<"For print Last Move = LAST MOVE\n";
		//cout<<"Compare 2 game = COMPARE <game number> (COMPARE 2)\n";
		cout<<"End The Program : (END program)";
		check=0;

		if(turn%2==0){			//turn%2==0 ise User1'in sırası
			cout<<"\n\n\n\nUser1's turn (x)\n";
		}
		else if(turn%2==1){		//turn%2==1 ise User2'nin sırası
			cout<<"\n\n\n\nUser2's turn (o)\n\n";
		}
		

		cout<<"\nEnter an input:";	//Kullanıcıdan iki string alıyorum.
		cin>>str>>str2;
		
		substring3=str.substr(0,3);//3 karakter olan END stringini kontrol etmek için
		substring4=str.substr(0,4);//4 karakter olan SAVE ve LOAD stringlerini kontrol etmek için
		substring6=str.substr(0,6);//6 karakter olan SWITCH stringini kontrol etmek için
		substring7=str.substr(0,7);//7 karakter olan COMPARE stringini kontrol etmek için

		if(substring3=="END"){	//Girilen string END program ise program terminate ediliyor.
			if(str2=="program"){
				cout<<"Program Terminating...\n\n";
				end=true;
			}
			else{
				cout<<"Wrong entered, Terminating failed.";
			}
		}
		
		else if(substring4=="SAVE"){	//Girilen ilk string SAVE ise;
			writeToFile(str2);	//ve Save fonksiyonumu çağırıyorum.
			turn--;		//Kullanıcı hamle yapmadığından turn'ün değişmemesi için
		}				//bir eksiltiyorum.
		else if(substring4=="LOAD"){	//Girilen ilk string LOAD ise;
			readFromFile(str2);	//ve Loadfonksiyonumu çağırıyorum.
			turn--;
		}

		else if(substring6=="SWITCH"){	//Girilen ilk string SWITCH ise;
			turn--;
			num=stoi(str2)-1;	//Geçilmek istenen oyunun numarasını str2'den çekiyorum.
			AbstractHex::setGameNum(num);	//str2'den çektiğim yeni oyunun numarasını gameNum'a,yani güncel oyun data'sına atıyorum.
		}
		else if(str == "LAST" && str2 == "MOVE"){	//Girilen string LAST MOVE ise
			turn--;
			try{							//Exception handling yapıyorum.
				if(numberOfMoves() == 0){
					throw NoMove();
				}
				cout<<"\nLast Move is : "<<last_move<<"\n\n";	//Eğer hamle sayısı 0 değilse last move'u bastırıyorum.
			}
			catch(NoMove& obj){
				cout<<"------Exception Occured : "<<obj.what()<<"------\n\n";	//exception yakalanmışsa hata mesajını yazdırıyorum.
			}
		}
		else if(str == "MOVE" && str2 == "NUMBER"){	//Girilen string MOVE NUMBER ise
			turn--;
			cout<<"\nNumber of Moves is : "<<numberOfMoves()<<"\n\n";	//hamle sayısını yazdırıyorum.
		}
	
		//Compare kısmını yapamadım.
	
	/*		
		else if(substring7=="COMPARE"){	//Girilen ilk string COMPARE ise;
			cout<<"\n\n!!!!!!!!!!!!"<<substring7<<"!!!!!!!\n"<<endl;
			num=stoi(str2)-1;	//Compare edilmek istenen oyunun numarasını çekiyorum.
			cout<<"\n\n___if'e girecek ___\n\n";
			if(*this == games[num]){	//Overloaded '==' fonksiyonunu çağırdım.
				cout<<"\n\n\nGAMES ARE EQUAL!!!\n";	//True döndürdüyse iki oyun eşittir.
			}
			else{
				cout<<"\n\n\nGAMES ARE NOT EQUAL  ...\n";
				//cout<<"\n\n\nGAMES ARE NOT EQUAL\n";//False döndürdüyse iki oyun eşit değildir.
			}
			turn--;
		}
	*/
		
		else{	//Yukarıdakilerden hiçbirini girmediyse cell'in koordinatını girmiştir.
			
			column=str[0]-65;	//row ve Column değerlerini stringlerden çekiyorum.
			row=stoi(str2)-1;
			check=1;
			while(check==1){	//Girilen koordinat geçerli olana kadar istemeye devam ediyorum.
				check=0;
				if(column>=boardsize||column<0||row>=boardsize||row<0){
					cerr<<"\nEntered input is out of board\n";
					check=1;		//Oynanılmak istenen hücre tahtanın dışındaysa hata veriyor
				}
				else if(this->operator()(row,column)!=dot){
					cerr<<"\nCell is full\n";
					check=1;		//Oynanılmak istenen hücre doluysa hata veriyor
				}
				if(check==1){
					cout<<"\nEnter Coordinate of the Cell (C 5) :";
					cin>>str>>str2;	
					column=str[0]-65;
					row=stoi(str2)-1;
				}

			}
			last_move = str + " " + str2;	//last_move'uma girilen stringleri atayıp oynanılan hamle sayısını bir artırıyorum.
			number_of_moves++; 
			play(row,column);	//Verdiğim koordinatlara sıra kimdeyse onun harfini koyuyor.
		}
	}


/*
	bool AbstractHex::operator==(const AbstractHex& other){
		cout<<"\n\n----------PRINT CHECK--------\n\n";
		int i,j,check=0;	//Check'i default olarak 0 yaptım.
		//cout<<"\n\n_____"<<this->operator()(0,0)<<"____\n\n";
		if((*this).boardsize==other.getSize()){		//Basit bir comparison işlemiyle sonuca göre true veya false döndürüyorum.
			cout<<"Boardsize'lar eşit\n\n";
			for(i=0;i<boardsize;i++){
				for(j=0;j<boardsize;j++){
					if((*this).operator()(i,j)!=other(i,j)){	
						//cout<<"Farklı hücre var ! \n\nthis = "<<this->operator()(i,j)<<"other = "<<other.operator()(i,j)<<endl;
						check=1;	//eğer farklı tek bir hücre varsa check 1 oluyor.
					}
				}
			}
			if(check==0){	//Check 0 olarak kaldıysa tüm hücreler aynı demektir.
				return true;
			}
		}
		return false;
	}
*/

	ostream& operator <<(ostream& output, const AbstractHex& object){	//board'umu ekrana yazdırıyorum.
		int i,j,k;
		cout<<"   ";
		for(i=0;i<object.boardsize;i++){		//Cout işlemi
			cout<<static_cast<char>(object.letter+i)<<"  ";
		}
		cout<<"\n";							//Object'imin gerekli olan data'larını
		for(i=0;i<object.boardsize;i++){	//ekrana yazdırıyorum.
			cout<<i+1;
			for(k=0;k<i;k++){
				cout<<" ";
			}
			for(j=0;j<object.boardsize;j++){
				cout<<"  "<<object(i,j);
			}
			cout<<"\n";
		}
		return output;
	}

	void AbstractHex::startBoard(){ 	//Bu fonksiyonda tahta için gerekli olan bilgileri kullanıcıdan alıyorum.
		int check=1,size,vs;			
		while(check==1){
			cout<<"Enter the board size of the "<<AbstractHex::gameNum+1<<". Game(5 to 26) : ";
			check=0;
			cin>>size;				//Objemin gerekli olan data'larını kullanıcıdan istiyorum
			if(size<5||size>26){
				cerr<<"\nYou entered wrong, please try again.\n\n";
				check=1;			//Validity'e de dikkat ettim.
			}
		}
		setSize(size);
		
		check=1;
		
		while(check==1){
			cout<<"\nEnter '0' for user1 vs user2\nEnter '1' for computer vs user for "<<AbstractHex::gameNum+1<<". Game : ";
			check=0;
			cin>>vs;
			if(vs!=1&&vs!=0){
				cerr<<"\nYou entered wrong, please try again.\n\n";
				check=1;
			}
		 	if(vs==1){
		 		cerr<<"\nvs Computer part is not available yet, please try again.\n\n";
		 		check=1;
		 	}
		}
		setVersus(vs);
	}

	AbstractHex::AbstractHex(){		//Constructor'ımda olması gereken default değerleri atadım.
		end=false;
		turn=-1;
		initialize=0;
		number_of_moves=0;
	}

	void AbstractHex::print()const{
		cout<<*this;	//operator<< overloaded fonksiyonuma gönderdim.
	}


	bool AbstractHex::winCheck(){		//Kazanma durumunu kontrol eden fonksiyonum
		int i,j,row=0,column=0,finish;
		if(turn%2==0){		//User1'in kazanma durumunu kontrol ediyorum
			for(row=0;row<boardsize;row++){		//Eğer sol duvardaki hücrelerden birinde 'x' varsa
				if(this->operator()(row,column)==pl1){	//Kontrol etmeye başlıyor, aksi takdirde geçiyor.
					finish=is_x_win(row,column);	//is_x_win fonksiyonu 0 dışında bir değer gönderirse
					if(finish!=0){					//User1 kazanmış demektir.
						for(i=0;i<boardsize;i++){	
							for(j=0;j<boardsize;j++){	//Bütün 'x'leri büyütüyorum
								if(path[i][j]==1){	//Bunu anlamak için de programın galibiyet yolunu bulduğu path'ı kullanıyorum.
									this->operator()(i,j,this->operator()(i,j)-32);
								}
							}
						}
						print();	//Kazananın harflerinin büyük yazıldığı board'ı bastırıyorum.
						cout<<"\n\n\nUser1 (x) Won!!\n";
						initialize=0;	//Oyun bittiği için initialize flag'ımı 0 yaptım.
						return true;	//Kazanan olduğunu belirtmek için true döndürüyorum.
					}
				}
			}
		}
		
		else if(turn%2==1){		//User1'in kazanma durumunu kontrol ediyorum
			for(column=0;column<boardsize;column++){	//Eğer üst duvardaki hücrelerden birinde 'o' varsa
				if(this->operator()(row,column)==pl2){	//Kontrol etmeye başlıyor, aksi takdirde geçiyor.
					finish=is_o_win(row,column);	//is_o_win fonksiyonu 0 dışında bir değer gönderirse
					if(finish!=0){					//User2 kazanmış demektir.
						for(i=0;i<boardsize;i++){
							for(j=0;j<boardsize;j++){	//Bütün 'x'leri büyütüyorum
								if(path[i][j]==1){	//Bunu anlamak için de programın galibiyet yolunu bulduğu path'ı kullanıyorum.
									this->operator()(i,j,this->operator()(i,j)-32);
								}
							}
						}
						print();	//Kazananın harflerinin büyük yazıldığı board'ı bastırıyorum.
						cout<<"\n\n\nUser2 (o) Won!!\n";
						initialize=0;	//Oyun bittiği için initialize flag'ımı 0 yaptım.
						return true;	//Kazanan olduğunu belirtmek için true döndürüyorum.
					}
				}
			}
		}
		return false;	//Kazanan yoksa false döndürüyor.
	}


	void AbstractHex::writeToFile(string filename)const{
		int i,j;
		ofstream output;
		try{			//Exception handling yapıyorum.
			output.open(filename);		//Save işlemi
			if(output == nullptr){
				throw FileError();
			}
			output<<boardsize<<"\n";		//Gerekli olan tüm data'yı belirlediğim sırada dosyaya yazdırıyorum.
			for(i=0;i<boardsize;i++){
				for(j=0;j<boardsize;j++){
					output<<this->operator()(i,j);
				}
			}

			output<<"\n"<<turn<<"\n"<<versus;
			cout<<"Save Completed.\n";		
		}
		catch(FileError& obj){
			cout<<"\nError Occured : "<<obj.what()<<"------\n\n";
		}

		output.close();
	}

	void AbstractHex::readFromFile(string filename){
		int i,j;
		char c;							//Load işlemi
		ifstream input;
		try{		//Exception handling yapıyorum
			input.open(filename);	
			if(input.fail()){		//Eğer böyle bir dosya yoksa object throw yapıyor.
				throw FileError();
			}		
			input>>boardsize;				//İlk boardsize'ımı alıyorum ki x ve o'ları yeni tahtama
			for(i=0;i<boardsize;i++){		//göre dizebileyim.
				for(j=0;j<boardsize;j++){
					input>>c;
					this->operator()(i,j,c);	//ardından overloaded operator() fonksiyonumla tahtanın [i][j] indeksine c karakterini koyuyorum.
				}
			}
			input>>turn;					//ardından turn  ve versus değişkenlerimi alıyorum
			input>>versus;
			cout<<"\nLoading Completed\n";	
		}
		catch(FileError& obj){
			cout<<"\nError Occured : "<<obj.what()<<"------\n\n";
		}
		input.close();
	}


	int AbstractHex::is_x_win(int row,int column){
		int i,j,k,var=0;				//Bu fonksiyonda harf aramayı soldan sağa doğru yapıyorum. 

		if(this->operator()(row,column)!=pl1){	//Bakılan hücrede x yoksa 0 döndür
			return 0;
		}
								//Bakılan hücrede x varsa gelinen yolu unutmamak için path
		path[row][column]=1;	//arrayinin aynı hücresine 1 koyuyorum.
									//Eğer ilk column'dan son column'a kadar gelinebilmişse
		if(column==boardsize-1){	//x doğru bir path kurmuş demektir
			return 1;				//Galibiyet durumunda 1 döndür
		}

		if(row==0&&column==0){		//Buradaki if else bloklarında tahtanın her bir ayrı köşesi, duvarı için
			var=is_x_win(row,column+1);	//ayrı bir durumu kontrol etmem gerekti.
									//Mesela mevcut konum tahtanın sol üst köşedeki hücresiyse, bir hücre üstü veya
			if(var==0){				//bir hücre solu kontrol edemem, out of board'ı kontrol etmiş olurum.
				path[row][column]=0;//Tahtanın her spesifik köşesi/duvarı için farklı kontrol mekanizması.
			}						//Yanlış yollardan dönüp doğru yola girebilmek için recursion kullandım.
			return var;
		}
		else if(row==boardsize-1&&column==0){
			if(path[row][column+1]!=1){
				var=is_x_win(row,column+1);
			}
			if(path[row-1][column+1]!=1){
				var=var+is_x_win(row-1,column+1);
			}
			
			if(var==0){
				path[row][column]=0;
			}
			return var;
		}
		else if(row==0){
			if(path[row][column+1]!=1){
				var=var+is_x_win(row,column+1);
			}
			if(path[row+1][column]!=1){
				var=var+is_x_win(row+1,column);
			}		
			if(path[row+1][column-1]!=1){
				var=var+is_x_win(row+1,column-1);
			}
			
			if(var==0){
				path[row][column]=0;
			}
			return var;
		}
		else if(column==0){
			if(path[row-1][column+1]!=1){
				var=var+is_x_win(row-1,column+1);
			}		
			if(path[row][column+1]!=1){
				var=var+is_x_win(row,column+1);
			}
			
			if(var==0){
				path[row][column]=0;
			}
			return var;
		}
		else if(row==boardsize-1){
			if(path[row-1][column]!=1){
				var=var+is_x_win(row-1,column);
			}		
			if(path[row-1][column+1]!=1){
				var=var+is_x_win(row-1,column+1);
			}
			if(path[row][column+1]!=1){
				var=var+is_x_win(row,column+1);
			}		
			
			if(var==0){
				path[row][column]=0;
			}
			return var;
		}
		else{
			if(path[row-1][column+1]!=1){
				var=var+is_x_win(row-1,column+1);
			}		
			if(path[row][column+1]!=1){
				var=var+is_x_win(row,column+1);
			}
			if(path[row+1][column]!=1){
				var=var+is_x_win(row+1,column);
			}
			if(path[row-1][column]!=1){
				var=var+is_x_win(row-1,column);
			}
			if(path[row][column-1]!=1){
				var=var+is_x_win(row,column-1);
			}
			if(path[row+1][column-1]!=1){
				var=var+is_x_win(row+1,column-1);
			}		
			
			if(var==0){
				path[row][column]=0;
			}
			return var;
		}	
	}

	int AbstractHex::is_o_win(int row,int column){
		int i,j,var=0;					//is_x_win fonksiyonunun 'o' için düzenlenmiş hali.
		if(this->operator()(row,column)!=pl2){	//Mantık aynı.
			return 0;
		}
		
		path[row][column]=1;
		
		if(row==boardsize-1){
			return 1;
		}

		if(row==0&&column==0){
			var=is_o_win(row+1,column);
			
			if(var==0){
				path[row][column]=0;
			}
			return var;
		}
		else if(row==0&&column==boardsize-1){
			if(path[row+1][column]!=1){
				var=is_o_win(row+1,column);
			}
			if(path[row+1][column-1]!=1){
				var=var+is_o_win(row+1,column-1);
			}
			
			if(var==0){
				path[row][column]=0;
			}
			return var;
		}
		else if(row==0){
			if(path[row+1][column]!=1){
				var=var+is_o_win(row+1,column);
			}		
			if(path[row+1][column-1]!=1){
				var=var+is_o_win(row+1,column-1);
			}
			
			if(var==0){
				path[row][column]=0;
			}
			return var;
		}
		else if(column==0){
			if(path[row-1][column+1]!=1){
				var=var+is_o_win(row-1,column+1);
			}		
			if(path[row][column+1]!=1){
				var=var+is_o_win(row,column+1);
			}
			if(path[row+1][column]!=1){
				var=var+is_o_win(row+1,column);
			}
			
			if(var==0){
				path[row][column]=0;
			}
			return var;
		}
		else if(column==boardsize-1){
			if(path[row+1][column]!=1){
				var=var+is_o_win(row+1,column);
			}		
			if(path[row+1][column-1]!=1){
				var=var+is_o_win(row+1,column-1);
			}
			if(path[row][column-1]!=1){
				var=var+is_o_win(row,column-1);
			}		
			
			if(var==0){
				path[row][column]=0;
			}
			return var;
		}
		else{
			if(path[row-1][column+1]!=1){
				var=var+is_o_win(row-1,column+1);
			}
			if(path[row][column+1]!=1){
				var=var+is_o_win(row,column+1);
			}
			if(path[row+1][column]!=1){
				var=var+is_o_win(row+1,column);
			}
			if(path[row-1][column]!=1){
				var=var+is_o_win(row-1,column);
			}
			if(path[row][column-1]!=1){
				var=var+is_o_win(row,column-1);
			}
			if(path[row+1][column-1]!=1){
				var=var+is_o_win(row+1,column-1);
			}		
			
			if(var==0){
				path[row][column]=0;
			}
			return var;
		}
	}	
}

