/*!
@file STREAM_macros.h

@brief The macros defined here allow values to be streamed without the developer
being concerned about endianness issues. The endian option can be a parameter using
the TYPE_FROM_STREAM macros. The STREAM_ENDIAN can be defined to globally set the
option using the STREAM_TYPE_FROM macros. Endian options are either LE_ or BE_.

The types that can be streamed are all integers. Floats and doubles can also be
streamed by treating their storage as integers, but FP number endianness might be
independent of integer endianness. The integer types are UINT8_, UINT16_, UINT24_,
UINT32_, UINT64_.

Always include the underscore at the end of the options. If the option has been
defined as something then it cannot be used as a parameter. For example, if UINT8_
has been defined as something then UINT8_ cannot be used as an option parameter.

@copyright (c) 2016, Bay Computer Associates.<br>
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

Repository URL:		$HeadURL: svn://svn/Insulet/Eros_ClosedLoop_BLE/Biscuit/BLE/Profiles/UART/uartservice.c $
Last changed by:	$Author: jheaney $
Last changed on:	$Date: 2016-01-12 10:12:51 -0500 (Tue, 12 Jan 2016) $
Revision:			$Rev: 9477 $
*/
#ifndef STREAM_MACROS_H
#define STREAM_MACROS_H

#include "ProjectConfig.h"

#define BIG_ENDIAN_STREAM 1
#define LITTLE_ENDIAN_STREAM 2

// When creating device independent streams between two platforms, choose
// endianness and use the STREAM macros on both platforms to preserve byte order.
#ifndef STREAM_ENDIAN
#define STREAM_ENDIAN LITTLE_ENDIAN_STREAM
#endif

#if defined(UINT8_) || defined(UINT16_) || defined(UINT24_) || defined(INT24_) || defined(UINT32_) || defined(UINT64_)
#error Stream type params are reserved!
#endif

//These macros use a specified type to select the appropriate macro for the
// number of bytes associated with the type. Valid specifiers for type are
// UINT8_, UINT16_, UINT24_, INT24_, UINT32_ and UINT64_. NOTE the underscore at the end of each. The names without
// the underscore match macro definitions for types, so they would be evaluated if used as a macro
// parameter value. The endianness is given by STREAM_ENDIAN.
#define TYPE_FROM_STREAM_ITERATOR(type, buffer, iterator)		MACRO_CONCAT2(type, FROM_STREAM_ITERATOR)(buffer, iterator)
#define TYPE_FROM_STREAM_OFFSET(type, buffer, offset)			MACRO_CONCAT2(type, FROM_STREAM_OFFSET)(buffer, offset)
#define TYPE_TO_STREAM_ITERATOR(type, buffer, iterator, value)	MACRO_CONCAT2(type, TO_STREAM_ITERATOR)(buffer, iterator, value)
#define TYPE_TO_STREAM_OFFSET(type, buffer, offset, value)		MACRO_CONCAT2(type, TO_STREAM_OFFSET)(buffer, offset, value)

//These macros are further generalized to take a parameter to select the endianness.
// The endian parameter is either BE_ or LE_.
#define TYPE_ENDIAN_FROM_STREAM_ITERATOR(type, endian, buffer, iterator)		MACRO_CONCAT3(endian, type, FROM_STREAM_ITERATOR)(buffer, iterator)
#define TYPE_ENDIAN_FROM_STREAM_OFFSET(type, endian, buffer, offset)			MACRO_CONCAT3(endian, type, FROM_STREAM_OFFSET)(buffer, offset)
#define TYPE_ENDIAN_TO_STREAM_ITERATOR(type, endian, buffer, iterator, value)	MACRO_CONCAT3(endian, type, TO_STREAM_ITERATOR)(buffer, iterator, value)
#define TYPE_ENDIAN_TO_STREAM_OFFSET(type, endian, buffer, offset, value)		MACRO_CONCAT3(endian, type, TO_STREAM_OFFSET)(buffer, offset, value)

