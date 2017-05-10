/*
 * TreeVisitorResult.h
 *
 *  Created on: May 9, 2017
 *      Author: boris
 */

#ifndef PARSER_INCLUDES_TREEVISITORTYPECHECKRESULT_H_
#define PARSER_INCLUDES_TREEVISITORTYPECHECKRESULT_H_

class TreeVisitorTypeCheckResult {
private:
	char const * _error = nullptr;

public:
	char const * getError() { return this->_error; }
	bool isFailed() {return !this->isSucceeded(); }
	bool isSucceeded() { return this->_error == nullptr; }
	void setError(char const * const error) { this->_error = error; }
};

#endif /* PARSER_INCLUDES_TREEVISITORTYPECHECKRESULT_H_ */
