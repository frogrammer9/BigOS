#ifndef _KERNEL_VIRTUAL_MEMORY_VMM_H_
#define _KERNEL_VIRTUAL_MEMORY_VMM_H_

#include <stdbigos/error.h>
#include <stdbigos/types.h>

#include "mm_common.h"

typedef enum : u8 {
	VMS_BARE = 0,
	VMS_Sv39 = 8,
	VMS_Sv48 = 9,
	VMS_Sv57 = 10,
	VMS_Sv64 = 11, // NOTE: RISC-V ISA does not specify Sv64 yet (29-03-2025)
} virt_mem_scheme_t;

typedef enum : u8 {
	PTEP_R = 0x01,
	PTEP_W = 0x02,
	PTEP_X = 0x04,
	PTEP_U = 0x08,
	PTEP_G = 0x10,
	PTEP_S = 0x20,
	PTEP_NOT_YET_DEFINES = 0x40,
} page_table_entry_perms_t;
/* (* is an OS reserved bit not yet defines)
 * page_talbe_entry_perms_t structure:
 * u8[0*SGUXWR]
 * perms structure required by RISC-V ISA:
 * u10[*SDAGUXWRV] (D, A and V bits will be always initialized to 0, 0 and 1 so there's no need to specify them)
 */

typedef u16 asid_t;
typedef u64 virt_addr_t;
typedef u64 page_table_entry_t;
/* (03-04-2025)
 * page table entry:
 * |N|PBMT|Reserved|PPN|RSW|D|A|G|U|X|W|R|V|
 * |1| 2  |    7   | 44| 2 |1|1|1|1|1|1|1|1|
 * where:
 * N - reserved by Svnapot extension (must be 0 otherwise)
 * PBMT - reserved by Svpbmt extension (must be 0 otherwise)
 * Reserved - reserved for future standard use (must be 0)
 * PPN - is the phisical page number, it is split into 3(Sv39), 4(Sv48) or 5(Sv57) levels (PPN[0] - PPN[4])
 * RSW - reserved for use by supervisor software (OS)
 * D - dirty bit (has this page been writted to?)
 * A - accessed bit (has this page been accessed?)
 * G - global bit (is this page accessable from multiple address spaces?)
 * U - user bit (can this page be accessed in U-mode?)
 * X - execute permission bit (can data from this page be executed?)
 * W - write permission bit (can data be written to this page?)
 * R - read permission bit (can data be read from this page?)
 * V - valid bit (is this page table entry valid?)
 * further information is avalible here:
 * https://drive.google.com/file/d/17GeetSnT5wW3xNuAHI95-SI1gPGd5sJ_/view
 */

[[nodiscard]] error_t virtual_memory_init(void* RAM_start);
[[nodiscard]] error_t virtual_memory_enable(virt_mem_scheme_t vms, asid_t asid);
[[nodiscard]] error_t virtual_memory_disable();

[[nodiscard]] asid_t get_asid_max_val();
[[nodiscard]] virt_mem_scheme_t get_active_virt_mem_scheme();
[[nodiscard]] const char* get_virt_mem_scheme_str_name(virt_mem_scheme_t vms);

[[nodiscard]] error_t create_page_table(asid_t asid, bool saint);
[[nodiscard]] error_t destroy_page_table(asid_t asid);
[[nodiscard]] error_t add_page_table_entry(asid_t asid, page_size_t page_size, virt_addr_t vaddr, phys_addr_t paddr, page_table_entry_perms_t perms);
[[nodiscard]] error_t get_page_table_entry(asid_t asid, virt_addr_t vaddr, page_table_entry_t** pteOUT);
[[nodiscard]] error_t remove_page_table_entry(asid_t asid, virt_addr_t vaddr);
[[nodiscard]] error_t resolve_page_fault();

#endif //_KERNEL_VIRTUAL_MEMORY_VMM_H_
