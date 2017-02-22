#include <iostream>
#include <string>
#include <fstream>
using namespace std;


int** create_int_grid(int, int);
char** create_char_grid(int, int);
string** create_string_grid(int);
void free_int_grid(int, int, int**);
void free_char_grid(int, int, char**);
void free_string_grid(int, string**);
void print_int_grid(int, int, int**);
void print_char_grid(int, int, char**);
void print_string_grid(int, string**);
int find_cost(char,char,int**);
int find_test_cost(char,char,int**);
int minimum(int,int,int);
int diff(char,char,int**);
int** fill_in_edit_distance_table(string , string , int**, char**, int,int, int**);
int** fill_test_in_edit_distance_table(string , string , int**, char**, int,int, int**);

int main(int argc, char** argv) {
	string cost_file;
	string input_file;
	string sequence;
	char ch;
	int number;
	fstream f;

	int** cost_table = create_int_grid(5, 5);
	string** sequence_table;

	int count = 0;
	int row = 0;
	int column = 0;
	int i = 0;
	int j = 0;
	
	// if files were provided, use them. Otherwise, use the default cost and
	// input files given to us.
	if (argc > 1) {
		cost_file = argv[1];
		input_file = argv[2];
	}
	else {
		cost_file = "imp2cost.txt";
		input_file = "imp2input.txt";
	}

	// read the cost file and populate a 5x5 cost table of just the ints:
	f.open(cost_file.c_str());
	ch = f.peek();								// peek at first char
	while (ch != EOF) {
		if (isdigit(ch)) {						// if char starts a number,
			f >> number;						// read entire number
			cost_table[row][column] = number;			// place in int grid
			column++;						// move on to next square
			if (column >= 5) {					// if end of row,
				column = 0;	
				row++;						// move on to next row
			}
		}
		else {
			ch = f.get();						// otherwise: ignore char
		}
		ch = f.peek();							// peek at next char
	}

	f.close();
	
	/* The following proves that the cost file has successfully been converted
	 * to a 5x5 int array. Try changing a value in the cost file to be a
	 * double-digit number-- the entire number should appear in the correct
	 * cell of the int array.
	 */
	cout << "PRINTING THE COST TABLE" << endl;
	//print_int_grid(5, 5, cost_table);
	cout << "DONE PRINTING THE COST TABLE" << endl;

	// read the input file and populate a ``num_pairs`` x 2 table of just the
	// strings:
	f.open(input_file.c_str());
	getline(f, sequence);
	while (f) {
		count++;
		getline(f, sequence);
	}
	f.close();

	sequence_table = create_string_grid(count);

	f.open(input_file.c_str());
	getline(f, sequence, ',');
	while (f) {
		sequence_table[i][j] = sequence;
		j++;
		if (j == 1) { 
			getline(f, sequence, '\n');
		}
		else if (j >= 2) {
			j = 0;
			i++;
			getline(f, sequence, ',');
		}
	}
	f.close();

	/* the following proves that the input file was successfully converted to
	 * a num_pairs x 2 array of just strings. Commas are printed out for
	 * readability.
	 */
	//cout << "PRINTIN:G THE SEQ TABLE " << endl;	
	//print_string_grid(count, sequence_table);
	//cout << "DONE PRINTING THE SEQ TABLE" << endl;
	
	//test for the editingDistance function	
	string str2 = "polynomial";
	string str1 = "exponential";
	int **cost_test = create_int_grid(12,12);
	for(int i = 0; i < 12; i++){
		for(int j = 0; j < 12; j++){
			if( i == j){
				cost_test[i][j] = 0;
			}
			else{
			
				cost_test[i][j] = 1;
			} 
			cout <<"	" << i << "]" << "[" << j  << ":" << cost_test[i][j];
			
		}
		cout << "\n";
	}	
	int ** ed_table = create_int_grid(str1.length()+1 , str2.length()+1 );
	int ** test ;
	char ** bt_table = create_char_grid(str1.length()+1, str2.length()+1);
	
	
	test = fill_test_in_edit_distance_table(str1, str2, cost_test, bt_table, str1.length()+1,  str2.length()+1, ed_table);
	//print_char_grid(str1.length()+1, str2.length()+1, bt_table);	
	cout << endl << endl;	
	print_int_grid(str1.length()+1, str2.length()+1, test);	
	
	//free the dynamic menmory
	free_int_grid(str1.length()+1,str2.length()+1, ed_table);
	free_char_grid(str1.length()+1, str2.length()+1, bt_table);
	free_int_grid(5, 5, cost_table);
	free_string_grid(count, sequence_table);
	
	return 0;
}


