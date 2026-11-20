#pragma once
#include <string>

int compile(const std::string& buildType = "", bool force = false, bool quiet = false);
int clean();
