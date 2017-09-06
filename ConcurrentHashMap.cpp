#include "ConcurrentHashMap.hpp"
#define debug 0

//ConcurrentHashMap::ConcurrentHashMap() {
//  for (int i = 0; i < DIMENSION_TABLA; i++) {
//    Lista< pair<string, unsigned int> > * l = new Lista< pair<string, unsigned int> >();
//    tabla.push_back(l);
//  }
//}


ConcurrentHashMap::ConcurrentHashMap() {
  // inicializamos listas vacias y mutex que usa la clase
  for (int i = 0; i < DIMENSION_TABLA; i++) {
    Lista< pair<string, unsigned int> > * l = new Lista< pair<string, unsigned int> >();
    tabla.push_back(l);
    pthread_mutex_init(&mutex[i], NULL);
  }
  pthread_mutex_init(&mutex_maximum, NULL);
}
  
//ConcurrentHashMap::~ConcurrentHashMap() {}*/

//ConcurrentHashMap::~ConcurrentHashMap(){
//   for (int i = 0; i < DIMENSION_TABLA; i++) {
//        delete tabla[i];
//      } 
//}
//*/

//
//void ConcurrentHashMap::addAndInc(string key){
//  char c = key.at(0);
//  unsigned int pos = calculoPosicion(c); //posicion en el arreglo.
//  bool existsEqual = false;
//  Lista<<string, unsigned int>> *l = tabla[pos];
//  for (auto it = l->CrearIt(); it.HaySiguiente(); it.Avanzar()) {
//    auto t = it.Siguiente();
//    if(key == t.first){
//      it.SiguienteRef()->_val.second += 1;
//      existsEqual = true;
//      break;
//    }
//  }
//  if(!existsEqual){
//    pair<string, unsigned int> p = make_pair(key,1);
//    l->push_front(p);
//  }
//}

//

void ConcurrentHashMap::addAndInc(string key){
  char c = key.at(0);
  unsigned int pos = calculoPosicion(key[0]);
  bool existsEqual = false;

 
  pthread_mutex_lock(&mutex_maximum);
   
  pthread_mutex_lock(&mutex[pos]);
  
  auto it = tabla[pos]->CrearIt();

    while (it.HaySiguiente() && !existsEqual) {
    if (it.Siguiente().first == key) {
      it.Siguiente().second++;
      existsEqual = true;
    }
    it.Avanzar();
  }
  
 
  if (!existsEqual) {
    pair<string, unsigned int> entrada_diccionario (key,1);
    tabla[pos]->push_front(entrada_diccionario);
  }

 
  pthread_mutex_unlock(&mutex[pos]);
 
  pthread_mutex_unlock(&mutex_maximum);
}

bool ConcurrentHashMap::member(string key){
  
  unsigned int indice = calculoPosicion(key.at(0));
  // creamos iterador para la lista
  auto itera = tabla[indice]->CrearIt();

  // buscamos string 
  while(itera.HaySiguiente()) {
    if(itera.Siguiente().first == key)
      return true;
    itera.Avanzar();
  }
  return false;
}


// pair<string, unsigned int> ConcurrentHashMap::maximum(unsigned int nt) {
//   return make_pair("hola",1);
// }

// pair<string, unsigned int> ConcurrentHashMap::maximum(unsigned int p_archivos, unsigned int p_maximos, list<string>archs) {
//   return make_pair("hola",1);
// }

// ConcurrentHashMap ConcurrentHashMap::count_words(string arch) {
//   return new ConcurrentHashMap();
// }
  
// ConcurrentHashMap ConcurrentHashMap::count_words(list<string> archs) {
//   return new ConcurrentHashMap();
// }

// ConcurrentHashMap ConcurrentHashMap::count_words(unsigned int num_threads, list<string> archs) {
//   return new ConcurrentHashMap();
// }

  
ConcurrentHashMap ConcurrentHashMap::count_words(string arch) {
                  
  ConcurrentHashMap map;
    
  ifstream inFile;
  inFile.open(arch.c_str()); 
  string palabra;
 
  while (inFile >> palabra) {
    map.addAndInc(palabra);
  }
  inFile.close();

  return map;
}
//Ejercicio 3

