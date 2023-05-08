#include <stdint.h>
#include "ASI_values.h"
#include "AjitThreadUtils.h"

int privilegesOk (uint8_t asi, uint8_t rwbar, uint8_t exec, uint8_t acc)
{
	int S = (asi == ASI_SUPERVISOR_INSTRUCTION) || (asi == ASI_SUPERVISOR_DATA);
	int U = (asi == ASI_USER_INSTRUCTION) || (asi == ASI_USER_DATA);
	int ret_val = 0;

	switch(acc) 
	{
                        case 0:  // read:read
				ret_val = rwbar && !exec;
				break;
                        case 1:  // read/write : read/write
                                ret_val = !exec;
				break;
                        case 2: // read/exec : read/exec
                                ret_val = rwbar || exec;
				break;
                        case 3: //  read/write/exec : read/write/exec
                                ret_val = 1;
				break;
                        case 4: // exec: exec
                                ret_val = exec;
				break;
                        case 5: // read : read/write
                                ret_val = (!exec) && (S || rwbar);
				break;
                        case 6: // no-acc  : read/exec
                                ret_val = (!U) && (rwbar || exec);
				break;
                        case 7: // no-acc : read/write/exec
                                ret_val = S;
				break;
			default:
				break;

	}
	return(ret_val && (S || U));
}
