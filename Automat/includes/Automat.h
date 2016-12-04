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

typedef struct {
	state nextState;
	action actionToDo;
} stateElement;


class Automat {

public:
	state _currentState = STATE_INIT;
	// Default ADD Token Action ungetChar(1);
	stateElement _stateMatrix[10][11] = {
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
			{ STATE_COMMENT, NOTHING },		// Event: NEW_LINE	('\n')
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

public:
	Automat();
	virtual ~Automat();
	action stateEval(event e);
	action charEval(char c);
	bool isSimpleSign(char c);

private:
	char signArray[12] = { '+', '-', '<', '>', '!', ';', '(', ')', '{', '}', '[', ']', }; // ( + | - | < | > | ! | ; | ( | ) | { | } | [ | ] )
};

#endif /* Automat_H_ */
