#ifndef CONCURRENT_HASHMAP_H_
#define CONCURRENT_HASHMAP_H_

#include <atomic>
#include <vector>
#include <string>
#include <cstring>
//#include <utility>
#include <list>
#include <iostream>
//#include <fstream>
//#include <mutex> 
#include <pthread.h>
//#include <stdio.h>
#include "ListaAtomica.hpp"

#define DIMENSION_TABLA 26

using namespace std;

class ConcurrentHashMap {
	private:		
		unsigned int calculoPosicion(const char letra){return (int)letra - 97;}

	public:
		ConcurrentHashMap(); //constructor
		~ConcurrentHashMap();
		void addAndInc(string key); 
		bool member(string key);
		pair<string, unsigned int> maximum(unsigned int nt);

		vector< Lista < pair<string, unsigned int> >* > tabla;
		
		// lo de arriba es de la clase, lo de abajo no
		

        // void* cargoHashMap(void *thread_args); // en count_words necesita esto
		// solicita la funcion con 3 argumentos diferentes, es así?
		
		// ConcurrentHashMap count_words(string arch); //Ejercicio 2
	 //    ConcurrentHashMap count_words(list<string> archs); //Ejercicio 3
		// ConcurrentHashMap count_words(unsigned int n, list<string> archs); // Ejercicio 4
		// pair<string, unsigned int> maximum(unsigned int p_archivos, unsigned int p_maximos, list<string>archs); // Ejercicio 5
};

#endif /* CONCURRENT_HASHMAP__ */
