#include "validation.h"


/*int valid_string (char * string)
{
	int counter;
	int valid = TRUE;

	for (counter = 0 ; *(string + counter) != ; ++counter)
	{
		if ( ( *(string + counter) != ON ) && (*(string + counter) != OFF)) 
		{
			valid = FALSE;
		}
	}

	return valid;
}*/
/*
int valid_string_length (char * string, char puerto)
{
	int counter, valid = TRUE;
	for (counter = 0 ; *(string + counter) != 0 ; ++counter)
	{
	}
	--counter;

	if ( (counter > 7) && (puerto != 'd') )
	{
		valid = FALSE;
	}

}

int valid_char (char input, char verification)
{
	int valid;

	switch (input)
	{
		case verification : valid = TRUE;
		default : valid = FALSE;
	}

	return valid;
}
*/
int op_valid (char input)
{
	int value;
	switch(input)
	{
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case 'c': case 's': case 'b': case 'f': case 27: value = TRUE; break;
		default : value = FALSE; break;
	}
	return value; 
}