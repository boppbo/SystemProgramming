#include "../includes/Automat.h"
#include <iostream>
using namespace std;

Automat* automat;

void nothing() {
	cout << "Action: NOTHING | nextState: " << automat->_currentState << endl;
}
void add_char() {
	cout << "Action: ADD_CHAR | nextState: " << automat->_currentState << endl;
}
void add_token_integer() {
	cout << "Action: ADD_TOKEN_INTEGER | nextState: " << automat->_currentState << endl;
}
void add_token_identifier() {
	cout << "Action: ADD_TOKEN_IDENTIFIER | nextState: " << automat->_currentState << endl;
}
void add_token_sign() {
	cout << "Action: ADD_TOKEN_SIGN | nextState: " << automat->_currentState << endl;
}
void add_token_sign_ug0() {
	cout << "Action: ADD_TOKEN_SIGN_UG0 | nextState: " << automat->_currentState << endl;
}
void add_token_sign_ug2() {
	cout << "Action: ADD_TOKEN_SIGN_UG2 | nextState: " << automat->_currentState << endl;
}
void add_token_unknown() {
	cout << "Action: ADD_TOKEN_UKNOWN | nextState: " << automat->_currentState << endl;
}
void discard() {
	cout << "Action: DISCARD | nextState: " << automat->_currentState << endl;
}
void end() {
	cout << "Action: END | nextState: " << automat->_currentState << endl;
}


int main (int argc, char* argv[]){

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


	tansition_action[automat->stateEval(DIGIT)]();
	tansition_action[automat->stateEval(DIGIT)]();
	tansition_action[automat->stateEval(SIGN)]();
	tansition_action[automat->stateEval(EQUALS)]();
	tansition_action[automat->stateEval(COLON)]();
	tansition_action[automat->stateEval(COLON)]();
	tansition_action[automat->stateEval(EQUALS)]();
	tansition_action[automat->stateEval(LETTER)]();
	tansition_action[automat->stateEval(LETTER)]();
	tansition_action[automat->stateEval(EQUALS)]();

	return 1;
}
