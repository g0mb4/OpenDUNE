/* $Id$ */

#include <stdio.h>
#include <stdarg.h>
#include "types.h"
#include "libemu.h"
#include "../global.h"
#include "font.h"

/**
 * Emulator wrapper around Font_GetCharWidth()
 *
 * @name emu_Font_GetCharWidth
 * @implements 2521:000F:0022:6D87 ()
 */
void emu_Font_GetCharWidth()
{
	char c;

	/* Pop the return CS:IP. */
	emu_pop(&emu_ip);
	emu_pop(&emu_cs);

	c = emu_get_memory8(emu_ss, emu_sp, 0x0);

	emu_ax = Font_GetCharWidth(c);
}

/**
 * Emulator wrapper around Font_GetStringWidth()
 *
 * @name emu_Font_GetStringWidth
 * @implements 2521:0035:0015:AA0F ()
 */
void emu_Font_GetStringWidth()
{
	char *string;

	/* Pop the return CS:IP. */
	emu_pop(&emu_ip);
	emu_pop(&emu_cs);

	string = (char *)emu_get_memorycsip(emu_get_csip32(emu_ss, emu_sp, 0x0));

	emu_ax = Font_GetStringWidth(string);
}

/**
 * Emulator wrapper around Font_LoadFile()
 *
 * @name emu_Font_LoadFile
 * @implements 256D:0004:001C:9F23 ()
 */
void emu_Font_LoadFile()
{
	char *filename;
	csip32 csip;

	/* Pop the return CS:IP. */
	emu_pop(&emu_ip);
	emu_pop(&emu_cs);

	filename = (char *)emu_get_memorycsip(emu_get_csip32(emu_ss, emu_sp, 0x0));

	csip = Font_LoadFile(filename);

	emu_ax = csip.s.ip;
	emu_dx = csip.s.cs;
}