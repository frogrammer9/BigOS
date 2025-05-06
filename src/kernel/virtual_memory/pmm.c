#include "pmm.h"
#include "kmalloc.h"

#include <debug/debug_stdio.h>
/*
*/

// TODO: replace those functons with stdbit.h
static int first_zero_bit_index(u64 x) {
	for(int i = 0; i < 64; ++i) {
		if(((x >> i) & 1) == 0) return i;
	}
	return -1;
}
//ENDTODO

static u64* kilo_page_frame_bitmap = nullptr;
static u16* subpage_busy_counter[5] = { nullptr, nullptr, nullptr, nullptr, nullptr }; //[0] is always null for consistant indexing
static u64 page_frame_amount[5] = {0};

error_t initialize_pmm(virtual_memory_scheme_t vms, u64 ram_size) {
	for(u8 i = 0; i < vms + 3; ++i) {
		const i64 shift = 30 - 12 - i * 9; //(* sizeof(gb)) (/ 4 * sizeof(kb)) (/ sizeof(page_size[i]))
		const u64 size = ((shift < 0) ? (ram_size >> -shift) : ram_size << shift);
		page_frame_amount[i] = size;
		error_t err = ERR_NONE;
		if(i == 0) {
			const u64 ceil_div_size_64 = (size + 63) >> 6;
			err = kmalloc(ceil_div_size_64 * sizeof(u64), (void*)&kilo_page_frame_bitmap);
		}
		else {
			err = kmalloc(size * sizeof(u16), (void*)&subpage_busy_counter[i]);
		}
		if(err) {
			if(kilo_page_frame_bitmap) kfree(kilo_page_frame_bitmap);
			for(u8 j = 0; j < 5; ++j) {
				if(subpage_busy_counter[j]) kfree(subpage_busy_counter[j]);
				page_frame_amount[j] = 0;
			}
			return ERR_CRITICAL_INTERNAL_FAILURE;
		}
	}
	return ERR_NONE;
}

error_t allocate_page_frame(page_size_t page_size, ppn_t* ppnOUT) { // TODO:
	
}

error_t free_page_frame(ppn_t ppn) { // TODO:
	return ERR_NONE;
}

error_t set_phisical_memory_region_busy(ppn_t ppn, u64 size_in_bytes) { // TODO:
	return ERR_NONE;
}
