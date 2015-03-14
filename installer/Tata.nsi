!include "MUI2.nsh"
!include InstallOptions.nsh
!include "nsProcess.nsh"


OutFile "..\cdrom\setup.exe"
Name "TATA Photon MAX"
BrandingText "TATA Photon MAX Olive VME500 Dialer Ver 1.0.0 Setup"
InstallDir "$PROGRAMFILES32\TATA Photon MAX\Olive\VME500\"
RequestExecutionLevel admin

!define MUI_ICON "resource\logo.ico"
!define MUI_UNICON "resource\logo.ico"

!define MUI_WELCOMEFINISHPAGE_BITMAP "resource\image.bmp"
!define MUI_UNWELCOMEFINISHPAGE_BITMAP "resource\image.bmp"

;Pages
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
!define MUI_ABORTWARNING

!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH
!define MUI_UNABORTWARNING

!insertmacro MUI_LANGUAGE "English"

Function .onInit
ReadRegDWORD $language HKLM "SOFTWARE\MTC" "Language"
BringToFront
; Check if already running
System::Call "kernel32::CreateMutexA(i 0, i 0, t '$(^Name)') i .r0 ?e"
Pop $0
StrCmp $0 0 launch
StrLen $0 "$(^Name)"
IntOp $0 $0 + 1
loop:
FindWindow $1 '#32770' '' 0 $1
IntCmp $1 0 +5
System::Call "user32::GetWindowText(i r1, t .r2, i r0) i."
StrCmp $2 "$(^Name)" 0 loop
System::Call "user32::ShowWindow(i r1,i 9) i."
System::Call "user32::SetForegroundWindow(i r1) i."
Abort
launch:

advsplash::show 1000 600 400 0x04025C ..\resource\splash
FunctionEnd

Section "Desktop Shortcut" SectionX
SetOutPath $INSTDIR
SetShellVarContext current    
CreateShortCut "$DESKTOP\TATA Photon MAX.lnk" "$INSTDIR\Tata.exe" "" "$INSTDIR\Tata.exe" 0
SectionEnd

Section "Quick Launch Shortcut" SectionY
SetOutPath $INSTDIR
SetShellVarContext current   
CreateShortCut "$QUICKLAUNCH\TATA Photon MAX.lnk" "$INSTDIR\Tata.exe" "" "$INSTDIR\Tata.exe" 0
SectionEnd


Section "TATA Photon MAX"
!include "FileFunc.nsh"

${GetTime} "" "L" $0 $1 $2 $3 $4 $5 $6
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\About" "InstallDate" "$0/$1/$2,$4:$5:$6" ; GetTime

WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\About" "DialerVersion" "TTSL Olive VME500 1.0.0 Release 001"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\About" "MEID" "A10000126DE404"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\About" "SoftwareVersion" "OLME500DT01"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\About" "ESN" "8028F6E8"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\About" "PRL" "10"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\About" "HardwareVersion" "3"

WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "SidNid" "14838/3001"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "CDMAECIO" "13"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "SectorID" "8e/7e03/9f60/bb90/ab4/e651/a002/7052"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "DRC" "2"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "HDRECIO" "312"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "CDMAPNOffset" "12"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "WalshCode" "1"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "CDMAECIODB" "26"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "CHANNEL" "410"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "BandClass" "0"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "TXPower" "18"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "RXPower" "-86"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "BSPREV" "6"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "MSPREV" "9"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "PrevInUse" "6"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "PacketZoneID" "52"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "LastActiveCallState" "0"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "HDRRSSI" "87"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "CDMARSSI" "93"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "PER" "65535"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "AtState" "0"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "DormantState" "0"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "AcitveStatePNOffset" "446"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "ActiveStateECIO" "16"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "ActiveStateChannel" ""
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "NeoghborSetPNLable" "182,68,20,212,44,104,272,440,30,198,366,130,58,394,170,40,110,268,100,180,232,348,64,62,8,176,2,338,278"
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic" "NeoghborSetECIOLable" "63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63"

WriteRegDWORD HKLM "SYSTEM\CurrentControlSet\Services\Tcpip\Parameters" "TCPWindowSize" "65535"
WriteRegDWORD HKLM "SYSTEM\CurrentControlSet\Services\Tcpip\Parameters" "SackOpts" "1"
WriteRegDWORD HKLM "SYSTEM\CurrentControlSet\Services\Tcpip\Parameters" "TcpMaxDupAcks" "2"
WriteRegDWORD HKLM "SYSTEM\CurrentControlSet\Services\Tcpip\Parameters" "DefaultTTL" "64"

WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\TATA Photon MAX" "DisplayName" "TATA Photon MAX"
WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\TATA Photon MAX" "UninstallString" '"$INSTDIR\uninstall.exe"'
WriteRegDWORD HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\TATA Photon MAX" "NoModify" 1
WriteRegDWORD HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\TATA Photon MAX" "NoRepair" 1

SetOutPath $INSTDIR

CreateDirectory "$SMPROGRAMS\TATA Photon MAX\Olive\VME500"
CreateShortCut "$SMPROGRAMS\TATA Photon MAX\Olive\VME500\TATA Photon MAX.lnk" "$INSTDIR\Tata.exe" "" "$INSTDIR\Tata.exe" 0
CreateShortCut "$SMPROGRAMS\TATA Photon MAX\Olive\VME500\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\Tata.exe" 1

File ..\release\Tata.exe
File C:\QtSdk\Desktop\Qt\4.8.0\mingw\bin\libgcc_s_dw2-1.dll
File C:\QtSdk\Desktop\Qt\4.8.0\mingw\bin\mingwm10.dll        
File C:\QtSdk\Desktop\Qt\4.8.0\mingw\bin\QtCore4.dll         
File C:\QtSdk\Desktop\Qt\4.8.0\mingw\bin\QtGui4.dll
File C:\QtSdk\Desktop\Qt\4.8.0\mingw\bin\QtNetwork4.dll     
File C:\QtSdk\Desktop\Qt\4.8.0\mingw\bin\QtSql4.dll     
File C:\QtSdk\Desktop\Qt\4.8.0\mingw\bin\QtWebKit4.dll     
File C:\QtSdk\Desktop\Qt\4.8.0\mingw\bin\QtXml4.dll

File resource\DocomoTv.exe
File resource\help.chm

WriteUninstaller "uninstall.exe"

SetOutPath $INSTDIR\drivers\x86
File drivers\x86\Oliveusbser.sys

SetOutPath $INSTDIR\drivers\amd64
File drivers\amd64\Oliveusbser.sys

SetOutPath $INSTDIR\drivers
File drivers\Oliveusbmdm.inf
File drivers\Oliveusbser.inf
File drivers\oliveusbser.cat 
File drivers\dpinst.xml
File drivers\dpinst64.exe  
File drivers\dpinst32.exe

SetOutPath $INSTDIR\sqldrivers
File C:\QtSdk\Desktop\Qt\4.8.0\mingw\plugins\sqldrivers\qsqlite4.dll

SetOutPath $INSTDIR\imageformats
File C:\QtSdk\Desktop\Qt\4.8.0\mingw\plugins\imageformats\qgif4.dll
File C:\QtSdk\Desktop\Qt\4.8.0\mingw\plugins\imageformats\qico4.dll
File C:\QtSdk\Desktop\Qt\4.8.0\mingw\plugins\imageformats\qjpeg4.dll
File C:\QtSdk\Desktop\Qt\4.8.0\mingw\plugins\imageformats\qmng4.dll
File C:\QtSdk\Desktop\Qt\4.8.0\mingw\plugins\imageformats\qsvg4.dll
File C:\QtSdk\Desktop\Qt\4.8.0\mingw\plugins\imageformats\qtiff4.dll

;Get Tata.exe date time for registry key 
${GetTime} "$INSTDIR\Tata.exe" "C" $0 $1 $2 $3 $4 $5 $6
WriteRegStr HKLM "SOFTWARE\TATA Photon MAX\VME500\About" "CompileDate" "$0/$1/$2,$4:$5:$6" ; GetFileTime
WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\MTC" "DisplayIcon" "$INSTDIR\logo.ico"
SectionEnd

Section "Drivers"
!include "x64.nsh"
${If} ${RunningX64}
ExecWait $INSTDIR\drivers\dpinst64.exe
${Else}
ExecWait $INSTDIR\drivers\dpinst32.exe
${EndIf} 
SectionEnd

Section "Docomo TV"
ExecWait $INSTDIR\DocomoTv.exe
SectionEnd

Section "Uninstall"

${nsProcess::FindProcess} "MTC.exe" $R0
StrCmp $R0 0 0 +2
MessageBox MB_OKCANCEL|MB_ICONEXCLAMATION "Tata Photon MAX is RUNNING!\nDo you want to STOP it?" IDOK kill IDCANCEL end
kill:
${nsProcess::KillProcess} "MTC.exe" $R0


