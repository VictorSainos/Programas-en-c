#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define Max 100

typedef struct         //Trate de ir cambiando la cadena desntro de la estructura PILA  pero al escribirla ya no podia volver a usarla
{                      //poreso creo esta estructura para guradar y regresarla en im funcion posfija
	char cadena[Max];
	double X[27];
} pos;
                                             //Obserbacion: Desde la linea de comandos no reconoce el operador ^ asi que lo cambie por P

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                              //Estructura de la pila
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct 
{
	char a;
	double eval;
} Elem;


typedef struct nodo
{
	Elem E;
	struct nodo *sig;
} NODO;


typedef struct 
{
	char *cad;
	NODO *cima;
} PILA;


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

PILA* crearpila ();
int destruirpila (PILA *);
NODO* crearnodo (Elem);
int destruirnodo (NODO *);

int push (Elem, PILA *);
Elem obt (PILA *);
Elem pop (PILA *);

int eval (char [], pos);
pos posfija (PILA *);
int prioridad (char, char);
int evaluacion(pos);
double potencia (double, double);
int piso (double);

int main(int argc, char *argv[]) 
{
	int a,x,y;
	char exprecion[Max];
	int V[27];
	
	pos valores;
	
	strcpy(exprecion, argv[1]);
	
	for (x=0; x<27; x++)
	{
		V[x]=0;
		valores.X[x]=0;
	}
	
	for(y=0; exprecion[y]!=0; y++)
	{
		if(exprecion[y]>='a' && exprecion[y]<='z')
		{
			if ( exprecion[y] != 120)
			{
				if(V[exprecion[y] - 'a'] !=1)     
				{
					printf("Introdusca el valor para %c: ", exprecion[y]);    scanf("%lg", &valores.X[exprecion[y] - 'a']);
					V[exprecion[y] - 'a']=1;
				}
			}
		}
	}
	
	printf("La expresion ingresada es:  %s\n", exprecion);
	
	eval(exprecion, valores);
		
	return 0;
}




