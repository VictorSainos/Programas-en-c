#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define Max 51

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                              //Programa para encontrar el camino mas corto de un laberinto
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //¿Porque no uso un apuntador para que mi matriz se valla actualizando, por ejemplo en el caso del recorrido del caballo?
 //Ya que explorare todas las posibilidad, necesito que cad camino sigua una matriz distinta, si pusiera un apuntador es posible qque en un camino
 //se tope con una casilla ya explorada y eso no seraie xplorar todos los casos, seria explorar solo un camino
 
typedef struct
{
	int laberinto[Max][Max];   //Aqui guardo mi laberinto
	int filas, columnas;
} L;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

L leer(int *, int *);                 //lee un archivo txt
int mostrar(L);                       //muestra el laberinto
int caminocorto(int *, L, int, int, int);    //Encuentra el camino mas corto para encontrar lña salida
int menor (int, int);                 //regresa el emnor entero de 2 numeros

int main(int argc, char *argv[]) 
{
	int b=0,x,y,pasos=0;
	L a; 
	a = leer(&x,&y);
	
	printf("Este es el laberinto leido: \n");
	printf("columnas: %d, filas: %d\n\n",a.columnas,a.filas); 
	mostrar(a);    printf("\n\n");
	
	pasos = caminocorto(&b,a, x, y, pasos);
	
	//No hay solucion
	if(pasos<0)
	{
		printf("No se encontro solucion");
		return 0;
	}
	
	//Se encontro la solucion
	else
	{
		printf("Se obtiveron %d casos\n",b);
		printf("La cantidad de menor pasos recorridos fue: %d", pasos);
	}
	return 0;
}



L leer(int *Ix, int *Iy)
{
	L a;
	int x=0,y=0,ver=1, maxcol;
	char car;
	FILE *archivo;
	
	
	archivo = fopen("l.txt","r");
	
	while ( !feof(archivo))
	{
		car=fgetc(archivo);
		
		if(car==10)
		{
			x++;
			if(ver)      //Toma la primera fila leida
			{
				maxcol=y; ver=0;
			}
			y=0;
		}
		
		else
		{
			if(car == 'M') a.laberinto[x][y] = 1;
			if(car == ' ') a.laberinto[x][y] = 0;
			if(car == 'E') 
			{
				*Ix = x;    *Iy = y;   //identifico en que cordenada empiezo;
				a.laberinto[x][y] = 0;
			}
			if(car == 'S') a.laberinto[x][y] = 2;
			y++;
		}
	}
	x++; //suma uno mas para que cuenta la ultima fila
	
	y=maxcol;
	a.filas=x;   a.columnas=y;
	fclose(archivo);
	
	return a;
}



int mostrar(L a)
{
	int x,y;
	
	for(x=0; x<a.filas; x++)
	{
		for(y=0; y<a.columnas; y++)
		{
			if ( a.laberinto[x][y] == 0) printf(" ");
			if ( a.laberinto[x][y] == 1) printf("M");
			if ( a.laberinto[x][y] == 2) printf("S");
			if ( a.laberinto[x][y] == 3) printf("%c",219);
		}
		printf("\n");
	}
	
	return 0;
}




int caminocorto(int *b, L l, int x, int y, int pasos)
{
	int p1,p2,p3,p4,V,m;   //V sera mi verificador para saber si llegue a la meta o tope con pared
	
	if( (x>=0 && x<l.filas) && (y>=0 && y<l.columnas) )   //verifico que estoy dentro del laberinto
	{
		if (l.laberinto[x][y] == 2) 
		{
			*b +=1;                                                                        //opcionalmente se puede ir mostrando cada caso 
			V = pasos;   //llegue a la meta
			l.laberinto[x][y]=3;
//			printf("posible solucion numero: %d     ",*b); printf("pasos recorridos: %d\n",pasos);
//			mostrar(l);
//			printf("\n\n");
		}
		
		else
		{
			if (l.laberinto[x][y] == 1 || l.laberinto[x][y] == 3) V = -1;   //retrocedo un paso si topo con pared o si ya pase por ahi
			
			else 
			{
				l.laberinto[x][y] = 3;  //pongo uno donde ya pase
				
				//Aqui es donde empiza la recursividad, exploro todos los caminos posibles
				p1 = caminocorto (b,l, x-1, y, pasos+1); 	//abajo -1
				p2 = caminocorto (b,l, x+1, y, pasos+1); 	//arriba 4
				p3 = caminocorto (b,l, x, y-1, pasos+1);  	//izquierda -1
				p4 = caminocorto (b,l, x, y+1, pasos+1);  	//derecha -1
				
				V = menor(p1,p2);  						//comparo la posibilidad 1 con la 2 y tomo el mas pequeño
				V = menor(V, p3); 						//la 3, con el resultado de la 1 y 2
				V = menor(V, p4); 						//la 4 con el resultado de la 1, 2 y 3
				
				l.laberinto[x][y] = 0;
			}
		} 
	}
	else  V=-1;  //el movimiento no esta dentro de la matrizz del laberinto
	
	return V;
}




int menor (int a, int b)
{
	if(a<0) return b;  //ya que puede que los pasos sean negativos y la funcion toma el menor, regrese al valor positivo
	if(b<0) return a;
	
	if(a<b)   return a;
	
	else return b;
}
//><
