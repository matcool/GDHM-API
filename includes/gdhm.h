#pragma once

#include <cinttypes>

#define GDHM_FN __cdecl

#if GDHM_API_IMPL == 1
	#define GDHM_API __declspec(dllexport)
#else
	#define GDHM_API __declspec(dllimport)
	#include <string>
#endif

namespace gdhm
{
	struct Vec2
	{
		float
			x = 0.f,
			y = 0.f;
		Vec2() { x = y = 0.f; }
		Vec2(const float _x, const float _y) : x(_x), y(_y) {}
		#ifdef GDHM_API_USE_IMGUI
		Vec2(const ImVec2& v) : x(v.x), y(v.y) {}
		#endif
	};

	struct control
	{
		std::string label;
		std::string info;
		bool active = false;
		uint8_t hotkey = 0;
		control(
			const std::string& __label,
			const std::string& __info = std::string(),
			const bool __active = false,
			const uint8_t __hotkey = 0,
			void* __on_init = nullptr)
			: label(__label)
			, info(__info)
			, active(__active)
			, hotkey(__hotkey)
		{
			if (__on_init) reinterpret_cast<void(GDHM_FN *)()>(__on_init)();
		}
	};

	#if GDHM_API_IMPL != 1

	#define gdhm_new_id																		\
		[]() -> int																			\
		{																					\
			static const auto salted = std::hash<std::string>{}(__TIME__) + __COUNTER__;	\
			return static_cast<int>(salted) ;												\
		}																					\
		
	// This will add a new window in GDHM

	GDHM_API void GDHM_FN add_mod_window(
		const char* name,
		const char* mod_file_name,
		const char* tag = nullptr,
		void* callback = nullptr,
		void* header = nullptr,
		void* footer = nullptr,
		bool* handle = nullptr,
		const bool constraint_height = false,
		const float max_height = 0.f);

	// These will add common controls

	GDHM_API void GDHM_FN add_label(
		const char* label);

	GDHM_API bool GDHM_FN add_checkbox(
		const int unique_id,
		const char* label,
		bool* value,
		uint8_t* hotkey = nullptr,
		void* on_activate = nullptr,
		const char* info = "",
		void* on_hotkey_set = nullptr);

	GDHM_API bool GDHM_FN add_checkbox(
		const int unique_id,
		control* __control,
		void* on_activate = nullptr,
		void* on_hotkey_set = nullptr);

	GDHM_API bool GDHM_FN add_button(
		const int unique_id,
		const char* label,
		uint8_t* hotkey = nullptr,
		void* on_activate = nullptr,
		const char* info = "",
		void* on_hotkey_set = nullptr);

	GDHM_API bool GDHM_FN add_button(
		const int unique_id,
		control* __control,
		void* on_activate = nullptr,
		void* on_hotkey_set = nullptr);

	GDHM_API bool GDHM_FN add_input_text(
		const int unique_id,
		char* buffer,
		const size_t buffer_size,
		void* on_release = nullptr,
		void* on_active = nullptr);

	GDHM_API bool GDHM_FN add_input_float(
		const int unique_id,
		float* value,
		const char* label_format = "%.3f",
		const float v_speed = 1.0f,
		const float v_min = 0.0f,
		const float v_max = 0.0f,
		void* on_release = nullptr,
		void* on_active = nullptr);

	GDHM_API bool GDHM_FN add_input_int(
		const int unique_id,
		int* value,
		const char* label_format = "%.3f",
		const float v_speed = 1.0f,
		const int v_min = 0,
		const int v_max = 0,
		void* on_release = nullptr,
		void* on_active = nullptr);

	// This will check whether the last item has just released
	GDHM_API bool GDHM_FN last_item_just_released();

	// These will manage window position
	GDHM_API void GDHM_FN set_window_position_x(const float x_value);
	GDHM_API void GDHM_FN set_window_position_y(const float y_value);
	GDHM_API void GDHM_FN set_window_position(const float x_value, const float y_value);
	GDHM_API Vec2 GDHM_FN get_window_position();

	// These will manage window size
	GDHM_API Vec2 GDHM_FN get_window_size();

	// This will check whether GDHM is loaded
	static inline bool GDHM_FN is_gdhm_loaded() { return GetModuleHandle(TEXT("ToastedMarshmellow.dll")); }

	// This will check the current GDHM version
	GDHM_API std::string GDHM_FN get_version();
	#endif
}

#undef GDHM_API
