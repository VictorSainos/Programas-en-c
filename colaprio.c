#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max 100

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                   //Para la cola con prioridad solo cambian los elmentos del nodo y la funcion push
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct                         //en la estructura agurado los elmentos de cada nodo
{
	char cad1[Max], cad2[Max];        //cadena de caracteres
	int x1,x2;                        //entero
	double f;                          //punto flotante
} Elemento; 


typedef struct NODO     //Elementos de la cola
{
	Elemento *elemt;    //elemntos del nodo
	struct NODO *sig;   //siguiente nodo
} NODO;


typedef struct          //COLA
{
	int x;
	NODO *primero;
	NODO *ultimo;
} COLA;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int menu(COLA *);                     //Menu para eleguir la accion a realizar (insertar, eliminar, mostrar y salir)
int Verificarn ();                    //Verifica si se elgui una accion valida

NODO* crearN (Elemento *);            //Crea espacio para el nodo
int destruirN (NODO *);               //Destruye un nodo 
 
COLA* crearC ();                      //Crea espacio para una cola
int  destruirC (COLA *);              //Destruye una cola

int pushPrio (COLA *, Elemento *);   //Inserta un elemento a la cola
int pop (COLA *);                    //Quita un elemnto de la cola, el primero en llegar es el primero en irse
int escribir(COLA *);


int main(int argc, char *argv[]) 
{
	COLA *cola;
	cola = crearC();
	cola->x=0;
	menu (cola);     //Inicia el menu
	
	printf("\n");
	
	printf("Fin del programa");
	
	return 0;
}




//Inicio de la funcion menu
int menu (COLA *cola)
{
	int n,x;
	Elemento a;
	
	printf("Introdusca n para eleguir la accion a realizar: \n\n");
	printf("1: Insertar un elemento\n");
	printf("2: Eliminar un elemento\n");
	printf("3: Mostrar los elementos\n");
	printf("4: Salir\n");
	
	printf(": ");    n=Verificarn();   //Verifica n hasta que se introdusca una opcion valida
	
	switch (n)
	{
		case 1:
			printf("                              Opcion 1: Insertar un elemento\n\n");
			
			printf("Introdusca la primera cadena : ");                                    scanf("%s", &a.cad1);
			printf("Introdusca la segunda cadena : ");                                    scanf("%s", &a.cad2);
			printf("Introdusca los enteros entero (dejando espacio): ");                  scanf("%d %d", &a.x1, &a.x2);
			printf("Introdusca el punto flotante: ");                                     scanf("%lg", &a.f);
					
			pushprio(cola, &a);
			
			printf("Se agrego el elemento a la cola\n\n");
			break;
			
		case 2:
			printf("                              Opcion 2: Eliminar un elemento\n\n");
			pop(cola);
			printf("\n\n");
			break;
		
		case 3:
			printf("                              Opcion 3: Mostrar la cola\n\n");
			printf("Estos son los elementos de la cola: \n\n");
			escribir(cola);
			printf("\n");
			break;
			
		case 4:
			printf("                              Opcion 4: Salir\n\n");
			printf("La cola quedo asi: \n\n");
			destruirC(cola);
			return 0;
			
	}
	
	menu(cola);
}
//Fin de la funcion menu





int Verificarn ()
{
	int n;
	
	scanf("%d",&n);
	if (n<1 || 4<n)
	{
		printf("El valor no esta en el rango 1 a 4, vuelva a introducirlo: ");
		n=Verificarn();
	}
	
	return n;
}




NODO* crearN (Elemento *nuevo)
{
	NODO *nodo;
	
	if ( (nodo = (NODO *) malloc(sizeof(NODO))) == NULL)
	{
		printf("No hay espacio\n");    return NULL;
	}
	
	nodo->elemt = nuevo;
	nodo->sig = NULL;
	return nodo;
}



int destruirN (NODO *l)
{
	l->elemt = NULL;
	l->sig = NULL;
	free(l);
	return 0;
}




COLA* crearC ()
{
	COLA *cola;
	if ( (cola = (COLA *) malloc(sizeof(COLA))) == NULL)
	{
		printf("No hay espacio\n");    return NULL;
	}
	cola->primero = NULL;     cola->ultimo=NULL;
	return cola;
}





int destruirC (COLA* cola)
{
	int x=1;
	
	while (cola->primero != NULL)
	{
		printf("               Elemento %d: \n", x);
		pop(cola);
		x++;
		printf("\n");
	}
	
	free(cola);
	
	return 0;
}




