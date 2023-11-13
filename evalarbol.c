#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define Max 100

/////////////////////////////////////////// NOTA: la potencia se representa por el caracter "."

typedef struct Anodo
{
	char c;
	struct Anodo *izq;
	struct Anodo *der;
} ANODO;

ANODO* crearAnodo(char);
int destruirAnodo(ANODO *);

////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
	char car;
	ANODO *nodo;
} A;

typedef struct nodo
{
	A e;
	struct nodo *sig;
} NODO;

typedef struct
{
	NODO *cima;
} PILA;

////////////////////////////////////////////////////////////////////////////////////////////////

PILA* crearpila ();
int destruirpila (PILA *);
NODO* crearnodo (A);
int destruirnodo (NODO *);

int push (A, PILA *);
A obt (PILA *);
A pop (PILA *);

int polaca(char [], double []);
int prioridad (char);
int arbol (char [], double []);
int escribir(ANODO*);
double eval (double [], int, ANODO *);

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) 
{
	int x=0;
	double valores[27];
	int V[27];
	char expresion[Max];
	
	strcpy(expresion, argv[1]);
	
	for (x=0; x<27; x++)
	{
		V[x]=0;
		valores[x]=0;
	}
	
	for (x=0; expresion[x] != 0; x++)
	{
		if (expresion[x] != 'x')
		{
			if ( expresion[x] >= 'a' && expresion[x] <= 'z' )
			{
				if (V[expresion[x]-'a'] == 0)
				{
						printf("Introdusca el valor para %c: ", expresion[x]);    scanf("%lg", &valores[expresion[x]-'a']);
					V[expresion[x]-'a'] = 1;
				}
			}
		}
	}
	
	printf("La expresion es: %s\n", expresion);
	
	polaca(expresion,valores);
	
	return 0;
}



ANODO* crearAnodo (char n)
{
	ANODO *nodo;
	
	if ( (nodo = (ANODO *) malloc(sizeof(ANODO))) == NULL) { printf("No hay memoria\n");    return NULL; }
	nodo->c=n;
	nodo->izq=nodo->der=NULL;
	
	return nodo;
}




int destruirAnodo (ANODO *nodo)
{
	nodo->izq = nodo->der = NULL;
	free(nodo);
	return 0;
}




PILA* crearpila()
{
	PILA *pila;
	
	if ( (pila = (PILA*) malloc(sizeof(PILA))) == NULL) { printf("No hay espacio\n");	return NULL; }
	
	pila->cima = NULL;
	return pila;
}




int destruirpila (PILA * pila)
{
	while (pila->cima != NULL)
	{
		pop(pila);
	}
	
	return 0;
}





NODO* crearnodo(A n)
{
	NODO* nodo;
	
	if ( (nodo = (NODO *) malloc(sizeof(NODO))) == NULL) { printf("No hay memoria\n");    return NULL; }
	
	nodo->e = n;    nodo->sig = NULL;
	return nodo;
}




int destruirnodo (NODO *nodo)
{	
	nodo->sig = NULL;
	free(nodo);
	return 0;
}



int push (A n, PILA *p)
{
	NODO* nodo;
	if ( (nodo = crearnodo(n)) == NULL) return -1;
	
	nodo->sig = p->cima;	p->cima = nodo;
}




A pop (PILA *p)
{
	A e;
	NODO* eliminar;
	
	e=p->cima->e;
	eliminar=p->cima;
	
	p->cima = p->cima->sig;
	
	destruirnodo(eliminar);
	return e;
}



A obt (PILA *p)
{
	return p->cima->e;
}



