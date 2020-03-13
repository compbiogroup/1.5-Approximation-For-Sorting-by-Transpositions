#include <cstdlib>
#include <cstdio>
#include "perm.h"
#include "util.h"

namespace hs {
	struct perm {
			int *vet;
			int *inv_vet;
			bool valid_inv;
			int size;
			PermType type;
	};

	int length_perm(perm *pi) {return pi->size;}
	int get_perm(perm *pi, int i) {return pi->vet[i];}
	void set_perm(perm *pi, int i, int val) {pi->vet[i] = val; pi->valid_inv = false;}
	PermType type_of_perm(perm *pi) {return pi->type;}

	int get_perm_idx(perm *pi, int val) {
			int idx;

			if(!pi->valid_inv) {
					for(int i = 0; i < length_perm(pi); i++)
							pi->inv_vet[abs(get_perm(pi,i))] = i;
					pi->valid_inv = true;
			}
			idx = pi->inv_vet[abs(val)];
			if (pi->vet[idx] == val) {
					return idx;
			} else {
					return EMPTY;
			}
	}

	perm *create_perm(int size, PermType type) {
			perm *pi = (perm*) malloc(sizeof(perm));
			pi->vet = (int *) malloc(size * sizeof(int));
			pi->inv_vet = (int *) malloc(size * sizeof(int));
			pi->size = size;
			pi->type = type;
			pi->valid_inv = false;
			return pi;
	}

	perm *build_and_rename_perm(int *vet1, int *vet2, int n, PermType type) {
			perm *pi = (perm *) create_perm(n+2, type);
			int *labels = (int *) malloc((n+2) * sizeof(int));

			for(int i = 0; i < n; i++) {
					labels[abs(vet2[i])] = (vet2[i] < 0) ? -i-1 : i+1;
			}

			pi->vet[0] = 0;
			for(int i = 1; i <= n; i++) {
					pi->vet[i] = (vet1[i-1] < 0) ? - labels[abs(vet1[i-1])] : labels[abs(vet1[i-1])];
			}
			pi->vet[n+1] = n+1;

			free(labels);
			return pi;
	}

	perm *build_perm(int *vet, int n, PermType type) {
			perm *pi = (perm *) create_perm(n+2, type);
			pi->vet[0] = 0;
			for(int i = 1; i <= n; i++) {
					pi->vet[i] = vet[i-1];
			}
			pi->vet[n+1] = n+1;
			return pi;
	}

	void clear_perm(perm *pi) {
			free(pi->vet);
			free(pi->inv_vet);
			free(pi);
	}

	void print_perm(perm *pi) {
			print_vec(pi->vet, pi->size);
	}

	bool is_sorted(perm *pi) {
			for(int i = 1; i < pi->size; i++) {
					if(pi->vet[i-1] > pi->vet[i]) return false;
			}
			return true;
	}

	bool break_point(perm *pi, int x, int y) {
			switch(pi->type) {
			case Rev:
			case TransRev:
					return abs(pi->vet[y] - pi->vet[x]) != 1;
			case Trans:
			case SRev:
			case TransSRev:
					return pi->vet[y] - pi->vet[x] != 1;
			}
			return false;
	}

	void rev_(perm *pi, int i, int j, bool with_sign) {
			for(int k = 0; k < (j-i+1) / 2; k++) {
					SWAP(int, pi->vet[i+k], pi->vet[j-k]);
			}
			if(with_sign) {
					for(int k = i; k <= j; k++) {
							pi->vet[k] = - pi->vet[k];
					}
			}
	}

	void rev(perm *pi, int i, int j) {
			pi->valid_inv = false;
			switch(pi->type) {
			case Rev:
			case TransRev:
					rev_(pi, i, j, false);
					break;
			case SRev:
			case TransSRev:
					rev_(pi, i, j, true);
					break;
			case Trans:
					error((char *) "Invalid Operation (Rev) in Permutation");
			}
	}

	void trans(perm *pi, int i, int j, int k) {
			pi->valid_inv = false;
			switch(pi->type) {
			case Rev:
			case SRev:
					error((char *) "Invalid Operation (Trans) in Permutation");
					break;
			default:
					rev_(pi, i, k - 1, false);
					rev_(pi, i, i + k - j - 1, false);
					rev_(pi, i + k - j, k - 1, false);
			}
	}

	int end_strip(perm *pi, int i) {
			while(i < pi->size-1 && !break_point(pi,i,i+1)) i++;
			return i;
	}

	bool is_signed(perm *pi) {
			switch(pi->type) {
			case SRev:
			case TransSRev:
					return true;
			default:
					return false;
			}
	}

	bool singleton_strip(perm *pi, int i) {return (break_point(pi,i-1,i) && break_point(pi,i,i+1));}
}
