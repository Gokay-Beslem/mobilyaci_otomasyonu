
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
    
    cout << "|-------Ho�geldiniz------|" << endl ;
    cout << "|      Se�im Yap�n�z     |" << endl ;
    cout << "|  1- Mobilya Ekleme     |" << endl ;
    cout << "|  2- Mobilya Listeleme  |" << endl ;
    cout << "|  3- Mobilya Arama      |"<< endl;
    cout << "|  4- Mobilya Silme      |"<< endl;
    cout << "|  5- Mobilya D�zenleme  |"<< endl;
    cout << "|------------------------|" << endl ;
    char secim;
    
	cin>> secim;
    if(secim=='1')
    cout << "Mobilya ekleme ekran� a��l�yor.." << endl;
    else if(secim=='2')
    cout << "Mobilya listesi a��l�yor.." << endl;
    else if (secim == '3')
    cout << "Mobilya aran�yor.." << endl;
    else if(secim=='4')
    cout << "Mobilya silme ekran� a��l�yor.." << endl;
    else if (secim== '5')
    cout << "Mobilya d�zenleme ekran� a��l�yor.." << endl;
    
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
    
    cout << "Ana men�ye d�nmek i�in : a ,��kmak i�in : c tu�una bas�n�z.." <<endl ; 
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
    cout << "Eklemek istedi�iniz mobilyan�n ad�n� giriniz :" << endl;
    cin >> mob.ad;
    cout << "Eklemek istedi�iniz mobilyan�n t�r�n� giriniz :" << endl;
    cin >> mob.tur;
    cout << "Eklemek istedi�iniz mobilyan�n �r�n no'sunu giriniz :" << endl;
    cin >> mob.urun_no;
    cout << "Eklemek istedi�iniz mobilyan�n fiyat�n� giriniz :" << endl;
    cin >> mob.fiyat;
    cout << endl;
    yaz.write((char*)&mob, sizeof(mob));    
    adet++; 
    cout << "Ba�ka kay�t eklemek ister misiniz ? (E/H) :" << endl;
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
    cout << "Toplam mobilya kay�t say�s� :" << kayits << endl;
    
    if(kayits > 0)
    {
        for(int i=0; i<kayits; i++)
        {
            oku.seekg(i * sizeof(mob));
            oku.read((char*)&mob, sizeof(mob)); 
        
            cout << i+1 << ". Mobilyan�n bilgileri ;" << endl;
            cout << "Mobilyan�n Ad� : " << mob.ad << endl;
            cout << "Mobilyan�n T�r� : " << mob.tur << endl;
            cout << "Mobilyan�n �r�n No : " << mob.urun_no << endl;
            cout << "Mobilyan�n Fiyat� : " << mob.fiyat << endl;
            cout << "--------------------------------------------" << endl;
        }
    }
    else
        cout << "Kay�t bulunamad�..." << endl;

    oku.close();
}

void MobilyaArama()
{
    ifstream oku("mobilya.dat", ios::binary | ios::app);
    
    oku.seekg(0, ios::end);
    int kayits = oku.tellg() / sizeof(mob);

    cout << "Arad���n�z �r�n�n numaras�n� giriniz :" << endl;
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
                cout <<  "Bulunan Mobilyan�n Bilgileri ;" << endl;
                cout << "Mobilyan�n Ad� : " << mob.ad << endl;
                cout << "Mobilyan�n T�r� : " << mob.tur << endl;
                cout << "Mobilyan�n �r�n No : " << mob.urun_no << endl;
                cout << "Mobilyan�n Fiyat� : " << mob.fiyat << endl;
            }
        }
    }
    else
        cout << "Kay�t bulunamad�..." << endl;

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
    
    cout << "Kayd�n� silmek istedi�iniz �r�n no'sunu giriniz :";
    cin >> urun_no;

    for(int i = 0; i < kayitsayisi; i++)
    {
        oku.seekg(i * sizeof(mob));
        oku.read((char*)&mob, sizeof(mob));
            
        if(strcmp(mob.urun_no, urun_no) == 0)
        {
            cout << endl;
            cout << "Mobilyan�n";
            cout << "\nAd� : " << mob.ad;
            cout << "\nT�r� : " << mob.tur << endl;
            cout << "\n�r�n No : " << mob.urun_no;
            cout << "\nFiyat� : " << mob.fiyat << endl;

            cout << "\n\n Silmek istedi�iniz kay�t bu mu ? [E/H] :";
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
        cout << "\n Kay�t silindi..." << endl;
    }
    else
    {
        remove("Yedek.dat");
        cout << "\n Kay�t bulunamad�..." << endl;                  
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
        
    cout << "Kayd�n� d�zeltmek istedi�iniz �r�nun no'sunu giriniz :";
    cin >> urun_no;

    for(int i = 0; i < kayitsayisi; i++)
    {
        oku.seekg(i * sizeof(mob));
        oku.read((char*)&mob, sizeof(mob));
            
        if(strcmp(mob.urun_no, urun_no) == 0)
        {
            cout << endl;
            cout << "Mobilyan�n";
            cout << "\nAd� : " << mob.ad;
            cout << "\nT�r� : " << mob.tur << endl;
            cout << "\n�r�n No : " << mob.urun_no;
            cout << "\nFiyat� : " << mob.fiyat << endl;
                 
            cout << "\n\n D�zeltmek istedi�iniz kay�t bu mu ? [E/H] :";
            secim = getche();
            if(secim == 'E' || secim == 'e')
            {
                var = true;
                ofstream dosya("Yedek.dat", ios::app | ios::binary);
                
                cout << "\nYeni mobilya ad�n� giriniz :";
                cin >> mob.ad;
                cout << "Yeni mobilya t�r�n� giriniz :";
                cin >> mob.tur;
                cout << "Yeni �r�n no'sunu giriniz :";
                cin >> mob.urun_no;
                cout << "Yeni mobilya fiyat�n� giriniz : ";
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
        cout << "\nKay�t d�zenleme tamamland�..." << endl;
    }
    else
    {
        remove("Yedek.dat");
        cout << "\nKay�t bulunamad�..." << endl;                  
    }
}

