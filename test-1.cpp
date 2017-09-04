#include <iostream>
#include "ListaAtomica.hpp"
#define CANT_THREADS 4

using namespace std;

struct ListAndPair {
	ListAndPair(Lista<pair<string, unsigned int>> *l, pair<string, unsigned int> p) : _list(l), _p(p) {}
	Lista<pair<string, unsigned int>> *_list;
	pair<string, unsigned int> _p;
};

void *pushea_front(void *lAP)
{
	ListAndPair lAP = *(ListAndPair *) lAP;
	lAP._list->push_front(lAP._p);
	//printf("Hola mundo! Soy el thread nro. %d.\n", minumero);
	return NULL;
}

int main(void) {

	// cout << "----LISTA SIN PTHREADS----" << endl;
	Lista<pair<string, unsigned int>> *l= new Lista<pair<string, unsigned int>>;
	// pair<string, unsigned int> p1 = make_pair("(primer push_front) pos:", 3);
	// pair<string, unsigned int> p2 = make_pair("(segundo push_front) pos:", 2);
	// pair<string, unsigned int> p3 = make_pair("(tercer push_front) pos:", 1);
	// l->push_front(p1);
	// l->push_front(p2);
	// l->push_front(p3);
	// for (auto it = l->CrearIt(); it.HaySiguiente(); it.Avanzar()) {
	// 	auto t = it.Siguiente();
	// 	cout << t.first << " " << t.second << endl;
	// }

	cout << "----LISTA CON PTHREADS----" << endl;
	pthread_t thread[CANT_THREADS]; int tid;
	for (tid = 0; tid < CANT_THREADS; ++tid)
		ListAndPair lAP=new ListAndPair(l, make_pair("pusheo " + to_string(tid), 2^tid));
		pthread_create(&thread[tid], NULL, pushea_front, &lAP);
	for (tid = 0; tid < CANT_THREADS; ++tid)
		pthread_join(thread[tid], NULL);

	for (auto it = l->CrearIt(); it.HaySiguiente(); it.Avanzar()) {
		auto t = it.Siguiente();
		cout << t.first << " " << t.second << endl;
	}

	return 0;
}