#ifndef BIGOS_KERNEL_MEMORY_MANAGMENT_ADDRESS_SPACE_MANAGER
#define BIGOS_KERNEL_MEMORY_MANAGMENT_ADDRESS_SPACE_MANAGER

#include <stdbigos/error.h>
#include <stdbigos/types.h>

#include "memory_managment/physical_memory_manager.h"

typedef u32 asid_t;

typedef enum {
	PAGE_MODE_NORMAL,
	PAGE_MODE_HUGE,
	PAGE_MODE_GIGANTIC,
} page_mode_t;

typedef struct {
	bool mapped;
	bool read;
	bool write;
	bool execute;
	bool user;
	bool global;
	page_mode_t ps;
	void* addr;
	size_t size;
	phys_mem_region_t map_region;
} virt_mem_region_t;

typedef struct {
	bool user;
	bool global;
	bool valid;
	asid_t asid;
	ppn_t root_pte;
} as_handle_t;

[[nodiscard]] error_t address_space_managment_init(u16 max_asid);
[[nodiscard]] error_t address_space_create(as_handle_t* ashOUT);
[[nodiscard]] error_t address_space_destroy(as_handle_t* ash);
[[nodiscard]] error_t address_sapce_add_region(as_handle_t* ash, virt_mem_region_t region);
[[nodiscard]] error_t address_sapce_delete_region(as_handle_t* ash, virt_mem_region_t region);
[[nodiscard]] error_t address_space_resolve_page_fault(as_handle_t* ash, void* fault_addr, bool read, bool write,
                                                       bool execute);

#endif // !BIGOS_KERNEL_MEMORY_MANAGMENT_ADDRESS_SPACE_MANAGER