/* Creates and returns dynamic mxn array of ints */
int** create_int_grid(int m, int n) {
	int** array = new int* [m];
	for (int i = 0; i < m; i++) {
		array[i] = new int[n];
	}
	return array;
}


/* Creates and returns dynamic mxn array of chars */
char** create_char_grid(int m, int n) {
	char** array = new char* [m];
	for (int i = 0; i < m; i++) {
		array[i] = new char[n];
	}
	return array;
}


/* Creates and returns dynamic ``num_pairs``x2 array of strings */
string** create_string_grid(int num_pairs) {
	string** array = new string* [num_pairs];
	for (int i = 0; i < num_pairs; i++) {
		array[i] = new string[2];
	}
	return array;
}


/* Frees given mxn array of ints */
void free_int_grid(int m, int n, int** arr) {
	for (int i = 0; i < m; i++) {
		delete [] arr[i];
	}
	delete [] arr;
}


/* Frees given mxn array of chars */
void free_char_grid(int m, int n, char** arr) {
	for (int i = 0; i < m; i++) {
		delete [] arr[i];
	}
	delete [] arr;
}


/* Frees given ``num_pairs``x2 array of strings */
void free_string_grid(int num_pairs, string** arr) {
	for (int i = 0; i < num_pairs; i++) {
		delete [] arr[i];
	}
	delete [] arr;
}


/* Prints given mxn array of ints */
void print_int_grid(int m, int n, int** arr) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << arr[i][j] << "	";
		}
		cout << endl;
	}
}


/* Prints given mxn array of chars */
void print_char_grid(int m, int n, char** arr) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << arr[i][j];
		}
		cout << endl;
	}
}


/* Prints given ``num_pairs``x2 array of strings, with commas separating the
 * first sequence of a pair from the second sequence of a pair */
void print_string_grid(int num_pairs, string** arr) {
	for (int i = 0; i < num_pairs; i++) {
		for (int j = 0; j < 2; j++) {
			cout << arr[i][j];
			if (j == 0) {
				cout << ',';
			}
		}
		cout << endl;
	}
}

int find_test_cost(char one, char two, int** cost_table){
	int idx1 = 0, idx2 = 0;
	string alpha = "-alimtnoeypx";
	cout << " char one " << one << "	" << "char two " << two << endl;
	for(int i = 0; i < 12; i++){
		if(one == alpha[i]){
			idx1 = i;
			//cout << " index <<"<<i<<"<< : " << idx1 << endl;
		}
		if(two == alpha[i]){
			idx2 = i;
			//cout << " index <<"<<i<<"<< : " << idx2 << endl;
		}
	}
	
	return cost_table[idx1][idx2];
}

int find_cost(char one, char two, int** cost_table){
	int idx1 = 0, idx2 = 0;
	string alpha = "-ATGC";
	cout << " char one " << one << "	" << "char two " << two << endl;
	for(int i = 0; i < 5; i++){
		if(one == alpha[i]){
			idx1 = i;
			//cout << " index 1 : " << idx1 << endl;
		}
		if(two == alpha[i]){
			idx2 = i;
			//cout << " index 2 : " << idx2 << endl;
		}
	}
	
	return cost_table[idx1][idx2];
}

int minimum(int i, int j, int k){
	return min(min(i,j),k);
}

int diff(char a, char b, int** cost_table){
	if(a != b){
		return find_cost(a,b,cost_table);
	} 
	else return 0 ;
}

