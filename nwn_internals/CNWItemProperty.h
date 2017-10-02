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

#ifndef _NX_NWN_STRUCT_CNWITEMPROPERTY_
#define _NX_NWN_STRUCT_CNWITEMPROPERTY_

struct CNWItemProperty_s {
    uint16_t m_nPropertyName;//00
    uint16_t m_nSubType;//02
    uint8_t m_nCostTable;//04
    uint16_t m_nCostTableValue;//06
    uint8_t m_nParam1;//08
    uint8_t m_nParam1Value;//09
    uint8_t m_nChanceOfAppearing;//0A
    int32_t m_bUseable;//0C
    uint8_t m_nUsesPerDay;//10
    uint8_t m_nDurationType;//11 //02 = permanent, 01 = temporary
    uint64_t m_nID;//14
};

#endif /* _NX_NWN_STRUCT_CNWITEMPROPERTY_ */

/* vim: set sw=4: */
