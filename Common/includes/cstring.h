/*
 * cstring.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */


#ifndef CUSTOMCSTRING_H_
#define CUSTOMCSTRING_H_

int __strcmp (char const * str1, char const * str2);
char * __strdup (char const * source);
unsigned int __strlen (char const *const data);
char * __strncpy ( char * destination, char const * source, unsigned int num);

#endif /* CSTRING_H_ */
