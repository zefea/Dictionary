#include "kayit.h"
#include <vector>
using namespace std;
class Sozluk
{
	// Sozlukteki kayitli kelime sayisini ve toplam aciklama sayisini ekrana yazdirir.
	friend ostream & operator<<(ostream & o, const Sozluk & s);
	friend ofstream& operator <<(ofstream & out,const Sozluk & s);
	friend ifstream& operator >>(ifstream & in,Sozluk & s);
public:
	/*** CONSTRUCTORS ***/
	// bos bir sozluk oluturur.
	Sozluk();
	// tek bir kayittan olusan bir sozluk olusturur.
	Sozluk(const Kayit& kayit);
	// Bir kayit vektoru alir ve sozluk olusturur. Sozlukte her kayit sadece bir kez olabilir.
	// Eger vektor icinde ayni kayit sozcugu varsa bunların aciklamalarını birlestirir.
	Sozluk(const vector<Kayit> & kayitlar);
	
	//!!! Uc buyukleri unutmayin !!!
	~Sozluk();	//destructor 
	Sozluk(const Sozluk& other); //copy constructor
	Sozluk & operator=(const Sozluk& other); //assignment

	//Verilen bir kelime degerine sahip Kaydi donderen subscript operatorunu asiriyukleyiniz
	Kayit& operator[](const string & kelime);

	// Iki sozlugu buyukluk acisindan karislatiran operatorleri asiri yukleyin
	// Karsilasirmalar toplam sozlukteki toplam aciklama sayisina gore yapilir
	// ==, !=, >, <, <=, >= operatorlerinin tamamını asiri yukleyiniz
	
	bool operator ==(const Sozluk & digerSozluk);
	bool operator !=(const Sozluk & digerSozluk);
	bool operator >(const Sozluk & digerSozluk);
	bool operator <(const Sozluk & digerSozluk);
	bool operator <=(const Sozluk & digerSozluk);
	bool operator >=(const Sozluk & digerSozluk);

	// Iki sozlugu birlestiren iki operandli + operatorunu asiri yukleyiniz. Birlesim sonunda ayni kayittan iki tane olmaz, aciklamalar bir kelime altina toplanir
	// bir kayit altinda birebir ayni aciklama iki veya daha cok kez bulunamaz
	Sozluk & operator+(const Sozluk & digerSozluk);
	// Iki sozlugu birlestiren += operatorunu asiri yukleyiniz. Birlesim sonunda ayni kayittaniki tane olmaz, aciklamalar bir kelime altina toplanir
	// bir kayit altinda birebir ayni aciklama iki veya daha cok kez bulunamaz
	Sozluk & operator+=(const Sozluk & digerSozluk);
	
	
	// Sozluk icindeki kelimede yer alan aciklamalari siler. Eger hic aciklamakalmamissa tum kelimeyi siler
	Sozluk & operator-=(const Kayit & kayit);
	// Sozluk icindeki kelimede yer alan TUM aciklamalari siler.
	Sozluk & operator-=(const string & kelime);

private:
	Kayit * kayitlar;
	unsigned int toplamKayitSayisi;
};
