/// Projeto Métodos Numéricos 2017.1
/// Grupo 2:
///Dayane Kelly (drks@cin.ufpe.br)
///Iraline Nunes (ins@cin.ufpe.br)
///Lucas Xavier (lgxa@cin.ufpe.br)
///Lucas Maggi (lom@cin.ufpe.br)


/// RUNGE-KUTTA 4ª ORDEM

#include <iostream>
#include <cmath> // ou <math.h>
using namespace std;


float derivada(float massa, float tempo) {
	float dv, dm, u;
	dm = 10.f;
	u = 100.f;
	if (massa > dm) {
		dv = u*dm/massa;
	} else dv = 0.f;
	//cout<<dv<<endl;
	return dv;
}


int main(){
	
	int n, i;
	float x, y, h, k1, k2, k3, k4, mi, mf, dm;

	n = 10; //quantidade de interações
	mi = 100000.f; //massa inicial
	y = 1000.f; // tempo
	h = 1.f;
	dm = 10.f;
	mf = mi - y*dm;
	
	for(i=0; (i<n) && (mi > mf); i++){
	    
	    x = mi + i*h;
	    k1 = derivada(x,y);
	    k2 = derivada(x+(h/2), y+(h/2)*k1);
	    k3 = derivada(x+(h/2), y+ (h/2)*k2);
	    k4 = derivada(x+h, y+h*k3);
	    y = y + (h/6)*(k1+2*k2+2*k3+k4);
	    mi -= dm;
	}
	cout<<"O valor aproximado da funcao para "<<n<<" passos eh "<<y<<endl;
}
