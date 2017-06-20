#include "MasterHeader.hpp"

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


namespace MetodoEulerModificado {
	int iteracoes;
	float precisao = 0.0001;
	float tempo = 1.f;
	float h;
	float solucao_analitica;
#ifdef USE_OPENCV	
	cv::Mat graphic;
#endif
	/*
		u 	: 	velocidade relativa de ejeção do combustível
		dm	:	taxa de ejeção de combustível
	*/
	float dm, u, mi, mf, vi;
	
	std::vector<float> points;
	
	float Derivada(float t, float massa);
	

	void DefinirParametros(
			float nova_solucao_analitica, 
			float nova_dm,
			float novo_u,
			float nova_mi,
			float nova_mf,
			float novo_tempo = 1.f, 
			float novo_h = 0.001f, 
			float nova_precisao = 0.0001f
		) {
		cout << "Definindo parâmetros" << endl;
		solucao_analitica = nova_solucao_analitica;
		precisao = nova_precisao;
		tempo = novo_tempo;
		u = novo_u;
		dm = nova_dm;
		mi = nova_mi;
		mf = nova_mf;
		h = novo_h;
		points.clear();
	}
	
	void PrintValues() {
		cout << "Valores : " << endl << 
		" u 	: " << u << endl <<
		" mi	: " << mi << endl <<
		" mf	: " << mf << endl <<
		" vi	: " << vi << endl <<
		" tempo	: " << tempo << endl <<
		" dm	: " << dm << endl <<
		" h 	: " << h << endl;
	}
	
	
	void ClearGraphic() {
#ifdef USE_OPENCV
		graphic = cv::Mat::zeros(600,600, CV_8UC3);
		cv::rectangle(graphic, cv::Point(0,0), cv::Point(600,600),cv::Scalar(255,255,255),-1);
#endif
	}
	
	
	int EulerModificado(float tempo_aplicado = 1.f, float *y = NULL) {
		if (y == NULL) return 0;
		iteracoes = 0;
		float tempo_atual = 0.0f, m = mi;
		float erro = 1.f;
		vi = *y;
		points.push_back(*y);
		while (tempo_aplicado > tempo_atual) {
		//while (m > mf) {
			tempo_atual+=h;
			float y_previsao= *y + h*Derivada(tempo_atual+h,m);
			*y=*y+ (h/2.f)*( Derivada(tempo_atual,m)+Derivada(tempo_atual+h,m-dm) );
			points.push_back(*y);
			//cout << *y << endl;
			if (m > mf) m -= dm*h;
			++iteracoes;
		}
		cout << "Último valor " << points.back() << endl;
		erro = fabs(*y - solucao_analitica);
		printf("Resultado Analitico : %.5f\n", solucao_analitica);
		cout << "erro " << erro << endl;
		return iteracoes;
	}
	
	int Executar(float *y_retorno = NULL) {
		cout << linhas << "Executando Metodo de Euler Modificado" << endl;
		float y_final;
		if (y_retorno) y_final = *y_retorno;
		EulerModificado(tempo,&y_final);
		if (y_retorno) *y_retorno = y_final;
		cout << "tempo " << tempo << " y_final " << y_final << endl;
		cout << "Levou " << iteracoes << " iteracoes." << endl;
		return iteracoes;
	}
	
#ifdef USE_OPENCV
	void MostrarResultados(const cv::Scalar &color) {
		//cv::Mat lenna = cv::imread("../../../Lenna.png");
		//cv::imshow("Lenna", lenna);
		
		
		float maxy, miny, deltay;
		maxy = *max_element(points.begin(),points.end());
		miny = *min_element(points.begin(),points.end());
		cout << "Max min " << maxy << " " << miny << endl;
		deltay = maxy-miny;
		float x = 0, y = points[0];
		for(int i=0; i<points.size()-1;++i) {
			cv::Point2f p((i*600.f/points.size()),
			(1.f-((points[i]-miny)/deltay))*600.f),
			p2((i+1)*600.f/points.size(),
			(1.f-((points[i+1]-miny)/deltay))*600.f);
			cv::line(graphic,p2,p,color, 2);
		}
		//cv::line(graphic,cv::Point2f(0,0),cv::Point2f(100,100),cor, 2);
		cv::imshow("Grafico", graphic);
		while(cv::waitKey(0) != 27);
	}
#endif
	
	void SalvarResultados(std::string nome) {
#ifdef USE_OPENCV
		cv::imwrite(nome,graphic);
#endif
		cout << "Salvando resultados" << endl;
	}

}
