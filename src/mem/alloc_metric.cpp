#include <mem/alloc_metric.h>
#include <iostream>

uint32_t AllocationMetrics::current_usage() const 
{  
    return m_TotalAllocated - m_TotalFreed;
}

void AllocationMetrics::register_alloc(size_t size)
{
    m_TotalAllocated += size;
	std::cout << "Allocating " << size << " bytes. Total usage: " << current_usage() << " bytes" << std::endl;
}

void AllocationMetrics::register_free(size_t size)
{
    m_TotalFreed += size;
	std::cout << "Freeing " << size << " bytes. Total usage: " << current_usage() << " bytes" << std::endl;
}

void AllocationMetrics::print_usage()
{
	std::cout << "Current memory usage: " << current_usage() << " bytes" << std::endl;
}

static AllocationMetrics s_AllocationMetricInstance;
AllocationMetrics& AllocationMetrics::instance()
{
    return s_AllocationMetricInstance;
}