#pragma once

enum struct MemoryType : unsigned int
{
	UNKNOWN = 0,
	USER_OWNED,
	ICS_ARRAY,
	ICS_DARRAY,
	ICS_STRING,
	ICS_TEXTURE,
	ICS_RENDERER,
	ICS_MODEL,
	ICS_SCENE,
	ICS_APPLICATION,
	MAX_TERMS
};