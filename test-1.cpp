#include <iostream>
#include "ListaAtomica.hpp"

using namespace std;

int main(void) {
	Lista<pair<string, unsigned int>> *l= new Lista<pair<string, unsigned int>>;
	pair<string, unsigned int> p1 = make_pair("(primer push_front) pos:", 3);
	pair<string, unsigned int> p2 = make_pair("(segundo push_front) pos:", 2);
	pair<string, unsigned int> p3 = make_pair("(tercer push_front) pos:", 1);
	l->push_front(p1);
	l->push_front(p2);
	l->push_front(p3);

	for (auto it = l->CrearIt(); it.HaySiguiente(); it.Avanzar()) {
		auto t = it.Siguiente();
		cout << t.first << " " << t.second << endl;
	}

	return 0;
}
