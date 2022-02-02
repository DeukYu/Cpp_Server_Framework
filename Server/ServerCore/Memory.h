#pragma once
#include "Allocator.h"

template <typename Type, typename... Args>
Type* xnew(Args&&... args)
{
	Type* memory = static_cast<Type*>(BaseAllocator::Alloc(sizeof(args)));
	new(memory)Type();	// placement new
	return memory;
}

template <typename Type>
void xdelete(Type* obj)
{
	obj->~Type();
	BaseAllocator::Release(obj);
}