//
// Created by daniil on 07.03.2022.
//

#ifndef SCANNER_CPP_TREE4RE_H
#define SCANNER_CPP_TREE4RE_H

#include <string>

using std::string;

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

	/* if operation */
	string first;
	string follow;
	OpType op_type = NONE;
	bool is_nullable = false;

	/* if list(single symbol)*/
	string symbol;

	struct Node *left = nullptr, *right = nullptr, *parent = nullptr;
} Node;

class Tree4Re {
public:
	static Node* add(Node*, Node*);
};


#endif //SCANNER_CPP_TREE4RE_H
