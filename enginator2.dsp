# Microsoft Developer Studio Project File - Name="enginator2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=enginator2 - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "enginator2.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "enginator2.mak" CFG="enginator2 - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "enginator2 - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "enginator2 - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "enginator2 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /w /W0 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FAs /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib dsound.lib dinput8.lib dxerr9.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "enginator2 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /w /W0 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib dsound.lib dinput8.lib dxerr9.lib dxguid.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "enginator2 - Win32 Release"
# Name "enginator2 - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Application"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CVSS.CPP
# End Source File
# Begin Source File

SOURCE=.\CVSSReplay.cpp
# End Source File
# Begin Source File

SOURCE=.\myBenchmark.cpp
# End Source File
# Begin Source File

SOURCE=.\replay.cpp
# End Source File
# End Group
# Begin Group "myDSP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\FIR.cpp
# End Source File
# Begin Source File

SOURCE=.\IIR.cpp
# End Source File
# Begin Source File

SOURCE=.\Limiter.cpp
# End Source File
# Begin Source File

SOURCE=.\Noise.cpp
# End Source File
# End Group
# Begin Group "old DSP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CFilter2.cpp
# End Source File
# Begin Source File

SOURCE=.\CFX.CPP
# End Source File
# Begin Source File

SOURCE=.\CReverb.cpp
# End Source File
# Begin Source File

SOURCE=.\Filt.cpp
# End Source File
# Begin Source File

SOURCE=.\stk.cpp
# End Source File
# Begin Source File

SOURCE=.\stk_own.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Chain.cpp
# End Source File
# Begin Source File

SOURCE=.\ChainElement.cpp
# End Source File
# Begin Source File

SOURCE=.\ChainElements.cpp
# End Source File
# Begin Source File

SOURCE=.\CNormGraph.cpp
# End Source File
# Begin Source File

SOURCE=.\CSynth.cpp
# End Source File
# Begin Source File

SOURCE=.\engine.cpp
# End Source File
# Begin Source File

SOURCE=.\Exhaust.cpp
# End Source File
# Begin Source File

SOURCE=.\Intake.cpp
# End Source File
# Begin Source File

SOURCE=.\myLog.cpp
# End Source File
# Begin Source File

SOURCE=.\Params.cpp
# End Source File
# Begin Source File

SOURCE=.\perfWaveGuide.cpp
# End Source File
# Begin Source File

SOURCE=.\Settings.cpp
# End Source File
# Begin Source File

SOURCE=.\Waveguide.cpp
# End Source File
# Begin Source File

SOURCE=.\zylinder.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CFilter2.h
# End Source File
# Begin Source File

SOURCE=.\CFX.H
# End Source File
# Begin Source File

SOURCE=.\Chain.h
# End Source File
# Begin Source File

SOURCE=.\ChainElement.h
# End Source File
# Begin Source File

SOURCE=.\ChainElements.h
# End Source File
# Begin Source File

SOURCE=.\CLap.h
# End Source File
# Begin Source File

SOURCE=.\CNormGraph.h
# End Source File
# Begin Source File

SOURCE=.\CReverb.h
# End Source File
# Begin Source File

SOURCE=.\CSynth.h
# End Source File
# Begin Source File

SOURCE=.\CVSS.H
# End Source File
# Begin Source File

SOURCE=.\CVSSReplay.h
# End Source File
# Begin Source File

SOURCE=.\engine.h
# End Source File
# Begin Source File

SOURCE=.\Exhaust.h
# End Source File
# Begin Source File

SOURCE=.\Filt.h
# End Source File
# Begin Source File

SOURCE=.\FIR.h
# End Source File
# Begin Source File

SOURCE=.\IIR.h
# End Source File
# Begin Source File

SOURCE=.\intake.h
# End Source File
# Begin Source File

SOURCE=.\Limiter.h
# End Source File
# Begin Source File

SOURCE=.\myBenchmark.h
# End Source File
# Begin Source File

SOURCE=.\myLog.h
# End Source File
# Begin Source File

SOURCE=.\Noise.h
# End Source File
# Begin Source File

SOURCE=.\Params.h
# End Source File
# Begin Source File

SOURCE=.\perfWaveGuide.h
# End Source File
# Begin Source File

SOURCE=.\static_inline.h
# End Source File
# Begin Source File

SOURCE=.\stk.h
# End Source File
# Begin Source File

SOURCE=.\stk_own.h
# End Source File
# Begin Source File

SOURCE=.\typedef.h
# End Source File
# Begin Source File

SOURCE=.\vss_stdinc.h
# End Source File
# Begin Source File

SOURCE=.\Waveguide.h
# End Source File
# Begin Source File

SOURCE=.\zylinder.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "ASM"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\zyl.asm

!IF  "$(CFG)" == "enginator2 - Win32 Release"

# Begin Custom Build
OutDir=.\Release
InputPath=.\zyl.asm
InputName=zyl

"$(OutDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -f win32 -o $(OutDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "enginator2 - Win32 Debug"

# Begin Custom Build
OutDir=.\Debug
InputPath=.\zyl.asm
InputName=zyl

"$(OutDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -f win32 -o $(OutDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
