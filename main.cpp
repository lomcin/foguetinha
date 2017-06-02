#include "MasterHeader.hpp"
#include "MetodoEuler.hpp"
#include "MetodoEulerModificado.hpp"


char TITLE[] =
"################################\n\
# Projeto de Metodos Numericos #\n\
################################\n\n\
\tGrupo 2:\n\
\t\tDayane Kelly (drks@cin.ufpe.br)\n\
\t\tIraline Nunes (ins@cin.ufpe.br)\n\
\t\tLucas Xavier (lgxa@cin.ufpe.br)\n\
\t\tLucas Maggi (lom@cin.ufpe.br)\n";

/*
	Organizando derivadas
		u dM/dt = M dv/dt = M a
		dv/dt = u dM/Mdt
		*/

/*
	Resultado Analítico
	
Entrada
	u 	: 	velocidade relativa de ejeção do combustível
	mi	: 	massa inicial
	mf	:	massa final
	vi	:	velocidade inicial
	
Saida
	vf 	:	velocidade final [ vf = u*log(mi/mf) + vi]
*/
float ResultadoAnalitico(float u, float mi, float mf, float vi) {
	float vf;
	vf = u*log(mi/mf) + vi;
	return vf;
}


/*
	Derivada dv/dt (variação da velocidade pela variação de tempo)
Entrada
	dm	:	taxa de ejeção de combustível
	tempo	:	tempo atual
	massa	:	massa atual
	

Saida
	dv : variacao de velocidade
*/
float MetodoEuler::Derivada(float tempo, float massa) {
	float dv;
	if (massa > mf) {
		dv = u*dm/massa;
	} else dv = 0.f;
	return dv;
}

float MetodoEulerModificado::Derivada(float tempo, float massa) {
	float dv;
	if (massa > mf) {
		dv = u*dm/massa;
	} else dv = 0.f;
	return dv;
}


int main (int args, char* argv[]) {
	std::ios_base::sync_with_stdio(true);
	cout << TITLE;
	if (args > 1) {
	
	}
	
	/*
		u 	: 	velocidade relativa de ejeção do combustível
		mi	: 	massa inicial
		mf	:	massa final
		vi	:	velocidade inicial
		vf	:	velocidade final
		t	:	tempo
		tx	:	taxa de perda de combustível (dM/dt)
		
	*/
	float u, mi, mf, vi, t, vf, dm;
	vi = 0.f;
	mi = 100000.f;
	vf = 0.f;
	t = 1000.f;
	dm = 10.f;
	u = 100.f;
	mf = mi - t*dm;
	
	vf = ResultadoAnalitico(u, mi, mf, vi);
	
	printf("Resultado Analitico : %.5f\n", vf);
	
	
	float evf = vi;

	cout << endl << "Metodo de Euler" << endl << endl;
	MetodoEuler::DefinirParametros(vf,dm,u,mi,t,0.1);
	MetodoEuler::ClearGraphic();
	int iteracoes = MetodoEuler::Executar(&evf);
#ifdef USE_OPENCV
	MetodoEuler::MostrarResultados(cv::Scalar(255,0,0));
	//MetodoEuler::SalvarResultados("teste1.png");
#endif

#ifdef USE_OPENCV
	evf = vi;
	mi = 50000.f;
	vf = ResultadoAnalitico(u, mi, mf, vi);
	MetodoEuler::DefinirParametros(vf,dm,u,mi,t,0.1);
	MetodoEuler::Executar(&vi);
	MetodoEuler::MostrarResultados(cv::Scalar(0,255,0));
	//MetodoEuler::SalvarResultados("teste2.png");
	
	evf = vi;
	mi = 10000.f;
	vf = ResultadoAnalitico(u, mi, mf, vi);
	MetodoEuler::DefinirParametros(vf,dm,u,mi,t,0.1);
	MetodoEuler::Executar(&vi);
	MetodoEuler::MostrarResultados(cv::Scalar(0,0,0));
	MetodoEuler::SalvarResultados("teste3.png");
#endif	
	cout << endl << endl;
	
	evf = vi;
	mi = 100000.f;
	cout << endl << "Metodo de Euler Modificado" << endl << endl;
	MetodoEulerModificado::DefinirParametros(vf,dm,u,mi,t,0.1);
	MetodoEulerModificado::ClearGraphic();
	iteracoes = MetodoEulerModificado::Executar(&evf);
#ifdef USE_OPENCV
	MetodoEulerModificado::MostrarResultados(cv::Scalar(255,0,0));
	MetodoEulerModificado::SalvarResultados("em1.png");
#endif

	return 0;
}
