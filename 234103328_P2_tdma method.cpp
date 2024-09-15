#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
int main()
{
   	int m = 11, n = 11; 
	int i,j, iteration;
	double dx, dy;
	dx = 0.1;
	dy = 0.1;
	double error;
	double tem_old, tem_new[m][n];
    double a, b, c, d[m-2], p[m-2],q[m-2];
    
    	for(i = 0; i < m; i++)
	{
		for(j = 0; j < n; j++)
		{
			if( i == (m-1) )
			{
				tem_new[i][j] = 0.0; //Top b
			}
			else if ( j == 0)
			{
				tem_new[i][j] = 1.0; //left b
			}
			else if ( i == 0)
			{
				tem_new[i][j] = 1.0; //bottom b
			}
			else if ( j == (n-1) )
			{
				tem_new[i][j] = 1.0;//right b
			}
			else
			{
				 tem_new[i][j] = 0.0; //interior p
			}
			
		}
	}

  iteration=0;
  do{
  	error=0;
	for(j=1; j<n-1;j++)
	{
		a=-4;
		b=1;
		c=1;
		d[0]=-1*(tem_new[0][j-1]+tem_new[0][j+1]);
		p[0]=0.25;
		q[0]=d[0]/a;
		q[n-1]=tem_new[n-1][j];
		p[n-1]=0;
		
		for(i=1;i<m-1;i++)
		{
			d[i]=-1*(tem_new[i][j-1]+tem_new[i][j+1]);
			p[i]=-b/(a-c*p[i-1]);
			q[i]=(d[i]-c*q[i-1])/(a+c*p[i-1]);
		}
		for(i=m-2;i>0;i--)
		{
			tem_old=tem_new[i][j];
			tem_new[i][j]=p[i]*tem_new[i+1][j]+q[i];
			 error+=pow( (tem_new[i][j] - tem_old),2.0 );
		}
	}
	error=sqrt(error/81);
	 printf("Iteration = %d \t Error= %lf \n", iteration, error);
    iteration++;
	}while (error> 1e-8);
	
	
		for(i = 0; i < m; i++)
	{
		for(j = 0; j < n; j++)
		{
			
			printf("%lf ",tem_new[i][j]);
		}
		printf("\n");
	}
	
	FILE *file2;
        file2=fopen("Temprature.plt","w");
        fprintf(file2, "Variables= \"X\",\"Y\",\"PHI\"\n");
        fprintf(file2, "zone T= \"BLOCK1\", I=11, J=11, F=Point\n\n");
        
        for(i=0;i<m;i++)
        {
            for(j=0;j<n;j++)
            {

                fprintf(file2, "%lf \t %lf \t %lf \n", (i)*0.1, (j)*0.1, tem_new[j][i]);
            }
            
        }
	fclose(file2);
	
	return 0;
}