//The byte macros, operating on single bytes, have no order dependency, but the
// BE and LE versions are included to support the general macros above.
#define UINT8_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)		BUFFER[ITERATOR++] = (UINT8)VALUE
#define BE_UINT8_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)	UINT8_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)
#define LE_UINT8_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)	UINT8_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)
#define UINT8_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)			BUFFER[OFFSET] = (UINT8)VALUE
#define BE_UINT8_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)		UINT8_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)
#define LE_UINT8_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)		UINT8_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)

#define UINT8_FROM_STREAM_ITERATOR(BUFFER, ITERATOR)			BUFFER[ITERATOR++]
#define BE_UINT8_FROM_STREAM_ITERATOR(BUFFER, ITERATOR)			UINT8_FROM_STREAM_ITERATOR(BUFFER, ITERATOR)
#define LE_UINT8_FROM_STREAM_ITERATOR(BUFFER, ITERATOR)			UINT8_FROM_STREAM_ITERATOR(BUFFER, ITERATOR)
#define UINT8_FROM_STREAM_OFFSET(BUFFER, OFFSET)				BUFFER[OFFSET]
#define BE_UINT8_FROM_STREAM_OFFSET(BUFFER, OFFSET)				UINT8_FROM_STREAM_OFFSET(BUFFER, OFFSET)
#define LE_UINT8_FROM_STREAM_OFFSET(BUFFER, OFFSET)				UINT8_FROM_STREAM_OFFSET(BUFFER, OFFSET)

//Only multibyte values have byte order dependence. Since these macros hide the
// endianness, there is short/triple/long/longlong, to/from for a total of 8 macros that
// are presented to the application.
#if STREAM_ENDIAN == BIG_ENDIAN_STREAM
#define UINT16_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)	BE_UINT16_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)
#define UINT24_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)	BE_UINT24_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)
#define INT24_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)	BE_INT24_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)
#define UINT32_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)	BE_UINT32_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)
#define UINT64_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)	BE_UINT64_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)

#define UINT16_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)		BE_UINT16_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)
#define UINT24_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)		BE_UINT24_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)
#define INT24_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)		BE_INT24_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)
#define UINT32_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)		BE_UINT32_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)
#define UINT64_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)		BE_UINT64_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)

#define UINT16_FROM_STREAM_ITERATOR(BUFFER, ITERATOR)		BE_UINT16_FROM_STREAM_ITERATOR(BUFFER, ITERATOR)
#define UINT24_FROM_STREAM_ITERATOR(BUFFER, ITERATOR)		BE_UINT24_FROM_STREAM_ITERATOR(BUFFER, ITERATOR)
#define INT24_FROM_STREAM_ITERATOR(BUFFER, ITERATOR)		BE_INT24_FROM_STREAM_ITERATOR(BUFFER, ITERATOR)
#define UINT32_FROM_STREAM_ITERATOR(BUFFER, ITERATOR)		BE_UINT32_FROM_STREAM_ITERATOR(BUFFER, ITERATOR)
#define UINT64_FROM_STREAM_ITERATOR(BUFFER, ITERATOR)		BE_UINT64_FROM_STREAM_ITERATOR(BUFFER, ITERATOR)

#define UINT16_FROM_STREAM_OFFSET(BUFFER, OFFSET)			BE_UINT16_FROM_STREAM_OFFSET(BUFFER, OFFSET)
#define UINT24_FROM_STREAM_OFFSET(BUFFER, OFFSET)			BE_UINT24_FROM_STREAM_OFFSET(BUFFER, OFFSET)
#define INT24_FROM_STREAM_OFFSET(BUFFER, OFFSET)			BE_INT24_FROM_STREAM_OFFSET(BUFFER, OFFSET)
#define UINT32_FROM_STREAM_OFFSET(BUFFER, OFFSET)			BE_UINT32_FROM_STREAM_OFFSET(BUFFER, OFFSET)
#define UINT64_FROM_STREAM_OFFSET(BUFFER, OFFSET)			BE_UINT64_FROM_STREAM_OFFSET(BUFFER, OFFSET)

