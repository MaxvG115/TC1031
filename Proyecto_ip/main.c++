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

using namespace std;

struct record{
    public:
        string date;
        string IPqrt1;
        string IPqrt2; 
        string IPqrt3; 
        string IPqrt4;
        string port;
        string status;

        //funcion para comparar dos fechas
        bool operator<=(record& a){
            if(stoi(this->IPqrt1)<stoi(a.IPqrt1)){
                return true;
            }else if(stoi(this->IPqrt1)==stoi(a.IPqrt1)){
                if(stoi(this->IPqrt2)<stoi(a.IPqrt2)){
                    return true;
                }else if(stoi(this->IPqrt2)==stoi(a.IPqrt2)){
                    if(stoi(this->IPqrt3)<stoi(a.IPqrt3)){
                        return true;
                    }else if(stoi(this->IPqrt3)==stoi(a.IPqrt3)){
                        if(stoi(this->IPqrt4)<stoi(a.IPqrt4)){
                            return true;
                        }else if(stoi(this->IPqrt4)==stoi(a.IPqrt4)){
                            if(stoi(this->port)<=stoi(a.port)){
                                return true;
                            }
                        }
                    }
                }
            }
          return 0;
        }
};
