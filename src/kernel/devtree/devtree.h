#ifndef BIGOS_KERNEL_DEVTREE_DEVTREE
#define BIGOS_KERNEL_DEVTREE_DEVTREE

#include <stdbigos/error.h>
#include <stdbigos/types.h>

typedef struct {} devtree_reserved_region_t;
typedef struct {} devtree_memory_region_t;
typedef struct {} devtree_memory_mapped_region_t;

[[nodiscard]]
error_t devtree_get_reserved_regions_count(size_t* countOUT);

[[nodiscard]]
error_t devtree_get_reserved_regions(devtree_reserved_region_t* rregionsOUT);

[[nodiscard]]
error_t devtree_get_memory_regions_count(size_t* countOUT);

[[nodiscard]]
error_t devtree_get_memory_regions(devtree_memory_region_t* mregionsOUT);

[[nodiscard]]
error_t devtree_get_memory_mapped_regions_count(size_t* countOUT);

[[nodiscard]]
error_t devtree_get_memory_mapped_regions(devtree_memory_mapped_region_t* mmregionsOUT);

#endif
