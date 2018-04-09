#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <map>
#include <vector>
#include <iterator>

double rng();
int *getCentroids(int*, int);
double distance(double, double);
std::map<int, std::vector<double> > clusters(double*, int*, int, int);

int main()
{
	//Inicialización de la semilla del random
	srand(time(NULL));
	double X[10]; //Arreglo de 10 datos aleatorios
	int k=3; //Total de los K clusters que queremos, emulando el ejemplo en Python lo inicializamos en 3
	int *mu; //Si queremos hacerlo dinámico, en C++ hay que usar un puntero, o el compilador se pone tonto
	//Map es el diccionario de C++, pero como el compilador se pone fresa, los arreglos deben tener tamaño predefinido, usaremos vectores
	std::map<int, std::vector<double> > groups; 
	mu = new int[k]; //arreglo de k datos
	mu = getCentroids(mu, k);

	//Llenado de los datos aleatorios entre 0 y 10
	for(int i=0; i<10; i++)
		X[i]= rng();
	std::cout << "Puntos obtenidos:\n";
	for (int i = 0; i < 10; i++)
		std::cout << X[i] << " ";
	std::cout << "Centroides:\n";
	for(int i=0; i<k; i++)
		std::cout << mu[i] << " ";
	groups = clusters(X, mu, k, 10);
	std::cout << "Grupos de clusters:\n";
	for (std::map<int, std::vector<double> >::iterator it = groups.begin(); it != groups.end(); ++it) {
		std::cout << it->first << " => ";
		for (std::vector<double>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
			std::cout << *it2 << ", ";
		}
		std::cout << std::endl;
	}
    return 0;
}

double rng() {
	return (10)*(double)rand()/RAND_MAX;
}

int *getCentroids(int *mu, int k) {
	int input;
	//Dejaremos sólo por esta ocasión que el usuario los ingrese
	std::cout << "Insertar valores a usar como centroides\n";
	for (int i = 0; i < k; i++) {
		std::cin >> input;
		mu[i] = input;
	}
	return mu;
}

//Elegantemente, una distancia euclidiana
double distance(double x, double y) {
	return abs(x-y);
}

//DIS IS GONNA BE GUD
std::map<int, std::vector<double> > clusters(double *x, int *mu, int k, int n) {
	/*
	Función map
	Entrada: puntero a arreglo de tipo doble X
			 puntero a arreglo de enteros mu (centroides)
			 total de centroides - valor entero k
			 total de datos en X - valor entero n
	Salida: "Diccionario" con los puntos asociados a cada centroide (map<int, vector>)
	*/
	std::map<int, std::vector<double> > groups; //"Diccionario" de grupos
	std::map<int, std::vector<double> > distancias; //"Diccionario" de distancias
	std::vector<double> distancia; //vector de distancias
	std::vector<double> puntos; //vector de puntos
	double mindist=INFINITY; //Truco que usé para resolver esto en Python
	int mindistindex; //Indice de la menor distancia
	int tempi=-1, tempf;
	//Iniciamos el diccionario de grupos
	for (int i = 0; i < k; i++) {
		groups[mu[i]] = puntos;
	}
	//Calculamos distancias
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			distancia.push_back(distance(x[i], (double)mu[j])); //Agregamos las distancias al vector de distancias
		}
		distancias[i] = distancia; //Agregamos el vector de distancias al map
		for (std::vector<double>::iterator it = distancia.begin(); it != distancia.end(); ++it) {
			tempi++;
			if (*it < mindist) {
				mindist = *it; //Simple, siempre que encontremos una distancia menor, hacemos un cambio
				tempf = tempi; //Otro truco barato, para no pelearnos más con iteradores
			}
		}
		groups.at(mu[tempf]).push_back(x[i]);
		
		//std::cout << "DISTANCIA MINIMA OBTENIDA: " << mindist << " EN EL ÍNDICE: "<< tempf << std::endl;

		/*REINICIAMOS VALORES PARA EL SIGUIENTE PUNTO EN X*/
		mindist = INFINITY; //Volvemos a fijar la distancia minima al inifinito
		distancia.clear(); //Borramos el vector de distancias para volver a llenarlo
		tempi = -1;
	}
	return groups;
}