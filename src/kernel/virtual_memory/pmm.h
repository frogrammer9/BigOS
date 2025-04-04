#ifndef _KERNEL_VIRTUAL_MEMORY_PMM_H_
#define _KERNEL_VIRTUAL_MEMORY_PMM_H_

#include <stdbigos/error.h>
#include <stdbigos/types.h>

#include "mm_common.h"

[[nodiscard]] error_t alloc_frame(page_size_t psize, phys_addr_t* paddrOUT);
void free_frame();

#endif //!_KERNEL_VIRTUAL_MEMORY_PMM_H_