PILA* crearpila()
{
	PILA *pila;
	
	if ( (pila = (PILA*) malloc(sizeof(PILA))) == NULL)
	{
		printf("No hay espacio\n");
		return NULL;
	}
	
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





NODO* crearnodo(Elem p)
{
	NODO* nodo;
	
	if ( (nodo = (NODO *) malloc(sizeof(NODO))) == NULL) 
	{
		printf("No hay memoria\n");
		return NULL;
	}
	
	nodo->E = p;
	nodo->sig = NULL;
	return nodo;
}




int destruirnodo (NODO *nodo)
{	
	nodo->sig = NULL;
	free(nodo);
	return 0;
}




int push (Elem n, PILA *p)
{
	NODO* nodo;
	if ( (nodo = crearnodo(n)) == NULL) return -1;
	
	nodo->sig = p->cima;	
	p->cima = nodo;
}




Elem pop (PILA *p)
{
	Elem e;
	NODO* eliminar;
	
	e=p->cima->E;
	eliminar=p->cima;
	
	p->cima = p->cima->sig;
	
	destruirnodo(eliminar);
	return e;
}





Elem obt (PILA *p)
{
	return p->cima->E;
}





int eval (char car[], pos valores)
{
	
	PILA *pila;
	pila = crearpila();
	pila->cad = car;
	pos polaca;
	
	polaca = posfija(pila);
	
	printf("La notacion polaca inversa es:  %s\n", polaca.cadena);
	
	strcpy(valores.cadena, polaca.cadena);
	
	evaluacion(valores);
	
	return 0;
}




pos posfija (PILA *pila)       //esta funcion recibe una pila porque puse dentro la expresion
{
	int b,x, y=0, ver;
	
	Elem n,v;
	
	b = strlen(pila->cad);
	char a[b];
	
	for (x=0; pila->cad[x]!=0; x++)
	{
		if (pila->cad[x] >= 'a' && pila->cad[x] <= 'z')
		{
			a[y] = pila->cad[x];
			y++;
		}
		
		else
		{
			n.a = pila->cad[x];
			
			if (n.a == ')')
			{							
				v=obt(pila);
					
				while ( v.a !='(')
				{					
					v=pop(pila);
					a[y] = v.a;
					y++;
					v=obt(pila);
				}
				pop(pila);
			}		
						
			else 
			{
				if(pila->cima == NULL)
				{
					push(n, pila);
				}
				
				else
				{
					v=obt(pila);
					
					if ( (ver=prioridad(n.a, v.a)) != 0) push(n, pila);
					
					else 
					{
						while ( pila->cima != NULL && v.a!='(')
						{
							v=pop(pila);
							a[y] = v.a;
							y++;
							if (pila->cima != NULL) v=obt(pila);
						}
					
						push(n, pila);
					}	
				}
			}			
		}
	}
	
	while (pila->cima != NULL)
	{
		v=pop(pila);
		a[y] = v.a;
		y++;
	}
	a[y]='\0';
	pos posfi;    strcpy(posfi.cadena, a);
	
	return posfi;
}




int prioridad (char a, char b)
{
	//casos para los parentesis
	if ( a=='(' && ( (b=='(') || (b=='S') || (b=='C') || (a=='T') || (b=='*') ||  (b=='%') || (b=='/') || (b=='+') || (b=='-') || b=='P'))  return 1;
	
	if ( ( (a=='S') || (a=='C') || (a=='T') || (b=='P') || (a=='*') ||  (a=='%') ||(a=='/') || (a=='+') || (a=='-') ) && b=='(') return 1;
	/////////////////////////////////
	
	//Casos para funciones trigonometricas
	if ( ( (a=='S') || (a=='C') || (a=='T') ) && ( (b=='P') || (b=='*') ||  (b=='/') || (b=='%') || (b=='+') || (b=='-') )) return 1;
	
	//Casos para el exponente
	if ( a=='P' && ( (b=='(') || (b=='*') ||  (b=='/') || (a=='%') || (b=='+') || (b=='-') ))  return 1;
		
	if ( ( (a=='*') || (a=='/') || (a=='%') ) && ( (b=='*') || (b=='/') || (b=='%')))  return 0;
		
	if ( ( (a=='*') || (a=='/') || (a=='%')) && ( (b=='+') || (b=='-') ))  return 1;
		
	if ( ( (a=='+') || (a=='-') ) && ( (b=='*') || (b=='/') || (b=='%') )) return 0;
	
	if ( ( (a=='+') || (a=='-') ) && ( (b=='+') || (b=='-') )) return 1;
		
	return 0;
}




int evaluacion (pos p)
{
	int a,b,c,x,y;
	double E;
	Elem e,e2;
	
	PILA *pila;
	pila = crearpila();

	for (x=-5; x<=5; x++)
	{
		for (y=0; p.cadena[y] !=0; y++)
		{
			p.X[23] = x;
			if (p.cadena[y] >= 'a' && p.cadena[y] <= 'z')
			{
				e.eval = p.X[ p.cadena[y] - 'a'];
				
				push(e, pila);			
			}
			
			else
			{
				c = p.cadena[y];
				switch (c)
				{
					case 37:                    //Modulo
						e = pop(pila);
						e2 = pop(pila);
						a = piso(e.eval);    b = piso (e2.eval);
						
						e.eval = b%a;
						push(e, pila);
						
						break;
						
					case 42:                    //Multiplicacion
						e = pop(pila);
						e2 = pop(pila);
						e.eval *= e2.eval;
						push(e, pila);
						break;
						
						
					case 43:                     //Suma
						e = pop(pila);
						e2 = pop(pila);
						e.eval += e2.eval;
						push(e, pila);
						
						break;
						
					case 45:                     //Resta
						e = pop(pila);
						e2 = pop(pila);
						e2.eval -= e.eval;
						push(e2, pila);
					
						break;
						
					case 47:                    //Divicion
						e = pop(pila);
						e2 = pop(pila);
						e2.eval /= e.eval;
						push(e2, pila);
						
						break;
					
					case 67:                    //Coseno
						e = pop(pila);
						e.eval=cos(e.eval);
						push(e, pila);
						
						break;
					
					case 83:                    //Seno
						e = pop(pila);
						e.eval=sin(e.eval);
						push(e, pila);
						
						break;
					
					case 84:                    //Tangente
						e = pop(pila);
						e.eval=tan(e.eval);
						push(e, pila);
						
						break;
									 
					case 80:                   //Potencia
						e = pop(pila);
						e2 = pop(pila);
						
						e.eval = potencia(e2.eval, e.eval);
						
						push(e, pila);
						
						break;
							
				}
			}
		}
		e = pop(pila);
		printf("La evaluacion en x=%d, es: %lg\n", x, e.eval);
	}
	
	return 0;
}





double potencia (double a, double b)
{
	if (a<0) a*=-1;
	
	double l,p;
	
	l = log(a);
	l *= b;
	p = exp(l);
	
	return p;
}




int piso (double a)
{
	int x,y=0;
	
	if (a<0)
	{
		a *= -1;
		for (x=0; x<=a; x++)
		{
			y--;
		}
		
		return y;
		
	}
	
	else 
	{
		for (x=0; x<a; x++)
		{
			y++;
		}
		if (y!=a) y--;
	}
	
	return y; 
}
//-><
