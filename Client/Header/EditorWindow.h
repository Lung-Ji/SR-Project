#pragma once
class EditorWindow {

public:
	enum WINDOW_STATE { DISABLE, ACTIVE, DESTROYED };

public:
	EditorWindow() : Flags(ImGuiWindowFlags_None) {}
	virtual ~EditorWindow() {}

public:
	virtual void Initialize();
	virtual void Update()	;
	virtual void Render()	;
	virtual void OnEnable()	;
	virtual void OnDisable();
	virtual void OnDestroyed();

public:
	//ImGuiWindowFlags	Get_Flags() { return Flags; }
	//
	//WINDOW_STATE		Get_WindowState() { return State; }
	//VOID				Set_WindowState(WINDOW_STATE _State) { State = _State; }
	//
	//ImVec2				Get_WindowSize()	{ return Size; }
	//VOID				Set_WindowSize(ImVec2 _Size) { Size = _Size; }
	
	//VOID				Set_Name(const string& _Name)	{ mName = _Name; }
	//string&				Get_Name()						{ return mName; }

private:
	ImGuiWindowFlags Flags;
	WINDOW_STATE	 State;
	ImVec2			 Size;

	//string			mName;
};

