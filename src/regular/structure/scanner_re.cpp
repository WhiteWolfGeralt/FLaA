//
// Created by daniil on 03.03.2022.
//

#include "scanner_re.h"
#include <iostream>

using std::cout;

void Scanner_re::init(const string &expr) {
	this->buffer = expr + '\0';
	this->gc();
}

void Scanner_re::gc() {
	this->c = this->buffer[0];
	this->buffer = string(this->buffer.begin() + 1, this->buffer.end());
}

Lex_re Scanner_re::get_lex() {
	char curr_c = this->c;
	if (curr_c == '\0') {
		return {"", END};
	}
	while (isspace(curr_c)) {
		this->gc();
		curr_c = this->c;
	}
	switch (curr_c) {
		case '(': {
			this->gc();
			return {"(", L_BRACKET};
		}
		case ')': {
			this->gc();
			return {")", R_BRACKET};
		}
		case '*': {
			this->gc();
			return {"*", ASTER};
		}
		case '|': {
			this->gc();
			return {"|", BAR};
		}
		default: {
			if (isalnum(curr_c)) {
				this->gc();
				return {string(1, curr_c), IDENT};
			} else {
				string ret = "Scanner: wrong symbol: ";
				ret.push_back(curr_c);
				cout << ret;
				exit(1);
			}
		}
	}
}
