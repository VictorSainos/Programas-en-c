#include <stdio.h>
#include <stdlib.h>
#define Max1 5
#define Max2 41

typedef struct
{
	int p;
	int q;
} R;           //Racional

typedef struct
{
	R real;
	R img;
} C;           //Complejo

typedef struct
{
	C complejo[Max1][Max1];
} M;           //Matriz nxn   

typedef struct
{
	int M,identificador;
	int m[Max2];
	M coef[Max2];
} P;           //Caeficientes del polinomio


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int mcd (int, int);
R simplificar (R);
R Rsuma (R, R);
C Csuma (C, C);
M Msuma (M, M, int);
P Psuma (P, P, int);

R Rresta (R, R);
C Cresta (C, C);
M Mresta (M, M, int);
P Presta (P, P, int);

R Rmulti (R, R);
C Cmulti (C, C);
M Mmulti (M, M, int);
P Pmulti (P, P, int);

R Rderi (R, int);
C Cderi (C,  int);
M Mderi (M, int, int);
P Pderi (P, int);

R Rinte (R, int);
C Cinte (C,  int);
M Minte (M, int, int);
P Pinte (P, int);

int potencia (int, int);
R Reval (R, int, int);
C Ceval (C,  int, int);
M Meval (M, int, int, int);
P Peval (P, int, int);

int escribir(P, int);

