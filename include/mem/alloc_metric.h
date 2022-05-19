#include <memory>

struct AllocationMetrics
{
    private:
        uint32_t m_TotalAllocated;
        uint32_t m_TotalFreed;

    public:
        AllocationMetrics(const AllocationMetrics&) = delete;
        AllocationMetrics() : m_TotalAllocated(0), m_TotalFreed(0) {}

        uint32_t current_usage() const;
        void register_alloc(size_t size);
        void register_free(size_t size);
        void print_usage();

        static AllocationMetrics& instance();
};