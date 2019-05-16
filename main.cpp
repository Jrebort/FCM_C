#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

float vector_new[12]={0.73,0.67,0.7,0.73,0.73,0.67,0.7,0.63,0.63,0.63,0.67,0.6};
float Graph[12][12]={
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0},
	{0.66,0,0.5,0,0,0,0,0,0,0,0,0},
	{0.74,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0.44,0,0.96,0,0,0,0,0,0,0},
	{0.36,0,0.4,0,0,0.54,0,0,0,0,0,0},
	{0,0.48,0,0,0,0,0,0,0,0,0,0},
	{0.42,0.56,0,0,0,0.5,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0.3,0.58,0,0,0},
	{0,0.74,0.78,0.54,0,0.88,0.5,0,0,0,0,0.42},
	{0.42,0.66,0.78,0,0,0,0.58,0,0.84,0,0,0},
};
//test code
//int main(){
//	cout << Graph[10][11]	<<endl;
//}

float vector_old[12]={0};

float sigmoid(float x)
{	
    return (1 / (1 + exp(-x)));
}

float FCMfun(int i)
{	
	float result; // The value of activation
	for(int j=0;j<=12;j++) //FCM function
	{	
		result += Graph[i][j]*vector_new[j];
	}
	result = sigmoid(result+vector_old[i]);
	return result;
}

void wipe_file() //empty content of file
{	
	ofstream output;
	output.open("./FCM_result.csv",ios::trunc);
	output.close();
}

void write_csv(float *file) // write string in .csv file
{	
	string str;
	ofstream outfile;
	outfile.open("./FCM_result.csv",ios::app);
	outfile << ' '<<endl;
	for(int i=0;i<12;i++)
	{
		str = to_string(file[i]);
		outfile << str+',';
	}
	outfile.close();
}

int main()
{
	int epoch=0;
	float Maxerror=1;
	float error[12];
	string ss;
//	test code
	float result;
//	result = sigmoid();
//	cout << result << endl;
	wipe_file();
	while(Maxerror > 0.000001) //Max(error) < 0.000001 condition
	{	
		write_csv(vector_new);
		for(int n=0;n<=12;n++)
		{	
			vector_old[n] = vector_new[n];	
		}
		for(int i=0;i<=12;i++)
		{	
			result = FCMfun(i);
			vector_new[i] = result;
			error[i] = vector_new[i] - vector_old[i];
		}
		Maxerror=*max_element(error,error+12); 
		epoch++;
		ss = '\n';
		//write_csv(ss);
		cout << Maxerror <<endl;
	}

	return 0;
}
