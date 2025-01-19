
#include <iomanip> 
#include <cstring> 
#include <stdlib.h>
#include <conio.h>
#include <stdio.h> 
#include <fstream>                  
#include <iostream>
#include <locale.h>
using namespace std;

struct Mobilya
{
    char ad[80];
    char tur[80];
    char urun_no[10];
    float fiyat;
};
void MobilyaEkle();
void MobilyaListeleme();
void MobilyaArama();
void MobilyaSil();
void MobilyaDuzenle();
int main(){
    
	setlocale(LC_ALL,"Turkish");
    
    char anamenu;
    do{
    system("cls");
    
    cout << "|-------Hoþgeldiniz------|" << endl ;
    cout << "|      Seçim Yapýnýz     |" << endl ;
    cout << "|  1- Mobilya Ekleme     |" << endl ;
    cout << "|  2- Mobilya Listeleme  |" << endl ;
    cout << "|  3- Mobilya Arama      |"<< endl;
    cout << "|  4- Mobilya Silme      |"<< endl;
    cout << "|  5- Mobilya Düzenleme  |"<< endl;
    cout << "|------------------------|" << endl ;
    char secim;
    
	cin>> secim;
    if(secim=='1')
    cout << "Mobilya ekleme ekraný açýlýyor.." << endl;
    else if(secim=='2')
    cout << "Mobilya listesi açýlýyor.." << endl;
    else if (secim == '3')
    cout << "Mobilya aranýyor.." << endl;
    else if(secim=='4')
    cout << "Mobilya silme ekraný açýlýyor.." << endl;
    else if (secim== '5')
    cout << "Mobilya düzenleme ekraný açýlýyor.." << endl;
    
    cout << "----------------------------" << endl;
    
    switch(secim) 
    {
        case '1' : 
        {
        MobilyaEkle();
        break;  
        }
        case '2' : 
        {
         MobilyaListeleme() ;
         break;
        }
        case '3' : 
        {
         MobilyaArama() ;
         break;
        }
        case '4' : 
        {
         MobilyaSil()   ;
         break;
        }
        case '5' : 
        {
         MobilyaDuzenle();
         break;
        }
    }
    
    cout << "Ana menüye dönmek için : a ,çýkmak için : c tuþuna basýnýz.." <<endl ; 
    anamenu=getche();
    
    }while(anamenu=='a');
     

return 0;
}

Mobilya mob;

void MobilyaEkle()
{
    ofstream yaz("mobilya.dat", ios::binary | ios::app);
    char secim;
    int adet=0;
    
    do{
    cout << "Eklemek istediðiniz mobilyanýn adýný giriniz :" << endl;
    cin >> mob.ad;
    cout << "Eklemek istediðiniz mobilyanýn türünü giriniz :" << endl;
    cin >> mob.tur;
    cout << "Eklemek istediðiniz mobilyanýn ürün no'sunu giriniz :" << endl;
    cin >> mob.urun_no;
    cout << "Eklemek istediðiniz mobilyanýn fiyatýný giriniz :" << endl;
    cin >> mob.fiyat;
    cout << endl;
    yaz.write((char*)&mob, sizeof(mob));    
    adet++; 
    cout << "Baþka kayýt eklemek ister misiniz ? (E/H) :" << endl;
    secim=getche();
    cout << endl;
    }while(secim=='e' || secim=='E');
    
    cout << adet << " adet mobilya eklendi.." << endl;
    
    yaz.close();
    
    
}

void MobilyaListeleme()
{
    ifstream oku("mobilya.dat", ios::binary | ios::app);
    
    oku.seekg(0, ios::end);
    int kayits = oku.tellg() / sizeof(mob);
    cout << "Toplam mobilya kayýt sayýsý :" << kayits << endl;
    
    if(kayits > 0)
    {
        for(int i=0; i<kayits; i++)
        {
            oku.seekg(i * sizeof(mob));
            oku.read((char*)&mob, sizeof(mob)); 
        
            cout << i+1 << ". Mobilyanýn bilgileri ;" << endl;
            cout << "Mobilyanýn Adý : " << mob.ad << endl;
            cout << "Mobilyanýn Türü : " << mob.tur << endl;
            cout << "Mobilyanýn Ürün No : " << mob.urun_no << endl;
            cout << "Mobilyanýn Fiyatý : " << mob.fiyat << endl;
            cout << "--------------------------------------------" << endl;
        }
    }
    else
        cout << "Kayýt bulunamadý..." << endl;

    oku.close();
}

void MobilyaArama()
{
    ifstream oku("mobilya.dat", ios::binary | ios::app);
    
    oku.seekg(0, ios::end);
    int kayits = oku.tellg() / sizeof(mob);

    cout << "Aradýðýnýz ürünün numarasýný giriniz :" << endl;
    char urun_no[80];
    cin >> urun_no;
        
    if(kayits > 0)
    {
        for(int i=0; i<kayits; i++)
        {
            oku.seekg(i * sizeof(mob));
            oku.read((char*)&mob, sizeof(mob));
            
            if(strcmp(mob.urun_no, urun_no) == 0)
            {
                cout <<  "Bulunan Mobilyanýn Bilgileri ;" << endl;
                cout << "Mobilyanýn Adý : " << mob.ad << endl;
                cout << "Mobilyanýn Türü : " << mob.tur << endl;
                cout << "Mobilyanýn Ürün No : " << mob.urun_no << endl;
                cout << "Mobilyanýn Fiyatý : " << mob.fiyat << endl;
            }
        }
    }
    else
        cout << "Kayýt bulunamadý..." << endl;

    oku.close();
}

