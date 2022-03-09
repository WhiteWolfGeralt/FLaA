//
// Created by daniil on 07.03.2022.
//

#include "tree4re.h"
#include <cassert>

Node* Tree4Re::add(Node* adding, Node* par) {
	assert(par != nullptr);
	if (par->left) {
		par->right = adding;
	} else {
		par->left = adding;
	}
	adding->parent = par;
	return par;
}
