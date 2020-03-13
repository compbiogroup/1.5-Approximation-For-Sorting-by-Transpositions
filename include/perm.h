#ifndef H_HS_PERM
#define H_HS_PERM

#include "util.h"

namespace hs {
	typedef struct perm perm;
	typedef enum PermType {Trans, Rev, SRev, TransRev, TransSRev} PermType;

	perm *build_perm(int *vet, int n, PermType type);
	perm *build_and_rename_perm(int *vet1, int *vet2, int n, PermType type);
	perm *create_perm(int size, PermType type);
	void print_perm(perm *pi);
	void clear_perm(perm *pi_free);

	PermType type_of_perm(perm *pi);
	int length_perm(perm *pi);
	int get_perm(perm *pi, int i);
	int get_perm_idx(perm *pi, int val);
	void set_perm(perm *pi_mut, int i, int val);

	bool is_sorted(perm *pi);
	bool is_signed(perm *pi);
	bool singleton_strip(perm *pi, int i);

	bool break_point(perm *pi, int x, int y);
	int end_strip(perm *pi, int i);

	void rev(perm *pi_mut, int i, int j);
	void trans(perm *pi_mut, int i, int j, int k);
}

#endif
