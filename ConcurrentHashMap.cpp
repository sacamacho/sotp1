#include "ConcurrentHashMap.hpp"
#define debug 0

ConcurrentHashMap::ConcurrentHashMap() {
  // inicializamos listas vacias y mutex que usa la clase
  for (int i = 0; i < DIMENSION_TABLA; i++) {
    Lista< pair<string, unsigned int> > * l = new Lista< pair<string, unsigned int> >();
    tabla.push_back(l);
    pthread_mutex_init(&mutex[i], NULL);
  }
  pthread_mutex_init(&mutex_maximum, NULL);
}
  
// ConcurrentHashMap::~ConcurrentHashMap(){
//   for (int i = 0; i < DIMENSION_TABLA; i++) {
//     delete tabla[i];
//     pthread_mutex_destroy(&mutex[i]);
//   } 
//   pthread_mutex_destroy(&mutex_maximum);
// }

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


pair<string, unsigned int> ConcurrentHashMap::maximum(unsigned int nt) {

  pair<string, unsigned int> maxPair ("",0);
  if(nt > DIMENSION_TABLA){nt=DIMENSION_TABLA;}

  pthread_t thread[nt]; int tid;
  atomic<int> atPos{0};
  vector<pair<string, unsigned int>> maxVector(DIMENSION_TABLA);
  sMax._pos= &atPos;
  sMax._maxVector = &maxVector;

  for (tid = 0; tid < nt; ++tid)
  {
    pthread_create(&thread[tid], NULL, search_max, &sMax);
  }
  for (tid = 0; tid < nt; ++tid)
  {
    pthread_join(thread[tid], NULL);
  }

  for(vector<pair<string, unsigned int>>::iterator it = maxVector.begin(); it != maxVector.end(); ++it )
  {
    if(it->second > maxPair.second){
      maxPair = *it;
    }
  }

  return maxPair;
}

void *ConcurrentHashMap::search_max(void * arg){
  strucMaximum sMax = *((strucMaximum *) arg);
  int dimTabla = DIMENSION_TABLA;
  while(*(sMax._pos) < dimTabla){
    int i = (*(sMax._pos)).fetch_add(1);

    auto itera = tabla[i]->CrearIt();
    pair<string, unsigned int> maxPair ("",0);

    while(itera.HaySiguiente()) {
      if(itera.Siguiente().second > maxPair.second)
        maxPair = itera.Siguiente();
      itera.Avanzar();
    }
    strucMaximum._maxVector[i] = maxPair;
  }
  
}
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
