#include "Memory.hpp"

Memory::Memory(Config& cf){
	pageTables.resize(cf.pageTableLevels);

	nextAvailableFrame = 0;

}

void Memory::setPageTableEntry(uint32_t level, uint32_t index, const PageTableEntry& entry){
	
	pageTables[level][index] = entry;

}

PageTableEntry Memory::getPageTableEntry(uint32_t level, uint32_t index) const{

	return pageTables[level].at(index);
	
}
