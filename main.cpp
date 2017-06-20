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

enum Metodo {
	Metodo_Analitico = 0,
	Metodo_Euler,
	Metodo_EulerModificado,
	Metodo_RungeKutta,
	Metodo_Compare
};

string nameFromMetodo(Metodo metodo) {
	switch(metodo) {
		case Metodo_Analitico:
			return "A_";
			break;
		case Metodo_Euler:
			return "E_";
			break;
		case Metodo_EulerModificado:
			return "EM_";
			break;
		case Metodo_RungeKutta:
			return "RK_";
			break;
		case Metodo_Compare:
			return "C_";
			break;
		default:
			return "";
			break;
	}
}


struct Teste {
	string title;
	float mi, mf, vi, u, t, dm, h;
};
vector<Teste> testes;
Metodo metodo = Metodo_Analitico;

std::vector< std::vector<float> > points;



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


void plota() {
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
	t = 1200.f;
	dm = 100.f;
	u = 1.f;
	//mf = mi - t*dm;
	mf = 100.f;
	assert(mf > 0.f);
	


	
	float evf = vi;
	switch(metodo) {
		case Metodo_Analitico:
			cout << endl << "Metodo Analitico" << endl << endl;
			for(int i=0;i<testes.size();++i) {
				mi = testes[i].mi;
				mf = testes[i].mf;
				vi = testes[i].vi;
				dm = testes[i].dm;
				h = testes[i].h;
				u = testes[i].u;
				float tf = testes[i].t;
				evf = vi;
				t = 0.f;
				//dm *= h;

				vf = ResultadoAnalitico(u, mi, mf, vi);

				MetodoEuler::DefinirParametros(vf,dm,u,mi,mf,tf,h);
				MetodoEuler::PrintValues();
				cout << "resultado " << vf << endl;
				points[i].clear();
				float m = mi;
				for (int j=0;t<tf;++j) {
					if (m > mf) m -= dm*h;
					t+=h;
					vf = ResultadoAnalitico(u, mi, m, vi);
					points[i].push_back(vf);
				}
				points[i].push_back(points[i].back());
			}
			break;

		case Metodo_Euler:
			cout << endl << "Metodo de Euler" << endl << endl;
			for(int i=0;i<testes.size();++i) {
				mi = testes[i].mi;
				mf = testes[i].mf;
				vi = testes[i].vi;
				dm = testes[i].dm;
				h = testes[i].h;
				u = testes[i].u;
				t = testes[i].t;
				evf = vi;
				//dm *= h;
				vf = ResultadoAnalitico(u, mi, mf, vi);
				MetodoEuler::DefinirParametros(vf,dm,u,mi,mf,t,h);
				MetodoEuler::Executar(&evf);
				copyPointsTo(i,MetodoEuler);
				MetodoEuler::PrintValues();
			}
			break;

		case Metodo_EulerModificado:
			cout << endl << "Metodo de Euler Modificado" << endl << endl;
			for(int i=0;i<testes.size();++i) {
				mi = testes[i].mi;
				mf = testes[i].mf;
				vi = testes[i].vi;
				dm = testes[i].dm;
				h = testes[i].h;
				u = testes[i].u;
				t = testes[i].t;
				evf = vi;
				//dm *= h;
				vf = ResultadoAnalitico(u, mi, mf, vi);
				MetodoEulerModificado::DefinirParametros(vf,dm,u,mi,mf,t,h);
				MetodoEulerModificado::Executar(&evf);
				copyPointsTo(i,MetodoEulerModificado);
				MetodoEulerModificado::PrintValues();
			}
			break;
		default:
			break;
		}

	cout << endl << endl;
	/*
	evf = vi;
	mi = 100000.f;
	cout << endl << "Metodo de Euler Modificado" << endl << endl;
	MetodoEulerModificado::DefinirParametros(vf,dm,u,mi,mf,vi,t,0.1);
	MetodoEulerModificado::Executar(&evf);
	*/

/*
set datafile separator ","
set termoption dash
set style line 1 lt 2 lc rgb "red" lw 3
set style line 2 lt 2 lc rgb "orange" lw 2
set style line 3 lt 2 lc rgb "yellow" lw 3
set style line 4 lt 2 lc rgb "green" lw 2
plot 'points.csv' using 0:3
pause mouse any "Any key or button will terminate"
*/

	ofstream fi, gnuplot;
	gnuplot.open("plot.gnu");
	fi.open("points.csv");

	assert(fi.is_open() && gnuplot.is_open());
	gnuplot << "set datafile separator \",\"\n\
set termoption dash\nset style data points\n";
	for(int i=0;i<testes.size();++i) {
		gnuplot << "set style line " << i+1 << " lt 2 lw 10 pt 1 ps 0.5\n";
	}
	//gnuplot << "set for [i=1:3] linetype i dt i\n";
	/*
	unset paxis 1 tics\n
unset paxis 2 tics\n
unset paxis 3 tics\n";*/
	/*fi << "Tempo";
	for (int j=0; j < 3; ++j) {
		fi << ",v_" << j;
	}
	fi << endl;*/
	t = 0.f;
	int fator = 10;
	for(int i = 0; i < points[0].size()/fator + 1; ++i) {
		fi << t;
		for (int j=0; j < testes.size(); ++j) {
			fi << "," << points[j][i*fator];
		}
		fi << endl;
		t += h*fator;
	}

	gnuplot << "plot ";
	for (int i=0; i < testes.size(); ++i) {
		if (i != testes.size()-1) gnuplot << "'points.csv' using 1:"<< i+2 << " title '"<< nameFromMetodo(metodo) <<  testes[i].title << "' smooth unique with lines,\\\n\t ";
		else gnuplot << "'points.csv' using 1:"<< i+2 << " title '"<< nameFromMetodo(metodo) << testes[i].title << "' smooth unique with lines\n";
	}
	//gnuplot << "pause mouse keypress \"Any key or button will terminate\"";
	gnuplot.close();
	fi.close();
}