int polaca (char cad[], double V[])
{
	int b,c,x,y=0;
	char *a = cad, C[100];
	A aux,n;
	PILA *pila;    pila=crearpila();
	
	for (x=0; cad[x] != 0; x++)
	{
		if ( cad[x] >= 'a' && cad[x] <= 'z' )
		{
			C[y] = cad[x];    y++;
		}
		
		else
		{
			if (cad[x]==')')
			{
				aux=obt(pila);
				
				while (aux.car != '(')
				{
					aux=pop(pila);
					C[y] = aux.car;    y++;
					aux=obt(pila);
				}
				pop(pila);
			}
			
			else
			{
				n.car=cad[x];
				if (pila->cima == NULL)  push(n, pila);
				
				else
				{
					aux = obt(pila);
					
					if ( (b=prioridad(cad[x]) ) == (c=prioridad(aux.car)) )
					{
						aux = pop(pila);
						C[y] = aux.car;    y++;
						push(n, pila);
					}
					
					else 
					{
						if ( (b=prioridad(cad[x]) ) > (c=prioridad(aux.car)) )  push(n, pila);
						else 
						{			
							while ( pila->cima != NULL && aux.car!='(')
							{
								aux=pop(pila);
								C[y] = aux.car;    y++;
								if (pila->cima != NULL) aux=obt(pila);
							}
							push(n, pila);
						}
					}  
				}
			}
		}
	}

	while (pila->cima != NULL)
	{
		aux=pop(pila);
		C[y] = aux.car;    y++;
	}
	C[y] = '\0';
	
	destruirpila(pila);
	printf("La expresion en posfija es: %s\n",C);
	
	arbol(C,V);
	return 0;
}




int arbol (char cad[], double V[])
{
	int x;
	PILA *pila;    pila=crearpila();
	A aux,a;
	
	for (x=0; cad[x] != 0; x++)
	{
		if ( cad[x] >= 'a' && cad[x] <= 'z' )
		{
			ANODO *n;    n = crearAnodo(cad[x]);
			aux.nodo=n;
			push(aux, pila);
		}
		
		else
		{
			if ( cad[x] >= '*' && cad[x] <= '/')
			{
				ANODO *m;    m=crearAnodo(cad[x]);
				
				aux = pop(pila);
				m->der=aux.nodo;
				aux = pop(pila);
				m->izq = aux.nodo;
				a.nodo=m;
				push(a, pila);	
			}
			
					
			if (cad[x] >= 'C' && cad[x] <= 'T')
			{
				ANODO *l;    l=crearAnodo(cad[x]);
				aux = pop(pila);
				l->der=aux.nodo;
				a.nodo=l;
				push(a, pila);
			}
			
			if ( cad[x] == '^')
			{
				ANODO *m;    m=crearAnodo(cad[x]);
				
				aux = pop(pila);
				m->der=aux.nodo;
				aux = pop(pila);
				m->izq = aux.nodo;
				a.nodo=m;
				push(a, pila);	
			}
		}
	}
	
	aux=pop(pila);
	//escribir(aux.nodo);
	
	double r;
	
	for (x=-5; x<=5; x++)
	{
		r = eval(V, x, aux.nodo);
		printf("La evaluacion en %d, es: %lg\n", x,r);
	}
	
	destruirAnodo(aux.nodo);
	
	return 0;
}




int prioridad (char a)
{
	if (a=='(') return 5;
	if (a=='.') return 4;
	if (a=='S' || a=='C' || a=='T' || a=='L') return 3;
	if (a=='*' || a=='/') return 2;
	if (a=='+' || a=='-') return 1;
	return 0;
}




double eval (double V[], int X, ANODO *a)
{
	if (a->c == 'x') return X;
	
	if ( a->c >= 'a' && a->c <= 'z' ) return V[a->c-'a'];
	
	switch (a->c)
	{
		case '+': return (eval(V, X, a->izq)+eval(V, X, a->der));
		
		case '*': return (eval(V, X, a->izq)*eval(V, X, a->der));
		
		case '/': return (eval(V, X, a->izq)/eval(V, X, a->der));
		
		case '.':
			{
				if (X<0)  return exp(eval(V, X, a->der)*log(eval(V, -1*X, a->izq)));
				else      return exp(eval(V, X, a->der)*log(eval(V, X, a->izq)));
			}
		
		case 'C': return cos(eval(V, X, a->der));
		
		case 'S': return sin(eval(V, X, a->der));
		
		case 'T': return tan(eval(V, X, a->der));
		
		case 'L': return log(eval(V, X, a->der));
	}
}




int escribir (ANODO *a)
{
	if (a == NULL) return 0;
	
	escribir (a->izq);
	printf("%c", a->c);
	escribir (a->der);
	
	return 0;
}
//-><
