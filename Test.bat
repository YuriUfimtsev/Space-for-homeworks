@echo off
for /R Homework5 %%i in (*.sln) do (msbuild %%i)
for /R Homework6 %%i in (*.sln) do (msbuild %%i)
for /R Homework7 %%i in (*.sln) do (msbuild %%i)
for /R Homework8 %%i in (*.sln) do (msbuild %%i)
for /R Homework9 %%i in (*.sln) do (msbuild %%i)
for /R Homework10 %%i in (*.sln) do (msbuild %%i)
for /R Homework11/Substring %%i in (*.sln) do (msbuild %%i)
pause
for /R Homework5 %%i in (*.exe) do (%%i tests_only & echo %%i & (IF %errorlevel%==0 (echo Tests are correct) ELSE echo Tests are INcorrect) & echo ------------)
for /R Homework6 %%i in (*.exe) do (%%i tests_only & echo %%i & (IF %errorlevel%==0 (echo Tests are correct) ELSE echo Tests are INcorrect) & echo ------------)
for /R Homework7 %%i in (*.exe) do (%%i tests_only & echo %%i & (IF %errorlevel%==0 (echo Tests are correct) ELSE echo Tests are INcorrect) & echo ------------)
for /R Homework8 %%i in (*.exe) do (%%i tests_only & echo %%i & (IF %errorlevel%==0 (echo Tests are correct) ELSE echo Tests are INcorrect) & echo ------------)
for /R Homework9 %%i in (*.exe) do (%%i tests_only & echo %%i & (IF %errorlevel%==0 (echo Tests are correct) ELSE echo Tests are INcorrect) & echo ------------)
for /R Homework10 %%i in (*.exe) do (%%i tests_only & echo %%i & (IF %errorlevel%==0 (echo Tests are correct) ELSE echo Tests are INcorrect) & echo ------------)
for /R Homework11/Substring %%i in (*.exe) do (%%i tests_only & echo %%i & (IF %errorlevel%==0 (echo Tests are correct) ELSE echo Tests are INcorrect) & echo ------------)
pause

