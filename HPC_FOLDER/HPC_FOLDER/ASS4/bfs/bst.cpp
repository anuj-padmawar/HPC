#include<iostream>
#include<stdlib.h>
#include<omp.h>
using namespace std;

void binary(int *, int, int, int,int);

void binary(int *a, int low, int high, int key1,int key2)
{

	int mid;
	mid=(low+high)/2;
	int low1,low2,high1,high2,mid1,mid2,found=0,loc1=-1,loc2=-1;
	int low3,low4,high3,high4,mid3,mid4,f1=0,loc3=-1,loc4=-1;


	#pragma omp parallel sections
	{
	    #pragma omp section
    		{
			low1=low;
			high1=mid;

			while(low1<=high1)
			{

				if(!(key1>=a[low1] && key1<=a[high1]))
				{
					low1=low1+high1;
					continue;
				}

				mid1=(low1+high1)/2;

				if(key1==a[mid1])
				{
					found=1;
					loc1=mid1;
					low1=high1+1;
				}

				else if(key1>a[mid1])
				{

					low1=mid1+1;
				}

				else if(key1<a[mid1])
					high1=mid1-1;

			}
		}



    	    #pragma omp section
    		{
      			low2=mid+1;
			high2=high;
			while(low2<=high2)
			{

				if(!(key1>=a[low2] && key1<=a[high2]))
				{
					low2=low2+high2;
					continue;
				}

				cout<<"here2";
				mid2=(low2+high2)/2;

				if(key1==a[mid2])
				{

					found=1;
					loc1=mid2;
					low2=high2+1;
				}
				else if(key1>a[mid2])
				{

				low2=mid2+1;
				}
				else if(key1<a[mid2])
				high2=mid2-1;

			}


                 }
#pragma omp section
    		{
			low3=low;
			high3=mid;

			while(low3<=high3)
			{

				if(!(key2>=a[low3] && key2<=a[high3]))
				{
					low3=low3+high3;
					continue;
				}

				mid3=(low3+high3)/2;
				if(key2==a[mid3])
				{
					f1=1;
					loc2=mid3;
					low3=high3+1;
				}

				else if(key2>a[mid3])
				{

					low3=mid3+1;
				}

				else if(key2<a[mid3])
					high3=mid3-1;

			}
		}



    	    #pragma omp section
    		{
      			low4=mid+1;
			high4=high;
			while(low4<=high4)
			{

				if(!(key2>=a[low4] && key2<=a[high4]))
				{
					low4=low4+high4;
					continue;
				}

				cout<<"here2";
				mid4=(low4+high4)/2;

				if(key2==a[mid4])
				{

					f1=1;
					loc2=mid4;
					low4=high4+1;
				}
				else if(key2>a[mid4])
				{

				low4=mid4+1;
				}
				else if(key2<a[mid4])
				high4=mid4-1;

			}



}

	}

	//return loc1;
if(loc1==-1)
		cout<<"\n Key1 not found.";
	else
		cout<<"\n Key1 found"<<"\n";
		//cout<<"\n Key1 found at position=>"<<loc1+1<<"\n";

	if(loc2==-1)
		cout<<"\n key2 not found.";
	else
		cout<<"\n Key2 found."<<"\n";

}


int main()
{


	int *a,i,n,key1,key2;
//int loc1=0,loc2=0;
	cout<<"\n enter total no of elements=>";
	cin>>n;
	a=new int[n];

	cout<<"\n enter elements=>";
	for(i=0;i<n;i++)
	{
	  cin>>a[i];
        }

	cout<<"\n enter key1 to find=>";
	cin>>key1;

        cout<<"\n enter key2 to find=>";
	cin>>key2;

	binary(a,0,n-1,key1,key2);





	return 0;
}
