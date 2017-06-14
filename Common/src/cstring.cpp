#include "../includes/cstring.h"

char * strcat(char const * str1, char const* str2) {
	if (str1 == nullptr || str2 == nullptr) {
		return nullptr;
	}

	auto str1len = strlen(str1);
	auto str2len = strlen(str2);

	char *destination = new char[str1len + str2len + 1];
	strncpy(destination, str1, str1len+1);
	strncpy(destination + str1len , str2, str2len+1);

	return destination;
}

int strcmp(char const * str1, char const * str2) {
		if (str1 == nullptr || str2 == nullptr)
			return str1 == str2;

		for(; *str1 == *str2; str1++, str2++) {
			if (*str1 == '\0')
				return 0;
		}
		return *str1 - *str2;
}

char * strdup (char const * source) {
	auto length = strlen(source) + 1;

	char *destination = new char[length];
	strncpy(destination, source, length);

	return destination;
}

unsigned int strlen (char const *const data) {
	unsigned int result = 0;
	if (data != nullptr)
		while(data[result] != '\0') result++;

	return result;
}

char * strncpy ( char * destination, char const * source, unsigned int num) {
	if (source == nullptr)
		return nullptr;

	bool padding = false;
	for (unsigned int i = 0; i < num; i++) {
	    if (source[i] == '\0')
	    	padding = true;

	    destination[i] = padding ? '\0' : source[i];
	}

	return destination;
}
