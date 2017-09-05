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
