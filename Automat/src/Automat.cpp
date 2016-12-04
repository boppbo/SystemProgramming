/*
 * Automat.cpp
 *
 */

#include "../includes/Automat.h"
#include <ctype.h>

Automat::Automat() {
	// TODO Auto-generated constructor stub

}

Automat::~Automat() {
	// TODO Auto-generated destructor stub
}

action Automat::stateEval(event e) {

	stateElement stateEvaluation = this->_stateMatrix[ this->_currentState ][ e ];

	this->_currentState = stateEvaluation.nextState;

	return stateEvaluation.actionToDo;
}

action Automat::charEval(char c) {

	if (isdigit(c)) {
		return this->stateEval(DIGIT);
	}
	if(isalpha(c)) {
		return this->stateEval(LETTER);
	}
	if (isSimpleSign(c)) {
		return this->stateEval(SIGN);
	}
	switch (c) {
		case ':': return this->stateEval(COLON);
		case '*': return this->stateEval(STAR);
		case '=': return this->stateEval(EQUALS);
		case '&': return this->stateEval(AND);
		case ' ': return this->stateEval(SPACE);
		case '\n': return this->stateEval(NEW_LINE);
	}
	if (c == '\0') {
		return this->stateEval(EOF);
	}

	return this->stateEval(UNKNOWN);
}


bool Automat::isSimpleSign(char c) {

	for (unsigned int i = 0; i < sizeof(signArray); i++) {
		if (c == signArray[i])
			return true;
	}
	return false;
};
