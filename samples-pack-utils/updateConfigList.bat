@ECHO OFF

call :getabs "../../configurations.cfg"

echo AUTO UPDATE 'configurations.cfg'
echo This will add all folders begining by "./config/SAMPLE_" to "%abspath%"

:choice
set /P c=Are you sure you want to continue [Y/N]?
if /I "%c%" EQU "Y" goto :update
if /I "%c%" EQU "N" goto :cancel
goto :choice

:update
for /f %%c IN ('dir "../config/" /a:d /b ^| findstr /b "SAMPLE_"') do (
	echo adding %%c...
	echo %%c = ${STUDIO_PATH}/SCANeRstudio_2022/config/%%c >> ../../configurations.cfg
)
echo successfully updated "%abspath%".
pause
goto :eof

:cancel
echo 'configurations.cfg' was not updated.
pause
goto :eof

:getabs
  SET abspath=%~f1
  EXIT /B
