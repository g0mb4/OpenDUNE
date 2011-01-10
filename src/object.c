/* $Id$ */

#include <stdio.h>
#include <string.h>
#include "types.h"
#include "libemu.h"
#include "global.h"
#include "object.h"
#include "pool/pool.h"
#include "pool/structure.h"
#include "pool/unit.h"
#include "structure.h"
#include "tools.h"
#include "unit.h"
#include "map.h"

/**
 * Link two variable4 values to eachother, and clean up existing values if
 *  needed.
 * @param encodedFrom From where the link goes.
 * @param encodedTo To where the link goes.
 */
void Object_Script_Variable4_Link(uint16 encodedFrom, uint16 encodedTo)
{
	Object *objectFrom;
	Object *objectTo;

	if (!Tools_Index_IsValid(encodedFrom)) return;
	if (!Tools_Index_IsValid(encodedTo)) return;

	objectFrom = Tools_Index_GetObject(encodedFrom);
	objectTo = Tools_Index_GetObject(encodedTo);

	if (objectFrom == NULL) return;
	if (objectTo == NULL) return;

	if (objectFrom->script.variables[4] != objectTo->script.variables[4]) {
		Object_Script_Variable4_Set(objectFrom, 0);
		Object_Script_Variable4_Set(objectTo, 0);
	}
	if (objectFrom->script.variables[4] != 0) return;

	Object_Script_Variable4_Set(objectFrom, encodedTo);
	Object_Script_Variable4_Set(objectTo, encodedFrom);

	return;
}

/**
 * Set in a safe way the new value for variable4.
 * @param o The Object to set variable4 for.
 * @param index The encoded index to set it to.
 */
void Object_Script_Variable4_Set(Object *o, uint16 encoded)
{
	Structure *s;
	StructureInfo *si;

	if (o == NULL) return;

	o->script.variables[4] = encoded;

	if (o->flags.s.variable_6_0001) return;

	si = &g_structureInfo[o->type];
	if (!si->flags.s.variable_0010) return;

	s = (Structure *)o;
	if (Structure_GetLinkedUnit(s) != NULL) return;

	Structure_SetAnimation(s, 1);
}

/**
 * Clear variable4 in a safe (and recursive) way from an object.
 * @param object The Oject to clear variable4 of.
 */
void Object_Script_Variable4_Clear(Object *object)
{
	Object *objectVariable;
	uint16 encoded = object->script.variables[4];

	if (encoded == 0) return;

	objectVariable = Tools_Index_GetObject(encoded);

	Object_Script_Variable4_Set(object, 0);
	Object_Script_Variable4_Set(objectVariable, 0);
}

/**
 * Get the object on the given packed tile.
 * @param packed The packed tile to get the object from.
 * @return The object.
 */
Object *Object_GetByPackedTile(uint16 packed)
{
	Tile* t;

	if (packed >= 4096) return NULL;

	t = Map_GetTileByPosition(packed);
	if (t->hasUnit) return &Unit_Get_ByIndex(t->index - 1)->o;
	if (t->hasStructure) return &Structure_Get_ByIndex(t->index - 1)->o;
	return NULL;
}