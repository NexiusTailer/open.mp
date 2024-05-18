/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2022, open.mp team and contributors.
 */

#include "../Types.hpp"
#include "sdk.hpp"
#include <iostream>
#include "../../format.hpp"

SCRIPT_API(NPC_Create, int(const String& name))
{
	auto component = PawnManager::Get()->npcs;
	if (component)
	{
		auto npc = component->create(name.c_str());
		if (npc)
		{
			return npc->getID();
		}
	}
	return INVALID_PLAYER_ID;
}

SCRIPT_API(NPC_Destroy, bool(INPC& npc))
{
	PawnManager::Get()->npcs->destroy(npc);
	return true;
}

SCRIPT_API(NPC_IsValid, bool(INPC* npc))
{
	return npc != nullptr;
}

SCRIPT_API(NPC_Spawn, bool(INPC& npc))
{
	npc.spawn();
	return true;
}

SCRIPT_API(NPC_SetPos, bool(INPC& npc, Vector3 position))
{
	npc.setPosition(position);
	return true;
}

SCRIPT_API(NPC_GetPos, bool(INPC& npc, Vector3& position))
{
	position = npc.getPosition();
	return true;
}

SCRIPT_API(NPC_SetRot, bool(INPC& npc, Vector3 rotation))
{
	npc.setRotation(rotation);
	return true;
}

SCRIPT_API(NPC_GetRot, bool(INPC& npc, Vector3& rotation))
{
	rotation = npc.getRotation().ToEuler();
	return true;
}

SCRIPT_API(NPC_SetFacingAngle, bool(INPC& npc, float angle))
{
	auto rotation = npc.getRotation().ToEuler();
	rotation.z = angle;
	return true;
}

SCRIPT_API(NPC_GetFacingAngle, bool(INPC& npc, float& angle))
{
	auto rotation = npc.getRotation().ToEuler();
	angle = rotation.z;
	return true;
}

SCRIPT_API(NPC_SetVirtualWorld, bool(INPC& npc, int virtualWorld))
{
	npc.setVirtualWorld(virtualWorld);
	return true;
}

SCRIPT_API(NPC_GetVirtualWorld, int(INPC& npc))
{
	return npc.getVirtualWorld();
}

SCRIPT_API(NPC_Move, bool(INPC& npc, Vector3 targetPos, int moveType))
{
	return npc.move(targetPos, NPCMoveType(moveType));
}

SCRIPT_API(NPC_StopMove, bool(INPC& npc))
{
	npc.stopMove();
	return true;
}

SCRIPT_API(NPC_SetSkin, bool(INPC& npc, int model))
{
	npc.setSkin(model);
	return true;
}

SCRIPT_API(NPC_IsStreamedIn, bool(INPC& npc, IPlayer& player))
{
	return npc.isStreamedInForPlayer(player);
}

SCRIPT_API(NPC_IsAnyStreamedIn, bool(INPC& npc))
{
	auto streamedIn = npc.streamedForPlayers();
	return streamedIn.size() > 0;
}

SCRIPT_API(NPC_GetAll, int(DynamicArray<int>& outputNPCs))
{
	int index = -1;
	auto npcs = PawnManager::Get()->npcs;
	if (npcs)
	{
		if (outputNPCs.size() < npcs->count())
		{
			PawnManager::Get()->core->printLn(
				"There are %zu NPCs in your server but array size used in `NPC_GetAll` is %zu; Use a bigger size in your script.",
				npcs->count(),
				outputNPCs.size());
		}

		for (INPC* npc : *npcs)
		{
			index++;
			if (index >= outputNPCs.size())
			{
				break;
			}
			outputNPCs[index] = npc->getID();
		}
	}
	return index + 1;
}

SCRIPT_API(NPC_SetInterior, bool(INPC& npc, int interior))
{
	npc.setInterior(interior);
	return true;
}

SCRIPT_API(NPC_GetInterior, int(INPC& npc))
{
	return npc.getInterior();
}
