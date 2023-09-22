#pragma once

// Platform detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define ICS_PLATFORM_WINDOWS 1

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Windowsx.h>

#include <dxgi.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

#pragma warning(disable:4265)
#include <wrl.h>
#pragma warning(default:4265)

#ifndef _WIN64
#error "64 Bit is required"
#endif
#else 
#error "Unkown platform!"
#endif

#ifdef ICS_EXPORT
// Function exporting
#ifdef _MSC_VER
#define ICS_API __declspec(dllexport)
#else
#define ICS_API __attribute__((visibility("defualt")))
#endif
#else
// Function importing
#ifdef _MSC_VER
#define ICS_API __declspec(dllimport)
#else
#define ICS_API
#endif
#endif
