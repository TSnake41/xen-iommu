#define __HYPERVISOR_iommu_op 43
static inline int
HYPERVISOR_iommu_op(void *arg, unsigned int count)
{
	return _hypercall2(int, iommu_op, arg, count);
}