#include <debug/debug_stdio.h>
#include <stdbigos/types.h>

#include "stdbigos/error.h"
#include "virtual_memory/vmm.h"

/* Phisical memory ('|' - 2MB)
 *  _________
 * |         |
 * |         |
 * |         |
 * |         |
 * |         |
 * |         |
 * |         |
 * |         |
 *	   ...
 * |         |
 * |         | - Kernel stack
 * |         | - Kernel
 * |_________| - Kernel
 */

// NOTE: This is an example so far.
void kinit(u64 kernel_physical_address, u64 kernel_size, u64 stack_physical_address, u64 stack_size) {
	DEBUG_PRINTF("Kernel loaded at phisical address: 0x%lx (size: %luMB). Stack at: 0x%lx (size: %luMB)\n", kernel_physical_address, kernel_size >> 20, stack_physical_address, stack_size >> 20);
	error_t err = virtual_memory_init(VMS_DISABLE, 0);
	if(err)
		DEBUG_PRINTF("Error: %s\n", get_error_msg(err));
	else
		DEBUG_PRINTF("Virtual memory enabled, asidlen: %hu\n", get_asid_max_val());
}
