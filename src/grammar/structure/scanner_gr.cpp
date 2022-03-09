//
// Created by daniil on 01.03.2022.
//

#include "scanner_gr.h"
#include <fstream>

using std::cout; using std::cin; using std::ifstream; using std::endl;

void Scanner_gr::scan_grammar(const string& filename) {
	string line;
	ifstream file(filename);
	if (file.is_open()) {
		while (getline(file, line)) {
			this->dirty_grammar.push_back(line);
		}
		file.close();
	} else {
		cout << "Wrong filename!";
		exit(1);
	}
}

char Scanner_gr::get_char() {
	if (this->current_string.empty()) { return '\n'; }

	char ret = this->current_string[0];
	this->current_string = this->current_string.substr(1);
	return ret;
}

void Scanner_gr::get_tokens() {
	vector<Lex> res;
	States CS = H;
	char curr_char = this->get_char();
	while (true) {
		switch (CS) {
			case H: {
				if (curr_char != '\n' && isspace(curr_char)) {
					curr_char = get_char();
				} else if (isalpha(curr_char)) {
					this->buf = "";
					this->buf += curr_char;
					if (isupper(curr_char)) {
						CS = N_TERM;
					} else {
						CS = TERM;
					}
					curr_char = get_char();
				} else if (curr_char == '-') {
					this->buf = "";
					this->buf += curr_char;
					curr_char = get_char();
					CS = ARROW;
				} else {
					if (curr_char == '\n') { //end of expression
						goto while_end;
					} else if (curr_char == eps) {
						res.emplace_back(string(1, eps), END);
					} else if (curr_char == bar) {
						res.emplace_back(string(1, bar), BAR);
					} else {
						res.emplace_back(string(1, curr_char), TERM);
					}
					curr_char = get_char();
				}
				break;
			}
			case N_TERM: {
				if (isupper(curr_char)) {
					this->buf += curr_char;
					curr_char = get_char();
				} else {
					res.emplace_back(this->buf, N_TERM);
					CS = H;
				}
				break;
			}
			case TERM: {
				if (islower(curr_char)) {
					this->buf += curr_char;
					curr_char = get_char();
				} else {
					res.emplace_back(this->buf, N_TERM);
					CS = H;
				}
				break;
			}
			case ARROW: {
				if (curr_char == '>') {
					res.emplace_back("->", ARROW);
					curr_char = get_char();
				} else {
					res.emplace_back(this->buf, TERM);
				}
				CS = H;
				break;
			}
			default: {
				cout << "WTF? Wrong state...";
				exit(1);
			}
		}
	}
while_end:
	this->clear_grammar.emplace_back(res);
}

void Scanner_gr::merge_tokens() {
	vector<vector<Lex>> new_grammar;
	for (auto expr: this->clear_grammar) {
		vector<Lex> new_tokens;
		auto prev_token = expr[0];
		for (int i = 1; i < expr.capacity(); i++) {
			auto token = expr[i];
			if (prev_token.lex_type == TERM && prev_token.lex_type == token.lex_type) {
				prev_token.sym += token.sym;
			} else {
				new_tokens.emplace_back(prev_token);
				prev_token = token;
			}
		}
		new_tokens.emplace_back(prev_token);
		new_grammar.emplace_back(new_tokens);
	}
	this->clear_grammar = new_grammar;
}

void Scanner_gr::tokenize_grammar() {
	for (const string& expr: this->dirty_grammar) {
		this->current_string = expr;
		this->get_tokens();
	}
	this->merge_tokens();
}

void Scanner_gr::print_grammar() {
	for (const auto& expr: this->clear_grammar) {
		for (const auto& token: expr) {
			cout << token << ' ';
		}
		cout << endl;
	}
}
