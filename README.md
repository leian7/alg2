CS 325 Implementation Assignment 2

Yingshi Huang && Anne Lei

To compile and run the program:
g++ -o [executable name] edit_distance.cpp
./[executable name]

If you want to use a cost file and input file other than imp2cost.txt and
imp2input.txt (see last paragraph for info on timing), you can provide
alternate files like this:
./[executable name] [name of cost file] [name of input file]

Execution will output results to imp2output.txt; if it does not exist
beforehand, it will be generated. A file of this name is included here
regardless; feel free to delete.

For best results, the cost file should be set up so that identical pairs of
characters have an alignment cost of 0 (i.e. the diagonal of the cost matrix
should be all 0s).

To generate random sequences (for timing):
``python3 generate_random.py``
This creates (or overwrites, if they were created and written to previously)
five files in the current directory, rand_500.txt, rand_1000, etc., where
rand_500.txt has 10 pairs of 500-character-long randomized sequences,
rand_1000.txt has 10 pairs of 1000-character-long randomized sequences, etc.

To see the timing in action, uncomment the relevant code (a copy is found in
our report document) to print out times to stdout. Times from our own runs are
also documented in our report.
