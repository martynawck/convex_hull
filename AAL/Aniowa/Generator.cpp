#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <math.h>
#include <vector>
#include "Generator.h"
using namespace std;

/*konstruktory*/

Generator::Generator() {}

Generator::~Generator() {}


/*zwraca iloœæ elementów w vectorze*/
int Generator::getSize() {

	return generated_set.size();

}


/*funkcja generuj¹ca punkty w szeœcianie*/
void Generator::generateInCube(int no_to_generate, double x_axis, double y_axis, double z_axis, double edge_length) {

	int no_generated = 0;
	double xL, xR, yL, yR, zL, zR;
	srand(time(NULL));
	x0 = x_axis;
	y0 = y_axis;
	z0 = z_axis;
	r = edge_length/2;

	//obliczamy granice, w których mo¿emy coœ generowaæ
	xL = x_axis-edge_length/2;
	xR = x_axis+edge_length/2;
	yL = y_axis-edge_length/2;
	yR = y_axis+edge_length/2;
	zL = z_axis-edge_length/2;
	zR = z_axis+edge_length/2;

	//jesli iloœæ punktów, któr¹ chcemy wygenerowac za ma³a, generujemy dalej
	while (no_generated < no_to_generate) {
	
		//generujemy sobie liczby
		double x = (xR - xL) * ( (double)rand() / (double)RAND_MAX ) + xL;
		double y = (yR - yL) * ( (double)rand() / (double)RAND_MAX ) + yL;
		double z = (zR - zL) * ( (double)rand() / (double)RAND_MAX ) + zL;
		Point p = Point(x,y,z);

		//i wrzucamy do wektora
		generated_set.push_back(p);
		no_generated++;

	}

}


/*funkcja generuj¹ca punkty w kuli*/
void Generator::generateInSphere(int no_to_generate, double x_axis, double y_axis, double z_axis, double radius) {

	int no_generated = 0;
	double xL, xR, yL, yR, zL, zR;
	srand(time(NULL));

	//granice generowania
	x0 = x_axis;
	y0 = y_axis;
	z0 = z_axis;
	r = radius;

	xL = x_axis-radius;
	xR = x_axis+radius;
	yL = y_axis-radius;
	yR = y_axis+radius;

	//jesli iloœæ punktów, któr¹ chcemy wygenerowac za ma³a, generujemy dalej
	while (no_generated < no_to_generate) {
	
		double x = (xR - xL) * ( (double)rand() / (double)RAND_MAX ) + xL;
		double y = (yR - yL) * ( (double)rand() / (double)RAND_MAX ) + yL;
		double xy = x*x + y*y;
		double drad = radius*radius;

		//losujemy sobie x i y a z dobieramy z rownania kuli
		if ((xy) > drad )
			continue;
		zL = - sqrt(drad - xy);
		zR = zL *(-1);

		double z = (zR - zL) * ( (double)rand() / (double)RAND_MAX ) + zL;

		Point p = Point(x,y,z);
		generated_set.push_back(p);
		no_generated++;

	}

}


/*funkcja generuj¹ca punkty na powierzchni kuli*/
void Generator::generateOnSphere(int no_to_generate, double x_axis, double y_axis, double z_axis, double radius) {

	int no_generated = 0;
	double xL, xR, yL, yR, zL, zR;
	srand(time(NULL));

	x0 = x_axis;
	y0 = y_axis;
	z0 = z_axis;
	r = radius;

	//ustalamy granice
	xL = x_axis-radius;
	xR = x_axis+radius;
	yL = y_axis-radius;
	yR = y_axis+radius;
	zL = z_axis-radius;
	zR = z_axis+radius;

	//jesli iloœæ punktów, któr¹ chcemy wygenerowac za ma³a, generujemy dalej
	while (no_generated < no_to_generate) {
	
		double x = (xR - xL) * ( (double)rand() / (double)RAND_MAX ) + xL;
		double y = (yR - yL) * ( (double)rand() / (double)RAND_MAX ) + yL;

		double xy = x*x + y*y;
		double drad = radius*radius;

		if ((xy) > drad )
			continue;

		//wyliczamy sobie z bezpoœrednio z równania 
		double z = sqrt(drad - xy);

		//losujemy sobie czy z ma mieæ dodatni¹ czy ujemn¹ wartoœæ (¿eby nie by³o ca³y czas w pó³kuli zbioru
		if (zL < 0) {
		int sign = rand();
			if (z_axis + radius > 0) {
				if (sign%2)
				z = z*(-1);
			} else
				z = z*(-1);
		}

		Point p = Point(x,y,z);
		generated_set.push_back(p);
		no_generated++;

	}

}


/*czyœcimy zbiór punktów*/
void Generator::clearSet() {

     generated_set.clear();

}


/*zapisujemy punkty do pliku*/
void Generator::writeToFile(string s) {

	ofstream plik (s);
    if( plik.good() == true ) {
		plik<<x0<<" "<<y0<<" "<<z0<<" "<<r<<endl;
	for ( vector<Point>::iterator it = generated_set.begin(); it != generated_set.end(); it++) {
		plik<<it->getX()<<"  "<<it->getY()<<"  "<<it->getZ()<<endl;
		plik.flush();
	}
	plik.close();

	}

}
