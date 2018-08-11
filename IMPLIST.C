/* 
 *
 * SYNOPSIS
 *
 *	implist pathname                                                    
 *
 *
 *
 * DESCRIPTION
 *
 * 	IMPLIST  Will list exported function names and cardinal numbers
 *	from a xxx.lib file on OS/2 1.2 and 1.3.  The lib file may be one 
 *	supplied by the compiler vendor such as OS2.LIB or it can be created
 *	from any xxx.DLL by using the IMPLIB utility, such as supplied by
 *	the MICROSOFT C compiler:  implib  xxx.LIB  xxx.DLL .
 *
 *
 *	Aside from simple informational purposes, IMPLIST is intended to build
 *	a simple sequential database of exported function names and cardinal
 *	numbers which can be used by IMPFILT to add the name information to the
 *	output of the MICROSOFT EXEHDR utility.  This can be helpful when 
 *	reverse engineering a software component such as PSTAT.EXE.
 *
 *
 * COMPILATION
 *
 *	See implist.mak for a simple makefile to be used with NMAKE. 
 *
 * AUTHOR
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


#include    <stdio.h>             /* Library I/O routines.    */
#include    <stdlib.h>            /* Library common routines. */
#include    <string.h>            /* Library string routines. */

#define     INCL_BASE
#include    <os2.h>

#include    "SYMTYPES.H"

PCHAR             ErrTxt1           = "Usage: IMPLIST implib-path" ;

CHAR              szImpLib [ 20 ]   = "" ;
FILE *            hfImpLib ;

USHORT            cInternalNameLen  = 0 ;
UCHAR             szInternalName [ 50 ] ;

USHORT            cExternalNameLen  = 0 ;
UCHAR             szExternalName [ 50 ] ;

USHORT            cDllNameLen       = 0 ;
UCHAR             szDllName [ 50 ] ;

USHORT            usOrdinal         = 0 ;

USHORT            i ;
USHORT            cBytes            = 0 ;
SHORT             sChar ;
SHORT             sChar1 ;
SHORT             sChar2 ;
SHORT             sChar3 ;
SHORT             sChar4 ;
SHORT             sChar5 ;
SHORT             sChar6 ;
SHORT             sChar7 ;
SHORT             sChar8 ;

SHORT             sLo               = 0 ;
SHORT             sHi               = 0 ;


USHORT            usStatus          = 0 ;



/*------------------------------------------------------------*/
/* Main function.                                             */
/*------------------------------------------------------------*/

main ( USHORT argc, PCHAR argv [] )
   {

   if ( argc < 2 )
      {
      printf ( "%s\n", ErrTxt1 ) ;
      DosExit ( 1, 1 ) ;
      }

   if ( strlen ( argv [ 1 ] ) < 2 )
      {
      printf ( "%s\n", ErrTxt1 ) ;
      DosExit ( 1, 1 ) ;
      }

   strcpy ( szImpLib, argv [ 1 ] ) ;

   hfImpLib = fopen ( szImpLib, "rb" ) ;

   if ( ! hfImpLib )
      {
      printf ( "\nError - Cannot open %s file\n\n", szImpLib ) ;

      DosExit ( 1, 1 ) ;
      }

   for ( i  = 0 ; i < 8 ; i++ )
      sChar = fgetc ( hfImpLib ) ;

   for ( ; ; )
      {
      sChar1   = fgetc ( hfImpLib ) ;
      sChar2   = fgetc ( hfImpLib ) ;
      sChar3   = fgetc ( hfImpLib ) ;
      sChar4   = fgetc ( hfImpLib ) ;
      sChar5   = fgetc ( hfImpLib ) ;
      sChar6   = fgetc ( hfImpLib ) ;
      sChar7   = fgetc ( hfImpLib ) ;
      sChar8   = fgetc ( hfImpLib ) ;

      cBytes   = 8 ;


               /*---------------------------------------------*/
               /* Parse the identifying character string      */
               /* which proceeds the internal name.           */
               /*---------------------------------------------*/

      for ( ; ; )
         {

         if (( sChar1 == 0 ) &&
             ( sChar2 == 0 ) &&
             ( sChar3 == 0 ) &&
             ( sChar4 == 0x80 ) &&
             ( sChar7 > 0 ) &&
             ( sChar7 < 40 ) &&
             ( sChar8 >= 'A' ) &&
             ( sChar8 <= 'Z' ))
            break ;

         if ( cBytes > 500 )
            DosExit ( EXIT_PROCESS, 0 ) ;

         sChar1   = sChar2 ;
         sChar2   = sChar3 ;
         sChar3   = sChar4 ;
         sChar4   = sChar5 ;
         sChar5   = sChar6 ;
         sChar6   = sChar7 ;
         sChar7   = sChar8 ;
         sChar8   = fgetc ( hfImpLib ) ;

         cBytes++ ;
         }

               /*---------------------------------------------*/
               /* Parse the function internal name.           */
               /*---------------------------------------------*/

      cInternalNameLen     = sChar7 ;
      szInternalName [ 0 ] = ( UCHAR ) sChar8 ;

      for ( i  = 1 ; i < cInternalNameLen ; i++ )
         {
         szInternalName [ i ] = ( UCHAR ) fgetc ( hfImpLib ) ;

         cBytes++ ;
         }

      szInternalName [ i ] = '\0' ;

      for ( i  = 0 ; i < 8 ; i++ )
         {
         sChar = fgetc ( hfImpLib ) ;

         cBytes++ ;
         }

               /*---------------------------------------------*/
               /* Parse the function external name.           */
               /*---------------------------------------------*/

      cExternalNameLen  = fgetc ( hfImpLib ) ;

      cBytes++ ;

      for ( i  = 0 ; i < cExternalNameLen ; i++ )
         {
         szExternalName [ i ] = ( UCHAR ) fgetc ( hfImpLib ) ;

         cBytes++ ;
         }

      szExternalName [ i ] = '\0' ;


               /*---------------------------------------------*/
               /* Parse the function DLL cardinal name.       */
               /*---------------------------------------------*/

      cDllNameLen          = fgetc ( hfImpLib ) ;

      cBytes++ ;

      for ( i  = 0 ; i < cDllNameLen ; i++ )
         {
         szDllName [ i ]   = ( UCHAR ) fgetc ( hfImpLib ) ;

         cBytes++ ;
         }

      szDllName [ i ]   = '\0' ;

      sLo               = fgetc ( hfImpLib ) ;

      cBytes++ ;

      sHi               = fgetc ( hfImpLib ) ;

      cBytes++ ;

      usOrdinal         = MAKEUSHORT ( sLo, sHi ) ;

      printf (
         "%-32s %s.%u\n",
         szExternalName,
         szDllName,
         usOrdinal ) ;

      }

               /* Suppress warning message.                   */
   return ( 0 ) ;

   }           /* End of main function.                       */





