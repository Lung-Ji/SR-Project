#pragma once

class _declspec(dllexport) Base abstract {
protected:
	inline explicit Base();
	inline virtual ~Base();

public:
	inline unsigned long AddRef();
	inline unsigned long Release();

protected:
	unsigned	long		ReferenceCount;

public:
	inline virtual void		Free() = 0;
};

#include "Base.inl"