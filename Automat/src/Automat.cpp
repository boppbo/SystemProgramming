/*
 * Automat.cpp
 *
 */

#include "../includes/Automat.h"
#include <ctype.h>

action Automat::charEval(unsigned char c) {

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
		case '	':
		case ' ': return this->stateEval(SPACE);
		case '\n': return this->stateEval(NEW_LINE);
	}
	if (c == '\0') {
		return this->stateEval(EOF);
	}

	return this->stateEval(UNKNOWN);
}

action Automat::stateEval(event e) {
	stateElement stateEvaluation = this->_StateMatrix[ this->_currentState ][ e ];
	this->_currentState = stateEvaluation.nextState;

	return stateEvaluation.actionToDo;
}

bool Automat::isSimpleSign(char const c) const {
	for (unsigned int i = 0; i < sizeof(_SimpleSigns); i++) {
		if (c == _SimpleSigns[i])
			return true;
	}
	return false;
};

char const Automat::_SimpleSigns[] = { '+', '-', '<', '>', '!', ';', '(', ')', '{', '}', '[', ']'};
Automat::stateElement const Automat::_StateMatrix[][11] = {
	// State0
	{
		{ STATE_INTEGER, ADD_CHAR },		// Event: DIGIT
		{ STATE_IDENTIFIER, ADD_CHAR },		// Event: LETTER
		{ STATE_INIT, ADD_TOKEN_SIGN_UG0 },	// Event: SIGN		( + | - | < | > | ! | ; | ( | ) | { | } | [ | ] )
		{ STATE_SIGN_COLON, ADD_CHAR },		// Event: COLON		(':')
		{ STATE_INIT, ADD_TOKEN_SIGN_UG0 },	// Event: STAR		('*')
		{ STATE_SIGN_EQUALS_0, ADD_CHAR },	// Event: EQUALS	('=')
		{ STATE_SIGN_AND, ADD_CHAR },		// Event: AND		('&')
		{ STATE_INIT, NOTHING },			// Event: SPACE		(' ')
		{ STATE_INIT, ADD_NEW_LINE },		// Event: NEW_LINE	('\n')
		{ STATE_UNKNOWN, ADD_CHAR},			// Event: UNKNOWN	(others)
		{ STATE_INIT, END }					// Event: EOF
	},
	// State1 (Integer)
	{
		{ STATE_INTEGER, ADD_CHAR },		// Event: DIGIT
		{ STATE_INIT, ADD_TOKEN_INTEGER },	// Event: LETTER
		{ STATE_INIT, ADD_TOKEN_INTEGER },	// Event: SIGN
		{ STATE_INIT, ADD_TOKEN_INTEGER },	// Event: COLON		(':')
		{ STATE_INIT, ADD_TOKEN_INTEGER },	// Event: STAR		('*')
		{ STATE_INIT, ADD_TOKEN_INTEGER },	// Event: EQUALS	('=')
		{ STATE_INIT, ADD_TOKEN_INTEGER },	// Event: AND		('&')
		{ STATE_INIT, ADD_TOKEN_INTEGER },	// Event: SPACE		(' ')
		{ STATE_INIT, ADD_TOKEN_INTEGER },	// Event: NEW_LINE	('\n')
		{ STATE_INIT, ADD_TOKEN_INTEGER },	// Event: UNKNOWN	(others)
		{ STATE_INIT, ADD_TOKEN_INTEGER }	// Event: EOF
	},
	// State2 (Identifier)
	{
		{ STATE_IDENTIFIER, ADD_CHAR },			// Event: DIGIT
		{ STATE_IDENTIFIER, ADD_CHAR },			// Event: LETTER
		{ STATE_INIT, ADD_TOKEN_IDENTIFIER },	// Event: SIGN
		{ STATE_INIT, ADD_TOKEN_IDENTIFIER },	// Event: COLON		(':')
		{ STATE_INIT, ADD_TOKEN_IDENTIFIER },	// Event: STAR		('*')
		{ STATE_INIT, ADD_TOKEN_IDENTIFIER },	// Event: EQUALS	('=')
		{ STATE_INIT, ADD_TOKEN_IDENTIFIER },	// Event: AND		('&')
		{ STATE_INIT, ADD_TOKEN_IDENTIFIER },	// Event: SPACE		(' ')
		{ STATE_INIT, ADD_TOKEN_IDENTIFIER },	// Event: NEW_LINE	('\n')
		{ STATE_INIT, ADD_TOKEN_IDENTIFIER },	// Event: UNKNOWN	(others)
		{ STATE_INIT, ADD_TOKEN_IDENTIFIER }	// Event: EOF
	},
	// State3 (: | :=)
	{
		{ STATE_INIT, ADD_TOKEN_SIGN },		// Event: DIGIT
		{ STATE_INIT, ADD_TOKEN_SIGN },		// Event: LETTER
		{ STATE_INIT, ADD_TOKEN_SIGN },		// Event: SIGN
		{ STATE_INIT, ADD_TOKEN_SIGN },		// Event: COLON		(':')
		{ STATE_COMMENT, DISCARD },			// Event: STAR		('*')
		{ STATE_INIT, ADD_TOKEN_SIGN_UG0 },	// Event: EQUALS	('=')
		{ STATE_INIT, ADD_TOKEN_SIGN },		// Event: AND		('&')
		{ STATE_INIT, ADD_TOKEN_SIGN },		// Event: SPACE		(' ')
		{ STATE_INIT, ADD_TOKEN_SIGN },		// Event: NEW_LINE	('\n')
		{ STATE_INIT, ADD_TOKEN_SIGN },		// Event: UNKNOWN	(others)
		{ STATE_INIT, ADD_TOKEN_SIGN }		// Event: EOF
	},
	// State4 (= | =:=)
	{
		{ STATE_INIT, ADD_TOKEN_SIGN },		// Event: DIGIT
		{ STATE_INIT, ADD_TOKEN_SIGN },		// Event: LETTER
		{ STATE_INIT, ADD_TOKEN_SIGN },		// Event: SIGN
		{ STATE_SIGN_EQUALS_1, ADD_CHAR },	// Event: COLON		(':')
		{ STATE_INIT, ADD_TOKEN_SIGN },		// Event: STAR		('*')
		{ STATE_INIT, ADD_TOKEN_SIGN },		// Event: EQUALS	('=')
		{ STATE_INIT, ADD_TOKEN_SIGN },		// Event: AND		('&')
		{ STATE_INIT, ADD_TOKEN_SIGN },		// Event: SPACE		(' ')
		{ STATE_INIT, ADD_TOKEN_SIGN },		// Event: NEW_LINE	('\n')
		{ STATE_INIT, ADD_TOKEN_SIGN },		// Event: UNKNOWN	(others)
		{ STATE_INIT, ADD_TOKEN_SIGN }		// Event: EOF
	},
	// State5 (=: | =:=)
	{
		{ STATE_INIT, ADD_TOKEN_SIGN_UG2 },	// Event: DIGIT
		{ STATE_INIT, ADD_TOKEN_SIGN_UG2 },	// Event: LETTER
		{ STATE_INIT, ADD_TOKEN_SIGN_UG2 },	// Event: SIGN
		{ STATE_INIT, ADD_TOKEN_SIGN_UG2 },	// Event: COLON		(':')
		{ STATE_INIT, ADD_TOKEN_SIGN_UG2 },	// Event: STAR		('*')
		{ STATE_INIT, ADD_TOKEN_SIGN_UG0 },	// Event: EQUALS	('=')
		{ STATE_INIT, ADD_TOKEN_SIGN_UG2 },	// Event: AND		('&')
		{ STATE_INIT, ADD_TOKEN_SIGN_UG2 },	// Event: SPACE		(' ')
		{ STATE_INIT, ADD_TOKEN_SIGN_UG2 },	// Event: NEW_LINE	('\n')
		{ STATE_INIT, ADD_TOKEN_SIGN_UG2 },	// Event: UNKNOWN	(others)
		{ STATE_INIT, ADD_TOKEN_SIGN_UG2 }	// Event: EOF
	},
	// State6 (& | &&)
	{
		{ STATE_INIT, ADD_TOKEN_UKNOWN },	// Event: DIGIT
		{ STATE_INIT, ADD_TOKEN_UKNOWN },	// Event: LETTER
		{ STATE_INIT, ADD_TOKEN_UKNOWN },	// Event: SIGN
		{ STATE_INIT, ADD_TOKEN_UKNOWN },	// Event: COLON		(':')
		{ STATE_INIT, ADD_TOKEN_UKNOWN },	// Event: STAR		('*')
		{ STATE_INIT, ADD_TOKEN_UKNOWN },	// Event: EQUALS	('=')
		{ STATE_INIT, ADD_TOKEN_SIGN_UG0 },	// Event: AND		('&')
		{ STATE_INIT, ADD_TOKEN_UKNOWN },	// Event: SPACE		(' ')
		{ STATE_INIT, ADD_TOKEN_UKNOWN },	// Event: NEW_LINE	('\n')
		{ STATE_UNKNOWN, ADD_CHAR },		// Event: UNKNOWN	(others)
		{ STATE_INIT, ADD_TOKEN_UKNOWN }	// Event: EOF
	},
	// State7 (comment)
	{
		{ STATE_COMMENT, NOTHING },		// Event: DIGIT
		{ STATE_COMMENT, NOTHING },		// Event: LETTER
		{ STATE_COMMENT, NOTHING },		// Event: SIGN
		{ STATE_COMMENT, NOTHING },		// Event: COLON		(':')
		{ STATE_COMMENT_END, NOTHING },	// Event: STAR		('*')
		{ STATE_COMMENT, NOTHING },		// Event: EQUALS	('=')
		{ STATE_COMMENT, NOTHING },		// Event: AND		('&')
		{ STATE_COMMENT, NOTHING },		// Event: SPACE		(' ')
		{ STATE_COMMENT, ADD_NEW_LINE },	// Event: NEW_LINE	('\n')
		{ STATE_COMMENT, NOTHING },		// Event: UNKNOWN	(others)
		{ STATE_COMMENT, END }			// Event: EOF
	},
	// State8 (comment_end)
	{
		{ STATE_COMMENT, NOTHING },		// Event: DIGIT
		{ STATE_COMMENT, NOTHING },		// Event: LETTER
		{ STATE_COMMENT, NOTHING },		// Event: SIGN
		{ STATE_INIT, NOTHING },		// Event: COLON		(':')
		{ STATE_COMMENT_END, NOTHING },	// Event: STAR		('*')
		{ STATE_COMMENT, NOTHING },		// Event: EQUALS	('=')
		{ STATE_COMMENT, NOTHING },		// Event: AND		('&')
		{ STATE_COMMENT, NOTHING },		// Event: SPACE		(' ')
		{ STATE_COMMENT, ADD_NEW_LINE },// Event: NEW_LINE	('\n')
		{ STATE_COMMENT, NOTHING },		// Event: UNKNOWN	(others)
		{ STATE_COMMENT, END }			// Event: EOF
	},
	// State9 (unknown)
	{
		{ STATE_INIT, ADD_TOKEN_UKNOWN },	// Event: DIGIT
		{ STATE_INIT, ADD_TOKEN_UKNOWN },	// Event: LETTER
		{ STATE_INIT, ADD_TOKEN_UKNOWN },	// Event: SIGN
		{ STATE_INIT, ADD_TOKEN_UKNOWN },	// Event: COLON		(':')
		{ STATE_INIT, ADD_TOKEN_UKNOWN },	// Event: STAR		('*')
		{ STATE_INIT, ADD_TOKEN_UKNOWN },	// Event: EQUALS	('=')
		{ STATE_INIT, ADD_TOKEN_UKNOWN },	// Event: AND		('&')
		{ STATE_INIT, ADD_TOKEN_UKNOWN },	// Event: SPACE		(' ')
		{ STATE_INIT, ADD_TOKEN_UKNOWN },	// Event: NEW_LINE	('\n')
		{ STATE_UNKNOWN, ADD_CHAR },		// Event: UNKNOWN	(others)
		{ STATE_INIT, ADD_TOKEN_UKNOWN }	// Event: EOF
	}
};
