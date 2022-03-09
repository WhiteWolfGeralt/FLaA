//
// Created by daniil on 07.03.2022.
//

#ifndef SCANNER_CPP_PARSER_RE_H
#define SCANNER_CPP_PARSER_RE_H

#include "scanner_re.h"
#include <stack>
#include <vector>

using std::vector;

class Parser_re {
	Scanner_re scanner;
	Lex_re curr_lex;
	vector<Lex_re> lex_vector;
	void EXPR();
	void DOP_EXPR();
	void STATE();
	void DOP_STATE();
	void SIMPLE_STATE();
	void WORD();

	void get_push();
	void print_queue();
public:
	void init(const string&);
	void parse();
	vector<Lex_re> get_lexemes() const;
};


#endif //SCANNER_CPP_PARSER_RE_H
