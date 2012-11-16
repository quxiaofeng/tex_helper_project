@ECHO ON
@del tex*.txt /q
@del tex*.png /q
@set "PATH=..\libs\opencv242\bin;..\libs\qt481\bin;%PATH%"

@set EXENAME=planTwo
@set "EXEDIR=..\%EXENAME%-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK____"
@set "RELEASEEXE=%EXEDIR%\release\%EXENAME%.exe"
@set "DEBUGEXE=%EXEDIR%\debug\%EXENAME%.exe"

@if not exist %RELEASEEXE% goto NoRelease
%RELEASEEXE%
@goto Done
:NoRelease

@if not exist %DEBUGEXE% goto NoDebug
%DEBUGEXE%
@goto Done
:NoDebug

:Done


