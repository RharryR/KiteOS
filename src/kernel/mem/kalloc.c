// kalloc.c
// Written by Harry Rigg
// Kernel memory allocator

#include <kernel/mem/kalloc.h>

void 
kalloc_init(void* mmloc, unsigned long mmsize)
{
	memory_map_entry_t* current_map = (memory_map_entry_t*) mmloc;
	
	memzone_t* last_looped;
	memzone_t* last_free;
	size_t last_size;
	int i=0;
	while(current_map < mmloc + mmsize)
	{
		if(current_map->type == 1)
		{
			memzone_t* append;
			append = (void*)current_map->base;
			append->flags =0;
			append->prev_h=last_looped;
			last_looped->next_h = append;
			last_looped = (void*) append;
			last_free = (void*) append;
			last_size = current_map->len;
			i++;
		}else{
			memzone_t* append = (void*)current_map->base;
			append->flags = 1;
			append->prev_h = last_looped;
			last_looped->next_h = append;
			last_looped = (void*) append;
		}
		current_map = (memory_map_entry_t*) ((uint32_t)current_map + current_map->size + sizeof(uint32_t));
	}
	// Add a EOM (End Of Memory) header at the end of the free memory
	memzone_t* eom = (void*) last_free + last_size - sizeof(memzone_t);
	// Set the flags to EOM
	eom->flags = 3;
	eom->next_h =0;
	eom->prev_h = last_free->prev_h;
	last_free->next_h = eom;
	return;
}

void* 
kmalloc(size_t size)
{
	memzone_t* this = (memzone_t*)0x0;
	for(int i; 1; i++)
	{	
		// Used?
		if(this->flags==1){
			this = (void*)this->next_h;
			continue;	// Already used
		}
		
		// End of memory?
		if(this->flags==3)
		{
			break;
		}
		
		// Big enough?
		if((this->next_h - (size_t)this) - sizeof(memzone_t) < size){
			this = (void*)this->next_h;
			continue;	// Too small
		}
		
		// This area of memory suits our needs
		
		// Create new header for the area left over
		memzone_t* split = (void*)this + sizeof(memzone_t) + size;
		split->flags = 0;
		split->prev_h = (void*)this;
		split->next_h = (void*)this->next_h;
		
		// Adjust some of this headers properties
		this->flags = 1;
		this->next_h = split;
		return (void*)this+sizeof(memzone_t);	
	}
	return (void*)-1;
}

void*
kcalloc(size_t size)
{
	void* ptr = kmalloc(size);
	memset(ptr, 0, size);
	return ptr;
}

void*
krealloc(void* ptr, size_t nsize)
{
	void* nptr = kmalloc(nsize);
	if(nptr == -1)
		return (void*)-1;
	memzone_t* fmz = (void*) ptr - sizeof(memzone_t);
	size_t this_size = (fmz->next_h - (size_t)fmz) - sizeof(memzone_t);
	memcpy(nptr, ptr, this_size);
	kfree(ptr);
	return nptr;
}

void 
kfree(void* alloc)
{
	memzone_t* this = (void*)alloc-sizeof(memzone_t);
	
	memzone_t* next = (void*) this->next_h;
	if(next->flags==1)
	{
		this->flags = 0;
		return;
	}
	
	while(1)
	{
		next = (void*) next->next_h;
		if(next->flags == 3)
			break;
		if(next->flags == 1)
			break;
	}
	this->next_h = (void*)next;
	this->flags = 0;
}
