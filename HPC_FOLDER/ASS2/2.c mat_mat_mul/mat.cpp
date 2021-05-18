#include <iostream>
#include <stdlib.h>
#include <omp.h>
#define max 100

using namespace std;


class Matrix{

private:
	long int rows,cols;
	long int mat[max][max];

public:
	void accept();
	void display();
	void smultiply(Matrix);
	void pmultiply(Matrix);
};


void Matrix::accept(){					//function accepting input from the user

	cout<<"Enter the total number of rows:";
	cin>>rows;
	cout<<"\nEnter the total number of columns:";
	cin>>cols;
	cout<<endl;
	//mat= new long int[max][max];
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			mat[i][j]=rand()%100;
			}
		cout<<endl;
		}	
}


void Matrix::display()				//displaying the out put of the matrix
{
	cout<<"Matrix is :-"<<endl;
		for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			cout<<"\t"<<mat[i][j];
			}
		cout<<endl;
		}	

}

void Matrix::smultiply(Matrix m1){	//matrix matrix multiplication sequentially
	Matrix m2;				
	if(cols=m1.rows){		//checking condition in first matrix column is equal to second matrix row
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++){
				m2.mat[i][j]=0;
					for(int k=0;k<rows;k++){
						m2.mat[i][j]+=mat[i][k]*m1.mat[k][j];
						}
					}
				
		}
		}
	m2.rows=rows;
	m2.cols=cols;
	m2.display();
	
}

void Matrix::pmultiply(Matrix m1){			//matrix matrix multiplication parallelly
	Matrix m2;				
	if(cols=m1.rows){			//checking condition if first matrix column is equal to second matrix row
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++){
				m2.mat[i][j]=0;
				#pragma omp parallel for	
				for(int k=0;k<rows;k++){
						m2.mat[i][j]+=mat[i][k]*m1.mat[k][j];
						}
					}
				
		}
		}
	m2.rows=rows;
	m2.cols=cols;
	m2.display();
}


int main(){
	double stime1=0,stime2=0,stime=0,ptime1=0,ptime2=0,ptime=0,speedup=0,eff=0;	
	Matrix m,m1;
	m.accept();
	m.display();
	m1.accept();
	m1.display();
	stime1=omp_get_wtime();
	m.smultiply(m1);
	stime2=omp_get_wtime();
	stime=stime2-stime1;	
	ptime1=omp_get_wtime();
	m.pmultiply(m1);
	ptime2=omp_get_wtime();
	ptime=ptime2-ptime1;
	speedup=(stime/ptime);
	eff=speedup/omp_get_num_procs();
	cout<<"Before Sequential Matrix Multiplication time:"<<stime1<<" s."<<endl;	
	cout<<"After Sequential Matrix Multiplication time:"<<stime2<<" s."<<endl;
	cout<<"Total Sequential Matrix Multiplication time:"<<stime<<" s."<<endl;
	cout<<"Before Parallel Matrix Multiplication time:"<<ptime1<<" s."<<endl;
	cout<<"After Parallel Matrix Multiplication time:"<<ptime2<<" s."<<endl;
	cout<<"Total Parallel Matrix Multiplication time:"<<ptime<<" s."<<endl;
	cout<<"Speedup:"<<speedup<<" units."<<endl;
	cout<<"Efficiency:"<<eff<<" units."<<endl;
	return 0;
}

