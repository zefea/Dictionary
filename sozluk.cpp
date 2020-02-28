/* functions 
 * Zeynep Ferah Akkurt
 * 
 * 18120205001
 * sozluk.cpp
 * 
 * odev6-5
 * ifstream ve ofstream fonksiyonlarinin yazilmasi
 * 
 * (odev5'i zamaninda teslim etmistim)
 */

#include "sozluk.h"
#include <fstream>

//output
ostream & operator<<(ostream & o, const Sozluk & s){
	
	int toplamaciklama = 0;
	if(s.toplamKayitSayisi == 0){
		o << "BOS KAYIT" << endl;
		return o;
	}
	for(unsigned i = 0 ; i<s.toplamKayitSayisi ; ++i)
		toplamaciklama = toplamaciklama + s.kayitlar[i].count();
	
	o << "Sozlukteki aciklama sayisi:  " << toplamaciklama << endl;
	o << "Sozlukteki kayit sayisi:  " << s.toplamKayitSayisi << endl;
	return o;
}

//kayitlari dosyaya yazdirir
ofstream & operator<<(ofstream & out, const Sozluk & s){
	
	for(unsigned i=0 ; i < s.toplamKayitSayisi ; ++i){
		out << "KAYIT" << i+1 << endl << s.kayitlar[i] << endl;
	}
	return out;
}

//kayitlari dosyadan okur
ifstream & operator>>(ifstream & in, Sozluk & s){
	
	string next,kelime,anlam;
	vector<Kayit>soz;
	while(getline(in,next)){   			//kacinci kayit oldugunu okur
		vector<string>a;				//aciklamalari bir sureligine tutar.
		in >> next;						//kelime yazisini okur.
		getline(in,kelime);				//kelimenin kendisini okur.
		getline(in,next);				//aciklamalar basligini okur
		while(getline(in,anlam)){		//aciklamalari okur.
			if(anlam == "")break;		//aciklamalar bittiyse cikar.
			  a.push_back(anlam);
		}
		Kayit yeni(kelime,a);
		soz.push_back(yeni);	
	}
	Sozluk s2(soz);
	s = s2;
	
	return in;
}
// bos bir sozluk oluturur.
Sozluk::Sozluk(){
	kayitlar = nullptr;
	toplamKayitSayisi = 0;
}
// tek bir kayittan olusan bir sozluk olusturur.
Sozluk::Sozluk(const Kayit& kayit){
	
	kayitlar = new Kayit[1];
	if(kayitlar == nullptr)
		exit(-1);
	kayitlar[0] = kayit;
	toplamKayitSayisi = 1;
}
// Bir kayit vektoru alir ve sozluk olusturur. Sozlukte her kayit sadece bir kez olabilir.
// Eger vektor icinde ayni kayit sozcugu varsa bunların aciklamalarını birlestirir.
Sozluk::Sozluk(const vector<Kayit> & kayitlar){
	
	toplamKayitSayisi = kayitlar.size();
	//yedekleme
	vector<Kayit>temp;
	for(unsigned i=0 ; i<toplamKayitSayisi; ++i){
		temp.push_back(kayitlar[i]);
	}
	
	//ayni kaydi silme
	for(unsigned i= 0; i<toplamKayitSayisi; ++i){
		for(unsigned j=i+1 ; j<toplamKayitSayisi; ++j){
			if(temp[i].isThere(temp[j])){
				temp[i] + temp[j];
				temp.erase(temp.begin()+j);
			}
		}
	}
	toplamKayitSayisi = temp.size();
	this->kayitlar = nullptr;
	this->kayitlar = new Kayit[toplamKayitSayisi];
	if(this->kayitlar == nullptr)
		exit(-1);
	//gercek kayit
	for(unsigned i=0 ; i<toplamKayitSayisi; ++i){
		this->kayitlar[i] = temp[i];
	}
}

//destructor
Sozluk::~Sozluk(){
	if(kayitlar != nullptr)
		delete[] kayitlar;
}
//copy constructor
Sozluk::Sozluk(const Sozluk& other){
	
	kayitlar = nullptr;
	toplamKayitSayisi = other.toplamKayitSayisi;
	if(toplamKayitSayisi > 0){
		kayitlar = new Kayit[toplamKayitSayisi];
		if(kayitlar == nullptr)
			exit(-1);
		for(unsigned i = 0 ; i<toplamKayitSayisi ; ++i){
			kayitlar[i] = other.kayitlar[i];
		}	
	}
} 

//assigment
Sozluk & Sozluk::operator=(const Sozluk& other){
	
	if(this == &other) //self assigment
		return *this;
		
	if(kayitlar != nullptr)
		delete[] kayitlar;
		
	toplamKayitSayisi = other.toplamKayitSayisi;
	kayitlar = new Kayit[toplamKayitSayisi];
	if(kayitlar == nullptr)
		exit(-1);
		
	for(unsigned i = 0 ; i<toplamKayitSayisi ; ++i){
		kayitlar[i] = other.kayitlar[i];
	}
	return *this;
}



//Verilen bir kelime degerine sahip Kaydi donderen subscript operatorunu asiriyukleyiniz
Kayit& Sozluk::operator[](const string & kelime){
	unsigned i;
	for(i = 0 ; i<2; ++i){
		if(this->kayitlar[i] == kelime)
			return kayitlar[i];
	}
	cout << "ERROR" << endl;
	cout << "bulunamadi" << endl;
	exit(-1);  
}

/*Iki sozlugu birlestiren iki operandli + operatorunu asiri yukleyiniz. Birlesim sonunda ayni kayittan iki tane olmaz, 	
 *aciklamalar bir kelime altina toplanir
 *bir kayit altinda birebir ayni aciklama iki veya daha cok kez bulunamaz*/
