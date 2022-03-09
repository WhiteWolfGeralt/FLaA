//
// Created by daniil on 03.03.2022.
//

#ifndef SCANNER_CPP_PARSER_GR_H
#define SCANNER_CPP_PARSER_GR_H

#include "scanner_gr.h"
#include <map>

using std::map;

class Parser_gr {
	//Variables
	Scanner_gr scanner;
	map<string, vector<Scanner_gr::Lex>> rules;
	bool deriving_eps;
	Scanner_gr::Lex start_non_term;

	//Methods
	bool is_correct();
	void mark_deriving_epsilon();

public:
	Parser_gr(string);
	void parse();
};


#endif //SCANNER_CPP_PARSER_GR_H
