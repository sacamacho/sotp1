#ifndef CONCURRENT_HASHMAP_H_
#define CONCURRENT_HASHMAP_H_

#include <atomic>
#include <vector>
#include <string>
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
		void addAndInc(string key); 
		bool member(string key);
		pair<string, unsigned int> maximum(unsigned int nt);
		
		// lo de arriba es de la clase, lo de abajo no
		

        static void* cargoHashMap(void *thread_args); // en count_words necesita esto
		// solicita la funcion con 3 argumentos diferentes, es así?
		
		static ConcurrentHashMap count_words(string arch); //Ejercicio 2
	    static ConcurrentHashMap count_words(list<string> archs); //Ejercicio 3
		static ConcurrentHashMap count_words(unsigned int n, list<string> archs); // Ejercicio 4
		static pair<string, unsigned int> maximum(unsigned int p_archivos, unsigned int p_maximos, list<string>archs); // Ejercicio 5
				
		vector< Lista < pair<string, unsigned int> >* > tabla;

        unsigned int calculoposicion(const char letra) {
	  	return (int)letra - 97; 
		}

};

#endif /* CONCURRENT_HASHMAP__ */
