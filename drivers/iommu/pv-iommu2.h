/*
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef __XEN_PUBLIC_PV_IOMMU_H__
#define __XEN_PUBLIC_PV_IOMMU_H__

#define IOMMU_DEFAULT_CONTEXT (0)

/**
 * Allocate an IOMMU context, the new context handle will be written to ctx_no.
 */
#define IOMMUOP_alloc_context         2

/**
 * Destroy a IOMMU context.
 * All devices attached to this context are reattached to default context.
 *
 * The default context can't be destroyed (0).
 */
#define IOMMUOP_free_context          3

/**
 * Reattach the device to IOMMU context.
 */
#define IOMMUOP_reattach_device       4

#define IOMMUOP_map_page              5
#define IOMMUOP_unmap_page            6

struct pv_iommu_op {
    uint16_t subop_id;
    uint16_t ctx_no;

/**
 * Create a context that is cloned from default. 
 * The new context will be populated with 1:1 mappings covering the entire guest memory.
 */
#define IOMMU_CREATE_clone (1 << 0)

#define IOMMU_OP_readable (1 << 0)
#define IOMMU_OP_writeable (1 << 1)
    uint32_t flags;

    union {
        struct {
            uint64_t gfn;
            uint64_t dfn;
        } map_page;

        struct {
            uint64_t dfn;
        } unmap_page;

        struct {
            struct physdev_pci_device dev;
        } reattach_device;
    };
};

typedef struct pv_iommu_op pv_iommu_op_t;
DEFINE_GUEST_HANDLE_STRUCT(pv_iommu_op_t);

#endif

/*
 * Local variables:
 * mode: C
 * c-file-style: "BSD"
 * c-basic-offset: 4
 * tab-width: 4
 * indent-tabs-mode: nil
 * End:
 */