#elif STREAM_ENDIAN == LITTLE_ENDIAN_STREAM
#define UINT16_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)	LE_UINT16_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)
#define UINT24_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)	LE_UINT24_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)
#define INT24_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)	LE_INT24_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)
#define UINT32_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)	LE_UINT32_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)
#define UINT64_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)	LE_UINT64_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)

#define UINT16_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)		LE_UINT16_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)
#define UINT24_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)		LE_UINT24_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)
#define INT24_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)		LE_INT24_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)
#define UINT32_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)		LE_UINT32_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)
#define UINT64_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)		LE_UINT64_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)

#define UINT16_FROM_STREAM_ITERATOR(BUFFER, ITERATOR)		LE_UINT16_FROM_STREAM_ITERATOR(BUFFER, ITERATOR)
#define UINT24_FROM_STREAM_ITERATOR(BUFFER, ITERATOR)		LE_UINT24_FROM_STREAM_ITERATOR(BUFFER, ITERATOR)
#define INT24_FROM_STREAM_ITERATOR(BUFFER, ITERATOR)		LE_INT24_FROM_STREAM_ITERATOR(BUFFER, ITERATOR)
#define UINT32_FROM_STREAM_ITERATOR(BUFFER, ITERATOR)		LE_UINT32_FROM_STREAM_ITERATOR(BUFFER, ITERATOR)
#define UINT64_FROM_STREAM_ITERATOR(BUFFER, ITERATOR)		LE_UINT64_FROM_STREAM_ITERATOR(BUFFER, ITERATOR)

#define UINT16_FROM_STREAM_OFFSET(BUFFER, OFFSET)			LE_UINT16_FROM_STREAM_OFFSET(BUFFER, OFFSET)
#define UINT24_FROM_STREAM_OFFSET(BUFFER, OFFSET)			LE_UINT24_FROM_STREAM_OFFSET(BUFFER, OFFSET)
#define INT24_FROM_STREAM_OFFSET(BUFFER, OFFSET)			LE_INT24_FROM_STREAM_OFFSET(BUFFER, OFFSET)
#define UINT32_FROM_STREAM_OFFSET(BUFFER, OFFSET)			LE_UINT32_FROM_STREAM_OFFSET(BUFFER, OFFSET)
#define UINT64_FROM_STREAM_OFFSET(BUFFER, OFFSET)			LE_UINT64_FROM_STREAM_OFFSET(BUFFER, OFFSET)

#else
#error "Bad endian specifier"
#endif

//The macros presented to the application have two variants of big endian/little
// endian so there are double the number of macros that do the actual work.

/////////// Big endian specific macros. ////////////////
//These output a value using an iterator variable that advances automatically.
#define BE_UINT16_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)	\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >>  8);	\
        BUFFER[ITERATOR++] = 0xFF & (VALUE)
#define BE_UINT24_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)	\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >> 16);	\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >>  8);	\
        BUFFER[ITERATOR++] = 0xFF & (VALUE)
#define BE_INT24_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)	\
		BE_UINT24_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)
#define BE_UINT32_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)	\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >> 24);	\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >> 16);	\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >>  8);	\
        BUFFER[ITERATOR++] = 0xFF & (VALUE)
#define BE_UINT64_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)	\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >> 56);	\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >> 48);	\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >> 40);	\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >> 32);	\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >> 24);	\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >> 16);	\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >>  8);	\
        BUFFER[ITERATOR++] = 0xFF & (VALUE)

//These output a value using an offset without iterating.
#define BE_UINT16_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)		\
        BUFFER[OFFSET  ] = 0xFF & ((VALUE) >>  8);	\
        BUFFER[OFFSET+1] = 0xFF & (VALUE)
#define BE_UINT24_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)		\
        BUFFER[OFFSET  ] = 0xFF & ((VALUE) >> 16);	\
        BUFFER[OFFSET+1] = 0xFF & ((VALUE) >>  8);	\
        BUFFER[OFFSET+2] = 0xFF & (VALUE)
#define BE_INT24_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)		\
		BE_UINT24_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)
