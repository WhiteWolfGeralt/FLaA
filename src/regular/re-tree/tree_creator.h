//
// Created by daniil on 07.03.2022.
//

#ifndef SCANNER_CPP_TREE_CREATOR_H
#define SCANNER_CPP_TREE_CREATOR_H

#include "../structure/parser_re.h"
#include "tree4re.h"
#include <string>
#include <stack>

using std::string;
using std::stack;

class TreeCreator {
	Parser_re parser_re;
	vector<Lex_re> lex_vector;
	stack<Node*> op_stack{};
	stack<Node*> node_stack{};
	Node* root;
	void print_tree(Node*);
public:
	void print_tree();
	void init(const string&);
	void create_tree();
};


#endif //SCANNER_CPP_TREE_CREATOR_H
