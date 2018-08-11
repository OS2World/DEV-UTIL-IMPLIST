IMPLIST and IMPFILT are tools to help you understand the Dynamic
Link Library (DLL) function calls, which are used by a program.

The utilities EXEHDR and IMPLIB are supplied by Microsoft as part of
their C Compiler for OS/2.  



PACKAGE CONTENTS:


SYMTYPES.H   - Source code header for common symbols.

IMPLIST.C    - Source code.

IMPLIST.DEF  - Module definition file for OS/2 window compatibility.

IMPLIST.MAK  - NMAKE make file to compile implist.

IMPLIST.EXE  - An OS/2 program to list the functions contained in an import
               library.

IMPFILT.C    - Source code.

IMPFILT.DEF  - Module definition file for OS/2 window compatibility.

IMPLIST.MAK  - NMAKE make file to compile implist.

IMPFILT.EXE  - An OS/2 program to filter the listing created by EXEHDR and
               list the imported function names.

IMPLST.CMD   - Sample execution which must be tailored for your 
               ram disk configuration.

SAMPLE.TXT   - Implst run against PSTAT.EXE to show its usefulness. 

IMPLIST.TXT  - Sample from implist run against OS2.LIB.



INSTALLATION:


Copy entire contents to a subdirectory.  If you make repeated use of this
tool, then the cmd and exe files could be placed in the PATH.


DESCRIPTION:


The use of ordinal names in OS2.LIB complicates the process of figuring
out how a particular EXE file works when you do not have the source code.
I wrote IMPLIST and IMPFILT to automate this task.  IMPLIST takes any
import library as input and creates a cross-reference list showing both
the function ordinal number and full function name. IMPFILT uses this list
and filters the output of the Microsoft C utility EXEHDR.  Ordinal function
names are looked-up and the full function name is listed also.



IMPLIST  Will list exported function names and cardinal numbers
from a xxx.lib file on OS/2 1.2 and 1.3.  The lib file may be one 
supplied by the compiler vendor such as OS2.LIB or it can be created
from any xxx.DLL.


The utility IMPLIB can be used to create xxx.LIB import definition files
from any DLL which does come with one.  Simply:

   implib  xxx.LIB  xxx.DLL

   where xxx.DLL is the existing Dynamic Link Library and xxx.LIB is the
   function import library that will be created.


IMPFILT will lookup imported function names from corresponding 
cardinal numbers on the output from the MICROSOFT EXEHDR utility.

IMPFILT.C is written in an inefficient fashion since it opens and reads
the cross-reference file for each look-up.  You should put the cross
reference file on a ram disk for reasonable performance.    



AUTHOR:

    Stephen L. Reed, Stephen Reed Software.  


	 NET:        70401.3342@compuserve.com
	 BIX:        sreed
	 COMPUSERVE: 70401,3342


	 Your comments are appreciated!


COPYRIGHT

Copyright (c) 1990-91  Stephen L. Reed.  All rights reserved.

Redistribution and use in source and binary forms are permitted
provided that the above copyright notice and this paragraph are
duplicated in all such forms and that any documentation,
advertising materials, and other materials related to such
distribution and use acknowledge that the software was developed
by Stephen L. Reed.

THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
