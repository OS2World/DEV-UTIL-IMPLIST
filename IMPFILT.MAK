#--------------------------------------------------------------------*
# This is a sample make file for IMPFILT.C.                          *
#                                                                    *
# To use, enter the following at an OS/2 command line:               *
#                                                                    *
#    NMAKE /F IMPFILT.MAK                                            *
#                                                                    *
#--------------------------------------------------------------------*
# Link IMPFILT.EXE if the object components are younger.             *
# The primary target is built after the dependents are built.        *
# The module definition file provides OS/2 window compatibility.     *
#--------------------------------------------------------------------*
IMPFILT.EXE:  IMPFILT.OBJ 
   LINK  IMPFILT,IMPFILT,IMPFILT,,IMPFILT.DEF; 

#--------------------------------------------------------------------*
# Compile IMPFILT.OBJ if the source component is younger.            *
#--------------------------------------------------------------------*
IMPFILT.OBJ:  IMPFILT.C SYMTYPES.H 
   CL /AL /Lp /c /G2 /W4 IMPFILT.C











