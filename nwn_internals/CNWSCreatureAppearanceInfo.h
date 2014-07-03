/*
 *  NWNeXalt - Empty File
 *  (c) 2007 Doug Swarin (zac@intertex.net)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  $Id$
 *  $HeadURL$
 *
 */

#ifndef _NX_NWN_STRUCT_CNWSCREATUREAPPEARANCEINFO_
#define _NX_NWN_STRUCT_CNWSCREATUREAPPEARANCEINFO_

struct CNWSCreatureAppearanceInfo_s {
    uint32_t                    cai_lefthand_obj_id;    /* 0000 */  /* 0C28 in CNWSCreatureStats */
    uint32_t                    cai_righthand_obj_id;   /* 0004 */  /* 0C2C in CNWSCreatureStats */
    uint8_t                     cai_righthand_wpn_vfx;  /* 0008 */  /* 0C30 in CNWSCreatureStats */
    uint8_t                     cai_lefthand_wpn_vfx;   /* 0009 */  /* 0C31 in CNWSCreatureStats */
    uint8_t                     field_A;                /* 000A */  /* 0C32 in CNWSCreatureStats */
    uint8_t                     field_B;                /* 000B */  /* 0C33 in CNWSCreatureStats */
    uint32_t                    cai_chest_obj_id;       /* 000C */  /* 0C34 in CNWSCreatureStats */
    uint32_t                    cai_head_obj_id;        /* 0010 */  /* 0C38 in CNWSCreatureStats */ 
    uint16_t                    cai_appearance;         /* 0014 */  /* 0C3C in CNWSCreatureStats */ 
    uint8_t                     field_16;
    uint8_t                     field_17;
    uint8_t                     field_18;
    uint8_t                     field_19;
    uint8_t                     field_1A;
    uint8_t                     field_1B;
    uint8_t                     field_1C[12];
    uint32_t                    field_28;
    uint8_t                     field_2C;
    uint8_t                     field_2D;
    uint8_t                     field_2E;
    uint8_t                     field_2F;
    uint32_t                    field_30;
    uint32_t                    field_34;
    uint32_t                    field_38;
    uint32_t                    cai_cloak_obj_id;        /* 003C */
};

#endif /* _NX_NWN_STRUCT_CNWSCREATUREAPPEARANCEINFO_ */

/* vim: set sw=4: */
