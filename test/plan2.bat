@ECHO ON
@del tex*.txt
@set "PATH=%OPENCVBINPATH%;%QTBINPATH%;%PATH%"

@set EXENAME=texhelper
@set "EXEDIR=..\%EXENAME%-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK____"
@set "RELEASEEXE=%EXEDIR%\release\%EXENAME%.exe"
@set "DEBUGEXE=%EXEDIR%\debug\%EXENAME%.exe"

@set GENNAME=texgenerator
@set "GENDIR=..\%GENNAME%-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK____"
@set "GENRELEASE=%GENDIR%\release\%GENNAME%.exe"
@set "GENDEBUG=%GENDIR%\debug\%GENNAME%.exe"

@if not exist %GENRELEASE% goto NoRelease
del tex*.txt /q
del tex*.png /q
      %GENRELEASE% --autogen --interval 19 --origin 1 --size 32

:NoRelease

@if not exist %DEBUGEXE% goto NoDebug
start %DEBUGEXE%
:NoDebug

