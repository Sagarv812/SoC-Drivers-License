#include "MMU.hpp"
#include <cmath>

MMU::MMU(Memory& memory, Config& cfg)
	: mem(memory), config(cfg) {}

uint64_t MMU::translate(uint64_t vaddr){
	uint32_t offset = vaddr & (config.pageSize-1);
	int offsetBits = (int)log2(config.pageSize);
	vaddr = vaddr >> offsetBits;
	uint64_t pAddress = offset;
	int sumBits = 12;

	for(int i = config.pageTableLevels-1;i>=0;i--){
		uint32_t mask = (int)(pow(2, config.bitsPerLevel[i])-1);
		uint32_t index = vaddr & mask;
		vaddr = vaddr >> config.bitsPerLevel[i];
		try{
			pAddress = pAddress | (mem.getPageTableEntry(i, index).physicalFrame << sumBits);	
		}
		catch(const std::exception& e){
			bool user = false;
			if (i == config.pageTableLevels-1){
				user = true;
			}
			struct PageTableEntry p1 = {
				.physicalFrame = mem.nextAvailableFrame >> 12,
				.present = true,
				.user = user,
				.write = true
			};
			
			mem.setPageTableEntry(i, index, p1);
			mem.nextAvailableFrame += config.pageSize;
			pAddress = pAddress | (mem.getPageTableEntry(i, index).physicalFrame << sumBits);	
		}
		sumBits += config.bitsPerLevel[i];
	}
	return pAddress;
}

void MMU::storeVal(uint64_t vaddr, uint64_t val){

	uint64_t pAddress = translate(vaddr);

	mem.memory_contents[pAddress] = val;

}


uint64_t MMU::loadVal(uint64_t vaddr){
	
	uint64_t pAddress = translate(vaddr);
  
	return mem.memory_contents.at(pAddress);
}
