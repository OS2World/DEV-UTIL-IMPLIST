/* 
 *
 * SYNOPSIS	    ( OS/2 )
 *
 *	EXEHDR /V  exe-path | IMPFILT implist-path > IMPLIST.LST" ;
 *
 *
 *
 * DESCRIPTION
 *
 * 	IMPFILT  Will lookup imported function names from corresponding 
 *	cardinal numbers on the output from the MICROSOFT EXEHDR utility.
 *	The implist-path is a file created by the IMPLIST program included
 *	in this package.  This can be helpful when reverse engineering a 
 * software component such as PSTAT.EXE.
 *
 *
 * COMPILATION
 *
 *	See impfilt.mak for a simple makefile to be used with NMAKE. 
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

CHAR              szImpList [ 20 ]     = "" ;
FILE *            hfImpList ;

PCHAR             ErrTxt1              =
   "Usage: EXEHDR /V  exe-path | IMPFILT implist-path > IMPLIST.LST" ;

USHORT            cExternalNameLen     = 0 ;
UCHAR             szExternalName [ 50 ] ;
PUCHAR            pszExternalName      = szExternalName ;

USHORT            cDllFunctionLen      = 0 ;
UCHAR             szDllFunction [ 50 ] ;
PUCHAR            pszDllFunction       = szDllFunction ;

USHORT            usStatus             = 0 ;

CHAR              szText [ 200 ]       = "" ;
CHAR *            pszText ;
USHORT            cTextLen ;
CHAR              szLookupText [ 200 ] = "" ;
CHAR *            pszLookupText ;


PUCHAR            LookupExternalName ( PUCHAR szDllFunction ) ;


/*------------------------------------------------------------*/
/* Main function.                                             */
/*------------------------------------------------------------*/

main ( USHORT argc, PCHAR argv [] )
   {

   if ( argc < 2 )
      {
      printf ( "%s\n", ErrTxt1 ) ;
      exit ( 1 ) ;
      }

   if ( strlen ( argv [ 1 ] ) < 2 )
      {
      printf ( "%s\n", ErrTxt1 ) ;
      exit ( 1 ) ;
      }

   strcpy ( szImpList, argv [ 1 ] ) ;


               /*---------------------------------------------*/
               /* Copy the file.                              */
               /*---------------------------------------------*/


   pszText  = gets ( szText ) ;

   while ( pszText )
      {
      cTextLen = strlen ( szText ) ;

               /*---------------------------------------------*/
               /* For imported functions, lookup the DLL      */
               /* Ordinal and append the function external    */
               /* name.                                       */
               /*---------------------------------------------*/

      if (( cTextLen > 25 ) &&
          ( strncmp ( pszText + 16, "  imp ", 6 ) == 0 ))
         {
         USHORT   cSpacesToInsert   = 0 ;

         pszText += 22 ;
         pszDllFunction = szDllFunction ;

         while ( *pszText )
            *pszDllFunction++ = *pszText++ ;

         *pszDllFunction++    = '\0' ;

         if ( cTextLen < 40 )
            cSpacesToInsert   = 40 - cTextLen ;

         strncat (
            szText,
            "                    ",
            cSpacesToInsert ) ;

         strcat (
            szText,
            LookupExternalName ( szDllFunction )) ;

         }

      puts ( szText ) ;


      pszText  = gets ( szText ) ;

      }

   exit ( 0 ) ;

               /* Suppress warning message.                   */
   return ( 0 ) ;

   }           /* End of main function.                       */



/*------------------------------------------------------------*/
/* Lookup External Name.                                      */
/*------------------------------------------------------------*/

PUCHAR            LookupExternalName ( PUCHAR szDllFunction )
   {
   strcpy ( szExternalName, "" ) ;
   hfImpList                        = fopen ( szImpList, "r" ) ;

   if ( ! hfImpList )
      {
      printf ( "\nError - Cannot open %s file\n\n", szImpList ) ;

      exit ( 1 ) ;
      }

   for ( ; ; )
      {

      pszLookupText  = fgets ( szLookupText, 200, hfImpList ) ;

               /*---------------------------------------------*/
               /* Not found.                                  */
               /*---------------------------------------------*/

      if ( ! pszLookupText )
         break ;

      cDllFunctionLen   = strlen ( szDllFunction ) ;

      if ( cDllFunctionLen + 34 == strlen ( szLookupText ))
         {

         if ( strncmp ( pszLookupText + 33, szDllFunction, cDllFunctionLen )
              == 0 )
            {
               /*---------------------------------------------*/
               /* Found.                                      */
               /*---------------------------------------------*/

            pszExternalName   = szExternalName ;

            while ( *pszLookupText != ' ' )
               *pszExternalName++  = *pszLookupText++ ;

            *pszExternalName       = '\0' ;

            break ;
            }
         }
      }

   fclose ( hfImpList ) ;

   return ( szExternalName ) ;

   }           /* End of LookupExternalName function.         */










