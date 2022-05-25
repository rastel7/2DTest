#pragma once
#include"Def.h"
class InputManager;

using IM = InputManager;

struct InputAssembly {
	bool Left=0, Right=0, Up=0, Down=0, Jump=0, Start=0,Ok=0;
};
enum PadButtonNumber {
	Down=12,
	Left=13,
	Up=10,
	Right=11,
	Jump=0,
	Ok=1,
	Start=7,
};
class InputManager {
	void UpdatePadInput(InputAssembly& inputasm);
	std::vector<InputAssembly> m_previnput;
	void Add(InputAssembly _gp);
public:
	InputManager();
	const static unsigned int MAX_PREV_SIZE=60;
	bool GetPressed(PadButtonNumber pad_num,InputAssembly const& input_asm) const;
	bool GetPressed(PadButtonNumber pad_num) const;
	bool GetEdgePressed(PadButtonNumber pad_num) const;
	void Update();
	void DebugDraw() const;//画面上にパッド入力を表示
};
