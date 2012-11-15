@ECHO ON
@del tex*.txt
@set "PATH=%QTBINPATH%;%PATH%"

@set EXENAME=texhelper
@set "EXEDIR=..\%EXENAME%-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK____"
@set "RELEASEEXE=%EXEDIR%\release\%EXENAME%.exe"
@set "DEBUGEXE=%EXEDIR%\debug\%EXENAME%.exe"

@set GENNAME=texgenerator
@set "GENDIR=..\%GENNAME%-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK____"
@set "GENRELEASE=%GENDIR%\release\%GENNAME%.exe"
@set "GENDEBUG=%GENDIR%\debug\%GENNAME%.exe"

@if not exist %RELEASEEXE% goto NoRelease
      %GENRELEASE% --filename tex1.txt --interval 7 --origin 1 --size 32
      %GENRELEASE% --filename tex1.txt --interval 7 --origin 9 --size 32
      %GENRELEASE% --filename tex2.txt --interval 6 --origin 3 --size 32
      %GENRELEASE% --filename tex2.txt --interval 6 --origin 16 --size 32
      %GENRELEASE% --filename tex2.txt --interval 7 --origin 19 --size 32
      %GENRELEASE% --filename tex3.txt --interval 9 --origin 20 --size 32
      %GENRELEASE% --filename tex4.txt --interval 8 --origin 31 --size 32
      %GENRELEASE% --filename tex5.txt --interval 1 --origin 12 --size 32
      %GENRELEASE% --filename tex6.txt --interval 0 --origin 23 --size 32
      %GENRELEASE% --filename tex7.txt --interval 22 --origin 13 --size 32
      %GENRELEASE% --filename tex8.txt --interval 15 --origin 32 --size 32
      %GENRELEASE% --filename tex9.txt --interval 6 --origin 8 --size 32
      %GENRELEASE% --filename tex10.txt --interval 9 --origin 6 --size 32
      %RELEASEEXE% --input-number 10 --size 32 tex1.txt tex2.txt tex3.txt tex4.txt tex5.txt tex6.txt tex7.txt tex8.txt tex9.txt tex10.txt --output-filename texWeaveSuccess.txt
      %GENRELEASE% -f tex21.txt -i 5 -o 3 -s 16
      %GENRELEASE% -f tex22.txt -i 6 -o 8 -s 16
      %GENRELEASE% -f tex23.txt -i 9 -o 6 -s 16
      %RELEASEEXE% -n 3 -s 16 tex21.txt tex22.txt tex23.txt -o texWeaveMini.txt
:NoRelease

@if not exist %DEBUGEXE% goto NoDebug
start %DEBUGEXE%
:NoDebug

