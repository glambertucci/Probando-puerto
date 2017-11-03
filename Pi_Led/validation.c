#include "validation.h"

int op_valid (char input)
{
	int value;
	switch(input)
	{
            //case B_0 : 
            case B_1 : 
            case B_2 : 
            case B_3: 
            case B_4: 
            case B_5: 
            case B_6: 
            case B_7: 
            case ALLOFF : 
            case ALLON : 
            case INTERMITENCE : 
            case MASKON : 
            case MASKOFF : 
            case MASKTOGGLE:
            case ENDOFPROGRAM : 
                value = TRUE; 
                break;
		default : value = FALSE; break;
	}
	return value; 
}

int check_mask (char * mask_array, int max_bits)
{
	int i, mask;
	for (i=0 ; i < max_bits ; ++i)
	{
		if (i == 0)
		{
			mask = TRUE;
		}
		if ((*(mask_array + i) != '0') && (*(mask_array + i) != '1'))
		{
			mask = FALSE;
		}
	}
	return mask;
}