Sozluk & Sozluk::operator+(const Sozluk & digerSozluk){	
	
	vector<Kayit>temp;
	for(unsigned i=0 ; i<toplamKayitSayisi; ++i){
		temp.push_back(kayitlar[i]);
	}
	for(unsigned i=0; i<digerSozluk.toplamKayitSayisi; ++i){
		temp.push_back(digerSozluk.kayitlar[i]);
	
	}
	//ayni kaydi silme
	for(unsigned i= 0; i<temp.size(); ++i){
		for(unsigned j=i+1 ; j<temp.size(); ++j){
			if(temp[i].isThere(temp[j])){
				temp[i] + temp[j];
				temp.erase(temp.begin()+j);
			}
		}
	}
	
	delete[] kayitlar;
	toplamKayitSayisi = temp.size();
	kayitlar = new Kayit[toplamKayitSayisi];
	if(kayitlar == nullptr)
		exit(-1);
	//gercek kayit
	for(unsigned i=0 ; i<toplamKayitSayisi; ++i){
		this->kayitlar[i] = temp[i];
	}
	return *this;
}
// Iki sozlugu birlestiren += operatorunu asiri yukleyiniz. Birlesim sonunda ayni kayittaniki tane olmaz, aciklamalar bir kelime altina toplanir
// bir kayit altinda birebir ayni aciklama iki veya daha cok kez bulunamaz
Sozluk & Sozluk::operator+=(const Sozluk & digerSozluk){
	
	Sozluk unionSet = *this + digerSozluk;

	*this = unionSet;

	return *this;
	
}

// Sozluk icindeki kelimede yer alan TUM aciklamalari siler.
Sozluk & Sozluk::operator-=(const string & kelime){
	for(unsigned i = 0 ; i<toplamKayitSayisi ; ++i){
		if(kayitlar[i].isThere(kelime))
			kayitlar[i].deleting();
	}
	return *this;
}


// Sozluk icindeki kelimede yer alan aciklamalari siler. Eger hic aciklama kalmamissa tum kelimeyi siler
Sozluk & Sozluk::operator-=(const Kayit & kayit){
	
	vector<Kayit>temp;    //sözlükteki silinecek kayit hariç tüm kayıtları tutar
	for(unsigned i = 0 ; i<toplamKayitSayisi ; ++i){
		if(!(kayitlar[i].isThere(kayit))){
			temp.push_back(kayitlar[i]);
		}
	}
	delete[] kayitlar;
	toplamKayitSayisi = temp.size();
	kayitlar = new Kayit[toplamKayitSayisi];
	if(kayitlar == nullptr)
		exit(-1);
	for(unsigned i=0 ; i<toplamKayitSayisi; ++i){
		this->kayitlar[i] = temp[i];
	}
	return *this;
}

//toplam sozlukteki toplam aciklama sayisina gore yapilir
bool Sozluk::operator ==(const Sozluk & digerSozluk){
	
	int total =0,total2=0;
	for(unsigned int i=0 ; i< digerSozluk.toplamKayitSayisi ; ++i){
		total += digerSozluk.kayitlar[i].count();
	}
	for(unsigned int i=0 ; i< toplamKayitSayisi ; ++i){
		total2 += this->kayitlar[i].count();
	}
	if(total2 == total)
		return true;
		
	return false;
}

//aciklama sayisi esit degilse dogru dondurur.
bool Sozluk::operator !=(const Sozluk & digerSozluk){
	int total =0,total2=0;
	for(unsigned int i=0 ; i< digerSozluk.toplamKayitSayisi ; ++i){
		total += digerSozluk.kayitlar[i].count();
	}
	for(unsigned int i=0 ; i< toplamKayitSayisi ; ++i){
		total2 += this->kayitlar[i].count();
	}
	if(total2 != total)
		return true;
		
	return false;
}

//aciklama sayisi buyukse
bool Sozluk::operator >(const Sozluk & digerSozluk){
	int total =0,total2=0;
	for(unsigned int i=0 ; i< digerSozluk.toplamKayitSayisi ; ++i){
		total += digerSozluk.kayitlar[i].count();
	}
	for(unsigned int i=0 ; i< toplamKayitSayisi ; ++i){
		total2 += this->kayitlar[i].count();
	}
	if(total2 > total)
		return true;
		
	return false;
}

//aciklama sayisi kucukse
bool Sozluk::operator <(const Sozluk & digerSozluk){
	int total =0,total2=0;
	for(unsigned int i=0 ; i< digerSozluk.toplamKayitSayisi ; ++i){
		total += digerSozluk.kayitlar[i].count();
	}
	for(unsigned int i=0 ; i< toplamKayitSayisi ; ++i){
		total2 += this->kayitlar[i].count();
	}
	if(total2 < total)
		return true;
		
	return false;
}

//kucuk esit
bool Sozluk::operator <=(const Sozluk & digerSozluk){
	int total =0,total2=0;
	for(unsigned int i=0 ; i< digerSozluk.toplamKayitSayisi ; ++i){
		total += digerSozluk.kayitlar[i].count();
	}
	for(unsigned int i=0 ; i< toplamKayitSayisi ; ++i){
		total2 += this->kayitlar[i].count();
	}
	if(total2 <= total)
		return true;
		
	return false;
}

//buyuk esit
bool Sozluk::operator >=(const Sozluk & digerSozluk){
	int total =0,total2=0;
	for(unsigned int i=0 ; i< digerSozluk.toplamKayitSayisi ; ++i){
		total += digerSozluk.kayitlar[i].count();
	}
	for(unsigned int i=0 ; i< toplamKayitSayisi ; ++i){
		total2 += this->kayitlar[i].count();
	}
	if(total2 >= total)
		return true;
		
	return false;
}
