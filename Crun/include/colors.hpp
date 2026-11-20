#pragma once

namespace Color {
    inline constexpr const char* Reset       = "\033[0m";
    inline constexpr const char* Bold        = "\033[1m";
    inline constexpr const char* Dim         = "\033[2m";
    inline constexpr const char* Italic      = "\033[3m";
    inline constexpr const char* Underline   = "\033[4m";

    inline constexpr const char* Red         = "\033[31m";
    inline constexpr const char* Green       = "\033[32m";
    inline constexpr const char* Yellow      = "\033[33m";
    inline constexpr const char* Blue        = "\033[34m";
    inline constexpr const char* Magenta     = "\033[35m";
    inline constexpr const char* Cyan        = "\033[36m";
    inline constexpr const char* White       = "\033[37m";

    inline constexpr const char* BoldRed     = "\033[1;31m";
    inline constexpr const char* BoldGreen   = "\033[1;32m";
    inline constexpr const char* BoldYellow  = "\033[1;33m";
    inline constexpr const char* BoldBlue    = "\033[1;34m";
    inline constexpr const char* BoldMagenta = "\033[1;35m";
    inline constexpr const char* BoldCyan    = "\033[1;36m";
    inline constexpr const char* BoldWhite   = "\033[1;37m";
}
