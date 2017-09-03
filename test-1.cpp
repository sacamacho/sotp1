#include <iostream>
#include "ListaAtomica.hpp"

using namespace std;

int main(void) {
	Lista<pair<string, unsigned int>> *l;
	pair<string, unsigned int> p = make_pair("hola manola", 99);

	l->push_front(p);

	for (auto it = l->CrearIt(); it.HaySiguiente(); it.Avanzar()) {
		auto t = it.Siguiente();
		cout << t.first << " " << t.second << endl;
	}

	return 0;
}
