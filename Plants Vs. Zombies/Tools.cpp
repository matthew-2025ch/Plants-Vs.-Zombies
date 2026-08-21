#include"Tools.hpp"
auto Tools::UTF82Wide(const char* str) -> std::wstring {
	if (!str) {
		return L"";
	}
	int size = MultiByteToWideChar(CP_UTF8, 0, str, -1, nullptr, 0);
	std::wstring res(size, L'\0');
	MultiByteToWideChar(CP_UTF8, 0, str, -1, res.data(), size);
	res.pop_back();
	return res;
}