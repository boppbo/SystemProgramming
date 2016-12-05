/*
 * Automat.h
 *
 *  Created on: Jul 5, 2012
 *      Author: knad0001
 */

#ifndef Automat_H_
#define Automat_H_

typedef enum {
	STATE_INIT,
	STATE_INTEGER,
	STATE_IDENTIFIER,
	STATE_SIGN_COLON,
	STATE_SIGN_EQUALS_0,
	STATE_SIGN_EQUALS_1,
	STATE_SIGN_AND,
	STATE_COMMENT,
	STATE_COMMENT_END,
	STATE_UNKNOWN
} state;

typedef enum {
	NOTHING,
	ADD_CHAR,
	ADD_TOKEN_INTEGER,
	ADD_TOKEN_IDENTIFIER,
	ADD_TOKEN_SIGN,
	ADD_TOKEN_SIGN_UG0,
	ADD_TOKEN_SIGN_UG2,
	ADD_NEW_LINE,
	ADD_TOKEN_UKNOWN,
	DISCARD,
	END
} action;

class Automat {
public:
	Automat() { }
	action charEval(char c);
	state getCurrentState() const { return this->_currentState; }

protected:
	typedef enum {
		DIGIT,
		LETTER,
		SIGN,
		COLON,
		STAR,
		EQUALS,
		AND,
		SPACE,
		NEW_LINE,
		UNKNOWN,
		EOF
	} event;
	action stateEval(event e);

private:
	struct stateElement {
		state nextState;
		action actionToDo;
	};

	bool isSimpleSign(char const c) const;

	static char const _SimpleSigns[12];
	static stateElement const _StateMatrix[10][11];

	state _currentState = STATE_INIT;
};

#endif /* Automat_H_ */