void *ConcurrentHashMap::ArmoHashMap(void *thread_args) {
  
  struct datos_thread* datos;
  datos = (struct datos_thread*) thread_args;
  string arch = datos->archivo;

  
  ifstream inFile;
  inFile.open(arch.c_str()); 
  string palabra;

 
  while (inFile >> palabra)
    (datos->map)->addAndInc(palabra);

 
  inFile.close();

  pthread_exit(NULL);
}

ConcurrentHashMap ConcurrentHashMap::count_words(list<string> archs) {

  unsigned int num_threads = archs.size();
  pthread_t threads[num_threads];           
  ConcurrentHashMap map;                    
  datos_thread args[num_threads]; // en cada thread tengo id string y archivo
  list<string>::iterator itera = archs.begin(); 
  
  int resultado;

  
  for (unsigned int i = 0; i < num_threads; i++) {
    args[i] = {i, &map, *itera};  
    resultado=pthread_create(&threads[i], NULL, ConcurrentHashMap::ArmoHashMap, (void*) &args[i]);
    
    if (resultado) {
      printf("ERROR en pthread_create()  %d)\n resultado %d", i , resultado);
      exit(-1);
    }
   
    itera++;
  }

  
  void *status;
  
  for (unsigned int i= 0; i < num_threads; i++) {
     resultado = pthread_join(threads[i], &status);
    if (resultado) {
      printf("ERROR en pthread_join()   %d)\n resultado %d", i, resultado);
      exit(-1);
    }
  }

  return map;
} 
//Ejercicio 4
ConcurrentHashMap ConcurrentHashMap::count_words(unsigned int num_threads, list<string> archs) {
  
  if (num_threads > archs.size()) 
    num_threads = archs.size();

  pthread_t threads[num_threads];           
  
  ConcurrentHashMap map;                    
  
  list<string>::iterator itera_ini = archs.begin();  
   
  list<string>::iterator itera_fin = archs.end();       
  
  pthread_mutex_t mutex_itera;                          
  
  pthread_mutex_init(&mutex_itera, NULL);
  
  datos_tread_ejercicio4 args[num_threads]; 
 
  int resultado;

  
  for (unsigned int i = 0; i < num_threads; i++) {
    args[i] = {i, &map, &itera_ini, itera_fin, &mutex_itera};
    resultado = pthread_create(&threads[i], NULL, ConcurrentHashMap::ArmoHashMapEj4, (void*) &args[i]);
      
    if (resultado) {
         printf("ERROR en pthread_create()  %d)\n resultado %d", i , resultado);
      exit(-1);
    }
  }

  
  void *status;
  for (int i = 0; i < num_threads; i++) {
    resultado = pthread_join(threads[i], &status);
    if (resultado) {
         printf("ERROR en pthread_join()  %d)\n resultado %d", i , resultado);
      exit(-1);
    }
  }

  return map;
}
void *ConcurrentHashMap::ArmoHashMapEj4(void *thread_args) {

  struct datos_tread_ejercicio4* datos;
  datos = (struct datos_tread_ejercicio4*) thread_args;
  list<string>::iterator* it = datos->itera_ini;
  list<string>::iterator itera_fin = datos->itera_fin;
  ifstream inFile;
  string arch;
  
  while (true) {
    
    pthread_mutex_lock(datos->mutex_itera);
 
    if (*it != itera_fin) {
      arch = *(*it);
      (*it)++;
    }
    else
      break;
 
    pthread_mutex_unlock(datos->mutex_itera);

  
    inFile.open(arch.c_str()); 
    string palabra;

    
    while (inFile >> palabra)
      (datos->map)->addAndInc(palabra);

   
    inFile.close();
  }
  
  pthread_mutex_unlock(datos->mutex_itera);

  
  pthread_exit(NULL);
}

