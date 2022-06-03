#include"Def.h"
#include"../Headers/InputManager.h"

InputManager::InputManager() {
	//空状態だと押されたかの判定にこまる
	for (int i = 0; i < MAX_PREV_SIZE; ++i) {
		Add(InputAssembly());
	}
}
void InputManager::Add(InputAssembly gp) {
	while (m_previnput.size() >= MAX_PREV_SIZE) {
		m_previnput.pop_back();
	}
	m_previnput.insert(m_previnput.begin(), gp);
}

void InputManager::Update() {
	InputAssembly inputasm;
	UpdatePadInput(inputasm);
	Add(inputasm);
}

void InputManager::UpdatePadInput(InputAssembly& input_asm) {
	if(const auto gamepad = Gamepad(0)) {
		input_asm.Down |= gamepad.buttons[PadButtonNumber::Down].pressed();
		input_asm.Up |= gamepad.buttons[PadButtonNumber::Up].pressed();
		input_asm.Left |= gamepad.buttons[PadButtonNumber::Left].pressed();
		input_asm.Right |= gamepad.buttons[PadButtonNumber::Right].pressed();
		input_asm.Jump |= gamepad.buttons[PadButtonNumber::Jump].pressed();
		input_asm.Start |= gamepad.buttons[PadButtonNumber::Start].pressed();
		input_asm.Ok |= gamepad.buttons[PadButtonNumber::Ok].pressed();
		if(gamepad.axes.size() >= 4) {
			input_asm.RightPad.x = gamepad.axes.at(3);
			input_asm.RightPad.y = gamepad.axes.at(4);
		}
		else {
			Print << U"ゲームパッドの軸が足りていません";
		}
		Print << input_asm.RightPad;
	}
	const char32_t str[] = U"hoge";
	return;
}
//引数にinputasmを取るとそれに対して入力検知
bool InputManager::GetPressed(PadButtonNumber pad_num, InputAssembly const& input_asm) const{
	switch (pad_num)
	{
	case Down:
		return input_asm.Down;
		break;
	case Left:
		return input_asm.Left;
		break;
	case Up:
		return input_asm.Up;
		break;
	case Right:
		return input_asm.Right;
		break;
	case Jump:
		return input_asm.Jump;
		break;
	case Start:
		return input_asm.Start;
		break;
	case Ok:
		return input_asm.Ok;
	default:
		break;
	}
	return false;
}
bool InputManager::GetPressed(PadButtonNumber pad_num) const {
	return GetPressed(pad_num, m_previnput[0]);
}
bool InputManager::GetEdgePressed(PadButtonNumber pad_num) const {
	auto now = GetPressed(pad_num, m_previnput[0]);
	auto prev = GetPressed(pad_num, m_previnput[1]);
	return(now&&(!prev));
}

void InputManager::DebugDraw() const {
	//押されているボタンの名前をsetに格納
	std::set<String> pressed_button;
	if (GetPressed(PadButtonNumber::Down)) pressed_button.insert(U"Down");
	if (GetPressed(PadButtonNumber::Jump)) pressed_button.insert(U"Jump");
	if (GetPressed(PadButtonNumber::Left)) pressed_button.insert(U"Left");
	if (GetPressed(PadButtonNumber::Right)) pressed_button.insert(U"Right");
	if (GetPressed(PadButtonNumber::Start)) pressed_button.insert(U"Start");
	if (GetPressed(PadButtonNumber::Up)) pressed_button.insert(U"Up");
	if (GetPressed(PadButtonNumber::Ok)) pressed_button.insert(U"Ok");
	//描画
	for (auto name : pressed_button) {
		Print << U"{}"_fmt(name);
	}
}

Vec2 InputManager::GetRightPad() const {
	return m_previnput[0].RightPad;
}
