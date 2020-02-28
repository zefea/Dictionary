/*functions
 * kayit.cpp
 * Zeynep Ferah Akkurt 
 * 18120205001
 */ 

#include "kayit.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

//Kelime ve o kelimeye ait tum aciklamalari satir satir ekrana yazar.
ostream& operator<<(ostream& outStream, const Kayit& kayit){
	
	outStream << "Kelime: " << kayit.kelime << endl;
	outStream << "Aciklamalar: " << endl;
	for(unsigned int i=0 ; i<kayit.aciklama.size() ; i++){
		outStream << kayit.aciklama[i] << " " << endl;
	}
	return outStream;
}

// getline ile satır satır veri okunur. İlk satır kelimedir, diğer her bir satır bir açıklamadır.
// Boş açıklama geldiğinde çıkar.
istream& operator>>(istream& inStream, Kayit& kayit){
	
	unsigned int i=0,done=1;
	cout << "Girmek istediginiz kelime:" << endl; 
	getline(inStream,kayit.kelime);
	while(done){
		string c;
		cout << i+1 << ".aciklama:" << endl;
		getline(inStream,c); 
		if(c == ""){
			done = 0;
		}
		kayit.aciklama.push_back(c);
		i++;
	}
	return inStream; 
}

/* Sozlukteki her bir kayıt bir kelime ve o kelimeye ait aciklamalari icerir.
 *Bu yapici(constructor) fonksiyon bir kelime icin tek bir aciklama metni alir.*/
Kayit::Kayit(const string & kelime, const string & aciklama){
	this->kelime = kelime;
	this->aciklama.push_back(aciklama);
}

/* Bir kelimenin birden cok anlami/aciklamasi olabilir. Bu yapici aciklamalarin bir vektorunu alir.*/
Kayit::Kayit(const string & kelime, const vector<string> & aciklamalar){
	
	this->kelime = kelime;
	for(unsigned int i=0 ; i< aciklamalar.size() ; i++){
		this->aciklama.push_back(aciklamalar[i]);
	}
}

// Eger iki kaydin kelime degerleri esit ise aciklama vektorlerinin birlesim kumesi olusturulur.
// Ayni aciklama yeni kayitta birden cok kez bulunamaz!
const Kayit & Kayit::operator +(const Kayit & digerKayit){
	

	if(this->kelime == digerKayit.kelime){
		for(unsigned i= 0 ; i<digerKayit.aciklama.size() ; i++){
			int n=0;
			int x=0;
			for(unsigned j=0 ; j<this->aciklama.size() ; j++){
				if(digerKayit.aciklama[i] == this->aciklama[j])
					n++;
			}
			if(n==x)
				this->aciklama.push_back(digerKayit.aciklama[i]);   
		}
	}
	return *this;
}

// Bir kayita daha once o kayitta olmayan yeni bir anlam/aciklama eklenebilir. 
const Kayit & Kayit::operator +(const string & aciklama){
	
	unsigned int n = 0;
	for(unsigned int i = 0 ; i<this->aciklama.size() ; i++){
		if(this->aciklama[i] != aciklama){
			n++;
		}
	}
	if(n == this->aciklama.size())
		this->aciklama.push_back(aciklama);
		
	return *this;
}

// Bir kayitta bulunan anlam/aciklama cikartilabilir. Fonksiyon cikartilacak aciklamayi argüman olarak alır.
const Kayit & Kayit::operator -(const string & aciklama){
	
	for(unsigned int i = 0 ; i< this->aciklama.size() ; i++){
		if(this->aciklama[i] == aciklama)
			this->aciklama.erase(this->aciklama.begin()+i);
	}
	return *this;
}

// Bir kayit bossa (kelime == "" veya hic aciklamasi yoksa) dogru yoksa yanlis donderir
bool Kayit::operator!(){
	
	unsigned int a = 0;
	if(this->kelime == ""){
		return true;
	}
	for(unsigned int i=0 ; i< this->aciklama.size(); i++){
		if(this->aciklama[i] == "")
			a++;
	}	
	if(a == this->aciklama.size()){
		return true;
	}
	
	return false;
}

// Eger iki kaydin kelimeleri ayniysa veya kayitlar es anlamli kelimeler ise dogru donderir
// Bir kelimenin aciklamasi tek bir kelime ise o kelime ile esanlamlidir.
bool Kayit::operator==(const Kayit & digerKayit){
	
	int n = 0;
	if(this->kelime == digerKayit.kelime)  //iki kelime birbirine eşitse doğru döndürür
		return true;
		
	if(digerKayit.kelime.find(' ') != string::npos){  //iki kelimeden oluşan bir eş anlamlısı olamaz.
		return false;
	}
	//diğer kelimenin açıklamalarından biri kelimenin kendisiyle eşse doğru döndürür.
	for(unsigned int i=0 ; i< this->aciklama.size(); i++){   
		if(this->aciklama[i] == digerKayit.kelime)
			n++;
	}	
	int m = this->aciklama.size();
	if(n == m){
		return true;
	}
	
	//iki kayitta farkli iki kelimenin açıklamarına göre eş anlamlı olup olmadığını döndürür.
	for(unsigned int i=0 ; i< this->aciklama.size(); i++){
		for(unsigned int j = 0 ; j < digerKayit.aciklama.size() ; j++){
			if(this->aciklama[i] == digerKayit.aciklama[j])
				return true;
		}
	}
	return false;
}

// Eger kaydin kelimesi verilen kelime ayniysa veya kayitlar es anlamli kelimeler ise dogru donderir
// Bir kelimenin aciklamasi tek bir kelime ise o kelime ile esanlamlidir.
bool Kayit::operator==(const string & digerKelime){
	
	if(this->kelime == digerKelime)
		return true;
	if(digerKelime.find(' ') != string::npos){
		return false;
	}
	for(unsigned int i=0 ; i< this->aciklama.size(); i++){
		if(this->aciklama[i] == digerKelime)
			return true;
	}
	return false;
}

//kelime erisimi kayit uzerinden
bool Kayit::isThere(const Kayit& digerKayit)const{
	
	if(kelime == digerKayit.kelime)
		return true;

	return false;
}

//string uzerinden kelime erisimi
bool Kayit::isThere(const string & digerKelime) const{
	
	if(kelime == digerKelime)
		return true;

	return false;	
}

//aciklama silme
void Kayit::deleting(){
	
	int size = aciklama.size();
	for( int i = 0 ; i<size ; ++i){
		aciklama.erase(aciklama.begin()+i);
	}
}
 
//aciklama sayar
int Kayit::count(){
	 return aciklama.size();
}