#define BE_UINT32_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)		\
        BUFFER[OFFSET  ] = 0xFF & ((VALUE) >> 24);	\
        BUFFER[OFFSET+1] = 0xFF & ((VALUE) >> 16);	\
        BUFFER[OFFSET+2] = 0xFF & ((VALUE) >>  8);	\
        BUFFER[OFFSET+3] = 0xFF & (VALUE)
#define BE_UINT64_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)	\
        BUFFER[OFFSET  ] = 0xFF & ((VALUE) >> 56);	\
        BUFFER[OFFSET+1] = 0xFF & ((VALUE) >> 48);	\
        BUFFER[OFFSET+2] = 0xFF & ((VALUE) >> 40);	\
        BUFFER[OFFSET+3] = 0xFF & ((VALUE) >> 32);	\
        BUFFER[OFFSET+4] = 0xFF & ((VALUE) >> 24);	\
        BUFFER[OFFSET+5] = 0xFF & ((VALUE) >> 16);	\
        BUFFER[OFFSET+6] = 0xFF & ((VALUE) >>  8);	\
        BUFFER[OFFSET+7] = 0xFF & (VALUE)

//These get a value using an iterator variable that advances automatically.
#define BE_UINT16_FROM_STREAM_ITERATOR(BUFFER, ITERATOR) (UINT16)	\
	(	ITERATOR += 2,					\
	(	(BUFFER[ITERATOR-2] <<  8) |	\
		 BUFFER[ITERATOR-1])	)
#define BE_UINT24_FROM_STREAM_ITERATOR(BUFFER, ITERATOR) (UINT32)	\
    (	ITERATOR += 3,					\
    (	(BUFFER[ITERATOR-3] << 16) |	\
		(BUFFER[ITERATOR-2] <<  8) |	\
		 BUFFER[ITERATOR-1])	)
#define BE_INT24_FROM_STREAM_ITERATOR(BUFFER, ITERATOR) (INT32)		\
    (	ITERATOR += 3,					\
    (((INT32)(	(BUFFER[ITERATOR-3] << 24) |	\
				(BUFFER[ITERATOR-2] << 16) |	\
				(BUFFER[ITERATOR-1] <<  8) )	\
				) >> 8)	)
#define BE_UINT32_FROM_STREAM_ITERATOR(BUFFER, ITERATOR) (UINT32)	\
    (	ITERATOR += 4,					\
    (	(BUFFER[ITERATOR-4] << 24) |	\
		(BUFFER[ITERATOR-3] << 16) |	\
		(BUFFER[ITERATOR-2] <<  8) |	\
		 BUFFER[ITERATOR-1])	)
#define BE_UINT64_FROM_STREAM_ITERATOR(BUFFER, ITERATOR) (UINT32)	\
    (	ITERATOR += 8,					\
    (	(BUFFER[ITERATOR-8] << 56) |	\
		(BUFFER[ITERATOR-7] << 48) |	\
		(BUFFER[ITERATOR-6] << 40) |	\
		(BUFFER[ITERATOR-5] << 32) |	\
		(BUFFER[ITERATOR-4] << 24) |	\
		(BUFFER[ITERATOR-3] << 16) |	\
		(BUFFER[ITERATOR-2] <<  8) |	\
		 BUFFER[ITERATOR-1])	)

//These get a value using an offset without iterating.
#define BE_UINT16_FROM_STREAM_OFFSET(BUFFER, OFFSET) (UINT16)	\
	(	(BUFFER[OFFSET  ]	<<  8) |	\
		 BUFFER[OFFSET+1]	)
#define BE_UINT24_FROM_STREAM_OFFSET(BUFFER, OFFSET) (UINT32)	\
    (	(BUFFER[OFFSET  ]	<< 16) |	\
		(BUFFER[OFFSET+1]	<<  8) |	\
		 BUFFER[OFFSET+2]	)
#define BE_INT24_FROM_STREAM_OFFSET(BUFFER, OFFSET) (INT32)		\
    (((INT32)(	(BUFFER[OFFSET  ] << 24) |	\
				(BUFFER[OFFSET+1] << 16) |	\
				(BUFFER[OFFSET+2] <<  8) )	\
				) >> 8	)
