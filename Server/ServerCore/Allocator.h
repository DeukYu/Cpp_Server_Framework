#pragma once

/*-------------------
	BaseAllocator
-------------------*/
class BaseAllocator
{
	static	void*	Alloc(int32 size);
	static	void	Release(void* ptr);
};

/*-------------------
	StompAllocator
-------------------*/