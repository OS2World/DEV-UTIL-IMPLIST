#--------------------------------------------------------------------*
# This is a sample make file for IMPLIST.C.                          *
#                                                                    *
# To use, enter the following at an OS/2 command line:               *
#                                                                    *
#    NMAKE /F IMPLIST.MAK                                            *
#                                                                    *
#--------------------------------------------------------------------*
# Link IMPLIST.EXE if the object components are younger.             *
# The primary target is built after the dependents are built.        *
# The module definition file provides OS/2 window compatibility.     *
#--------------------------------------------------------------------*
IMPLIST.EXE:  IMPLIST.OBJ 
   LINK  IMPLIST,IMPLIST,IMPLIST,,IMPLIST.DEF; 

#--------------------------------------------------------------------*
# Compile IMPLIST.OBJ if the source component is younger.            *
#--------------------------------------------------------------------*
IMPLIST.OBJ:  IMPLIST.C SYMTYPES.H 
   CL /AL /Lp /c /G2 /W4 IMPLIST.C









