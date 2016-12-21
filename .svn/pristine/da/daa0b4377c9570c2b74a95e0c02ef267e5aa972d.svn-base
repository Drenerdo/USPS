/*!
@file typedefs.h
Fundamental type definitions and related constants.

@copyright (c) 2014, Bay Computer Associates.<br>
All rights reserved.<br>
This file contains CONFIDENTIAL material.<br>
Bay Computer Associates and forbids duplication of
this material with out express written permission
from Bay Computer Associates.

@author John Heaney<br>
Bay Computer Associates, Inc.<br>
136 Frances Ave.<br>
Cranston, RI 02910<br>
Tel. (401) 461-1484

Repository URL:		$HeadURL: svn://svn/BCA/RTOS/CompanyStarter/ProjectStarter/trunk/ProjectStarter/Target/ProjectConfiguration/typedefs.h $
Last changed by:	$Author: jheaney $
Last changed on:	$Date: 2015-02-20 17:00:04 -0500 (Fri, 20 Feb 2015) $
Revision:			$Rev: 8071 $
*/

#ifndef _TYPEDEFS_H
#define _TYPEDEFS_H

#ifndef VOID
#define VOID	void
#endif

#ifndef NULL
#define NULL	((void *)0)
#endif

#ifndef BYTE
#define BYTE	unsigned char
#endif

#ifndef BOOL
#define BOOL	int
#endif

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

#ifndef FAILURE
#define FAILURE	1
#endif

#ifndef SUCCESS
#define SUCCESS	0
#endif

//
// The following types should be used for any new code created, and when
// existing code is modified:
//
//  INT8, UINT8, INT16, UINT16, INT32, UINT32

// The signed types
#ifndef INT8
#define INT8	signed char
#endif

#ifndef INT16
#define INT16	signed short
#endif

#ifndef INT32
#define INT32	signed long
#endif

// The unsigned types
#ifndef UINT8
#define UINT8	unsigned char
#endif

#ifndef UINT16
#define UINT16	unsigned short
#endif

#ifndef UINT32
#define UINT32	unsigned long
#endif

// The signed limits

#ifndef INT8_MAX
#define INT8_MAX	0x7F
#endif

#ifndef INT8_MIN
#define INT8_MIN	(-INT8_MAX - 1)
#endif

#ifndef INT16_MAX
#define INT16_MAX	0x7FFF
#endif

#ifndef INT16_MIN
#define INT16_MIN	(-INT16_MAX - 1)
#endif

#ifndef INT32_MAX
#define INT32_MAX	0x7FFFFFFF
#endif

#ifndef INT32_MIN
#define INT32_MIN	(-INT32_MAX - 1)
#endif

// The unsigned limits

#ifndef UINT8_MAX
#define UINT8_MAX	0xFF
#endif

#ifndef UINT8_MIN
#define UINT8_MIN	0x0
#endif

#ifndef UINT16_MAX
#define UINT16_MAX	0xFFFF
#endif

#ifndef UINT16_MIN
#define UINT16_MIN	0x0
#endif

#ifndef UINT32_MAX
#define UINT32_MAX	0xFFFFFFFF
#endif

#ifndef UINT32_MIN
#define UINT32_MIN	0x0
#endif

/** A general purpose pointer to a void function. */
typedef void (*FuncPtr) (void);
typedef void (*FuncPtr1Arg) (int);

#define FNULL NULL

#endif //_TYPEDEFS_H

