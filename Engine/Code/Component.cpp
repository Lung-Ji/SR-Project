#include "Component.h"

Component::Component()							: GRPDEV(nullptr)		,CLONE(FALSE)	{					}
Component::Component(LPDIRECT3DDEVICE9 _GRPDEV) : GRPDEV(_GRPDEV)		,CLONE(FALSE)	{ GRPDEV->AddRef(); }
Component::Component(const Component& _RHS)		: GRPDEV(_RHS.GRPDEV)	,CLONE(TRUE)	{ GRPDEV->AddRef(); }
Component::~Component()																	{					}