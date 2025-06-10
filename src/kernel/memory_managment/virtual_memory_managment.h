#ifndef BIGOS_KERNEL_MEMORY_MANAGMENT_VIRTUAL_MEMORY_MANAGMENT
#define BIGOS_KERNEL_MEMORY_MANAGMENT_VIRTUAL_MEMORY_MANAGMENT

#include <stdbigos/types.h>

#include "memory_managment/physical_memory_manager.h"

[[nodiscard]] u16 virt_mem_get_max_asid();
void virt_mem_set_satp(u16 asid, u8 vms, ppn_t page_table);

#endif // !BIGOS_KERNEL_MEMORY_MANAGMENT_VIRTUAL_MEMORY_MANAGMENT
