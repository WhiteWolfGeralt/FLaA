//
// Created by daniil on 07.03.2022.
//

#include "tree4re.h"
#include <cassert>

Node* Tree4Re::add(Node* adding, Node* par) {
	assert(par != nullptr);
	if (par->right) {
		par->left = adding;
	} else {
		par->right = adding;
	}
	adding->parent = par;
	return par;
}