#define BE_UINT32_FROM_STREAM_OFFSET(BUFFER, OFFSET) (UINT32)	\
    (	(BUFFER[OFFSET  ]	<< 24) |	\
		(BUFFER[OFFSET+1]	<< 16) |	\
		(BUFFER[OFFSET+2]	<<  8) |	\
		 BUFFER[OFFSET+3]	)
#define BE_UINT64_FROM_STREAM_OFFSET(BUFFER, OFFSET) (UINT64)	\
    (	(BUFFER[OFFSET  ]	<< 56) |	\
		(BUFFER[OFFSET+1]	<< 48) |	\
		(BUFFER[OFFSET+2]	<< 40) |	\
		(BUFFER[OFFSET+3]	<< 32) |	\
		(BUFFER[OFFSET+4]	<< 24) |	\
		(BUFFER[OFFSET+5]	<< 16) |	\
		(BUFFER[OFFSET+6]	<<  8) |	\
		 BUFFER[OFFSET+7]	)

/////////// Little endian specific macros. ////////////////
//These output a value using an iterator variable that advances automatically.
#define LE_UINT16_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)	\
        BUFFER[ITERATOR++] = 0xFF & (VALUE);			\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >>  8)
#define LE_UINT24_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)	\
        BUFFER[ITERATOR++] = 0xFF & (VALUE);			\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >>  8);	\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >> 16);
#define LE_INT24_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)	\
		LE_UINT24_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)
#define LE_UINT32_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)	\
        BUFFER[ITERATOR++] = 0xFF & (VALUE);			\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >>  8);	\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >> 16);	\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >> 24)
#define LE_UINT64_TO_STREAM_ITERATOR(BUFFER, ITERATOR, VALUE)	\
        BUFFER[ITERATOR++] = 0xFF & (VALUE);			\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >>  8);	\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >> 16);	\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >> 24)		\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >> 32);	\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >> 40);	\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >> 48);	\
        BUFFER[ITERATOR++] = 0xFF & ((VALUE) >> 56);

//These output a value using an offset without iterating.
#define LE_UINT16_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)	\
        BUFFER[OFFSET  ] = 0xFF & (VALUE);			\
        BUFFER[OFFSET+1] = 0xFF & ((VALUE) >>  8)
#define LE_UINT24_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)	\
        BUFFER[OFFSET  ] = 0xFF & (VALUE);			\
        BUFFER[OFFSET+1] = 0xFF & ((VALUE) >>  8);	\
        BUFFER[OFFSET+2] = 0xFF & ((VALUE) >> 16);
#define LE_INT24_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)	\
		LE_UINT24_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)
#define LE_UINT32_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)	\
        BUFFER[OFFSET  ] = 0xFF & (VALUE);			\
        BUFFER[OFFSET+1] = 0xFF & ((VALUE) >>  8);	\
        BUFFER[OFFSET+2] = 0xFF & ((VALUE) >> 16);	\
        BUFFER[OFFSET+3] = 0xFF & ((VALUE) >> 24)
#define LE_UINT64_TO_STREAM_OFFSET(BUFFER, OFFSET, VALUE)	\
        BUFFER[OFFSET  ] = 0xFF & (VALUE);			\
        BUFFER[OFFSET+1] = 0xFF & ((VALUE) >>  8);	\
        BUFFER[OFFSET+2] = 0xFF & ((VALUE) >> 16);	\
        BUFFER[OFFSET+3] = 0xFF & ((VALUE) >> 24)	\
        BUFFER[OFFSET+4] = 0xFF & ((VALUE) >> 32);	\
        BUFFER[OFFSET+5] = 0xFF & ((VALUE) >> 40);	\
        BUFFER[OFFSET+6] = 0xFF & ((VALUE) >> 48);	\
        BUFFER[OFFSET+7] = 0xFF & ((VALUE) >> 56);

