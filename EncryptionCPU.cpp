#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>

float encrypt[3][100], decrypt[3][100], a[3][100], b[3][100], mes[3][100], c[3][100];

void encryption();	//encrypts the message
void decryption();	//decrypts the message
void getKeyMessage();	//gets key and message from user
void inverse();		//finds inverse of key matrix

void main() {
clock_t start,stop;
double T;
int n;
printf("Enter the string  :");
char a[100];
gets(a);
int i=0;
while(a[i] != '\0')
    i++;



    if(i%3==0)
    {
        n=i/3;
        a[i]='\0';
    }

else if(n%3==1)
{  a[i]='a';
    a[i+1]='b';
    a[i+2]='\0';
    n=(i+2)/3;


}

else if(n%3==2)
{
     a[i]='a';
    n=(i+1)/3;
    a[i+1]='\0';

}


	getKeyMessage(n,a);
	start = clock();
	encryption(n,i);
	stop = clock();
	T = ((double)(stop-start));
	printf("\n\ntime to encrypt is   %f:",T);
	decryption(n,i);
}

void encryption(int n,int n1) {
	int i, j, k;

	for(i = 0; i < 3; i++)
		for(j = 0; j < n; j++)
			for(k = 0; k < 3; k++)
				encrypt[i][j] = encrypt[i][j] + a[i][k] * mes[k][j];
    char arr[3*n];
    int m=0;
	printf("\nEncrypted string is: ");
	for(i = 0; i < 3; i++)
        for(j =0;j<n;j++)
		arr[m++]= (char)(fmod(encrypt[i][j], 26) + 97);
    arr[m]='\0';

	if(n1%3==0)
	{
    printf("%s",arr);
	}
	else if(n1%3==1)
      {
	    for(int i=0;i<3*n -2;i++)
        printf("%c",arr[i]);
	}
    else if(n1%3==2)
      {
    for(int i=0;i<3*n -1 ;i++)
            printf("%c",arr[i]);
	}




}

void decryption(int n,int n1) {
	int i, j, k;

	inverse();

	for(i = 0; i < 3; i++)
    {
        for(j = 0; j < n; j++)
        {
          for(k = 0; k < 3; k++)
				decrypt[i][j] = decrypt[i][j] + b[i][k] * encrypt[k][j];
        }
    }

    char arr[3*n];
    int m=0;
	printf("\nDecrypted string is: ");
	for(i = 0; i < 3; i++)
    {
         for(j=0;j<n;j++)
        {


        if((char)(fmod(decrypt[i][j], 26) + 97) == 'T')
        {
            arr[m++]=' ';
        }
        else
    arr[m++]=(char)(fmod(decrypt[i][j], 26) + 97);
        }
    }
    arr[m]='\0';
    if(n1%3==0)
	{
	    for(int i=0;i<3*n ;i++)


	     printf("%c",arr[i]);
	}
	else if(n1%3==1)
      {
	    for(int i=0;i<3*n -2;i++)


	     printf("%c",arr[i]);
	}
    else if(n1%3==2)
      {

	    for(int i=0;i<3*n-1;i++)


	     printf("%c",arr[i]);
	}




}

void getKeyMessage(int n,char *message) {
	int i, j;
	char **msg = (char **)calloc(3 ,sizeof(char *));
    for (i=0; i<3; i++)
         msg[i] = (char *)calloc(n, sizeof(char *));


	printf("Enter 3x3 matrix for key (It should be inversible):\n");

	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++) {

			scanf("%f", &a[i][j]);
			c[i][j] = a[i][j];
		}


int t=0;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<n;j++)

        msg[i][j]= message[t++];
    }

	for(i = 0; i < 3; i++)
    {


        for(int j=0;j<n;j++)
    {
        mes[i][j] = msg[i][j] - 97;
}
}
    }


void inverse() {
	int i, j, k;
	float p, q;

	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			if(i == j)
				b[i][j]=1;
			else
				b[i][j]=0;
		}
	}
	for(k = 0; k < 3; k++) {
		for(i = 0; i < 3; i++) {
			p = c[i][k];
			q = c[k][k];

			for(j = 0; j < 3; j++) {
				if(i != k) {
					c[i][j] = c[i][j]*q - p*c[k][j];
					b[i][j] = b[i][j]*q - p*b[k][j];
				}
			}
		}
	}

	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			b[i][j] = b[i][j] / c[i][i];


}
