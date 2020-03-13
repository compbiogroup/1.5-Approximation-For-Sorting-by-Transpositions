#include <iostream>
#include <getopt.h>
#include <sstream>
#include "include/hartman_shamir.h"
using namespace std;

#define N_POS_ARGS 0

struct Args {
	int size;
	char *pi;
	char *sigma;
};

void help(char *name) {

	cout <<
	"Usage:  Use Hartman and Shamir algorithm to find a 1.5 aproximation of the transposition distance between the provided sequences"
	<< endl <<
	"\t" << name << "[-h] [-n SIZE] [-p PI] [-s SIGMA]"
	<< endl << endl <<
	"optional arguments:"
	<< endl <<
	"\t-h, --help              show this help message and exit"
	<< endl <<
	"\t-n SIZE, --size SIZE    size of permutations"
	<< endl <<
	"\t-p PI, --pi PI          origin permutation (coma separeted list of positive integers)"
	<< endl <<
	"\t-s SIGMA, --sigma SIGMA target permutation (coma separeted list of positive integers)"
	<< endl;

	exit(EXIT_SUCCESS);
}

void get_args(Args &args, int argc, char *argv[]) {
	extern char *optarg;
	extern int optind;
	int n_pos_args = 0;

	struct option longopts[] = {
		{"size", 1, NULL, 'n'},
		{"pi", 1, NULL, 'p'},
		{"sigma", 1, NULL, 's'},
		{"help", 0, NULL, 'h'}
	};

	char op;
	while ((op = getopt_long(argc, argv, "n:p:s:h", longopts, NULL)) != -1) {
		switch (op) {
		case 'n':
			args.size = atoi(optarg);
			break;
		case 'p':
			args.pi = optarg;
			break;
		case 's':
			args.sigma = optarg;
			break;
		default:
			help(argv[0]);
		}
	}
	for (int i = optind; i < argc; i++) {
		n_pos_args++;
		optind++;
	}

	if(n_pos_args != N_POS_ARGS || args.size <= 0) {
		help(argv[0]);
	}
}

int main(int argc, char *argv[]) {
	int *pi,*sigma,i;
	string str;
	Args args;

	get_args(args,argc,argv);

	pi = (int *) malloc(args.size * sizeof(int));
	sigma = (int *) malloc(args.size * sizeof(int));
	stringstream ss1(args.pi);
	for (i = 0; getline(ss1,str,','); i++) {
		if(i >= args.size) {
        cerr << "ERROR: origin permutation longer than size" << endl;
				exit(EXIT_SUCCESS);
		}
		pi[i] = stoi(str);
	}
	if(i < args.size) {
			cerr << "ERROR: origin permutation shorter than size" << endl;
			exit(EXIT_SUCCESS);
	}
	stringstream ss2(args.sigma);
	for (i = 0; getline(ss2,str,','); i++) {
		if(i >= args.size) {
        cerr << "ERROR: target permutation longer than size" << endl;
			  exit(EXIT_SUCCESS);
		}
		sigma[i] = stoi(str);
	}
	if(i < args.size) {
			cerr << "ERROR: target permutation shorter than size" << endl;
			exit(EXIT_SUCCESS);
	}

	int dist = hs::hartman_shamir(pi,sigma,args.size);
	cout << dist << endl;

	return 0;
}
