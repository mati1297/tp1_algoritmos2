#include <iostream>
#include <string>
#include <fstream>

using namespace std;


/* Programa que se encarga de probar las ejecuciones que deberian dar error,
 * se le pasa un archivo el cual contiene las lineas como se ejecutarian en la 
 * terminal. Luego devuelve en otro archivo lo que imprime el programa. */
int main(){
  ifstream file;
  file.open("ejecuciones_con_error.txt");
  string line;
  string output_line = " 2>salida_ejecuciones_con_error.txt";
  if(getline(file, line)){
    line = line + output_line;
    system(line.c_str());
  }
  output_line = " 2>>salida_ejecuciones_con_error.txt";
  while(getline(file, line)){
    line = line + output_line;
    system(line.c_str());
  }
  file.close();
}
