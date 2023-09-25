#pragma once

enum struct MemoryType : unsigned int
{
	UNKNOWN = 0,
	ICS_SCENE,
	ICS_MODEL,
	ICS_SHADER,
	ICS_TEXTURE,
	ICS_RENDERER,
	ICS_ARRAY,
	ICS_DARRAY,
	ICS_STRING,
	ICS_APPLICATION,
	USER_OWNED,
	MAX_TERMS
};