int pushprio (COLA * cola, Elemento *n)
{
	int x=0, y=0;	
	NODO* nodo;
	NODO *aux;
	
	nodo= crearN(n);
	
	if (cola->primero == NULL)       //si la cola esta vacia
	{
		cola->primero = nodo;
		cola->ultimo = nodo;
		cola->x++;
		
		return 0;
	}
	
	if (nodo->elemt->cad1[0] < cola->primero->elemt->cad1[0])    //si el primer caracter es mayor al caracter agregado lo mete
	{
		nodo->sig = cola->primero;
		cola->primero = nodo;
		cola->x++;
		
		return 0;	
	}
	
	
	if (nodo->elemt->cad1[0] == cola->primero->elemt->cad1[0])   //si el primer caracter es igual al que se queire meter, recore la cadena
	{
		x=1;
		
		while (nodo->elemt->cad1[x] != 0)
		{
			if (nodo->elemt->cad1[x] < cola->primero->elemt->cad1[x])
			{
				nodo->sig = cola->primero;
				cola->primero = nodo;
				cola->x++;
				
				return 0;
			}
			x++;
		}
	}
	
	if ( strcmp(nodo->elemt->cad1, cola->primero->elemt->cad1) == 0)  //si es la misma cadena busca en la segunda
	{	
		while (nodo->elemt->cad2[y] != 0)
		{
			if (nodo->elemt->cad2[y] > cola->primero->elemt->cad2[y])
			{
				nodo->sig = cola->primero;
				cola->primero = nodo;
				return 0;
				cola->x++;
			}
			y++;
		}
	}
	
	
	aux=cola->primero;
	x=0;    y=0;
	
	if (cola->x!= 1)                                                 //se asegura que por lo menos se tenga 1 en elemento en al cola
	{
		while (nodo->elemt->cad1[x] != 0)                            //recorre la cadena introducrida para saber si va entre el principio y el segundo elemnto
		{
			if (nodo->elemt->cad1[x] < aux->sig->elemt->cad1[x])
			{
				nodo->sig = cola->primero->sig;
				cola->primero->sig = nodo;
				return 0;
			}
			x++;
		}
		
		if ( strcmp(nodo->elemt->cad1, aux->sig->elemt->cad1) == 0)  //si es la misma cadena busca en la segunda
		{	
			while (nodo->elemt->cad2[y] != 0)                          //Agrega de mayor a menor
			{
				if (nodo->elemt->cad2[y] > aux->sig->elemt->cad2[y])
				{
					nodo->sig = cola->primero->sig;
					cola->primero->sig = nodo;
					return 0;
				}
				y++;
			}
		}
	}
	
	aux = cola->primero->sig;
	x=0;    y=0;
	
	if (cola->x!= 1)                                                 //se asegura que por lo menos se tenga 1 en elemento en al cola
	{
		while (aux->sig != NULL)                                     //para si llega al ultimo elmento
		{
			while (nodo->elemt->cad1[x] != 0)                         //recorre la primera cadena
			{
				if (nodo->elemt->cad1[x] < aux->sig->elemt->cad1[x])  //si es menor la grega entre 2 elementos
				{
					nodo->sig = aux->sig;
					aux->sig = nodo;
					return 0;
				}
				x++;
			}
			
			if ( strcmp(nodo->elemt->cad1, aux->sig->elemt->cad1) == 0)  //si es la imsma cadena busca en la segunda
			{	
				while (nodo->elemt->cad2[y] != 0)                          //Agrega de mayor a menor
				{
					if (nodo->elemt->cad2[y] > aux->sig->elemt->cad2[y])
					{
						nodo->sig = aux->sig;
						aux->sig = nodo;
						return 0;
					}
					y++;
				}
			}
		
			aux = aux->sig;
		}
	}
	
	//si es que el elmento es mayor al ultimo elemento, entonces el nuevo elemnto es el ultimo
	cola->ultimo->sig = nodo;
	cola->ultimo = nodo;
	cola->x++;
		
	return 0;
}





int pop (COLA *cola)
{
	NODO *aux;
	Elemento *e;
	
	if (cola->primero != NULL)
	{
		aux = cola->primero;
		e = aux->elemt;
		cola->primero = cola->primero->sig;
		destruirN(aux);
		if (cola->primero == NULL) { cola->ultimo = NULL; }
	}
	
	if (e == NULL)
	{
		printf("No hay elementos para mostrar\n");    return 0;
	}
	
	else
	{
		printf("Primera Cadena de caracteres: %s \n", e->cad1);
		printf("Segunda de caracteres: %s \n", e->cad2);
		printf("Primer Entero: %d \n", e->x1);
		printf("Segundo Entero: %d \n", e->x2);
		printf("Punto flotante: %g \n", e->f);
	}
	
	printf("\n");
	return 0;
}





int escribir(COLA *cola)
{
	int x=1,y;
	NODO *aux;
	
	aux=cola->primero;
	
	while (aux->sig != NULL)                                        //Cuando el aux->sig es NULL estaria apuntando al ultimo elemento asi que ese no lo escribe 
	{                                                               //poreso lo puse fuera del while, intente usar un for pero solo me escribia un elemnto, lo deje comentado abajo
		printf("               Elemento %d: \n", x);
		
		printf("Primera Cadena de caracteres: %s \n", aux->elemt->cad1);
		printf("Segunda de caracteres: %s \n", aux->elemt->cad2);
		printf("Primer Entero: %d \n", aux->elemt->x1);
		printf("Segundo Entero: %d \n", aux->elemt->x2);
		printf("Punto flotante: %g \n", aux->elemt->f);
		
		x++;
		aux = aux->sig;
		printf("\n");
	}
	
	printf("               Elemento %d: \n", x);
		
	printf("Primera Cadena de caracteres: %s \n", aux->elemt->cad1);
	printf("Segunda de caracteres: %s \n", aux->elemt->cad2);
	printf("Primer Entero: %d \n", aux->elemt->x1);
	printf("Segundo Entero: %d \n", aux->elemt->x2);
	printf("Punto flotante: %g \n", aux->elemt->f);
		
	return 0;
}
//<->