int **fill_test_in_edit_distance_table(string str1, string str2, int **cost_table, char **bt_table, int m, int n, int** ed_table){ 
	//base cases:
	//print_int_grid(12,12,cost_table);
	int cost_i = 0, cost_d = 0, cost_a = 0;
	ed_table[0][0] = 0;
	for (int i = 1; i < m; i++){
		cout << " i " << i << endl;
		//cout << " find " << find_test_cost(str1[i],'-',cost_table) << endl;
		ed_table[i][0] = i * find_test_cost(str1[i-1], '-', cost_table);
		//cout << " ed_table [" << i << "]" << "[" << 0 << "]" << ": " << ed_table[i][0] << endl;
		bt_table[i][0] = 'd';

	} //(deletions)
	
	for(int j = 1; j < n; j++){
		ed_table[0][j] = j * find_test_cost('-', str2[j-1], cost_table);
		//cout << " ed_table [" <<0 << "]" << "[" << j << "]" << ": " << ed_table[0][j] << endl;
		bt_table[0][j] = 'i';

	
	}// (insertions)
	
	//main algorithm:
	for (int i = 1; i < m; i++){
		for (int j = 1; j < n; j++){
			//Find the costs of deletion, insertion, and alignment for this particular pair of characters, str1[i] and str2[j]:		

			cost_d = find_test_cost(str1[i], '-', cost_table);
			cost_i = find_test_cost('-', str2[j], cost_table);
			cost_a = find_test_cost(str1[i], str2[j], cost_table);
			//cout << " cost_d, cost_i, cost_a : " << cost_d << cost_i << cost_a << endl;
			//Choose best edit distance for pair:
			ed_table[i][j] = minimum(ed_table[i-1][j] + cost_d , ed_table[i][j-1] + cost_i , ed_table[i-1][j-1] + cost_a);

			//Record operation for backtrace:
			if (ed_table[i][j] == ed_table[i-1][j] + cost_d){
				bt_table[i][j] = 'd';
			}
			else if (ed_table[i][j] == ed_table[i][j-1] + cost_i){
				bt_table[i][j] = 'i';	
			}
			else{	// (alignment/substitution/diagonal)
				bt_table[i][j] = 'a';
			}
			//cout << " ed_table [" << i << "]" << "[" << j << "]" << ": " << ed_table[i][j] << endl;
				

		}
	}
	//return ed_table, the entire edit distance table. Best edit distance is ed_table[m][n];
	return ed_table;

}
int **fill_in_edit_distance_table(string str1, string str2, int **cost_table, char **bt_table, int m, int n, int** ed_table){ 
	//base cases:
	int cost_i = 0, cost_d = 0, cost_a = 0;
	for (int i = 0; i < m; i++){
		ed_table[i][0] = i * find_cost(str1[i], '-', cost_table);
		cout << " ed_table [" << i << "]" << "[" << 0 << "]" << ": " << ed_table[i][0] << endl;
		bt_table[i][0] = 'd';

	} //(deletions)
	
	for(int j = 1; j < n; j++){
		ed_table[0][j] = j * find_cost('-', str2[j], cost_table);
		cout << " ed_table [" <<0 << "]" << "[" << j << "]" << ": " << ed_table[0][j] << endl;
		bt_table[0][j] = 'i';

	
	}// (insertions)
	
	//main algorithm:
	for (int i = 1; i < m; i++){
		for (int j = 1; j < n; j++){
			//Find the costs of deletion, insertion, and alignment for this particular pair of characters, str1[i] and str2[j]:		

			cost_d = find_cost(str1[i], '-', cost_table);
			cost_i = find_cost('-', str2[j], cost_table);
			cost_a = find_cost(str1[i], str2[j], cost_table);
			//cout << " cost_d, cost_i, cost_a : " << cost_d << cost_i << cost_a << endl;
			//Choose best edit distance for pair:
			ed_table[i][j] = minimum(ed_table[i-1][j] + cost_d , ed_table[i][j-1] + cost_i , ed_table[i-1][j-1] + cost_a);

			//Record operation for backtrace:
			if (ed_table[i][j] == ed_table[i-1][j] + cost_d){
				bt_table[i][j] = 'd';
			}
			else if (ed_table[i][j] == ed_table[i][j-1] + cost_i){
				bt_table[i][j] = 'i';	
			}
			else{	// (alignment/substitution/diagonal)
				bt_table[i][j] = 'a';
			}
			cout << " ed_table [" << i << "]" << "[" << j << "]" << ": " << ed_table[i][j] << endl;
				

		}
	}
	//return ed_table, the entire edit distance table. Best edit distance is ed_table[m][n];
	return ed_table;

}

