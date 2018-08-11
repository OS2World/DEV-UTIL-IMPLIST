/*------------------------------------------------------------*/
/* SYMTYPES.H    -  Symbolic Type Definitions.                */
/*------------------------------------------------------------*/

/* AUTHOR
 *
 *     Stephen L. Reed, Stephen Reed Software.  
 *
 *
 *		 NET:        70401.3342@compuserve.com
 *		 BIX:        sreed
 *		 COMPUSERVE: 70401,3342
 *
 *
 *		 Your comments are appreciated!
 *
 *
 * COPYRIGHT
 *
 *	Copyright (c) 1990-91  Stephen L. Reed.  All rights reserved.
 *
 *	Redistribution and use in source and binary forms are permitted
 *	provided that the above copyright notice and this paragraph are
 *	duplicated in all such forms and that any documentation,
 *	advertising materials, and other materials related to such
 *	distribution and use acknowledge that the software was developed
 *	by Stephen L. Reed.
 *
 *	THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 *	IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 *	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#if !defined (SYMTYPES_INCLUDED)

   #define SYMTYPES_INCLUDED

               /* Dynamic Link Library function type.         */
   #if !defined (DLLFUN)
      #define DLLFUN    pascal far _saveregs _loadds
   #endif

   #if !defined (LINT_ARGS)
      #define    LINT_ARGS   1           /* Enable Library type checking.  */
   #endif

   #if !defined (FLOAT)
      #define FLOAT     float
   #endif

   #if !defined (DOUBLE)
      #define DOUBLE    double
   #endif

/*------------------------------------------------------------*/
/* Windows compatible definitions.                            */
/*------------------------------------------------------------*/


   #if !defined (TRUE)
      #define TRUE       1
   #endif

   #if !defined (FALSE)
      #define FALSE      0
   #endif

   #if !defined (VOID)
      #define VOID       void
   #endif


   #if !defined (FAR)
      #define FAR        far
   #endif

   #if !defined (NEAR)
      #define NEAR       near 
   #endif

   #if !defined (HUGE)
      #define HUGE       huge 
   #endif

   #if !defined (PASCAL)
      #define PASCAL     pascal
   #endif

   #if !defined (FASTCALL)
      #define FASTCALL   _fastcall
   #endif

   typedef unsigned long   DWORD ;

   typedef unsigned short  WORD ;

   typedef char *    PSTR ;

   typedef char NEAR *  NPSTR ;

   typedef char FAR *   LPSTR ;

   typedef int FAR *    LPINT ;

/*------------------------------------------------------------*/
/* OS/2 compatible definitions.                               */
/*------------------------------------------------------------*/

   #if !defined(OS2DEF_INCLUDED)

      typedef unsigned short        BOOL ;

      typedef unsigned char         BYTE ;

      typedef signed char           CHAR ;

      typedef signed short          SHORT ;

      typedef unsigned char         UCHAR ;

      typedef unsigned short        USHORT ;

      typedef unsigned long         ULONG ;

      typedef long                  LONG ;

      typedef unsigned char far *   PSZ ;

      typedef LONG FAR *            PLONG ;

      typedef CHAR FAR *            PCHAR ;

      typedef SHORT FAR *           PSHORT ;

      typedef UCHAR FAR *           PUCHAR ;

      typedef USHORT FAR *          PUSHORT ;

      typedef ULONG FAR *           PULONG ;

      typedef VOID FAR *            PVOID ;

   #endif

#endif

