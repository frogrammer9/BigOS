#ifndef BIGOS_KERNEL_DEVICE_TREE_DTBLOB
#define BIGOS_KERNEL_DEVICE_TREE_DTBLOB

#include <stdbigos/error.h>
#include <stdbigos/types.h>

typedef struct {
	u32 magic;
	u32 total_size;
	u32 off_dt_struct;
	u32 off_dt_strings;
	u32 off_mem_rsvmap;
	u32 version;
	u32 last_comp_version;
	u32 boot_cpuid_phys;
	u32 size_dt_strings;
	u32 size_dt_struct;
} fdevtree_header_t;

typedef struct {
	fdevtree_header_t header;

} fdevtree_t;

typedef struct {

} fdevtree_meta_t;

typedef enum : u32 {
	FDT_BEGIN_NODE = 1,
	FDT_END_NODE = 2,
	FDT_PROP = 3,
	FDT_NOP = 4,
	//(yes there is a gap)
	FDT_END = 9,
} fdevtree_token_t;

typedef struct {
	u32 length;
	u32 nameoff;
} fdevtree_prop_metadata_t;

[[nodiscard]]
error_t devtree_blob_validate(fdevtree_t* dt, fdevtree_meta_t* dt_meta_out);



#endif //BIGOS_KERNEL_DEVICE_TREE_DTBLOB