//These get a value using an iterator variable that advances automatically.
#define LE_UINT16_FROM_STREAM_ITERATOR(BUFFER, ITERATOR) (UINT16)	\
	(	ITERATOR += 2,					\
	(	(BUFFER[ITERATOR-1] <<  8) |	\
		 BUFFER[ITERATOR-2])	)
#define LE_UINT24_FROM_STREAM_ITERATOR(BUFFER, ITERATOR) (UINT32)	\
    (	ITERATOR += 3,					\
	(	(BUFFER[ITERATOR-1] << 16) |	\
		(BUFFER[ITERATOR-2] <<  8) |	\
		 BUFFER[ITERATOR-3])	)
#define LE_INT24_FROM_STREAM_ITERATOR(BUFFER, ITERATOR) (INT32)		\
    (	ITERATOR += 3,					\
    (((INT32)(	(BUFFER[ITERATOR-1] << 24) |	\
				(BUFFER[ITERATOR-2] << 16) |	\
				(BUFFER[ITERATOR-3] <<  8) )	\
				) >> 8)	)
#define LE_UINT32_FROM_STREAM_ITERATOR(BUFFER, ITERATOR) (UINT32)	\
    (	ITERATOR += 4,					\
    (	(BUFFER[ITERATOR-1] << 24) |	\
		(BUFFER[ITERATOR-2] << 16) |	\
		(BUFFER[ITERATOR-3] <<  8) |	\
		 BUFFER[ITERATOR-4])	)
#define LE_UINT64_FROM_STREAM_ITERATOR(BUFFER, ITERATOR) (UINT64)	\
    (	ITERATOR += 8,					\
    (	(BUFFER[ITERATOR-1] << 56) |	\
		(BUFFER[ITERATOR-2] << 48) |	\
		(BUFFER[ITERATOR-3] << 40) |	\
		(BUFFER[ITERATOR-4] << 32) |	\
		(BUFFER[ITERATOR-5] << 24) |	\
		(BUFFER[ITERATOR-6] << 16) |	\
		(BUFFER[ITERATOR-7] <<  8) |	\
		 BUFFER[ITERATOR-8])	)

//These get a value using an offset without iterating.
#define LE_UINT16_FROM_STREAM_OFFSET(BUFFER, OFFSET) (UINT16)	\
    (	 BUFFER[OFFSET  ]		 |		\
		(BUFFER[OFFSET+1] <<  8)		)
#define LE_UINT24_FROM_STREAM_OFFSET(BUFFER, OFFSET) (UINT32)	\
    (	 BUFFER[OFFSET  ]		 |		\
		(BUFFER[OFFSET+1] <<  8) |		\
		(BUFFER[OFFSET+2] << 16)		)
#define LE_INT24_FROM_STREAM_OFFSET(BUFFER, OFFSET) (INT32)	\
    (((INT32)(	(BUFFER[OFFSET  ] << 24) |	\
				(BUFFER[OFFSET+1] << 16) |	\
				(BUFFER[OFFSET+2] <<  8) )	\
				) >> 8	)
#define LE_UINT32_FROM_STREAM_OFFSET(BUFFER, OFFSET) (UINT32)	\
    (	 BUFFER[OFFSET  ]		 |		\
		(BUFFER[OFFSET+1] <<  8) |		\
		(BUFFER[OFFSET+2] << 16) |		\
		(BUFFER[OFFSET+3] << 24)		)
#define LE_UINT64_FROM_STREAM_OFFSET(BUFFER, OFFSET) (UINT64)	\
    (	 BUFFER[OFFSET  ]		 |		\
		(BUFFER[OFFSET+1] <<  8) |		\
		(BUFFER[OFFSET+2] << 16) |		\
		(BUFFER[OFFSET+3] << 24) |		\
		(BUFFER[OFFSET+4] << 32) |		\
		(BUFFER[OFFSET+5] << 40) |		\
		(BUFFER[OFFSET+6] << 48) |		\
		(BUFFER[OFFSET+7] << 56)		)

#endif  /* STREAM_MACROS_H */
