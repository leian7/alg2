#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <iomanip>
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
int find_cost(char, char, int**);
string* get_alignment(string, string, int**, char**);
int find_test_cost(char, char, int**);
int minimum(int, int, int);
int diff(char, char, int**);
int** fill_in_edit_distance_table(string, string, int**, char**, int**);
int** fill_test_in_edit_distance_table(string, string, int**, char**, int, int,
									   int**);

int main(int argc, char** argv) {
	string cost_file;							// name of cost file
	string input_file;							// name of input file
	string sequence;
	char ch;									// for reading grids from files
	int number;									// for reading nums from files
	fstream f;

	int** cost_table = create_int_grid(5, 5);	// guaranteed size
	string** sequence_table;					// array ver. of input file

	int count = 0;								// input file's line/pair count
	int row = 0;								// grid indices
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
			cost_table[row][column] = number;	// place in int grid
			column++;							// move on to next square
			if (column >= 5) {					// if end of row,
				column = 0;	
				row++;							// move on to next row
			}
		}
		else {
			ch = f.get();						// otherwise: ignore char
		}
		ch = f.peek();							// peek at next char
	}

	f.close();

	print_int_grid(5, 5, cost_table);
	
	// read the input file and populate a ``num_pairs`` x 2 table of just the
	// strings:
	// first obtain number of lines/number of pairs of sequences...
	f.open(input_file.c_str());
	getline(f, sequence);
	while (f) {
		count++;
		getline(f, sequence);
	}
	f.close();

	sequence_table = create_string_grid(count);

	// ... then populate the sequence table with the sequences from the file:
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
/*	cout << "PRINTIN:G THE SEQ TABLE " << endl;	
	print_string_grid(count, sequence_table);
	cout << "DONE PRINTING THE SEQ TABLE" << endl;
	i = 0; j = 0; */

	cout <<	sequence_table[0][0] << endl;
	cout << sequence_table[0][1] << endl;

	cout << "len 1: " << sequence_table[0][0].length() << endl;
	cout << "len 2: " << sequence_table[0][1].length() << endl;

	cout << sequence_table[0][0][sequence_table[0][0].length()-1] << endl;
	cout << sequence_table[0][1][sequence_table[0][1].length()-1] << endl;
	// for each pair,
	for (int i = 0; i < 1; i++) { 
		int** ed_table = create_int_grid(sequence_table[i][0].length()+1,
										 sequence_table[i][1].length()+1);
		char** bt_table = create_char_grid(sequence_table[i][0].length()+1,
										   sequence_table[i][1].length()+1);
	
	
		ed_table = fill_in_edit_distance_table(sequence_table[i][0],
											   sequence_table[i][1],
											   cost_table, bt_table, ed_table);

		print_int_grid(sequence_table[i][0].length()+1,
					   sequence_table[i][1].length()+1, ed_table);

		string* alignment;
		alignment = get_alignment(sequence_table[i][0], sequence_table[i][1],
								  ed_table, bt_table);
		cout << alignment[0] << endl;
		cout << alignment[1] << ed_table[sequence_table[i][0].length()][sequence_table[i][1].length()] << endl;

		//free the dynamic memory
		free_int_grid(sequence_table[i][0].length()+1,
					  sequence_table[i][1].length()+1, ed_table);
		free_char_grid(sequence_table[i][0].length()+1,
					   sequence_table[i][1].length()+1, bt_table);
		delete [] alignment;
	}
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
			cout << setw(3) << arr[i][j];
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


/* Looks up cost for particular pair of characters from the cost table */
int find_test_cost(char one, char two, int** cost_table){
	int idx1 = 0, idx2 = 0;
	string alpha = "-xucetion";
//	cout << " char one " << one << "	" << "char two " << two << endl;
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
	for(int i = 0; i < 5; i++){
		if(one == alpha[i]){
			idx1 = i;
		}
		if(two == alpha[i]){
			idx2 = i;
		}
	}
	return cost_table[idx1][idx2];
}


/* Returns alignment (two new strings) between two original strings, based on
 * the completed edit distance table and the completed backtrace table */
string* get_alignment(string str1, string str2, int** ed_table,
					  char** bt_table) {
	string* alignment = new string[2]; 			// hold the final two strings
	string align1 = "";
	string align2 = "";
	int i = str1.length();						// first cell: bottom right
	int j = str2.length();
	int old1 = str1.length() - 1;				// first pair: ending chars
	int old2 = str2.length() - 1;

	for (int x = 0; x < str1.length() + str2.length(); x++) {
		if (bt_table[i][j] == 'd') {			// there was a deletion
			align1 = str1[old1] + align1;
			align2 = "-" + align2;
			old1--;
			i--;
		}
		else if (bt_table[i][j] == 'i') {		// there was an insertion
			align1 = "-" + align1;
			align2 = str2[old2] + align2;
			old2--;
			j--;
		}
		else {									// there was an alignment
			align1 = str1[old1] + align1;
			align2 = str2[old2] + align2;
			old1--; old2--;
			i--; j--;
		}
		if (i == 0 && j == 0) {
			break;
		}
	}
	alignment[0] = align1;
	alignment[1] = align2;

	return alignment;
}


