#include "MasterHeader.hpp"
#include "MetodoEuler.hpp"

char TITLE[] =
"######################\n\
# Projeto de Metodos #\n\
######################\n";



/*

Pseudo-código EULER MODIFICADO

Entrada:
	tempo_aplicado
Saída:
	y, qntd_loops
Inicio
	h = tempo_aplicado
	erro = 1
	Enquanto erro>=0.0001 faça:
		qntd_loops = 0
		tempo_atual = 0
		y = capital_inicial
		Enquanto tempo_atual<tempo_aplicado faça:
		y_previsao=y+h*derivada(tempo_atual+h)
		y=y+ (h/2)*( derivada(tempo_atual,y)+derivada(tempo_atual+h,y_previsao) )
			tempo_atual = tempo_atual+h
			qntd_loops = qntd_loops+1
		Fim-Enquanto
		erro = abs(y-solucao_analitica)
		Se erro>=0.0001 então
			h = h/4
		Senão
			Retorna y, qntd_loops
		Fim-se
	Fim-Enquanto
Fim



*/

float MetodoEuler::Derivada(float tempo) {

}


int main (int args, char* argv[]) {
	cout << TITLE;
	if (args > 1) {
	
	}

	cout << endl << "Metodo de Euler" << endl << endl;
	MetodoEuler::DefinirParametros();
	MetodoEuler::Executar();
#ifdef USE_OPENCV
	MetodoEuler::MostrarResultados();
#endif
	MetodoEuler::SalvarResultados();
	cout << endl << endl;

	return 0;
}
