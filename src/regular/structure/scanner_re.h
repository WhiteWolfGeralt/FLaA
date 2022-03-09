//
// Created by daniil on 03.03.2022.
//

#ifndef SCANNER_CPP_SCANNER_RE_H
#define SCANNER_CPP_SCANNER_RE_H

#include <string>
#include <fstream>
#include <utility>

using std::string;

enum Lex_type_re {
	IDENT, L_BRACKET, R_BRACKET, ASTER, BAR, EPS, END
};

class Lex_re {
	string symbol{};
	Lex_type_re lex_type{};
public:
	Lex_re() = default;
	Lex_re(string sym, Lex_type_re type) { this->symbol = std::move(sym); this->lex_type = type;}
	string sym() const {return this->symbol; }
	Lex_type_re type() const { return this->lex_type; }
};

class Scanner_re {
	char c{};
	std::ifstream input;

	void gc();
public:
	Lex_re get_lex();
	void init(const string& filename);
	~Scanner_re() { input.close(); }
};

#endif //SCANNER_CPP_SCANNER_RE_H
