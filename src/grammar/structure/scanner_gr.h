//
// Created by daniil on 01.03.2022.
//

#ifndef FLAA_ANALYZER_SCANNER_H
#define FLAA_ANALYZER_SCANNER_H

#include <iostream>
#include <vector>

using std::string;
using std::vector;

enum States{
	H, //start state
	N_TERM, //non-terminal symbol
	TERM, // terminal symbol
	ARROW, // -> symbol
	//TODO: add option to choose the epsilon and bar symbol
	END, // epsilon symbol
	BAR, // | symbol
};

class Scanner_gr {
	friend class Parser_gr;

	class Lex {
	public:
		Lex(string sym, States lex_type) { this->sym = std::move(sym); this->lex_type = lex_type; }
		std::string sym;
		States lex_type;
		friend std::ostream& operator<<(std::ostream& os, const Lex& lex) { os << lex.sym; return os;}

	explicit operator string() const { return this->sym; }
	bool is_eps() const { return this->lex_type == States::END; }
	};

	//Variables
	char eps = '#';
	char bar = '|';

	vector<string> dirty_grammar; //input grammar
	string current_string; //current expression in grammar
	string buf; //for terminals and non-terminals

	vector<vector<Lex>> clear_grammar; //tokenized grammar

	//Methods
	void scan_grammar(const string& filename);
	char get_char();
	void get_tokens();
	void merge_tokens();
	void tokenize_grammar();
	void print_grammar();
};

#endif //FLAA_ANALYZER_SCANNER_H
