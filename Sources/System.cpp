#include"Def.h"
#include"System.h"
namespace mySystem {
	void Initialize() {
		Window::Resize(Size(SystemNum::WindowWidth,SystemNum::WindowHeight));
	}
	Point GetViewportPoint(float x,float y) {
		return Point(int(SystemNum::WindowWidth*x),int(SystemNum::WindowHeight * y));
	}
}
