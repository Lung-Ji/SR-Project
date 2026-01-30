#pragma once
#include "EditorWindow.h"
class Inspector : public EditorWindow {
public:
	Inspector();
	virtual ~Inspector();

public:
	virtual void Initialize()	{}
	virtual void Update()		{}
	virtual void Render()		{}
	virtual void OnEnable()		{}
	virtual void OnDisable()	{}
	virtual void OnDestroyed()	{}


};