void MobilyaSil()
{
    char urun_no[80];
    char secim = ' ';
    bool var = false;
     
    ifstream oku("mobilya.dat", ios::binary | ios::app);
    
    oku.seekg(0, ios::end);

    int kayitsayisi = oku.tellg() / sizeof(mob);
    
    cout << "Kaydýný silmek istediðiniz ürün no'sunu giriniz :";
    cin >> urun_no;

    for(int i = 0; i < kayitsayisi; i++)
    {
        oku.seekg(i * sizeof(mob));
        oku.read((char*)&mob, sizeof(mob));
            
        if(strcmp(mob.urun_no, urun_no) == 0)
        {
            cout << endl;
            cout << "Mobilyanýn";
            cout << "\nAdý : " << mob.ad;
            cout << "\nTürü : " << mob.tur << endl;
            cout << "\nÜrün No : " << mob.urun_no;
            cout << "\nFiyatý : " << mob.fiyat << endl;

            cout << "\n\n Silmek istediðiniz kayýt bu mu ? [E/H] :";
            secim = getche();
            if(secim == 'H' || secim == 'h')
            {      
                Mobilya y_mob;
                ofstream y_dosya("Yedek.dat", ios::app | ios::binary);
                
                strcpy(y_mob.ad, mob.ad);
                strcpy(y_mob.tur, mob.tur);
                strcpy(y_mob.urun_no, mob.urun_no);
                y_mob.fiyat = mob.fiyat;
                        
                y_dosya.write((char*)&mob, sizeof(mob));
                y_dosya.close();
            }
            if(secim == 'e' || secim == 'E')
            {
                var = true;
            }
        }
        else
        {
            Mobilya y_mob;
            ofstream y_dosya("Yedek.dat", ios::app | ios::binary);
              
            strcpy(y_mob.ad, mob.ad);
            strcpy(y_mob.tur, mob.tur);
            strcpy(y_mob.urun_no, mob.urun_no);
            y_mob.fiyat = mob.fiyat;
                       
            y_dosya.write((char*)&mob, sizeof(mob));
            y_dosya.close();
        }
    }
    oku.close();
    if(var)
    {
        remove("mobilya.dat");
        rename("Yedek.dat", "mobilya.dat");
        cout << "\n Kayýt silindi..." << endl;
    }
    else
    {
        remove("Yedek.dat");
        cout << "\n Kayýt bulunamadý..." << endl;                  
    }
}

void MobilyaDuzenle()
{
    char urun_no[80];
    char secim = ' ';
    bool var = false;
     
    ifstream oku("mobilya.dat", ios::binary | ios::app);
    
    oku.seekg(0, ios::end);

    int kayitsayisi = oku.tellg() / sizeof(mob);
        
    cout << "Kaydýný düzeltmek istediðiniz ürünun no'sunu giriniz :";
    cin >> urun_no;

    for(int i = 0; i < kayitsayisi; i++)
    {
        oku.seekg(i * sizeof(mob));
        oku.read((char*)&mob, sizeof(mob));
            
        if(strcmp(mob.urun_no, urun_no) == 0)
        {
            cout << endl;
            cout << "Mobilyanýn";
            cout << "\nAdý : " << mob.ad;
            cout << "\nTürü : " << mob.tur << endl;
            cout << "\nÜrün No : " << mob.urun_no;
            cout << "\nFiyatý : " << mob.fiyat << endl;
                 
            cout << "\n\n Düzeltmek istediðiniz kayýt bu mu ? [E/H] :";
            secim = getche();
            if(secim == 'E' || secim == 'e')
            {
                var = true;
                ofstream dosya("Yedek.dat", ios::app | ios::binary);
                
                cout << "\nYeni mobilya adýný giriniz :";
                cin >> mob.ad;
                cout << "Yeni mobilya türünü giriniz :";
                cin >> mob.tur;
                cout << "Yeni ürün no'sunu giriniz :";
                cin >> mob.urun_no;
                cout << "Yeni mobilya fiyatýný giriniz : ";
                cin >> mob.fiyat;
                cout << endl;
          
                dosya.write((char*)&mob, sizeof(mob));
                dosya.close();
            }
            else
            {
                Mobilya y_mob;
                ofstream y_dosya;
                y_dosya.open("Yedek.dat", ios::app | ios::binary);
                         
                strcpy(y_mob.ad, mob.ad);
                strcpy(y_mob.tur, mob.tur);
                strcpy(y_mob.urun_no, mob.urun_no);
                y_mob.fiyat = mob.fiyat;
                         
                y_dosya.write((char*)&y_mob, sizeof(y_mob));
                y_dosya.close();
            }
        }
    }
    oku.close();
    if(var)
    {
        remove("mobilya.dat");
        rename("Yedek.dat", "mobilya.dat");
        cout << "\nKayýt düzenleme tamamlandý..." << endl;
    }
    else
    {
        remove("Yedek.dat");
        cout << "\nKayýt bulunamadý..." << endl;                  
    }
}

