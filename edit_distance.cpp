#include <iostream>
#include <string>
#include <string.h>
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
string* get_alignment(string, string, int**, char**);


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
	
	/* The following proves that the cost file has successfully been converted
	 * to a 5x5 int array. Try changing a value in the cost file to be a
	 * double-digit number-- the entire number should appear in the correct
	 * cell of the int array.
	 */
	cout << "PRINTING THE COST TABLE" << endl;
	print_int_grid(5, 5, cost_table);
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

	//cout << "PRINTING THE SEQ TABLE " << endl;	
	//print_string_grid(count, sequence_table);
	//cout << "DONE PRINTING THE SEQ TABLE" << endl;
	
	int cost = find_cost('G', '-', cost_table);
	cout << "Finding cost in table : " << cost << endl;

	/* DELETE LATER: read in dummy ed_table for testing */
	row = 0; column = 0;
	int** ed_table = create_int_grid(11+1, 10+1);
	f.open("test_ed_table.txt");
	ch = f.peek();								// peek at first char
	while (ch != EOF) {
		if (isdigit(ch)) {						// if char starts a number,
			f >> number;						// read entire number
			ed_table[row][column] = number;		// place in int grid
			column++;							// move on to next square
			if (column >= 11) {					// if end of row,
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

	print_int_grid(11+1, 10+1, ed_table);

	/* DELETE LATER: read in dummy bt_table for testing */
	row = 0; column = 0;
	char** bt_table = create_char_grid(11+1, 10+1);
	f.open("test_bt_table.txt");
	ch = f.get();								// peek at first char
	while (ch != EOF) {
		if (ch != ' ' && ch != '\n') {			// if char starts a number,
			bt_table[row][column] = ch;			// place in int grid
			column++;							// move on to next square
			if (column >= 11) {					// if end of row,
				column = 0;
				row++;							// move on to next row
			}
		}
		ch = f.get();							// peek at next char
	}
	f.close();

	print_char_grid(11+1, 10+1, bt_table);

	/* DELETE LATER: testing that get_alignment works with the dummy data */
	string* alignment;
	alignment = get_alignment("exponential", "polynomial", ed_table, bt_table);
	for (int i = 0; i < 2; i++) {
		cout << alignment[i] << endl;
	}

	free_int_grid(5, 5, cost_table);
	free_string_grid(count, sequence_table);
	free_int_grid(11+1, 10+1, ed_table);
	free_char_grid(11+1, 10+1, bt_table);
	delete [] alignment;
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
			cout << arr[i][j];
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
string* get_alignment(string str1, string str2, int** ed_table, char** bt_table) {
	string* alignment = new string[2]; 			// hold the final two strings
	string align1 = "";
	string align2 = "";
	int i = str1.length();						// first cell: bottom right
	int j = str2.length();
	int old1 = str1.length() - 1;				// first pair: ending chars
	int old2 = str2.length() - 1;

	for (int x = 0; x < str1.length() + str2.length(); x++) {
		cout << "examining " << i << ", " << j << ": " << bt_table[i][j] << endl;
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
		cout << "align1 is now " << align1 << endl;
		cout << "align2 is now " << align2 << endl;
		if (i == 0 && j == 0) {
			break;
		}
	}
	alignment[0] = align1;
	alignment[1] = align2;

	return alignment;
}
