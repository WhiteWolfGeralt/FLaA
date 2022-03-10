//
// Created by daniil on 07.03.2022.
//

#include "parser_re.h"
#include <iostream>

using std::cout;

void Parser_re::parse() {
	string wrong_sym;
	this->curr_lex = this->scanner.get_lex();
	try {
		EXPR();
		if (this->curr_lex.type() == END) {
			return;
		} else {
			wrong_sym = this->curr_lex.sym();
		}
	}
	catch (string e) {
		if (e.empty()) {
			wrong_sym = "{eps}";
		} else {
			wrong_sym = e;
		}
	}
	cout << "Parser: wrong symbol.\n";
	this->print_queue();
	cout << wrong_sym + '\n';
	for (const auto& iter: this->lex_vector) {
		if (iter.sym() == "{eps}") {
			cout << "    ";
		}
		cout << ' ';
	}
	cout << "^ here\n";
	exit(0);
}

void Parser_re::EXPR() {
	STATE();
	DOP_EXPR();
}

void Parser_re::DOP_EXPR() {
	if (this->curr_lex.type() == IDENT || this->curr_lex.type() == L_BRACKET) {
		EXPR();
	} else {
		return;
	}
}

void Parser_re::STATE() {
	SIMPLE_STATE();
	DOP_STATE();
}

void Parser_re::DOP_STATE() {
	if (this->curr_lex.type() == ASTER) {
		this->get_push();
		DOP_STATE();
	} else if (this->curr_lex.type() == BAR) {
		this->get_push();
		STATE();
	} else {
		return;
	}
}

void Parser_re::SIMPLE_STATE() {
	if (this->curr_lex.type() == L_BRACKET) {
		this->get_push();
		EXPR();
		if (this->curr_lex.type() != R_BRACKET) {
			throw this->curr_lex.sym();
		}
		this->get_push();
	} else {
		WORD();
	}
}

void Parser_re::WORD() {
	if (this->curr_lex.type() == IDENT) {
		this->get_push();
	} else {
		this->lex_vector.emplace_back("{eps}", EPS);
		return;
	}
}

void Parser_re::get_push() {
	this->lex_vector.push_back(this->curr_lex);
	this->curr_lex = this->scanner.get_lex();
}

void Parser_re::print_queue() {
	for (const auto& iter: this->lex_vector) {
		cout << iter.sym();
	}
}

vector<Lex_re> Parser_re::get_lexemes() const {
	return this->lex_vector;
}

void Parser_re::init(const string& filename) {
	this->scanner.init(filename);
}