int main(int argc, char *argv[]) 
{
	int x,y,w,n,k;
	P a,b;   //Polinomios a y b;
	
	//scaneo de n
	printf("Introducir el valor de n para los coeficintes matrices nxn: ");    scanf("%d",&n);
	if (n>5) 
	{
		printf("Valor erroneo para n (1 a 5), volver a introducirlo: ");    scanf("%d",&n);
	}
	
	//scaeno de k para evaluar el polinomio
	printf("Introdusca el valor de la evaluacion del polinomio: ");    scanf("%d",&k);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	printf("          polinomio a\n");
	//scaneo de m1
	printf("Introducir el coeficinte maximo para el polinomio a(x): ");    scanf("%d",&a.M);
	if (a.M>20 || a.M<0) 
	{
		printf("Valor erroneo para m1 (0 a 20), volver a introducirlo: ");    scanf("%d",&a.M);
	}
	
	//scaneo de los elmentos de a(x)
	for (x=0; x<=a.M; x++)
	{
		for (y=0; y<n; y++)
		{
			for (w=0; w<n; w++)
			{
				printf("a/b y ic/d para el coeficinete %d matriz[%d][%d]: ",x,y,w);    scanf("%d %d %d %d", &(a.coef[x].complejo[y][w].real.p), &(a.coef[x].complejo[y][w].real.q), &(a.coef[x].complejo[y][w].img.p), &(a.coef[x].complejo[y][w].img.q));		
				//Caso de un denominador 0
				if (a.coef[x].complejo[y][w].real.q==0 || a.coef[x].complejo[y][w].img.q==0)
				{
					printf("introducio un 0 en un denominador"); return 0;
				}
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	
	printf("          polinomio b\n");
	//scaneo de m2
	printf("Introducir el coefiente maximo para el polinomio b(x): ");    scanf("%d",&b.M);
	if (b.M>20 || b.M<0) 
	{
		printf("Valor erroneo para m2 (0 a 20), volver a introducirlo: ");    scanf("%d",&b.M);
	}
	
	//scaneo de los elmentos de b(x)
	for (x=0; x<=b.M; x++)
	{
		for (y=0; y<n; y++)
		{
			for (w=0; w<n; w++)
			{
				printf("a/b y ic/d para el coeficinete %d matriz[%d][%d]: ",x,y,w);    scanf("%d %d %d %d", &(b.coef[x].complejo[y][w].real.p), &(b.coef[x].complejo[y][w].real.q), &(b.coef[x].complejo[y][w].img.p), &(b.coef[x].complejo[y][w].img.q));
				//Caso de un denominador 0
				if (a.coef[x].complejo[y][w].real.q==0 || a.coef[x].complejo[y][w].img.q==0)
				{
					printf("introducio un 0 en un denominador"); return 0;
				}
			}
		}
	}
	
	//Expoenntte de a
	for (x=0; x<=a.M; x++)
	{
			a.m[x]=x;
	}
	
	//Exponente b
	for (x=0; x<=b.M; x++)
	{
			b.m[x]=x;
	}
	
	//Suma de polinomios
	printf("La suma de a(x)+b(x) es: \n");    Psuma(a, b, n);      printf("\n\n");
	
	//Resta de polinomios
	printf("La resta de a(x)-b(x) es: \n");    Presta(a, b, n);    printf("\n\n");
	
	//Multipolicacion de polinomios
	printf("La multiplicacion de a(x)*b(x) es: \n");    Pmulti(a, b, n);    printf("\n\n");
	
	//Derivada de polinomios
	printf("La derivada de a(x) es: \n");    Pderi(a, n);    printf("\n\n");
	
	//Integral de polinomios
	printf("La integral de b(x) es: \n");    Pinte(b, n);    printf("\n\n");
	
	//Evaluacion de polinomios
	printf("La evalucion de a(x) es: \n");    Peval(a, n, k);    printf("\n\n");
	
	return 0;
}



//Inicio de la funcion maximo comun divisor
int mcd (int n, int m)
{
	int mod,mcd;
	
	do
	{
		mod = n%m;
		
		if(mod!=0)
		{
		    n=m;
		    m=mod;
	    }
	    else
	    {
	    	mcd=m;
		}
	}
	while (mod!=0);
	
	return mcd;
}
//Fin de la funcion maximo comun divisor



//Inicio de l funcion simplificar
R simplificar (R a)
{
	int maximo;
	R s;
	
	maximo = mcd(a.p, a.q);
	
	s.p = a.p/maximo;
	s.q = a.q/maximo;
	
	if (s.q<0) { s.p*=-1;    s.q*=-1; }
	
	return s;
}
//Fin de la funcion simplificar



//Inicio de la funcion suma
R Rsuma (R a, R b)
{
	R suma;
	
	suma.p = (a.p*b.q) + (b.p*a.q);    suma.q = a.q*b.q;
	
	return simplificar(suma);
}
//Fin dela funcion suma



//Inicio de la funcion Csuma
C Csuma (C a, C b)
{
	C suma;
	
	suma.real = Rsuma(a.real, b.real);   
	suma.img = Rsuma(a.img, b.img);
	
	return suma;
}
//Fin de la funcion Csuma



//Inicio de la funcion Msuma
M Msuma (M a, M b, int n)
{
	int x,y;
	M suma;
	
	for (x=0; x<n; x++)
	{
		for (y=0; y<n; y++)
		{
			suma.complejo[x][y] = Csuma(a.complejo[x][y], b.complejo[x][y]);
		}
	}
	
	return suma;
}
//Fin de la funcion Msuma



//Inicio de la funcion Psuma
P Psuma (P a, P b, int n)
{
	int x,m,M;
	P suma;
	
	//Caso polinomios con mismo ceoficeinte maximo
	if(a.M==b.M)
	{
		suma=a;    m=a.M;    M=a.M;
	}
	
	else
	{
		//Casos con polinomios con diferentes expoenntes maximos
		if (a.M<b.M)
		{
			suma=b;    m=a.M;    M=b.M;
		}
		
		else
		{
			suma=a;    m=b.M;    M=a.M;
		}
	}
	
	for (x=0; x<=m; x++)
	{
		suma.coef[x] = Msuma(a.coef[x], b.coef[x], n);
	}
	
	suma.M=M;    suma.identificador=32;
	escribir(suma, n);
	return suma;
}
//Fin dela funcion Psuma

///////////////////////////////////////////////////////////////////////////////////////////////////////////


//Inicio de la funcion resta
R Rresta (R a, R b)
{
	R resta;
	
	resta.p = (a.p*b.q) - (b.p*a.q);    resta.q = a.q*b.q;
	
	return simplificar(resta);
}
//Fin dela funcion resta



//Inicio de la funcion Cresta
C Cresta (C a, C b)
{
	C resta;
	
	resta.real = Rresta(a.real, b.real);   resta.img = Rresta(a.img, b.img);
	
	return resta;
}
//Fin de la funcion Cresta



//Inicio de la funcion Mresta
M Mresta (M a, M b, int n)
{
	int x,y;
	M resta;
	
	for (x=0; x<n; x++)
	{
		for (y=0; y<n; y++)
		{
			resta.complejo[x][y] = Cresta(a.complejo[x][y], b.complejo[x][y]);
		}
	}
	
	return resta;
}
//Fin de la funcion Mresta



//Inicio de la funcion Presta
P Presta (P a, P b, int n)
{
	int x,m,M;
	P resta;
	//Caso polinomios con mismo ceoficeinte maximo
	if(a.M==b.M)
	{
		resta=a;    m=a.M;    M=a.M;
	}
	
	else
	{
		//Casos con polinomios con diferentes exponentes maximos
		if (a.M<b.M)
		{
			resta=b;    m=a.M;    M=b.M;
		}
		
		else
		{
			resta=a;    m=b.M;    M=a.M;
		}
	}
	
	for (x=0; x<=m; x++)
	{
		resta.coef[x] = Mresta(a.coef[x], b.coef[x], n);
	}
	
	resta.M=M;    resta.identificador=32;
	escribir(resta, n);
	return resta;
}
//Fin dela funcion Presta


///////////////////////////////////////////////////////////////////////////////////////////////

//Inicio de la funcion Rmulti
R Rmulti (R a, R b)
{
	R ret;
	
	ret.p = a.p*b.p;    ret.q = a.q*b.q;
	
	return simplificar(ret);
}
//Fin de la funcion Rmulti



//Inicio de la funcion Cmulti
C Cmulti (C a, C b)
{
	C mult;
	
	//Multiplicacion de racionales complejos
	mult.real = Rresta( Rmulti(a.real,b.real), Rmulti(a.img, b.img));
	mult.img = Rsuma( Rmulti(a.real,b.img), Rmulti(a.img,b.real));
	
	return mult;
}
//Fin de la funcion Cmulti


//Inicio de la funcion Mmulti
M Mmulti (M a, M b, int n)
{
	int x,y,z;
	M mult;
	
	for (x=0; x<n; x++)
	{
		for (y=0; y<n; y++)
		{
			//Inicializacion en p=0; y q=1;
			mult.complejo[x][y].real.p=0;    mult.complejo[x][y].real.q=1;
			mult.complejo[x][y].img.p=0;    mult.complejo[x][y].img.q=1;
            ////////////////////////////////////////////////////////////////////////
		}
	}
	
	//multipicacion de matrizes
	for (x=0; x<n; x++)
	{
		for (y=0; y<n; y++)
		{				
			for (z=0; z<n; z++)
			{
				mult.complejo[x][y] = Csuma(mult.complejo[x][y], Cmulti(a.complejo[x][z], b.complejo[z][y]) );
			}
		}
	}
	
	return mult;
}
//Fin de la funcion Mmulti


//Inicio de la funcion Pmulti
P Pmulti (P a, P b, int n)
{
	int x,y,z;
	P mult;
	
	//Inicializacion en 0 y 1
	for (x=0; x<=a.M+b.M; x++)
	{
		for (y=0; y<n; y++)
		{
			for (z=0; z<n; z++)
			{
				mult.coef[x].complejo[y][z].real.p = 0;    mult.coef[x].complejo[y][z].real.q = 1;
				mult.coef[x].complejo[y][z].img.p = 0;    mult.coef[x].complejo[y][z].img.q = 1;
			}
		}
	}
	
	//Multiplicacion de polinomios
	for (x=0; x<=a.M; x++)
	{
		for (y=0; y<=b.M; y++)
		{
			mult.coef[x+y] = Msuma(mult.coef[x+y], Mmulti(a.coef[x], b.coef[y], n), n);
			mult.m[x+y] = x+y;
		}
	}
	
	mult.M=a.M+b.M;
	mult.identificador = 32;
	escribir(mult, n);
	
	return mult;
}
//Fin de la funcion Pmulti

///////////////////////////////////////////////////////////////////////////////////////////////////////

//Inicio de la funcion Rderi
R Rderi (R a, int e)
{
	R der;
	der.p= a.p*e;    der.q = a.q;
		
	return simplificar(der);
}
//Fin de la funcion Rderi



//Inicio de la funcion Cderi
C Cderi (C a, int e)
{
	C der;
	
	der.real = Rderi(a.real,e);    der.img = Rderi(a.img,e);
	return der;
}
//Fin de la funcion Cderi



//Inicio de la funcion Mderi
M Mderi (M a, int n, int e)
{
	int x,y;
	M der;
	
	for (x=0; x<n; x++)
	{
		for (y=0; y<n; y++)
		{
			der.complejo[x][y] = Cderi(a.complejo[x][y], e);
		}
	}
	return der;
}
//Fin de la funcion Mderi



//Inicio de la funcion Pderi
P Pderi (P a, int n)
{
	int x;
	P der;
	
	for (x=0; x<=a.M; x++)
	{
		der.coef[x-1] = Mderi(a.coef[x], n, a.m[x]);    //Resta a a x en der.coef para que la entrada con coeficiente 0 no entre a la matriz y al escribrla no salga
		der.m[x]=a.m[x];

	}
	
	der.M = a.M-1;    der.identificador = 32;
	escribir(der, n);    
	return der;
}
//Fin de la funcion Pderi

/////////////////////////////////////////////////////////////////////////////////////////////////////


//Inicio de la funcion Rinte
R Rinte (R a, int e)
{
	R inte;
	inte.p= a.p;    inte.q = a.q*e;
		
	return simplificar(inte);
}
//Fin de la funcion Rinte



//Inicio de la funcion Cinte
C Cinte (C a, int e)
{
	C inte;
	
	inte.real = Rinte(a.real,e);    inte.img = Rinte(a.img,e);
	return inte;
}
//Fin de la funcion Cinte



//Inicio de la funcion Minte
M Minte (M a, int n, int e)
{
	int x,y;
	M inte;
	
	for (x=0; x<n; x++)
	{
		for (y=0; y<n; y++)
		{
			inte.complejo[x][y] = Cinte(a.complejo[x][y], e);
		}
	}
	return inte;
}
//Fin de la funcion Minte



//Inicio de la funcion Pinte
P Pinte (P a, int n)
{
	int x;
	P inte;
	
	for (x=0; x<=a.M; x++)
	{
		a.m[x]+=1;
		inte.coef[x] = Minte(a.coef[x], n, a.m[x]);
		inte.m[x]=a.m[x];
	}
	inte.M = a.M;
	inte.identificador = 67;
	escribir(inte, n);    
	return inte;
}
//Fin de la funcion Pinte

//////////////////////////////////////////////////////////////////////////////////////////


//Inicio de la funcion potencia
int potencia(int k, int exp)
{
	int x,t;
	
	t=1;
	for (x=0;x<=exp;x++)
	{
		t*=k;
	}
	
	return t;
}
//Fin de la funcion potencia



//Inicio de la funcion Reval
R Reval (R a, int e, int k)
{
	int exp;
	R elv;

	exp = potencia(k,e);
	elv.p = a.p*exp;    elv.q = a.q;
	
	return simplificar(elv);
}
//Fin de la funcion Reval


//Inicio de la funcion Ceval
C Ceval (C a,  int e, int k)
{
	C evl;
	
	evl.real = Reval(a.real, e, k);    evl.img = Reval(a.img, e, k);
	
	return evl;
}
//Fin de la funcion Ceval



//Fin de la funcion Meval
M Meval (M a, int n, int e, int k)
{
	int x,y;
	M evl;
	
	//Inicializacion en 0 y 1 para la suma de matrices
	for (x=0; x<n; x++)
	{
		for (y=0; y<n; y++)
		{
			evl.complejo[x][y].real.p=0;    evl.complejo[x][y].real.q=1;
			evl.complejo[x][y].img.p=0;     evl.complejo[x][y].img.q=1;
		}
	}
	
	 
	for (x=0; x<n; x++)
	{
		for (y=0; y<n; y++)
		{
		evl.complejo[x][y] = Ceval(a.complejo[x][y], e, k);
		}
	}

	return evl;
}
//Fin de la funcion Meval



//Fin de la funcion Peval
P Peval (P a, int n, int k)
{
	int x,y,z;
	P evl;
	
	//Inicializacion en 0
	for (x=0; x<n; x++)
	{
		for (y=0; y<n; y++)
		{
				evl.coef[0].complejo[x][y].real.p = 0;    evl.coef[0].complejo[x][y].real.q = 1;
				evl.coef[0].complejo[x][y].img.p = 0;     evl.coef[0].complejo[x][y].img.q = 1;
		}
	}
	
	
	for (x=0; x<=a.M; x++)
	{
		evl.coef[0] = Msuma(evl.coef[0], Meval(a.coef[x], n, a.m[x], k), n);
	}
	
	evl.M=0;
	evl.identificador = 32;
	escribir(evl, n);
	return evl;
}
//Fin de la funcion Peval

//////////////////////////////////////////////////////////////////////////////////////////


//Inicio de la funcion escribir
int escribir (P esc, int n)
{
	int x,y,z;
	x=0; y=0; z=0;
	for (x=0; x<=esc.M; x++)
	{
		if (esc.m[x]<0) printf("");
		else printf("[");
		
		for (y=0; y<n; y++)
		{
			for (z=0; z<n; z++)
			{
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
					if (esc.coef[x].complejo[y][z].real.p==0) printf("");
					else 
					{
						if (esc.coef[x].complejo[y][z].real.q==1) printf("%d +", esc.coef[x].complejo[y][z].real.p);
						else printf("%d/%d +", esc.coef[x].complejo[y][z].real.p, esc.coef[x].complejo[y][z].real.q);
					}
					
					if (esc.coef[x].complejo[y][z].img.p==0) printf("");
					else
					{
						if (esc.coef[x].complejo[y][z].img.q==1) printf("i(%d)", esc.coef[x].complejo[y][z].img.p);
						else printf("i(%d/%d) ", esc.coef[x].complejo[y][z].img.p, esc.coef[x].complejo[y][z].img.q);
					}										
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				if(y==n-1 && z==n-1) printf("");
			else printf(", ");
			}
		}
		
		if (esc.m[x]<0) printf("\n");
		else printf("]x^%d + %c\n",esc.m[x], esc.identificador);
	}
	return 0; 
}
