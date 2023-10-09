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
	constexpr auto dwPawnHealth = 0x808;
}



int main()
{
	const auto mem = Memory("cs2.exe");

	std::cout << "csgo found!" << std::endl;

	const auto client = mem.GetModuleAddress("client.dll");
	std::cout << "client.dll -> " << "0x" << std::hex << client << std::dec << std::endl;

	const auto entity_list = mem.Read<std::uintptr_t>(client + offsets::entityList); //process->read<uintptr_t>(base_module.base + updater::offsets::dwEntityList);
	int playerIndex = 1;

	for (int i = 1; i < 32; i++) {
		const auto list_entry = mem.Read<std::uintptr_t>(entity_list + (8 * (playerIndex & 0x7FFF) >> 9) + 16); //(entity_list + (8 * (playerIndex & 0x7FFF) >> 9) + 16);
		const auto player = mem.Read<std::uintptr_t>(list_entry + 120 * (playerIndex & 0x1FF));//process->read<uintptr_t>(list_entry + 120 * (playerIndex & 0x1FF));
		const auto playerHealth = mem.Read<std::uint32_t>(player + offsets::dwPawnHealth);//process->read<int>(player + updater::offsets::dwPawnHealth);
		std::cout << playerHealth << std::endl;
		playerIndex++;
	}
	
}