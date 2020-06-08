#include <iostream>
#include <fstream>
#include "imagen.h"
#include "cmdline.h"
#include "leer_cmdline.h"
#include "lista.h"


using namespace std;
/*
	if(argc < 2)
		return 0;

	lista<string> argumentos = shuntingYard(argv[1]);

	cout << argumentos << endl;
	prueba_transf = prueba.transformar(argumentos);
*/

int main(int argc, char * const argv[]) {
  /*Variables que se cargan con la funcion leer_argumentos
   * a partir de los parametros pasados por cmdline*/
  istream *input_ = 0;
  ostream *output_ = 0;
  ifstream *input_file_ = 0;
  ofstream *output_file_ = 0;
  lista<string> funcion; //Selector de funcion


  //Llamado a funcion para leer los argumentos de la linea de comandos.
  funcion = leer_cmdline(argc, argv, input_, output_, input_file_, output_file_);

  Imagen imagen_input = Imagen(); //Se crea una nueva imagen
  //Se carga con la lectura del archivo PGM, en caso de la función
  //devolver error, se cierran los archivos y se termina el programa
  //con un error.
  if(imagen_input.readPGM(*input_)){
    input_file_->close();
    output_file_->close();
    exit(EXIT_FAILURE);
  }

  //Se transforma la imagen de entrada y se guarda en una nueva imagen
  //de salida (por constructor por copia).
  Imagen imagen_output = imagen_input.transformar(funcion);

  std::cout<<"Llegue al main despues de transformar OwO"<<std::endl;

  imagen_output.savePGM(*output_);//Se guarda la nueva imagen en un pgm.
  //Se cierran los archivos.
  input_file_->close();
  output_file_->close();


  return(EXIT_SUCCESS); //Se termina el programa correctamente.
}
