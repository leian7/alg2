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

int EditingDistance(char One[], char Two[], int i, int j){
	int dis[i][j];
	for(int m = 0; m < i; m++){
		for(int n = 0; n < j; n++){
			if(m == 0){
				dis[m][n] = n;
			}
			else if(n == 0){
				dis[m][n] = m;
			}
			else if(One[m-1] == Two[n-1]){
				dis[m][n] = dis[m-1][n-1];
			}
			else{
				dis[m][n] =( 1 + minimum(dis[m][n-1], dis[m-1][n], dis[m-1][n-1]) );
			}
			cout << "["<<m<<"]["<<n<<"]" << dis[m][n] << "  " ;
		}
		cout << endl;
	}
	cout << "dis[i][j]" <<  dis[i-1][j-1] << endl;
	return dis[i-1][j-1];
}


int main (){

	char set[]    = {'p','o','l','y','n','o','m','i','a','l'};
	char setTwo[] = {'e','x','p','o','n','e','n','t','i','a','l'};
	/*int size = sizeof(set)/sizeof(char);
	  int sizeS = sizeof(setTwo)/sizeof(char);

	  cout << " this is size " << size << endl;
	  for(int i = 0; i < size; i++){
	  cout << set[i] << endl;
	//cout << setTwo[i] << endl;
	}
	for(int i = 0; i < sizeS; i++){
	//cout << set[i] << endl;
	cout << setTwo[i] << endl;
	}
	*/

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
			//cout << values[row][column] << " " ;

		}
		//cout << endl;
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

			break;
		}

		cout  << random;

	}
	sizeTwo = size - 2 - sizeOne;
	cout << endl;	
	cout << size << " " << sizeTwo <<" " << sizeOne;

	second.close();
	cout << endl;
	cout << "size" <<  size << endl;
	cout << EditingDistance(set,setTwo,10,11) << endl;
	
	return 0;
}
