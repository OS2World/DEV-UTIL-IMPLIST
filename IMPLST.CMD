@rem  IMPLST.CMD  -  List a module's imported functions.

@rem  %LIB% and %TEMP% below, refer to the current setting
@rem  of the environmental variables LIB and TEMP.

@rem  Substitute your path to OS2.LIB for %LIB%.
@rem  Substitute your ram drive for %TEMP%.

@IF EXIST %1 GOTO CREATE
@ECHO Usage is IMPLST file.exe,  cannot find input file %1
@GOTO END
:CREATE
@ECHO Creating import library cross-reference.
IMPLIST %LIB%\OS2.LIB > %TEMP%OS2LIB.LST
@ECHO Filtering EXEHDR output.
EXEHDR /V %1 | IMPFILT %TEMP%OS2LIB.LST > %TEMP%IMPLIST.LST
TYPE %TEMP%IMPLIST.LST
:END
