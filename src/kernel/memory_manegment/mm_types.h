#ifndef BIGOS_KERNEL_MEMORY_MANAGMENT_MM_TYPES
#define BIGOS_KERNEL_MEMORY_MANAGMENT_MM_TYPES

#include <stdbigos/types.h>

typedef u64 vpn_t;
typedef u64 ppn_t;
typedef u64 phys_addr_t;
typedef void* virt_addr_t;

[[nodiscard]]
static inline phys_addr_t ppn_to_phys_addr(ppn_t ppn, u16 offset) {
	return (phys_addr_t)(ppn << 12) + (offset & 0xfff);
}

[[nodiscard]]
static inline ppn_t phys_addr_to_ppn(phys_addr_t addr) {
	return (uintptr_t)(addr >> 12);
}

[[nodiscard]]
static inline virt_addr_t vpn_to_virt_addr(vpn_t vpn, u16 offset) {
	return (void*)((uintptr_t)vpn << 12) + (offset & 0xfff);
}

[[nodiscard]]
static inline vpn_t virt_addr_to_vpn(virt_addr_t addr) {
	return (vpn_t)((uintptr_t)addr >> 12);
}

typedef enum : u8 {
	PAGE_SIZE_4kB = 0,   // kilo-page
	PAGE_SIZE_2MB = 1,   // mega-page
	PAGE_SIZE_1GB = 2,   // giga-page
	PAGE_SIZE_512GB = 3, // tera-page
	PAGE_SIZE_256TB = 4, // peta-page
} page_size_t;

[[nodiscard]]
static inline u64 page_size_get_in_bytes(page_size_t ps) {
	switch (ps) {
	case PAGE_SIZE_4kB:   return 0x1000ull;
	case PAGE_SIZE_2MB:   return 0x200000ull;
	case PAGE_SIZE_1GB:   return 0x40000000ull;
	case PAGE_SIZE_512GB: return 0x8000000000ull;
	case PAGE_SIZE_256TB: return 0x1000000000000ull;
	default:              return 0;
	}
}

typedef struct {
	phys_addr_t addr;
	size_t size;
} phys_mem_region_t;

typedef struct {
	bool mapped;
	bool read;
	bool write;
	bool execute;
	bool user;
	bool global;
	page_size_t ps;
	void* addr;
	size_t size;
	phys_mem_region_t map_region;
	const char* debug_comment;
} virt_mem_region_t;

void log_virt_mem_region(const virt_mem_region_t* vmr);

#endif // !BIGOS_KERNEL_MEMORY_MANAGMENT_MM_TYPES
