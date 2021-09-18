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

//funcion para pasar de meses a numeros

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

string mon2num(string month){
    //regreso el valor numerico del map
    return Map.find(month)->second;
}

int main(){
    cout<<mon2num("Dec");

    return 0;
}
