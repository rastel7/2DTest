#include"Def.h"
#include"System.h"
namespace mySystem {
	void Initialize() {
		Window::Resize(Size(SystemNum::WindowWidth,SystemNum::WindowHeight));
	}
	Point GetViewportPoint(float x,float y) {
		return Point(int(SystemNum::WindowWidth*x),int(SystemNum::WindowHeight * y));
	}
	std::vector<String> split(String _str, char32_t deli) {
		std::vector<String> ret;
		String buf;
		for (auto c : _str) {
			if (c == deli) {
				if (!buf.isEmpty()) {
					ret.emplace_back(buf);
				}
				buf.clear();
			}
			else {
				buf += c;
			}
		}
		if (!buf.isEmpty()) {
			ret.emplace_back(buf);
		}
		return ret;
	}


}