!include "x64.nsh"
${If} ${RunningX64}
ExecWait '"$INSTDIR\drivers\dpinst64.exe" /S /D /U "$INSTDIR\drivers\oliveusbmdm.inf"'
ExecWait '"$INSTDIR\drivers\dpinst64.exe" /S /D /U "$INSTDIR\drivers\oliveusbser.inf"'
${Else}
ExecWait '"$INSTDIR\drivers\dpinst32.exe" /S /D /U "$INSTDIR\drivers\oliveusbmdm.inf"'
ExecWait '"$INSTDIR\drivers\dpinst32.exe" /S /D /U "$INSTDIR\drivers\oliveusbser.inf"'
${EndIf}
; Remove registry keys
DeleteRegKey HKLM "SOFTWARE\TATA Photon MAX\VME500\About"
DeleteRegKey HKLM "SOFTWARE\TATA Photon MAX\VME500\Diagnostic"
DeleteRegKey HKLM "SOFTWARE\TATA Photon MAX\VME500"
DeleteRegKey HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\TATA Photon MAX"
DeleteRegKey HKCU "SOFTWARE\Microsoft\Windows\CurrentVersion\Run\TATA Photon Max VME500"

; Remove files and uninstaller
Delete $INSTDIR\uninstall.exe
Delete $INSTDIR\Tata.exe
Delete $INSTDIR\libgcc_s_dw2-1.dll
Delete $INSTDIR\mingwm10.dll       
Delete $INSTDIR\QtCore4.dll        
Delete $INSTDIR\QtGui4.dll
Delete $INSTDIR\QtNetwork4.dll     
Delete $INSTDIR\QtSql4.dll     
Delete $INSTDIR\QtWebKit4.dll     
Delete $INSTDIR\QtXml4.dll
Delete $INSTDIR\DocomoTv.exe  
Delete $INSTDIR\help.chm
Delete $INSTDIR\sqldrivers\qsqlite4.dll
Delete $INSTDIR\imageformats\qgif4.dll
Delete $INSTDIR\imageformats\qico4.dll
Delete $INSTDIR\imageformats\qjpeg4.dll
Delete $INSTDIR\imageformats\qmng4.dll
Delete $INSTDIR\imageformats\qsvg4.dll
Delete $INSTDIR\imageformats\qtiff4.dll
Delete $INSTDIR\olive


;Driver Files
Delete $INSTDIR\drivers\Oliveusbmdm.inf
Delete $INSTDIR\drivers\Oliveusbser.inf
Delete $INSTDIR\drivers\oliveusbser.cat  
Delete $INSTDIR\drivers\dpinst32.exe 
Delete $INSTDIR\drivers\dpinst64.exe
Delete $INSTDIR\drivers\dpinst.xml
Delete $INSTDIR\drivers\x86\Oliveusbser.sys  
Delete $INSTDIR\drivers\amd64\Oliveusbser.sys
Delete $INSTDIR\drivers\max_64X64.ico

; Remove shortcuts, if any
Delete "$SMPROGRAMS\TATA Photon MAX\Olive\VME500\TATA Photon MAX.lnk"
Delete "$SMPROGRAMS\TATA Photon MAX\Olive\VME500\Uninstall.lnk"
Delete "$DESKTOP\TATA Photon MAX.lnk"
Delete "$QUICKLAUNCH\TATA Photon MAX.lnk"

; Remove Temporary Files
Delete "$TEMP\dialer-R1.html"
Delete "$TEMP\dialer-1.html"  
Delete "$TEMP\OliveConnectionLog.txt"
Delete "$TEMP\images\photon-right.jpg"
Delete "$TEMP\images\photon-left.jpg"
RMDir "$TEMP\images"

; Remove directories used
RMDir "$SMPROGRAMS\TATA Photon MAX\Olive\VME500"
RMDir "$SMPROGRAMS\TATA Photon MAX\Olive"
RMDir "$SMPROGRAMS\TATA Photon MAX"

RMDir "$INSTDIR\imageformats"
RMDir "$INSTDIR\drivers\x86"
RMDir "$INSTDIR\drivers\amd64"
RMDir "$INSTDIR\drivers"
RMDir "$INSTDIR\sqldrivers"
RMDir "$INSTDIR"

RMDir "$PROGRAMFILES32\TATA Photon MAX\Olive\VME500"
RMDir "$PROGRAMFILES32\TATA Photon MAX\Olive\"
RMDir "$PROGRAMFILES32\TATA Photon MAX\"

end:
SectionEnd
