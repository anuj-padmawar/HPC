#include <iostream>
#include <stdlib.h>
#include <omp.h>
#define max 1000

using namespace std;


class Matrix{

private:
	long int rows,cols,vsize;
	long int mat[max][max];
	long int vec[max];

public:
	Matrix(){
		for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			mat[i][j]=0;
			}
		}
		}
	void accept();
	void display();
	void svecmultiply();
	void pvecmultiply();
};


void Matrix::accept(){

	cout<<"Enter the total number of rows:";
	cin>>rows;
	cout<<"\nEnter the total number of columns:";
	cin>>cols;
	cout<<endl;
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			mat[i][j]=rand()%100;
			}
		}
		cout<<endl;
	cout<<"Enter the size of the vector:"<<endl;
	cin>>vsize;
	for(int i=0;i<vsize;i++){
			vec[i]=rand()%100;	
		}	
}


void Matrix::display()
{
	cout<<"Matrix is :-"<<endl;
		for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			cout<<"\t"<<mat[i][j];
			}
		cout<<endl;
		}
	cout<<"Vector is:-"<<endl;
	for(int i=0;i<vsize;i++){
			cout<<"\t"<<vec[i];	
		}	
	cout<<endl;
}

void Matrix::svecmultiply(){
	long int result[max];
	if(cols==vsize){	
	for(int i=0;i<vsize;i++){
		result[i]=0;		
		}
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			result[i]+=mat[i][j]*vec[i];			
			}
		}
cout<<"Result is :-"<<endl;
	for(int i=0;i<vsize;i++){
	cout<<result[i]<<" "<<endl;		
	}
	}
	else{
	cout<<"Not Possible to multiply the matrix."<<endl;		
	}

}

void Matrix::pvecmultiply(){
	long int result[max];
	if(cols==vsize){
	for(int i=0;i<vsize;i++){
		result[i]=0;		
		}
	#pragma omp parallel for
	for(int i=0;i<rows;i++){
				
	for(int j=0;j<cols;j++){
			result[i]+=mat[i][j]*vec[i];			
			}
		}
cout<<"Result is :-"<<endl;
	for(int i=0;i<vsize;i++){
	cout<<result[i]<<" "<<endl;		
	}
	}
	else{
		cout<<"Not Possible to multiply the matrix."<<endl;		
		}
}

int main(){
	double stime1=0,stime2=0,stime=0,ptime1=0,ptime2=0,ptime=0,speedup=0,eff=0;	
	Matrix v;
	v.accept();
	v.display();
	stime1=omp_get_wtime();
	v.svecmultiply();
	stime2=omp_get_wtime();
	stime=stime2-stime1;	
	ptime1=omp_get_wtime();
	v.pvecmultiply();
	ptime2=omp_get_wtime();
	ptime=ptime2-ptime1;
	speedup=(stime/ptime);
	eff=speedup/omp_get_num_procs();
	cout<<"Before Sequential Matrix-Vector Multiplication time:"<<stime1<<" s."<<endl;	
	cout<<"After Sequential Matrix-Vector Multiplication time:"<<stime2<<" s."<<endl;
	cout<<"Total Sequential Matrix-Vector Multiplication time:"<<stime<<" s."<<endl;
	cout<<"Before Parallel Matrix-Vector Multiplication time:"<<ptime1<<" s."<<endl;
	cout<<"After Parallel Matrix-Vector Multiplication time:"<<ptime2<<" s."<<endl;
	cout<<"Total Parallel Matrix-Vector Multiplication time:"<<ptime<<" s."<<endl;
	cout<<"Speedup:"<<speedup<<" units."<<endl;
	cout<<"Efficiency:"<<eff<<" units."<<endl;
	return 0;
}

