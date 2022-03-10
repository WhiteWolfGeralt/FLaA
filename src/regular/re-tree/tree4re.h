//
// Created by daniil on 07.03.2022.
//

#ifndef SCANNER_CPP_TREE4RE_H
#define SCANNER_CPP_TREE4RE_H

#include <string>
#include <set>

using std::string;
using std::set;

enum OpType {
	/// operation *
	ITER,
	/// operation •
	CONCAT,
	/// operation |
	CHOICE,
	/// default state
	NONE
};

typedef struct Node {
	bool is_operation = false;

	set<string> first;
	set<string> follow;
	OpType op_type = NONE;
	bool is_nullable = false;
	string symbol;

	struct Node *left = nullptr, *right = nullptr, *parent = nullptr;
} Node;

class Tree4Re {
	static void tree2dot_rec(Node*, std::ofstream&);
public:
	static Node* add(Node*, Node*);
	static void fill_node(Node*);
	static void tree2dot(Node*);
};


#endif //SCANNER_CPP_TREE4RE_H
