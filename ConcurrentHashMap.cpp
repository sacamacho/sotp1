#include "ConcurrentHashMap.hpp"
//define debug 0

ConcurrentHashMap::ConcurrentHashMap() {
    for (int i = 0; i < DIMENSION_TABLA; i++) {
      Lista< pair<string, unsigned int> > * list = new Lista< pair<string, unsigned int> >();
      tabla.push_back(list);
    }
}
  
bool ConcurrentHashMap::member(string key){
  
  unsigned int indice = calculoposicion(key[0]);
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

  
