#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>

double exact_temprature(int, int, double, double, double, double );
int main()
{
   	int m = 11, n = 11; 
	int i,j, iteration;
	
	double dx, dy;
	dx = 0.1;
	dy = 0.1;
	double errori,errorj, error;
	double tc=0;
	double th=1;
	double l=1,h=1;
	
	double temp, temp_new[m][n],temp_old[m][n];
    double ai, bi, ci, di[m-2], pi[m-2],qi[m-2]; // for col sweep (i or y sweep)
    double aj, bj, cj, dj[n-2], pj[n-2],qj[n-2]; // for col sweep (j or x sweep)
        
    	for(i = 0; i < m; i++)
	{
		for(j = 0; j < n; j++)
		{
			if( i == (m-1) )
			{
				temp_new[i][j] = 0.0; //Top b
			}
			else if ( j == 0)
			{
				temp_new[i][j] = 1.0; //left b
			}
			else if ( i == 0)
			{
				temp_new[i][j] = 1.0; //bottom b
			}
			else if ( j == (n-1) )
			{
				temp_new[i][j] = 1.0;//right b
			}
			else
			{
				 temp_new[i][j] = 0.0; //interior p
			}
			
		}
	}
	
		for(i = 0; i < m; i++)
		{
			for(j = 0; j < n; j++)
			{
			
				printf("%lf ",temp_new[i][j]);
			}
			printf("\n");
		}
	 printf("\n initial conditon\n");
	 
  iteration=0;
  do{
  	errori=0;
  	error=0.0;
  	
  	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			temp_old[i][j] = temp_new[i][j];
		}
	}
  	
  	
  	// y sweep || i sweep
	for(j=1; j<n-1;j++)
	{
		ai=-4;
		bi=1;
		ci=1;
		di[0]=-1*(temp_new[0][j-1]+temp_new[0][j+1]);
		pi[0]=0.25;
		qi[0]=di[0]/ai;
		qi[m-1]=temp_new[m-1][j];
		pi[m-1]=0;
		
		
		for(i=1;i<m-1;i++)
		{
			di[i]=-1*(temp_new[i][j-1]+temp_new[i][j+1]);
			pi[i]=-bi/(ai-ci*pi[i-1]);
			qi[i]=(di[i]-ci*qi[i-1])/(ai+ci*pi[i-1]);
		}
		
		for(i=m-2;i>0;i--)
		{
			temp=temp_new[i][j];
			temp_new[i][j]=pi[i]*temp_new[i+1][j]+qi[i];
			 errori+=pow( (temp_new[i][j] - temp),2.0 );
			
		}
	}
	
	
	// x sweep || j sweep
	errorj=0;
	for(i=1; i<m-1;i++)
	{
		aj=-4;
		bj=1;
		cj=1;
		dj[0]=-1*(temp_new[i-1][0]+temp_new[i+1][0]);
		pj[0]=0.25;
		qj[0]=dj[0]/aj;
		qj[n-1]=temp_new[i][n-1];
		pj[n-1]=0;
		
		
		for(j=1;j<n-1;j++)
		{
			dj[j]=-1*(temp_new[i-1][j]+temp_new[i+1][j]);
			pj[j]=-bj/(aj-cj*pj[j-1]);
			qj[j]=(dj[j]-cj*qj[j-1])/(aj+cj*pj[j-1]);
		}
		
		for(j=n-2;j>0;j--)
		{
			temp=temp_new[i][j];
			temp_new[i][j]=pj[j]*temp_new[i][j+1]+qj[j];
			 errorj+=pow( (temp_new[i][j] - temp),2.0 );
		}
	}
	
	
	for(i=1;i<m-1;i++)
	{
		for(j=1;j<n-1;j++)
		{
			error+=pow( (temp_new[i][j] - temp_old[i][j]),2.0 );
			
		}
	}
	
	errori=sqrt(errori/81);
	errorj=sqrt(errorj/81);
	error=sqrt(error/81);
	 printf("Iteration = %d \t Errori= %lf \t Errorj= %lf \t Error= %lf \n", iteration, errori, errorj, error);
    //fprintf(fp,"It = %d \t E= %lf \n", iteration, error);
    iteration++;
    
	}while (error>1e-6);
	
	
	
	// printing the final result
		for(i = 0; i < m; i++)
		{
			for(j = 0; j < n; j++)
			{
			
				printf("%lf ",temp_new[i][j]);
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

                fprintf(file2, "%lf \t %lf \t %lf \n", (i)*0.1, (j)*0.1, temp_new[j][i]);
            }
            
        }
	
	double exact_temprature(int i, int j, double l, double h, double tc, double th )
	{
		double term,temprature;
		term=0;
		int n;
		for(n=0;n<1000;n++)
		{
			term =term+((1-pow(-1,n))/ (n*M_PI))*((sinh(n*M_PI*j*0.1/l)/sinh(n*M_PI*h/l)) * sin(n*M_PI*i*0.1/l) );
		}
		temprature=tc+(th-tc)*(1-2*term);
		
		return temprature;
	}
	return 0;
}