int minimum(int i, int j, int k){
	return min(min(i,j),k);
}


int **fill_test_in_edit_distance_table(string str1, string str2, int **cost_table, char **bt_table, int m, int n, int** ed_table){ 
	//base cases:
	//print_int_grid(12,12,cost_table);
	int cost_i = 0, cost_d = 0, cost_a = 0;
	ed_table[0][0] = 0;
	for (int i = 1; i < m; i++){
		//cout << " find " << find_test_cost(str1[i],'-',cost_table) << endl;
		ed_table[i][0] = i * find_test_cost(str1[i-1], '-', cost_table);
		//cout << " ed_table [" << i << "]" << "[" << 0 << "]" << ": " << ed_table[i][0] << endl;
		bt_table[i][0] = 'd';
	}	// (deletions)
	
	for(int j = 1; j < n; j++){
		ed_table[0][j] = j * find_test_cost('-', str2[j-1], cost_table);
		//cout << " ed_table [" <<0 << "]" << "[" << j << "]" << ": " << ed_table[0][j] << endl;
		bt_table[0][j] = 'i';
	}	// (insertions)
	
	//main algorithm:
	for (int i = 1; i < m; i++){
		for (int j = 1; j < n; j++) {
			// Find the costs of deletion, insertion, and alignment for this
			// particular pair of characters, str1[i] and str2[j]:		
			cost_d = find_test_cost(str1[i-1], '-', cost_table);
			cost_i = find_test_cost('-', str2[j-1], cost_table);
			cost_a = find_test_cost(str1[i-1], str2[j-1], cost_table);

			// cout << " cost_d, cost_i, cost_a : " << cost_d << cost_i << cost_a << endl;
			// Choose best edit distance for pair:
			ed_table[i][j] = minimum(ed_table[i-1][j] + cost_d,
									 ed_table[i][j-1] + cost_i,
									 ed_table[i-1][j-1] + cost_a);

			// Record operation for backtrace:
			if (ed_table[i][j] == ed_table[i-1][j] + cost_d) {
				bt_table[i][j] = 'd';
			}
			else if (ed_table[i][j] == ed_table[i][j-1] + cost_i) {
				bt_table[i][j] = 'i';
			}
			else {		// (alignment/substitution/diagonal)
				bt_table[i][j] = 'a';
			}
			//cout << " ed_table [" << i << "]" << "[" << j << "]" << ": " << ed_table[i][j] << endl;
		}
	}
	// return ed_table, the entire edit distance table. Best edit distance is
	// ed_table[m][n];
	return ed_table;
}


int **fill_in_edit_distance_table(string str1, string str2, int **cost_table,
								  char **bt_table, int **ed_table) { 
	//base cases:
	int cost_i = 0, cost_d = 0, cost_a = 0;

	for (int i = 0; i < str1.length() + 1; i++) {
		if (i == 0) {
			ed_table[i][0] = 0;
		}
		else {
			ed_table[i][0] = i * find_cost(str1[i-1], '-', cost_table);
		}
		bt_table[i][0] = 'd';
	} 	// (deletions)
	
	for(int j = 1; j < str2.length() + 1; j++) {
		ed_table[0][j] = j * find_cost('-', str2[j-1], cost_table);
		bt_table[0][j] = 'i';
	}	// (insertions)
	
	//main algorithm (EXTRA CHECK THE i's AND j's???)
	for (int i = 1; i < str1.length() + 1; i++) {
		for (int j = 1; j < str2.length() + 1; j++) {
			// Find the costs of deletion, insertion, and alignment for this
			// particular pair of characters, str1[i] and str2[j]:
			cost_d = find_cost(str1[i-1], '-', cost_table);
			cost_i = find_cost('-', str2[j-1], cost_table);
			cost_a = find_cost(str1[i-1], str2[j-1], cost_table);
			// cout << " cost_d, cost_i, cost_a : " << cost_d << cost_i << cost_a << endl;
			// Choose best edit distance for pair:
			ed_table[i][j] = minimum(ed_table[i-1][j] + cost_d, ed_table[i][j-1] + cost_i, ed_table[i-1][j-1] + cost_a);

			//Record operation for backtrace:
			if (ed_table[i][j] == ed_table[i-1][j] + cost_d) {
				bt_table[i][j] = 'd';
			}
			else if (ed_table[i][j] == ed_table[i][j-1] + cost_i) {
				bt_table[i][j] = 'i';	
			}
			else {	// (alignment/substitution/diagonal)
				bt_table[i][j] = 'a';
			}
		}
	}
	// return ed_table, the entire edit distance table. Best edit distance is
	// ed_table[m][n];
	return ed_table;
}
