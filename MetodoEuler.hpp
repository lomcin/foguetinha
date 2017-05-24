#include "MasterHeader.hpp"

/*

Pseudo-código EULER

Entrada:
	tempo_aplicado
Saída:
	y, qntd_loops
Inicio
	h = tempo_aplicado
	erro = 1
	Enquanto erro>0.0001 faça:
		qntd_loops = 0
		tempo_atual = 0
		y = capital_inicial
		Enquanto tempo_atual<tempo_aplicado faça:
			y = y +h*derivada(tempo_atual+h)
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


namespace MetodoEuler {
	int iteracoes;
	float precisao = 0.0001;
	float tempo = 1.f;
	
	float Derivada(float tempo);
	
	void DefinirParametros(float nova_precisao = 0.0001, float novo_tempo = 1.f) {
		precisao = nova_precisao;
		tempo = novo_tempo;
		cout << "Definindo parâmetros" << endl;
	}
	
	void Euler(float tempo_aplicado = 1, float *y = NULL) {
		if (y == NULL) return;
		float h = tempo_aplicado,
			erro = 1.f;
		/*while (erro > precisao) {
			iteracoes++;
			*y = *y + h*derivada(tempo_atual+h);
		}*/
	}
	
	void Executar() {
		cout << "Executando Metodo de Euler" << endl;
		float y_final;
		Euler(tempo,&y_final);
		cout << "tempo " << tempo << " y_final " << y_final << endl;
		cout << "Levou " << iteracoes << " iteracoes." << endl;
	}
	
#ifdef USE_OPENCV
	void MostrarResultados() {
		cv::Mat lenna = cv::imread("../../../Lenna.png");
		cv::imshow("Lenna", lenna);
		cv::waitKey(0);
	}
#endif
	
	void SalvarResultados() {
		cout << "Salvando resultados" << endl;
	}

}
