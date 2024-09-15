#include<stdio.h>
#include<stdlib.h>
#include<math.h>
 
 int main (){
 	int m=11;
 	int n=11;
 	int o;
 
    double error;
 	double tem_old[m][n];
 	double tem_new[m][n];
 
 	int i,j ;
 		double ome=1.01;
 	double dy=0.1;
 	double dx=0.1;
 	double aw,ap,ae,as,an;
 	aw=1.0/pow(dx,2);
 	ap=-2.0*(pow(1/dx,2)+pow(1/dy,2));
 	ae=1.0/pow(dx,2);
 	as=1.0/pow(dy,2);
 	an=1.0/pow(dy,2);
 	 	
 	 for(i=0; i<m; i++)
 	 {
 	 	for(j=0;j<n;j++)
 	 	{
		  if(i==0)//left boundary
		 {
		   tem_new[i][j]=1.0;	 	
		  }
		  else if(j==0)//top b
		  {
		  	tem_new[i][j]=1.0;
	      }
	      else if(i==10)//bottom b
	      {
	      	tem_new[i][j]=1.0;
		  }
		  else if(j==10)
		  {
		  	tem_new[i][j]=0.0;
		  }
		  else
		  {
		  	tem_new[i][j]=0.0;
		  }
		  
		  }		  
	  }
	  
	  	for(j=0;j<n;j++)
	  	{
	  		for(i=0;i<m;i++)
	  		{
	  			printf("%lf ",tem_new[i][j]);//psi_old[m][n]=psi_new[m][n];
	  		}
	  		printf("\n");
	    }
	
	  
	  int iteration =0;
	  error=1.0;
	  FILE*file1;
	  file1=fopen("error_p2_psor.txt","w");
  for(o=1;o<99;o++)
	   {
	   		iteration=0;
	   		error= 1.0;
	   	//	printf("error=%lf\n ",error);
	   	
	   
	   		ome=ome+0.01;
	   	for(j=1;j<n-1;j++)
	  	{
	  		for(i=1;i<m-1;i++)
	  		{
	  		tem_new[i][j]=0.0;
	  		}
	  	
	    }
	 while(error>1e-6)
	  {
	  	for(i=0;i<m;i++)
	  	{
	  		for(j=0;j<n;j++)
	  		{
	  			tem_old[i][j]=tem_new[i][j];
	  		}
	    }
	    for(i=1;i<(m-1);i++)
	  	{
	  		for(j=1;j<(n-1);j++)
	  		{
	  		tem_new[i][j]= (1-ome)*tem_old[i][j]+(ome*1.0/ap)*(-as*tem_new[i][j-1]-aw*tem_new[i-1][j]-ae*tem_old[i+1][j]-an*tem_old[i][j+1]);
	  			//psi_new[i][j]=(psi_old[i][j-1]+psi_old[i-1][j]+psi_old[i+1][j]+psi_old[i][j+1])/4;
			  }
		  }
		
		    for(j=0;j<n;j++)
		  {
		  	tem_new[m-1][j]=tem_new[m-2][j];
		  }
		  
			   error=0.0;
	  	for(i=0;i<m;i++)
	  	{
	  		for(j=0;j<n;j++)
	  		{
	  			error=error + pow(tem_new[i][j]-tem_old[i][j],2.0);
	  			
            }
        }

           
		    error=sqrt(error/m*n);
            
           // printf("iteration %d\t",iteration);
			///printf("Error %lf\n",error);
			fprintf(file1,"%d\t%lf\n",iteration,error);
			iteration++;
		}
		printf("\niteration=%d\t w=%lf\n",iteration,ome );
}
		fclose(file1);
		
		
		for(i=0;i<m;i++)
	  	{
	  		for(j=0;j<n;j++)
	  		{
	  			printf("%lf ",tem_new[i][j]);
	  		}
	  		printf("\n");
	    }
	    
		FILE*file2;
		file2=fopen("stream_p2_psor.plt","w");
		fprintf(file2,"VARIABLES=\"X\", \"Y\",\"PHI\"\n");
		fprintf(file2,"ZONE T=\"BLOCK1\",I=11, J=11,F=POINT\n\n");
		 	for(j=0;j<n;j++)
	  	{
	  		for(i=0;i<m;i++)
	  		{
	  			fprintf(file2, "%lf \t %lf \t %lf \n",i*dx,j*dy,tem_new[i][j]);
	  		}
	    }
}



