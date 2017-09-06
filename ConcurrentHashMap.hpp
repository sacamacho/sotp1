#ifndef CONCURRENT_HASHMAP_H_
#define CONCURRENT_HASHMAP_H_

#include <atomic>
#include <vector>
#include <string>
#include <cstring>
#include <utility>
#include <list>
#include <iostream>
#include <fstream>
#include <mutex> 
#include <pthread.h>
#include <stdio.h>
#include "ListaAtomica.hpp"

#define DIMENSION_TABLA 26

using namespace std;

class ConcurrentHashMap {
   public:
		ConcurrentHashMap(); //constructor
		//*~ConcurrentHashMap();*/ 
		void addAndInc(string key); 
		bool member(string key);
		pair<string, unsigned int> maximum(unsigned int nt);
		vector< Lista < pair<string, unsigned int> >* > tabla;
		static ConcurrentHashMap count_words(string arch);
		static ConcurrentHashMap count_words(list<string> archs); //Ejercicio 3
		static ConcurrentHashMap count_words(unsigned int num_threads, list<string> archs);
		static void* ArmoHashMap(void *thread_args);
		static void* ArmoHashMapEj4(void *thread_args);
	private:		
		unsigned int calculoPosicion(const char letra){return (int)letra - 97;}
		pthread_mutex_t mutex[DIMENSION_TABLA];
		pthread_mutex_t mutex_maximum;

	struct datos_thread { 
		  unsigned int thread_id;
		  ConcurrentHashMap* map;
		  string archivo;
		};
		
	struct datos_tread_ejercicio4 { 
		  unsigned int thread_id;
		  ConcurrentHashMap* map;
		  list<string>::iterator* itera_ini;
		  list<string>::iterator itera_fin;
		  pthread_mutex_t* mutex_itera;
			};
	   
		// ConcurrentHashMap count_words(unsigned int n, list<string> archs); // Ejercicio 4
		// pair<string, unsigned int> maximum(unsigned int p_archivos, unsigned int p_maximos, list<string>archs); // Ejercicio 5
};

#endif /* CONCURRENT_HASHMAP__ */
