//
// Created by daniil on 07.03.2022.
//

#include "tree_creator.h"
#include <iostream>

using std::cout;

void TreeCreator::init(const string& filename) {
	this->parser_re.init(filename);
	this->parser_re.parse();
	this->lex_vector = this->parser_re.get_lexemes();
}

void TreeCreator::create_tree() {
	bool prev_bar = false;
	for (const auto& iter: this->lex_vector) {
		switch (iter.type() ) {
			case EPS:
			case IDENT: {
				if (node_stack.empty() || prev_bar) {
					Node* new_node = new Node();
					if (iter.sym() == "{eps}") {
						new_node->is_nullable = true;
					} else {
						new_node->first = new_node->follow = iter.sym();
					}
					new_node->symbol = iter.sym();
					node_stack.push(new_node);

					prev_bar = false;
				} else {
					Node* new_node = new Node();
					new_node->symbol = iter.sym();
					node_stack.push(new_node);

					new_node = new Node();
					new_node->is_operation = true;
					new_node->op_type = CONCAT;
					new_node->symbol = "•";
					op_stack.push(new_node);
				}
				break;
			}
			case L_BRACKET: {
				Node* l_bracket = new Node();
				l_bracket->symbol = "(";
				op_stack.push(l_bracket);
				break;
			}
			case R_BRACKET: {
				while (op_stack.top()->symbol != "(") {
					Node* op = op_stack.top();
					op_stack.pop();

					Node* op1 = node_stack.top();
					node_stack.pop();
					Node* op2 = node_stack.top();
					node_stack.pop();
					op = Tree4Re::add(op1, op);
					op = Tree4Re::add(op2, op);
					node_stack.push(op);
				}
				Node* op = op_stack.top();
				op_stack.pop();
				delete(op);
				break;
			}
			case ASTER: {
				Node* new_node = new Node();
				new_node->is_operation = true;
				new_node->op_type = ITER;
				new_node->symbol = "*";

				Node* operand = node_stack.top();
				node_stack.pop();
				new_node = Tree4Re::add(operand, new_node);
				node_stack.push(new_node);
				break;
			}
			case BAR: {
				if (!op_stack.empty() && op_stack.top()->op_type == CONCAT) {
					Node* concat_node = op_stack.top();
					op_stack.pop();

					Node* op1 = node_stack.top();
					node_stack.pop();
					Node* op2 = node_stack.top();
					node_stack.pop();

					concat_node = Tree4Re::add(op1, concat_node);
					concat_node = Tree4Re::add(op2, concat_node);
					node_stack.push(concat_node);

				}
				Node* new_node = new Node();
				new_node->is_operation = true;
				new_node->op_type = CHOICE;
				new_node->symbol = "|";
				op_stack.push(new_node);

				prev_bar = true;
				break;
			}
			case END: {
				cout << "Tree creator: wrong state 'END'\n";
				exit(1);
			}
		}
	}

	while (!op_stack.empty()) {
		Node* op = op_stack.top();
		op_stack.pop();

		Node* op1 = node_stack.top();
		node_stack.pop();
		Node* op2 = node_stack.top();
		node_stack.pop();
		op = Tree4Re::add(op1, op);
		op = Tree4Re::add(op2, op);
		node_stack.push(op);
	}
	this->root = node_stack.top();
	node_stack.pop();
}

void TreeCreator::print_tree(Node *node) {
	if (node->right == nullptr && node->left == nullptr) {
		cout << node->symbol;
		return;
	}
	if (node->left != nullptr) {
		this->print_tree(node->left);
	}
	cout << node->symbol;
	if (node->right != nullptr) {
		this->print_tree(node->right);
	}
}

void TreeCreator::print_tree() {
	this->print_tree(this->root);
}
