
#include "HelperFn.h"


bool IsValue(string input)
{
	// checks if the input string is a double value
	// return true if it's double value, false otherwise

	// Double values can be: 12.5, -12.5, -23, -23. , -23.0 …etc.


	int numdecimal = 0;
	int numposorneg = 0;
	int numdig = 0;

	for (int i = 0; i < (int)input.size(); i++)
	{
		// check invalid chars
		if ((input[i] < 48 || input[i] > 57) && input[i] != '-' && input[i] != '+' && input[i] != '.')
		{
			//if(input[i]==' ' && numdig>0)   ///check for spaces at begin of string if needed ///
			return false;
		}
		if ((input[i] >= 48 && input[i] <= 57)) // count digits
		{
			numdig++;
		}
		// check index and no. of the sign
		if (input[i] == '-' || input[i] == '+')    
		{
			if (i != 0)
			{
				return false;
			}
			numposorneg++;
		}

		// check no. of dots
		if (input[i] == '.')
		{
			numdecimal++;
		}
	}

	// end of for loop
	if (numdig == 0) {
		return false;
	}

	if (numdecimal > 1 || numposorneg > 1) {
		return false;
	}

	return true;
}

bool IsVariable(string input)
{
	// checks if the input string is a variable name
	// return true if it can be a variable name, false otherwise

	// Variable names must start with an alphabetic letter (small or capital) or an underscore (_). 
	// After the first initial letter, variable names can contain letters, numbers and underscores.  
	// No spaces or special characters, however, are allowed.

	


	// check first char
	if (input[0] != '_' && !isalpha(input[0]))
	{
		return false;
	}


	for (int i = 1; i < (int)input.size(); i++)
	{
		if (!isalnum(input[i]) && input[i] != '_')
		{
			return false;
		}
	}

		return true;

}


OpType ValueOrVariable(string input)
{
	// checks if the input string is a double value or a variable name
	// and returns enum "OpType" (the enum is declared in the .h)


	if(IsVariable(input)) 
	{
		return VARIABLE_OP;
	}

	else if (IsValue(input))
	{
		return VALUE_OP;
	}
	else 
	{
		return INVALID_OP;
	}
}
