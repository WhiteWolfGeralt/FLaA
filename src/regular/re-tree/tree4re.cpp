//
// Created by daniil on 07.03.2022.
//

#include "tree4re.h"
#include <cassert>
#include <fstream>

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

void Tree4Re::fill_node(Node* node) {
	assert(node != nullptr);
	assert(node->right != nullptr);

	if (node->symbol == "*") {
		assert(node->op_type == ITER);
		assert(node->left == nullptr);

		Node* list = node->right;
		node->first.insert(list->first.begin(), list->first.end());
		node->follow.insert(list->follow.begin(), list->follow.end());

		node->is_nullable = true;
	} else if (node->symbol == "|") {
		assert(node->op_type == CHOICE);
		assert(node->left != nullptr);

		node->first.insert(node->left->first.begin(), node->left->first.end());
		node->first.insert(node->right->first.begin(), node->right->first.end());

		node->follow.insert(node->left->follow.begin(), node->left->follow.end());
		node->follow.insert(node->right->follow.begin(), node->right->follow.end());

		node->is_nullable = (node->left->is_nullable || node->right->is_nullable);
	} else if (node->symbol == "•") {
		assert(node->op_type == CONCAT);
		assert(node->left != nullptr);

		node->first.insert(node->left->first.begin(), node->left->first.end());
		if ( node->left->is_nullable ) {
			node->first.insert(node->right->first.begin(), node->right->first.end());
		}

		node->follow.insert(node->right->follow.begin(), node->right->follow.end());
		if ( node->right->is_nullable ) {
			node->follow.insert(node->left->follow.begin(), node->left->follow.end());
		}

		node->is_nullable = (node->left->is_nullable && node->right->is_nullable);
	} else {
		// unreachable branch, if here then error
		assert(1 == 2);
	}
}

void Tree4Re::tree2dot(Node *root) {
	std::ofstream output;
	output.open("../docs/tree4re.dot");
	output << "digraph G {\n";

	tree2dot_rec(root, output);

	output << "}";
	output.close();
}

void Tree4Re::tree2dot_rec(Node *root, std::ofstream& output) {
	assert(root != nullptr);
	auto address_par = (unsigned long) root;

	if (root->left == nullptr && root->right == nullptr) {
		output << "\t" << address_par << " [label=\"" << root->symbol << "\"] [shape=triangle]\n";
		return;
	} else {
		output << "\t" << address_par << " [label=\"" << root->symbol << "\"] [shape=box]\n";
	}
	if (root->left != nullptr) {
		auto address_child = (unsigned long) root->left;
		output << "\t" << address_par << " -> " << address_child << "\n";
		tree2dot_rec(root->left, output);
	}
	if (root->right != nullptr) {
		auto address_child = (unsigned long) root->right;
		output << "\t" << address_par << " -> " << address_child << "\n";
		tree2dot_rec(root->right, output);
	}
}
