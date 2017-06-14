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


double funcao (double t, double q){

	return (-0.5*q + 10 + sin(2*t));

}

int main(){
	
	int n, i;
	double x, y, h, k1, k2, k3, k4, k;

	cout<<"Qual a quantidade do numero de passos?"<<endl;
	cin>>n;
	cout<<"Qual o valor inicial de x?"<<endl;
	cin>>x;
	k = x;
	
	cout<<"Qual o valor inicial de y?"<<endl;
	cin>>y;
	cout<<"Qual o espacamento do intervalo?"<<endl;
	cin>>h;
	
	for(i=0; i<n; i++){
	    
	    x=k+i*h;
	    k1=funcao(x,y);
	    k2=funcao(x+(h/2),y+(h/2)*k1);
	    k3=funcao(x+(h/2), y+ (h/2)*k2);
	    k4=funcao(x+h,y+h*k3);
	    y=y+(h/6)*(k1+2*k2+2*k3+k4);
	}
	cout<<"O valor aproximado da funcao para "<<n<<" passos eh "<<y<<endl;
}