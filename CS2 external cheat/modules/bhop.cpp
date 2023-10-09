#include "../memory.h"
#include <thread>
#include <iostream>
//#include "../../../../Desktop/CS2C/memory.h"

// https://github.com/frk1/hazedumper/blob/master/csgo.hpp
namespace offsets
{
	constexpr auto localPlayer = 0x1875C48; //0x187AC48;
	constexpr auto flags = 0x3C8;
	constexpr auto forceJump = 0x1690100;
	//constexpr auto entityList = 0x178D8E8;
	//constexpr auto glowObjectManager = 0x5309C78;
	//constexpr auto teamNum = 0x3BF;
	//constexpr auto glowIndex = 0x10488;
}

int bhop()
{
	const auto mem = Memory("cs2.exe");

	std::cout << "csgo found!" << std::endl;

	const auto client = mem.GetModuleAddress("client.dll");
	std::cout << "client.dll -> " << "0x" << std::hex << client << std::dec << std::endl;
	//0x300905A4D + 0x187AC48 + 0x32C
	//const auto localPlayer = mem.Read<std::uintptr_t>(client + offsets::localPlayer);
	//auto localPlayerhealth = mem.Read<std::int32_t>(localPlayer + offsets::flags);

	
	/*while (true)
	{
		localPlayerhealth = mem.Read<std::int32_t>(localPlayer + offsets::flags);
		mem.Write<std::int32_t>(localPlayer + offsets::flags, 100);
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		std::cout << localPlayerhealth << std::endl;

	}*/
	while (true)
	{
		// we don't need this running a billion times per second :)
		//std::this_thread::sleep_for(std::chrono::milliseconds(1));

		const auto localPlayer = mem.Read<std::uintptr_t>(client + offsets::localPlayer);

		if (!localPlayer)
			continue;

		//const auto localPlayerTeam = mem.Read<std::uintptr_t>(localPlayer + offsets::teamNum);
		//std::cout << localPlayerTeam << std::endl;
		const auto localPlayerFlags = mem.Read<std::uint32_t>(localPlayer + offsets::flags);
		//std::cout << localPlayerFlags << std::endl;

		// bhop
		if (GetAsyncKeyState(VK_SPACE)) {
			//std::cout << (localPlayerFlags << 0) << std::endl;
			if (localPlayerFlags & (1 << 0)) {
				//std::cout << ' ' << std::endl;
				mem.Write<std::uintptr_t>(client + offsets::forceJump, 65537);
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
				mem.Write<std::uintptr_t>(client + offsets::forceJump, 256);
			}
		}

	}
}