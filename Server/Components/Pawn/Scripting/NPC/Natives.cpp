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
	PawnManager::Get()->npcs->release(npc.getID());
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

SCRIPT_API(NPC_SetVirtualWorld, bool(INPC& npc, int virtualWorld))
{
	npc.setVirtualWorld(virtualWorld);
	return true;
}

SCRIPT_API(NPC_GetVirtualWorld, bool(INPC& npc, int& virtualWorld))
{
	virtualWorld = npc.getVirtualWorld();
	return true;
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