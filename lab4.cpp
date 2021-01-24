#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <stdexcept>
#include <stdlib.h>

using namespace std;
class Macierz{
    public:
        int** mm;
        int a,b;
        Macierz(int x,int y){
            a=x;
            b=y; 
            try {
                mm = new int*[x];
            }
            catch(bad_array_new_length){
                cout <<"Bledna wielkosc macierzy";
            }
            for(int i = 0; i <x; ++i){
                try{
                mm[i] = new int[y];  
                }     
                catch(out_of_range){
                    cout <<"wyszedlem za granice";
                }
                
            }    
            for(int i=0;i<x;i++){
                for(int j=0;j<y;j++){
                    try{
                        mm[i][j]=0;  
                    }     
                    catch(out_of_range){
                        cout <<"wyszedlem za granice";
                     }
                    mm[i][j]=0;
                }
            }      
        }
        Macierz(int x){
            a=x;
            b=x;
            try {
                mm = new int*[x];
            }
            catch(bad_array_new_length){
                cout <<"Bledna wielkosc macierzy";
            }
            for(int i = 0; i <x; ++i)
                mm[i] = new int[x];
            for(int i=0;i<x;i++){
                for(int j=0;j<x;j++){
                    mm[i][j]=0;
                }
            }    
        }
        Macierz(std::string filename, std::string path){
            string cokol=path+"\\"+filename;
            ifstream filel(cokol);
            string rows, columns,co;
            getline(filel,columns, ' ');
            getline(filel,rows,'\n');
            a=stoi(rows);
            b=stoi(columns);
            mm = new int*[a];
            for(int i = 0; i <a; ++i)
                mm[i] = new int[b]; 
            for(int i=0;i<a;i++){
                for(int j=0;j<b;j++){
                    getline(filel,co,' ');
                     mm[i][j]=stoi(co);
                 }
                    
            }    
            filel.close();
        }
        void set(int n,int m, int val){
            try{
                mm[n][m]=val;
            }
            catch(out_of_range){
                cout <<"Nie istnieje tak pozycja";
            }
        }
        int get(int n,int m){
            try{
                return mm[n][m];
            }
            catch(out_of_range){
                cout <<"Nie istnieje tak pozycja";
            }
        }
        Macierz add(Macierz m2){
            if(a!=m2.rows()||b!=m2.cols()){
                throw invalid_argument( "Arrays have different sizes" );
            }
            Macierz m3(m2.rows(),m2.cols());
             for(int i=0;i<a;i++){
                for(int j=0;j<b;j++){
                    m3.set(i,j,mm[i][j]+m2.get(i,j));
                }
            }   
            return m3;
        }
        Macierz subtract(Macierz m2){
            if(a!=m2.rows()||b!=m2.cols()){
                throw invalid_argument( "Arrays have different sizes" );
            }
            Macierz m3(m2.rows(),m2.cols());
             for(int i=0;i<a;i++){
                for(int j=0;j<b;j++){
                    m3.set(i,j,mm[i][j]-m2.get(i,j));
                }
            }   
            return m3;
        }
        Macierz multiply(Macierz m2){
            if(a!=m2.rows()||b!=m2.cols()){
                throw invalid_argument( "Arrays have different sizes" );
            }
            Macierz m3(m2.rows(),m2.cols());
             for(int i=0;i<a;i++){
                for(int j=0;j<b;j++){
                    m3.set(i,j,mm[i][j]*m2.get(i,j));
                }
            }   
            return m3;
        }
        int cols(){
            return b;
        }
        int rows(){
            return a;
        }
        void print(){
             for(int i=0;i<a;i++){
                for(int j=0;j<b;j++){
                   cout<<mm[i][j]<<" ";
                }
                cout << endl;
            }   
        }
        void store(std::string filename, std::string path){
            string cokol=path+"\\"+filename;
            ofstream filel(cokol);
            filel<<b<<" "<<a<<endl;
            for(int i=0;i<a;i++){
                for(int j=0;j<b;j++){
                   filel<<mm[i][j]<<" ";
                }
                filel << endl;
            }   
            filel.close();
        }

};

int main()
{
   
   Macierz hello(5);//Creating array with only one argument
   Macierz hello2(5,5);//Creating array with 2 arguments
   for(int i=0;i<hello.rows();i++){//Checking number of rows of hello through rows()
        for(int j=0;j<hello.cols();j++){//Checking number of columns of hello through cols()
            hello.set(i,j,1);//Setting every value in hello to 1 through set()
        }          
    }  
    cout<<"Macierz 1 wyglada nastepujaco:\n";
    for(int i=0;i<hello.rows();i++){//Wypisywanie macierzy hello za pomoca fukncji get()
        for(int j=0;j<hello.cols();j++){
            cout << hello.get(i,j)<< " ";
        }    
        cout <<endl;      
    }  
   for(int i=0;i<hello2.rows();i++){
        for(int j=0;j<hello2.cols();j++){
            hello2.set(i,j,2);//Setting every value in hello2 to 2
        }          
    }  
    cout<<"Macierz 2 wyglada nastepujaco:\n";
    for(int i=0;i<hello2.rows();i++){
        for(int j=0;j<hello2.cols();j++){
            cout << hello2.get(i,j)<< " ";
        }    
        cout <<endl;      
    }  
   
    try{   
        Macierz hello_add=hello.add(hello2);
         cout <<"Macierz dodawania wyglada nastepujaco: "<<endl;
        hello_add.print();
        }
    catch(invalid_argument){
        cout <<"Nie mozna dodac macierzy, macierze maja rozne rozmiary\n";
    }
    
    try{
        Macierz hello_subtract=hello2.subtract(hello);
        cout <<"Macierz odejmowania wyglada nastepujaco: "<<endl;
        hello_subtract.print();
    }
    catch(invalid_argument){
        cout <<"Nie mozna odjac macierzy, macierze maja rozne rozmiary\n";
    }
   
    try{
        Macierz hello_multiply=hello.multiply(hello2);
         cout <<"Macierz mnozenia wyglada nastepujaco: "<<endl;
        hello_multiply.print();
    }
    catch(invalid_argument){
        cout <<"Nie mozna pomnozyc macierzy, macierze maja rozne rozmiary\n";
    }
     hello.store("plik.txt","C:\\git\\lab3\\lab3");//Storing hello array
    Macierz hello3("plik.txt","C:\\lab3");//Creating hello3 array from saved file
    cout <<"Wczytana macierz wyglada nastepujaco:"<<endl;
    hello3.print();
    
}