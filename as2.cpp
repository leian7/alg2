#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

int minimum(int i, int j, int k){
	return min(min(i,j),k);
}


int diff(char a, char b){
	if(a == b) return 1;
	else return 0 ;
}

int EditingDistance(string One, string Two, int m, int n){
	int dis[m+1][n+1];
	for(int i = 0; i < m+1; i++){
		//cout << "In the outer for loop\n";
		for(int j = 0; j < n+1; j++){
			//cout << "In the inner for loop\n";
			if(i == 0){
				dis[i][j] = j;
			}
			else if(j == 0){
				dis[i][j] = i;
			}
			else if(One[i-1] == Two[j-1]){
				dis[i][j] = dis[i-1][j-1];
			}
			else{
				dis[i][j] =( 1 + minimum(dis[i][j-1], dis[i-1][j], dis[i-1][j-1]) );
			}
			cout << "["<<i<<"]["<<j<<"]" << dis[i][j] << "  " ;
		}
		cout << endl;
	}
	//cout << "dis[i][j]" <<  dis[m][n] << endl;
	return dis[m][n];
}


int main (){

	string two = "polynomial";
	string one = "exponential";
	
	char **values = new char*[6];
	for(int i =0; i<6; i++){
		values[i] = new char[6];
	}

	ifstream f;
	f.open("imp2cost.txt");
	for(int row = 0; row < 6; row++){
		for(int column = 0; column < 6; column++){
			f >> values[row][column];
			if(values[row][column] == ','){
				f >> values[row][column];
			}
			cout << values[row][column] << " " ;

		}
		cout << endl;
	}
	f.close();

	int sizeOne = 0 , sizeTwo = 0, size = 0;
	char random;
	ifstream second;
	second.open("input.txt");
	while(!second.eof()){
		second >> random;
		size++;
		if(random == ','){
			sizeOne = size-1;
			cout << " size one : " << sizeOne << endl;
		}

		cout  << random;

	}
	sizeTwo = size - 2 - sizeOne;
	cout << endl;	

	second.close();
	cout << endl;
	cout << EditingDistance(one, two,  sizeTwo, sizeOne) << endl;
	
	return 0;
}
