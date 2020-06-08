#include <iostream>
#include "cmdline.h"
#include "leer_cmdline.h"
#include "imagen.h"
#include "lista.h"
#include "shunting_yard.h"
using namespace std;


/* Prototipos de funciones de opcion */

/* Funcion que maneja la opcion input. De ser pasado
 * el argumento por default, se lee por cin. De ser pasado
 * un archivo, se abre y se indica que se lee de el. */
static void opt_input(string const &);

/* Funcion que maneja la opcion output. De ser pasado
 * el argumento por default, se imprime por cout. De ser pasado
 * un archivo, se abre y se indica que se imprime en el. */
static void opt_output(string const &);

/* Funcion que maneja la opcion funcion. Por defecto indica
 * que se hace la funcion f(z) = z. */
static void opt_funcion(string const &);

/* Funcion que maneja la opcion help. Imprime el archivo help.txt
 * y termina el programa con exito. */
static void opt_help(string const &);



/* Variables globales de parámetros para ser
 * accedidas desde las funciones de opcion. */
static istream *input = 0;
static ostream *output = 0;
static ifstream input_file;
static ofstream output_file;
static lista<string> funcion;


lista<string> leer_cmdline(int argc, char * const argv[], istream*& input_, ostream*& output_, ifstream*& input_file_, ofstream*& output_file_){
  static option_t options[OPTIONS_CANT]; //Se crea el vector static de opciones
  cargar_vector_argumentos(options); //Se carga el vector
  cmdline cmdl(options); //Se crea el objeto cmdline
  cmdl.parse(argc, argv); //Se llama al metodo de la clase cmdline

  //Se cargan las variables pasadas.
  input_ = input;
  output_ = output;
  input_file_ = &input_file;
  output_file_ = &output_file;

  //Se devuelve la lista ordenada por shunting yard.
  std::cout<<"Esto le devuelvo al main:"<<funcion<<std::endl;
  std::cout<<"Largo de funcion:"<<funcion.getTamano()<<std::endl;
  return funcion;
}

void cargar_vector_argumentos(option_t* options){
  options[0] = {1, "i", "input", "-", opt_input, OPT_DEFAULT};
  options[1] = {1, "o", "output", "-", opt_output, OPT_DEFAULT};
  options[2] = {1, "f", "funcion", "-", opt_funcion, OPT_DEFAULT};
  options[3] = {0, "h", "help", NULL, opt_help, OPT_DEFAULT};
}

static void opt_input(string const & arg) {
  if(arg == "-")
    input = &cin;
  else{
    input_file.open(arg.c_str(), ios::in);
    input = &input_file;
  }
  if(!input->good()){
    cerr << MSJ_ERROR_LECTURA_ENTRADA << endl;
    exit(EXIT_FAILURE);
  }
}

static void opt_output(string const & arg) {
  if(arg == "-")
    output = &cout;
  else{
    output_file.open(arg.c_str(), ios::out);
    output = &output_file;
  }
  if(!output->good()){
    cerr << MSJ_ERROR_LECTURA_SALIDA << endl;
    exit(EXIT_FAILURE);
  }
}

static void opt_funcion(string const & arg) {
  std::cout<<funcion<<std::endl;
  std::cout<<arg<<std::endl;

  if(arg == "-") {
    funcion.push("z");
  } else {
    funcion = lista<string>(shuntingYard(arg));
  }

  std::cout<<funcion<<std::endl;
  /* EN MI OPINION ESTO YA NO VALE PORQUE SE VALIDA EN SY -MANUEL
  else{
    cerr << MSJ_ERROR_FUNCION << endl;
    exit(EXIT_FAILURE);
  }*/
}

static void opt_help(string const & arg) {
  string line;
  ifstream archivo_help;
  archivo_help.open(ARCHIVO_HELP);
  if(!archivo_help.good())
    cerr << MSJ_ERROR_HELP << endl;
  while(getline(archivo_help, line))
    cout << line << endl;
  archivo_help.close();
  exit(EXIT_SUCCESS);
}
