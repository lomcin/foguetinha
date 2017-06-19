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
\t\tLucas Maggi (lom@cin.ufpe.br)\n\n\n\
################################\n\n\n";

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
	t	:	tempo atual
	massa	:	massa atual
	

Saida
	dv : variacao de velocidade
*/
float MetodoEuler::Derivada(float t, float massa) {
	float dv;
	if (massa > mf) {
		dv = u*dm/massa;
	} else dv = 0.f;
	return dv;
}

float MetodoEulerModificado::Derivada(float t, float massa) {
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
	float u, mi, mf, vi, t, vf, dm, h = 1.f;
	vi = 0.f;
	mi = 100000.f;
	vf = 0.f;
	t = 1000.f;
	dm = 100.f;
	u = 1.f;
	//mf = mi - t*dm;
	mf = 100.f;
	assert(mf > 0.f);

	std::vector<float> points[4];
	
	

	cout << endl << "Metodo de Euler" << endl << endl;

	
	float evf = vi;

	vf = ResultadoAnalitico(u, mi, mf, vi);
	MetodoEuler::DefinirParametros(vf,dm,u,mi,mf,t,h);
	MetodoEuler::ClearGraphic();
	MetodoEuler::Executar(&evf);
#ifdef USE_OPENCV
	MetodoEuler::MostrarResultados(cv::Scalar(255,0,0));
	//MetodoEuler::SalvarResultados("teste1.png");
#endif
	copyPointsTo(0,MetodoEuler);
	MetodoEuler::PrintValues();

#ifdef USE_OPENCV
	vi = 0.f;
	evf = vi;
	mi = 50000.f;
	vf = ResultadoAnalitico(u, mi, mf, vi);
	MetodoEuler::DefinirParametros(vf,dm,u,mi,mf,t,h);
	MetodoEuler::Executar(&evf);
	MetodoEuler::MostrarResultados(cv::Scalar(0,255,0));
	MetodoEuler::PrintValues();
	copyPointsTo(1,MetodoEuler);
	//MetodoEuler::SalvarResultados("teste2.png");
	
	vi = 0.f;
	evf = vi;
	mi = 10000.f;
	vf = ResultadoAnalitico(u, mi, mf, vi);
	MetodoEuler::DefinirParametros(vf,dm,u,mi,mf,t,h);
	MetodoEuler::Executar(&evf);
	MetodoEuler::MostrarResultados(cv::Scalar(0,0,0));
	MetodoEuler::PrintValues();
	MetodoEuler::SalvarResultados("teste3.png");
	copyPointsTo(2,MetodoEuler);
#endif	
	cout << endl << endl;
	
	evf = vi;
	mi = 100000.f;
	cout << endl << "Metodo de Euler Modificado" << endl << endl;
	MetodoEulerModificado::DefinirParametros(vf,dm,u,mi,mf,vi,t,0.1);
	MetodoEulerModificado::ClearGraphic();
	MetodoEulerModificado::Executar(&evf);
#ifdef USE_OPENCV
	MetodoEulerModificado::MostrarResultados(cv::Scalar(255,0,0));
	MetodoEulerModificado::SalvarResultados("em1.png");
#endif

	ofstream fi;
	fi.open("points.csv");

	assert(fi.is_open());
	fi << "Tempo";
	for (int j=0; j < 3; ++j) {
		fi << ";v_" << j;
	}
	fi << endl;
	t = 0.f;
	for(int i = 0; i < points[0].size()/100; ++i) {
		fi << t;
		for (int j=0; j < 3; ++j) {
			fi << ";" << points[j][i*100];
		}
		fi << endl;
		t += h*100;
	}

	fi.close();
	return 0;
}
