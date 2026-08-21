#include"common.hpp"
class Tools {
public:
	Tools() = delete;
	~Tools() = delete;
	static auto UTF82Wide(const char* str) -> std::wstring;
};