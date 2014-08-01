// MyBehaviours.cpp : code file for MyBehaviours Implementation
//

/***** FILE NOT USED *****/

#include "stdafx.h"
#include "MyBehaviours.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include "conio.h"

#define NF 8 // filas
#define NC 6 // columnas

#define N 0 // norte
#define E 1 // este
#define S 2 // sur
#define W 3 // oeste

#define mov_dir 4

using namespace std;

// Functions implementation

class nodo {
	
	int pos_x;
    int pos_y;
    int nivel;
    int peso;

public:
    
	nodo(int px, int py, int n, int p)
	{
		pos_x = px; pos_y = py; nivel = n; peso = p;
	}
    
    int getPosx() const {return pos_x;}
    int getPosy() const {return pos_y;}
    int getNivel() const {return nivel;}
    int getPeso() const {return peso;}

    void recalculaPeso(const int & dx, const int & dy)
	{
		peso = nivel + estimacion(dx, dy) * 10;
	}

	void siguienteNivel(const int & i)
	{
		nivel += (mov_dir == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
	}

	const int & estimacion(const int & dx, const int & dy) const {

		static int dist, dist_x, dist_y;
		
		dist_x = dx - pos_x;
		dist_y = dy - pos_y;

		// Distacia Euclidea
		//dist = static_cast<int>(sqrt((double) dist_x * dist_x + dist_y * dist_y));

        // Manhattan
		dist = abs(dist_x) + abs(dist_y);
            
        // Chebyshev
		//dist = max(abs(dist_x), abs(dist_y));

        return(dist);
    }
};

bool operator < (const nodo &a, const nodo &b){
  return a.getPeso() > b.getPeso();
}

string calcular_ruta(const int & ori_x, const int & ori_y, const int & fin_x, const int & fin_y, int mapa[NC][NF]){

	static int direcciones_x[mov_dir] = {1, 0, -1, 0};
	static int direcciones_y[mov_dir] = {0, 1, 0, -1};

	static int mapa_direcciones[NC][NF];
	static int mapa_abiertos[NC][NF];
	static int mapa_cerrados[NC][NF];

	static priority_queue<nodo> abiertos[2];
	static int n = 0;

	static nodo* actual;
    static nodo* posible;

	int x = NC, y = NF;
	int x_desp, y_desp;

	static int dir;
    static char c;

	for(int j = 0; j < NF; j++)
		for(int i = 0; i < NC; i++)
		{
			mapa_cerrados[i][j]=0;
            mapa_abiertos[i][j]=0;
        }

	actual = new nodo(ori_x, ori_y, 0, 0);
	actual->recalculaPeso(fin_x, fin_y);
    abiertos[n].push(*actual);
    mapa_abiertos[x][y] = actual->getPeso();
	
	while(!abiertos[n].empty())
	{
		actual = new nodo(abiertos[n].top().getPosx(), abiertos[n].top().getPosy(), abiertos[n].top().getNivel(), abiertos[n].top().getPeso());

		x = actual->getPosx();
		y = actual->getPosy();

        abiertos[n].pop();
		mapa_abiertos[x][y] = 0;
		mapa_cerrados[x][y] = 1;
		
		if(x == fin_x && y == fin_y)
		{
			string path = "";

			while((x == ori_x && y == ori_y) == false)
			{
				dir = mapa_direcciones[x][y];
                c = '0' + (dir + mov_dir/2) % mov_dir;
                path = c + path;
                x += direcciones_x[dir];
                y += direcciones_y[dir];
            }

            delete actual;
            
			while(!abiertos[n].empty())
				abiertos[n].pop();           
            
			return path;
        }

        for(int i = 0; i < mov_dir; i++)
		{
			x_desp = x + direcciones_x[i];
			y_desp = y + direcciones_y[i];

            if(!(x_desp < 0 || x_desp > NC-1 || y_desp < 0 || y_desp > NF-1 || mapa[x_desp][y_desp] == 1 || mapa_cerrados[x_desp][y_desp] == 1))
			{
				posible = new nodo(x_desp, y_desp, actual->getNivel(), actual->getPeso());
                posible->siguienteNivel(i);
                posible->recalculaPeso(fin_x, fin_y);

                if(mapa_abiertos[x_desp][y_desp] == 0)
				{
					mapa_abiertos[x_desp][y_desp] = posible->getPeso();
                    abiertos[n].push(*posible);
                    mapa_direcciones[x_desp][y_desp] = (i + mov_dir/2) % mov_dir;
				}
				else if(mapa_abiertos[x_desp][y_desp] > posible->getPeso())
				{
					mapa_abiertos[x_desp][y_desp] = posible->getPeso();
					mapa_direcciones[x_desp][y_desp] = (i + mov_dir/2) % mov_dir;
					
					while(!(abiertos[n].top().getPosx() == x_desp && abiertos[n].top().getPosy() == y_desp))
					{
						abiertos[1-n].push(abiertos[n].top());
						abiertos[n].pop();
					}

					abiertos[n].pop();
					
					if(abiertos[n].size() > abiertos[1-n].size())
						n = 1 - n;

					while(!abiertos[n].empty())
					{
						abiertos[1-n].push(abiertos[n].top());
                        abiertos[n].pop();       
                    }

					n = 1 - n;
                    abiertos[n].push(*posible);
				}
                else
					delete posible;
			}
        }
		delete actual;
	}
    return "";
}

void representar(int mapa[NC][NF])
{
	cout << "x x x x x x x x" << endl;
	for(int j = NF-1; j >= 0; j--)
	{
		cout << "x ";
		for(int i = 0; i < NC; i++)
		{
			if(mapa[i][j] == 0)
				cout << "  ";
			else if(mapa[i][j] == 1)
				cout << "+ "; // Obstacle
			else if(mapa[i][j] == 2)
				cout << "O "; // Origen
			else if(mapa[i][j] == 3)
				cout << "* "; // Cami
			else if(mapa[i][j] == 4)
				cout << "D "; // Desti
		}
		cout << "x " << endl;
	}
	cout << "x x x x x x x x\n" << endl;
}

void giro_derecha(CMoway *mymoway)
{
	mymoway->SetSpeed(30,30, CMoway::FORWARD,CMoway::BACKWARD, 11, 5);
	Sleep(282);
	mymoway->MotorStop();

}

void giro_izquierda(CMoway *mymoway)
{
	mymoway->SetSpeed(30,30, CMoway::BACKWARD,CMoway::FORWARD, 15, 5);
	Sleep(282);
	mymoway->MotorStop();
}

void giro_atras(CMoway *mymoway)
{
	mymoway->SetSpeed(50,50,CMoway::FORWARD, CMoway::BACKWARD, 10, 20);
	Sleep(655);
	mymoway->MotorStop();
}

void avanzar(CMoway *mymoway)
{
	mymoway->SetSpeedDistance(30, 30, CMoway::FORWARD, CMoway::FORWARD, 140, 140);
	Sleep(2000);
}

bool detectar(CMoway *mymoway)
{
	int l,cl,cr,r;
	mymoway->ReadProximitySensors(&l, &cl, &cr, &r);

	if(cr>10 && cl>10)
		return true;

	return false;
}

void orientar(CMoway *mymoway, int direccion, int &orientacion)
{
	switch(direccion){
	case 0:
		if(orientacion == N){
			giro_derecha(mymoway);
		}else if(orientacion == S){
			giro_izquierda(mymoway);
		}else if(orientacion == W){
			giro_atras(mymoway);
		}
		orientacion = E;
		break;
	case 1:
		if(orientacion == E){
			giro_izquierda(mymoway);
		}else if(orientacion == S){
			giro_atras(mymoway);
		}else if(orientacion == W){
			giro_derecha(mymoway);
		}
		orientacion = N;
		break;
	case 2:
		if(orientacion == N){
			giro_izquierda(mymoway);
		}else if(orientacion == E){
			giro_atras(mymoway);
		}else if(orientacion == S){
			giro_derecha(mymoway);
		}
		orientacion = W;
		break;
	case 3:
		if(orientacion == N){
			giro_atras(mymoway);
		}else if(orientacion == E){
			giro_derecha(mymoway);
		}else if(orientacion == W){
			giro_izquierda(mymoway);
		}
		orientacion = S;
		break;
	default:
		break;
	}
}

void aliveBehaviour(CMoway *mymoway, int ORIGEN_X, int ORIGEN_Y, int DESTINO_X, int DESTINO_Y)
{
	//TODO1: IMPLEMENT ALIVE BEHAVIOUR:

	AllocConsole();
	freopen("CONOUT$", "w+", stdout);
	
	int mapa[NC][NF];
	
	int ox, oy, dx, dy;

	ox = ORIGEN_X - 1;
	oy = ORIGEN_Y - 1;

	dx = DESTINO_X - 1;
	dy = DESTINO_Y - 1;
	
	cout << "Posicion origen en X: " << ORIGEN_X << endl;
	cout << "Posicion origen en Y: " << ORIGEN_Y << endl;
	cout << endl;
	cout << "Posicion destino en X: " << DESTINO_X << endl;
	cout << "Posicion destino en Y: " << DESTINO_Y << endl;
	cout << endl;
	
	for(int j = 0; j < NF; j++)
		for(int i = 0; i < NC; i++)
			mapa[i][j] = 0;

	mapa[ox][oy]=2;
	mapa[dx][dy]=4;

	cout << "Inicio:" << endl;
	representar(mapa);

	string ruta = calcular_ruta(ox, oy, dx, dy, mapa);
	
	if(ruta.length() > 0){

		char c;

		mapa[ox][oy] = 3;
		mapa[dx][dy] = 0;
        
		int x = ox;
        int y = oy;

		int o = N;

		int dir;

		int i = 0;
		int n = ruta.length();

		int paso = 0;

		cout << "Paso " << ++paso << ":" << endl;
		representar(mapa);

		while(i < n){

			c = ruta.at(i);
            dir = atoi(&c);

			orientar(mymoway, dir, o);

			if(!detectar(mymoway)){
				
				avanzar(mymoway);

				if(dir == 0)
					x++;
				else if(dir == 1)
					y++;
				else if(dir == 2)
					x--;
				else if(dir == 3)
					y--;

				mapa[x][y] = 3;

				i++;
			
			}else{

				if(dir == 0)
					mapa[x+1][y] = 1;
				else if(dir == 1)
					mapa[x][y+1] = 1;
				else if(dir == 2)
					mapa[x-1][y] = 1;
				else if(dir == 3)
					mapa[x][y-1] = 1;
				
				ruta = calcular_ruta(x, y, dx, dy, mapa);
				n = ruta.length();
				i = 0;
			}

			cout << "Paso " << ++paso << ":" << endl;
			representar(mapa);

			Sleep(500);
        }

		mapa[ox][oy]=2;
		mapa[dx][dy]=4;

		cout << "Fin:" << endl;
		representar(mapa);
	}

	mymoway->MotorStop();
	mymoway->DisconnectMoway();
	
	// END OF YOUR IMPLEMENTATION FOR ALIVE BEHAVIOUR
}

void fearBehaviour(CMoway *mymoway)
{
	//TODO2: IMPLEMENT FEAR BEHAVIOUR:
	
	avanzar(mymoway);
	Sleep(2000);

	// END OF YOUR IMPLEMENTATION FOR FEAR BEHAVIOUR
}

void aggressionBehaviour(CMoway *mymoway)
{
	//TODO3: IMPLEMENT AGGRESSION BEHAVIOUR:
	giro_derecha(mymoway);
	Sleep(2000);
	// END OF YOUR IMPLEMENTATION FOR AGGRESSION BEHAVIOUR
}

void loveBehaviour(CMoway *mymoway)
{
	//TODO4: IMPLEMENT LOVE BEHAVIOUR:

	//Recto
	mymoway->ChangeLEDState(CMoway::LED_FRONT,CMoway::ON);
	int l,cl,cr,r;
	mymoway->ReadProximitySensors(&l, &cl, &cr, &r);
/*
	mymoway->GoStraight(5, CMoway::FORWARD,10);
	Sleep(2000);

	while(mymoway->ReadProximitySensors(&l, &cl, &cr, &r) && l>200)

		mymoway->GoStraight(5, CMoway::FORWARD,1);*/
/*	mymoway->ChangeLEDState(CMoway::LED_FRONT,CMoway::ON);
	if( (l<200 && r<200) || cl<255)
		mymoway->GoStraightDistance(1, CMoway::FORWARD,140);


	Sleep(2000);*/

/*test linia
	mymoway->GoStraightDistance(50, CMoway::FORWARD,10);
	Sleep(2000);
*/
	/*mueve casilla
		if(cl<50 && cr<50){
		mymoway->GoStraightDistance(50, CMoway::FORWARD,140);
		Sleep(6000);
		mymoway->MotorStop();
		*/
/*
	if(cl<50 && cr<50){
		mymoway->GoStraightDistance(50, CMoway::FORWARD,70);
		Sleep(6000);
		mymoway->MotorStop();
	}

	else if(cl<250 && l<120){
		mymoway->GoStraightDistance(50, CMoway::FORWARD,10);
		Sleep(2000);
		mymoway->MotorStop();
	}
	mymoway->ChangeLEDState(CMoway::LED_FRONT,CMoway::OFF);
	Sleep(2000);
	*/

	giro_izquierda(mymoway);
	Sleep(2000);

	// END OF YOUR IMPLEMENTATION FOR LOVE BEHAVIOUR
}



void exploreBehaviour(CMoway *mymoway)
{
	//TODO5: IMPLEMENT EXPLORE BEHAVIOUR:

	avanzar(mymoway);
	Sleep(2000);
}

void lineBehaviour(CMoway *mymoway)
{
/*	int esq, dre;
	ofstream myfile;
	myfile.open ("color");
	
	myfile<<endl;

	for(int i=0; i<10;i++){
		mymoway->ReadLineSensors(&esq, &dre);
		myfile<<esq<<"\t"<<dre<<endl;
		Sleep(500);
	}
	 myfile.close();*/

	int l,cl,cr,r;
	ofstream myfile;
	
	myfile.open ("proximitat");

	mymoway->ChangeLEDState(CMoway::LED_FRONT,CMoway::OFF);

	for(int i=0; i<5;i++){
		mymoway->ReadProximitySensors(&l, &cl, &cr, &r);
		myfile<<l<<"\t"<<cl<<"\t"<<cr<<"\t"<<r<<endl;
		Sleep(250);
	}

	mymoway->ChangeLEDState(CMoway::LED_FRONT,CMoway::ON);

		for(int i=0; i<5;i++){
		mymoway->ReadProximitySensors(&l, &cl, &cr, &r);
		myfile<<l<<"\t"<<cl<<"\t"<<cr<<"\t"<<r<<endl;
		Sleep(250);
	}

	myfile<<endl<<endl<<endl<<endl;

	int bateria;
	mymoway->ReadBatteryStatus(&bateria);

	myfile<<bateria;

	mymoway->ChangeLEDState(CMoway::LED_FRONT,CMoway::OFF);

	myfile.close();
	// END OF YOUR IMPLEMENTATION FOR LINE FOLLOWING BEHAVIOUR
}

/***** FILE NOT USED *****/
