/*===============================*
<Autores>
+Vicente Viera Guízar, ID: A01639784
+Maximiliano Villegas Garcia. ID: A01635825
+
</Autores>
=================================*
*/

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

//estructura con los datos de cada registro
struct record{
    public:
        string month;
        string day;
        string hr;
        string min;
        string sec;
        string IP;
        string status;

        //funcion para comparar dos fechas
        bool operator<=(record& a){
            if(stoi(this->month)<stoi(a.month)){
                return true;
            }else if(stoi(this->month)==stoi(a.month)){
                if(stoi(this->day)<stoi(a.day)){
                    return true;
                }else if(stoi(this->day)==stoi(a.day)){
                    if(stoi(this->hr)<stoi(a.hr)){
                        return true;
                    }else if(stoi(this->hr)==stoi(a.hr)){
                        if(stoi(this->min)<stoi(a.min)){
                            return true;
                        }else if(stoi(this->min)==stoi(a.min)){
                            if(stoi(this->sec)<=stoi(a.sec)){
                                return true;
                            }
                        }
                    }
                }
            }
        }
};

//genero el map con los meses y su valor
map<string,string> Map {
    {"Jan","1"},
    {"Feb","2"},
    {"Mar","3"},
    {"Apr","4"},
    {"May","5"},
    {"Jun","6"},
    {"Jul","7"},
    {"Aug","8"},
    {"Sep","9"},
    {"Oct","10"},
    {"Nov","11"},
    {"Dec","12"},
};

//funcion para pasar de meses a numeros
string mon2num(string month){
    //regreso el valor numerico del map
    return Map.find(month)->second;
}

//funcion para leer archivo
void readFile(vector <record> &Vector){
    record line;
    string aux;
    ifstream file;//objeto para leer archivo
    file.open("bitacora.txt");

    if(file.fail()){
        exit(0);
    }else{
        //ciclo para identificar el significado de los datos de cada registro
        while (!file.eof()){
            getline(file, line.month,' ');
            getline(file, line.day, ' ');
            getline(file, line.hr, ':' );
            getline(file, line.min, ':' );
            getline(file, line.sec, ' ' );
            getline(file, line.IP, ' ' );
            getline(file, line.status, ' ' );
            aux=mon2num(line.month);
            line.month=aux;
            Vector.push_back(line);
        }
    }
    file.close();
}

void imprime(vector<record>& x){
    for(int i=0;i<x.size();i++){
        cout<<x[i].month;
    }
}

void printFile(vector<record> &Vector){
    ofstream newfile("salida.txt");
    if (newfile.fail()){
        exit(0);
    }
    for (int i = 0; i < Vector.size(); i++){
        newfile << Vector[i].month << " ";
        newfile << Vector[i].day << " ";
        newfile << Vector[i].hr << ":";
        newfile << Vector[i].min << ":";
        newfile << Vector[i].sec << " ";
        newfile << Vector[i].IP << " ";
        newfile << Vector[i].status << endl;
    }
    newfile.close();
}

int main(){
    vector<record> d;
    readFile(d);
    cout<< d[1].month << " ";
        cout << d[1].day << " ";
        cout << d[1].hr << ":";
        cout << d[1].min << ":";
        cout << d[1].sec << " ";
        cout << d[1].IP << " ";
        cout << d[1].status << endl;
        printFile(d);

    return 0;
}