void lerEntrada(char *fileName) {
	fstream entrada;
		entrada.open(fileName);
		assert(entrada.is_open());

		testes.clear();
		Teste teste;
		while(entrada.eof() == false) {
			entrada >> teste.title;
			if (teste.title.compare("Analitico") == 0) {
				metodo = Metodo_Analitico;
				testes.clear();
				continue;
			} else if (teste.title.compare("Euler") == 0) {
				metodo = Metodo_Euler;
				testes.clear();
				continue;
			} else if (teste.title.compare("EulerModificado") == 0) {
				metodo = Metodo_EulerModificado;
				testes.clear();
				continue;
			} else if (teste.title.compare("RungeKutta") == 0) {
				metodo = Metodo_RungeKutta;
				testes.clear();
				continue;
			} else if (teste.title.compare("Compare") == 0) {
				metodo = Metodo_Compare;
				testes.clear();
				continue;
			}
			entrada >> teste.mi;
			entrada >> teste.mf;
			entrada >> teste.vi;
			entrada >> teste.u;
			entrada >> teste.t;
			entrada >> teste.dm;
			entrada >> teste.h;
			points.resize(points.size()+1);

			testes.push_back(teste);
		}
		plota();

		entrada.close();
}

int main (int args, char* argv[]) {
	std::ios_base::sync_with_stdio(true);
	cout << TITLE;

	testes.push_back((Teste){"f1",100000.f,100.f, 0.f, 1.f, 1200.f, 100.f});
	testes.push_back((Teste){"f2",50000.f,100.f, 0.f, 1.f, 1200.f, 100.f});
	testes.push_back((Teste){"f3",10000.f,100.f, 0.f, 1.f, 1200.f, 100.f});
	testes.push_back((Teste){"f4",1000.f,100.f, 0.f, 1.f, 1200.f, 100.f});
	testes.push_back((Teste){"f5",1000.f,100.f, 0.f, 10.f, 1200.f, 100.f});

	if (args > 1) {
		lerEntrada(argv[1]);
	}
		
	return 0;
}
