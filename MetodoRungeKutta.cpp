/// Projeto Métodos Numéricos 2017.1
/// Grupo 2:
///Dayane Kelly (drks@cin.ufpe.br)
///Iraline Nunes (ins@cin.ufpe.br)
///Lucas Xavier (lgxa@cin.ufpe.br)
///Lucas Maggi (lom@cin.ufpe.br)


/// RUNGE-KUTTA 4ª ORDEM

#include <iostream>
#include <cmath> // ou <math.h>
#include <assert.h>
using namespace std;


float derivada(float tempo, float massa) {
	float dv, dm, u;
	dm = 100.f;
	u = 1.f;
	if (massa > dm) {
		dv = u*dm/massa;
	} else dv = 0.f;
	//cout<<dv<<endl;
	return dv;
}

float ResultadoAnalitico(float u, float mi, float mf, float vi) {
	float vf;
	vf = u*log(mi/mf) + vi;
	return vf;
}


int main(){
	
	int n, i;
	float x, vi, h, k1, k2, k3, k4, mi, mf, dm, u, t, tf;

	n = 100; //quantidade de interações
	mi = 100000.f; //massa inicial
	vi = 0.f; // velocidade inicial
	h = 1.f;
	dm = 100.f;
	tf = 1200.f;
	mf = 100.f;
	u = 1.f;
	t = 0.f;
	assert(mf > 0.f);
	
	cout<<"O resultado analitico eh " << ResultadoAnalitico(u, mi, mf, vi)<<endl;

	for(i=0; (t < tf); i++){
	    t += h;
	    k1 = derivada(t,mi);
	    k2 = derivada(t+(h/2.f), mi +(h/2.f)*k1);
	    k3 = derivada(t+(h/2.f), mi + (h/2.f)*k2);
	    k4 = derivada(t+h, mi+h*k3);
	    vi = vi + (h/6.f)*(k1+2.f*k2+2.f*k3+k4);
        if (mi > mf) mi -= dm*h;
	}
	
	
	cout<<"O valor aproximado da funcao para "<<i<<" passos e h "<< h <<" eh "<< vi <<endl;

}
