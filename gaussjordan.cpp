#include <iostream>
#define Max 25
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct               //Guardo aqui los valores de la matriz, use una estructura para facilitar el retorno en las funciones
{
	double M[Max][Max];
} matriz;

using namespace std;

// En las siguientes funciones se manipula la matriz, retorno una estrucutra que contenga la matriz
matriz gauss (int, int, matriz);
matriz cambiar (int, int, int, int, matriz );
matriz eliminar (int, int, int, int, matriz);
int escribir (int, int, matriz);


int main(int argc, char** argv) 
{
	int n,m,x,y;      // n columnas y m filas
	matriz a;
	
	cout << "Introduzca n de columnas y m de filas para la matriz: ";   cin >> n >> m;
	
	cout << "Introduzca las entradas de la matriz: ";
	
	for (x=0; x<n; x++)
	{
		for (y=0; y<m; y++)
		{
			cin >> a.M[x][y]; 
		}
	}
			
	cout << "La matriz es: " << endl;
	escribir(n,m,a);
	
	a = gauss(n,m,a);
	
	cout << "La matriz reducida es: " << endl;
	escribir(n,m,a);
	
	return 0;
}



matriz gauss(int n, int m, matriz a)
{
	int x,y,con=1;   double r;            // r divide toda la fila
	
	// El for se movera diagonalmente por la matriz, note que las diagonales si estamos en una posicion x, son (x+1, x+1)
	for (x=0; x<n; x++)
	{
		if(a.M[x][x] == 0 && x != n-1)    // si el elemento seleccionado es 0 y no es la ultima columna, lo cambia por otra fila
		{
			a = cambiar(n,m,x,x,a);
		}
		
		r = a.M[x][x];
		if(r!=0)                          // Divido la posicion interesada entre toda la fila
		{
			for (y=x; y<m; y++)
				a.M[x][y] /= r;		
		}
		
		if(a.M[x][x] != 0)                // si no es cero elimina todas las columnas de abajo y arriba para obtener un 1 dominante, si es que se puede
		{
			a = eliminar(n,m,x,x,a);
		}
		
		if (a.M[x][x]==0 && x==n-1)   // Si llegue a la ultima fila y en esa posicion de la columna no pedo conseguir el 1 dominante
		{
			while(x+1<m)
			{
			    if(a.M[x][x+1]!=0)
				{                                  // si en la misma fila, la posicion de la izquierda no rebasa m, entonces opero desde esa posicion
					a.M[x][x+1]/=a.M[x][x+1];
					a = eliminar(n,m,x,x+1,a);     // Solo muevo la columna un lugar
					x+=100;
				}
				x++;
		   	}
		}
//		cout << "Paso numero: " << con++ << endl;
//		escribir(n,m,a);  //escribir opcionalmente los pasos
	}                                                                 // El for termina cuendo se alcanzo la diagonal mas "baja", osea cuando ya no hay elemento debajo
	
	return a;
}


//Cambia de lugar a 2 filas, px y py se refieren a la posicion actual en donde estamos en la funcion gauss
matriz cambiar (int n, int m, int px, int py, matriz a)
{
	int x,y;    double aux1,aux2;   // Los usare para guardar temporalmente valores de la matriz
	x = px;
	
	while (x<n)                     // mientras que x no rebase el numero de columnas seguira, vea que no necesito revisar las columnas de arriba ya que se supone que son 0 
	{
		if (x+1<n && a.M[x+1][py] != 0)      // si la columna de abajo no es cero, las cambia
		{
			for(y=0; y<m; y++)
			{
				aux1 = a.M[px][y];    aux2 = a.M[x+1][y];      // guardo cada elemnto de la fila y las intercambio
				a.M[px][y] = aux2;    a.M[px+1][y] = aux1;
			}	
			return a;                                          // retorno la matriz porque ya no hay nada que hacer
		}
		x++;
	}
	
	// si ninguna columna de abajo es diferente de cero regresa la matriz sin hacerle nada
	return a;
}


// Multiplica una fila por una constante y la suma a otra fila
matriz eliminar (int n, int m, int px, int py, matriz a)
{
	int x,y;    double q;            // q es la constante con la que se volvera cero la comuna deceada

	for (x=px-1; x>=0; x--)          // x empieza en una posicion menor a la actual ya que vamos a eliminar las filas de arriba
	{
		q = a.M[x][py]/a.M[px][py];  // constante especial
	
		for (y=py; y<m; y++)
			a.M[x][y] = a.M[x][y]-(q*a.M[px][y]);   // multiplica la constante por la fila en la posicion actual y la resta a otra fila
	}
	
	//if(px!=n-1)  // si estoy en la ultima fila, ya no elimino hacia bajo
	//{
		for (x=px+1; x<n; x++)           // hace lo mismo pero ahora a las filas de abajo
		{
			q = a.M[x][py]/a.M[px][py];
		
			for (y=py; y<m; y++)
				a.M[x][y] = a.M[x][y]-(q*a.M[px][y]);
		}
	//}
	return a;
}


//Escribe la matriz
int escribir (int n, int m, matriz a)
{
	int x,y;
	
	for (x=0; x<n; x++)
	{
		for (y=0; y<m; y++)
			cout << a.M[x][y] << " ";
			
		cout << endl;
	}
	cout << endl;	
	
	return 0;
} 
//<<>>
