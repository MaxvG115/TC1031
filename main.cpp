/*===============================*
<Autores>
+Vicente Viera Guízar, ID: A01639784
+Maximiliano Villegas Garcia. ID: A01635825
+Emma Gabriela Alfaro De la Rocha. ID: A01740229
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
          return 0;
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

//genero el map con los meses y su valor
map<string,string> Map2 {
    {"1","Jan"},
    {"2","Feb"},
    {"3","Mar"},
    {"4","Apr"},
    {"5","May"},
    {"6","Jun"},
    {"7","Jul"},
    {"8","Aug"},
    {"9","Sep"},
    {"10","Oct"},
    {"11","Nov"},
    {"12","Dec"},
};

//funcion para pasar de meses a numeros
string mon2num(string month){
    //regreso el valor numerico del map
    return Map.find(month)->second;
}

//funcion para pasar de numero a mes
string num2mon(string month){
    //regreso el valor de texto del map
    return Map2.find(month)->second;
}

//funcion para leer archivo y guardar los datos en un vector
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
            getline(file, line.status);

            line.month=mon2num(line.month);
            Vector.push_back(line);
        }
    }
    file.close();
}

//generamos un archivo txt con los valores ya ordenados y con los meses escritos con letra
void printFile(vector<record> Vector){
    ofstream newfile("Bitacora_ordenada.txt");
    if (newfile.fail()){
        exit(0);
    }
    for (int i = 0; i < Vector.size(); i++){
        newfile << num2mon(Vector[i].month) << " ";
        newfile << Vector[i].day << " ";
        newfile << Vector[i].hr << ":";
        newfile << Vector[i].min << ":";
        newfile << Vector[i].sec << " ";
        newfile << Vector[i].IP << " ";
        newfile << Vector[i].status << endl;
    }
    newfile.close();
}

//funcion de intercambio de variables
void swap(record *a, record *b) {
  record t = *a;
  *a = *b;
  *b = t;
}

//hacemos la particion de quicksort
int partition(vector<record>& v, int low, int high) {
  record pivot = v[high];
  int i = (low - 1);

  for (int j = low; j < high; j++) {
    if (v[j] <= pivot) {
      i++; 
      swap(&v[i], &v[j]);
    }
  }
  
  swap(&v[i + 1], &v[high]);
  return (i + 1);
}

//ordenamos el vector con quick sort
void quickSort(vector<record>& v, int low, int high) {
  if(low < high){
    int p = partition(v, low, high);
    quickSort(v, low, p - 1);
    quickSort(v, p + 1, high);
  }
}

//algoritmo de busqueda
//primera parte: encontramos el mes con busqueda binaria
int binarySearch(vector<record>& v, int m, int low, int high) {
  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (stoi(v[mid].month) == m)
      return mid;

    if (stoi(v[mid].month) < m)
      low = mid + 1;

    else
      high = mid - 1;
  }

  return -1;
}

//segunda parte busqueda: encontramos día limite superior
int linearSearchU(vector<record>& v, int mon,int d){
    //encontramos el indice de algua posicion del mes
    int m=binarySearch(v,mon,0,v.size()-1);
    //buscamos el primer indice donde inicia el mes
    int i=m;
    while(stoi(v[i].month)==mon){
        i--;
    }
    //hacemos busqueda lineal desde el primer día del mes
    int j=(i+1);
    do{
        if(d==1){
            break;
        }else{
            j++;
        }
    }while(stoi(v[j].day)!=d);
    return j+1;
}

//busqueda lineal para el indice inferior
int linearSearchL(vector<record>& v, int mon,int d){
    //encontramos el indice de algua posicion del mes
    int m=binarySearch(v,mon,0,v.size()-1);
    //buscamos el primer indice donde inicia el mes
    int i=m;
    while(stoi(v[i].month)==mon){
        i--;
    }
    //hacemos busqueda lineal desde el primer día del mes
    int j=(i+1);
    do{
        j++;
    }while(stoi(v[j].day)<=d);
    return j;
}

//funcion imprimir rango de fechas
void printRange(int u, int l,int it){
    //declaro variables iniciales
    ifstream file;
    ofstream fileS("salida"+to_string(it)+".txt");
    string txt;
    vector<string> salida;

    //abrimos el archivo
    file.open("Bitacora_ordenada.txt");

    //leemos y guardamos cada linea en un espacio del vector
    if (file.fail()){
        exit(0);
    }

    while (!file.eof()){
            getline(file,txt);
            salida.push_back(txt);
    }

    //lo escribimos en el nuevo documento dentro de los limites
    for(int i = u;i<l;i++){
        fileS << salida[i] << endl;
    }
    fileS.close();
    file.close();
}

int main(){
    //creamos el vector
    vector<record> d;
    //leemos el archivo y asignamos valores en structs en d
    readFile(d);
    //ordenamos el vector generado
    quickSort(d,0,d.size()-1);
    //leemos los datos del vector y los guardamos en un txt con las fechas ya cambiadas
    printFile(d);

    //generamos las variables iniciales para el menu
    //con r = 0 se sale
    int controlador=1;
    int contador = 0;

    //iniciamos el menu
    do{
        //sumamos el contador
        contador++;
        int m1,d1,m2,d2;

        //pedimos los datos
        cin >> m1;
        cin >> d1;
        cin >> m2;
        cin >> d2;

        //obtenemos los margenes para mostrarlos en el txt
        int u = linearSearchU(d,m1,d1);
        int l = linearSearchL(d,m2,d2);

        //creamos el documento con los dotos en ese intervalo
        printRange(u,l,contador);

        cin.ignore();
        cin >> controlador;
    }while(controlador != 0);

    return 0;
}
