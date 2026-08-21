#pragma once
#include"common.hpp"
class Logger final {
public:
	Logger() = delete;
	~Logger() = delete;
	static auto Initialize() -> void;
	static auto Flush() -> void;
};