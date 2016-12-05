#include "../includes/Automat.h"
#include <iostream>
using namespace std;

Automat* automat;

void nothing() {
	cout << "Action: NOTHING | nextState: " << automat->getCurrentState() << endl;
}
void add_char() {
	cout << "Action: ADD_CHAR | nextState: " << automat->getCurrentState() << endl;
}
void add_token_integer() {
	cout << "Action: ADD_TOKEN_INTEGER | nextState: " << automat->getCurrentState() << endl;
}
void add_token_identifier() {
	cout << "Action: ADD_TOKEN_IDENTIFIER | nextState: " << automat->getCurrentState() << endl;
}
void add_token_sign() {
	cout << "Action: ADD_TOKEN_SIGN | nextState: " << automat->getCurrentState() << endl;
}
void add_token_sign_ug0() {
	cout << "Action: ADD_TOKEN_SIGN_UG0 | nextState: " << automat->getCurrentState() << endl;
}
void add_token_sign_ug2() {
	cout << "Action: ADD_TOKEN_SIGN_UG2 | nextState: " << automat->getCurrentState() << endl;
}
void add_token_unknown() {
	cout << "Action: ADD_TOKEN_UKNOWN | nextState: " << automat->getCurrentState() << endl;
}
void discard() {
	cout << "Action: DISCARD | nextState: " << automat->getCurrentState() << endl;
}
void end() {
	cout << "Action: END | nextState: " << automat->getCurrentState() << endl;
}


int main () {

	automat = new Automat();

	void (*tansition_action[10])() = {
		nothing,
		add_char,
		add_token_integer,
		add_token_identifier,
		add_token_sign,
		add_token_sign_ug0,
		add_token_sign_ug2,
		add_token_unknown,
		discard,
		end
	};


	tansition_action[automat->charEval('0')]();
	tansition_action[automat->charEval('9')]();
	tansition_action[automat->charEval('+')]();
	tansition_action[automat->charEval('=')]();
	tansition_action[automat->charEval(':')]();
	tansition_action[automat->charEval(':')]();
	tansition_action[automat->charEval('=')]();
	tansition_action[automat->charEval('f')]();
	tansition_action[automat->charEval('o')]();
	tansition_action[automat->charEval('=')]();

	return 1;
}
