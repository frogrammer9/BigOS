#include "memory_managment/address_space_manager.h"
#include "memory_managment/page_table.h"
#include "kernel_config.h"
#include "ram_map.h"
#include <stdbigos/buffer.h>
#include <stdbigos/string.h>

error_t address_space_managment_init(u16 max_asid) {

}

error_t address_space_create(as_handle_t* ashOUT) {

}

error_t address_space_destroy(as_handle_t* ash) {

}

error_t address_sapce_add_region(as_handle_t* ash, virt_mem_region_t region) {
	if(!ash->valid) {
		u8 flags = PTEF_VALID | PTEF_GLOBAL;
		ppn_t ppn = 0;
		error_t err = phys_mem_alloc_frame(PAGE_SIZE_4kB, &ppn);
		if(err) return err;
		void* page_table_page = physical_to_effective(ppn << 12);
		memset(page_table_page, 0, 0x1000);
		ash->root_pte = ppn;
	}
	void* curr_addr = region.addr;
	size_t size_left = region.size;
	phys_addr_t curr_map_addr = region.map_region.addr;

	u8 pt_height = 0;

	buffer_t pt_height_buffer = kernel_config_get(KERCFG_PT_HEIGHT);
	if(pt_height_buffer.error) return ERR_INTERNAL_FAILURE;
	const error_t err = buffer_read_u8(pt_height_buffer, 0, &pt_height);
	if(err) return ERR_INTERNAL_FAILURE;

	u8 flags = 0;
	if(region.read) flags |= PTEF_READ;
	if(region.write) flags |= PTEF_WRITE;
	if(region.execute) flags |= PTEF_EXECUTE;
	if(region.user) flags |= PTEF_USER;
	if(region.global) flags |= PTEF_GLOBAL;

	while(size_left > 0) {
		ppn_t ppn = 0;
		const size_t delta_size = 0x1000 << (9 * region.ps);
		if(region.mapped) {
			ppn = curr_map_addr >> 12;
			curr_map_addr += delta_size;
		}
		else {
			error_t err = phys_mem_alloc_frame(region.ps, &ppn);
			if(err) return err;
		}
		error_t err = page_table_add_entry(root_pte->ppn, pt_height, region.ps, (u64)curr_addr >> 12, ppn, flags);
		if(err) return err;
	}
	return ERR_NONE;
}

