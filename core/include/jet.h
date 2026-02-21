#pragma once

#include <cstdint>

namespace jet {

bool initialize();
void shutdown();

// Types
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using usize = std::size_t;
using isize = i64;

// Window
struct WindowDesc {
    u32 width = 800;
    u32 height = 800;
    const char* title = "Default Title";
};

using NativeWindowHandle = void*;

struct Window {
    u32 width;
    u32 height;
    const char* title;
    NativeWindowHandle handle;
};

Window* initWindow(const WindowDesc& desc);
void deinitWindow(Window* window);

};
