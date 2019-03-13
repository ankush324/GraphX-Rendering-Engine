#pragma once

namespace engine
{
	// Macro to bind the class event functions
#define BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)

	// Time of the day and Coresponding hours
	enum DayTime
	{
		GX_START = 0,
		GX_EARLY_MORNING = 3,
		GX_SUNRISE = 6,
		GX_MORNING = 9,
		GX_NOON = 12,
		GX_AFTERNOON = 15,
		GX_EVENING = 18,
		GX_NIGHT = 21
	};

	class EngineUtil
	{
		/* Convertor to convert between normal and wide strings */
		static std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> s_StringConvertor;

	public:
		/* Returns a byte string from the WideString */
		static std::string ToByteString(const std::wstring& WideString);

		/* Returns a wide string from the ByteString */
		static std::wstring ToWideString(const std::string& ByteString);
	};
}