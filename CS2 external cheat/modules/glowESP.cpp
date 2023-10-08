#include "../memory.h"
#include <thread>
#include <iostream>

namespace offsets
{
	constexpr auto localPlayer = 0x187AC48;
	//constexpr auto flags = 0x104;
	//constexpr auto forceJump = 0x526B590;
	constexpr auto entityList = 0x17888D8;
	constexpr auto glowObjectManager = 0x5309C78;
	constexpr auto teamNum = 0xF4;
	constexpr auto glowIndex = 0x10488;
}

__declspec(align(16)) struct Color
{
	constexpr Color(const float r, const float g, const float b, const float a = 1.f) noexcept :
		r(r), g(g), b(b), a(a) { }

	float r, g, b, a;
};

int main()
{
	const auto mem = Memory("csgo.exe");

	std::cout << "csgo found!" << std::endl;

	const auto client = mem.GetModuleAddress("client.dll");
	std::cout << "client.dll -> " << "0x" << std::hex << client << std::dec << std::endl;

	constexpr const auto color = Color{ 1.f, 0.f, 1.f };

	while (true)
	{
        for (int i = 1; i < 64; i++)
        {
            uintptr_t entity_list = mem.Read<std::uintptr_t>(client + offsets::p_entity_list);
            if (!entity_list)
                continue;

            uintptr_t list_entry = mem.Read<std::uintptr_t>(entity_list + (8 * (i & 0x7FFF) >> 9) + 16);
            if (!list_entry)
                continue;

            uintptr_t player = mem.Read<std::uintptr_t>(list_entry + 120 * (i & 0x1FF));
            if (!player)
                continue;

            uint32_t player_pawn = memory_read<uint32_t>(player + offsets::m_h_player_pawn);

            uintptr_t list_entry2 = mem.Read<std::uintptr_t>(entity_list + 0x8 * ((player_pawn & 0x7FFF) >> 9) + 16);
            if (!list_entry2)
                continue;

            uintptr_t p_cs_player_pawn = mem.Read<std::uintptr_t>(list_entry2 + 120 * (player_pawn & 0x1FF));
            if (!p_cs_player_pawn)
                continue;

            if (!glow_enabled)
                memory_write<float>(cs2_process_handle, p_cs_player_pawn + offsets::m_fl_detected_by_enemy_sensor_time, 0.f); // off
            else
                memory_write<float>(cs2_process_handle, p_cs_player_pawn + offsets::m_fl_detected_by_enemy_sensor_time, 86400.f); // on
        }

	}
}