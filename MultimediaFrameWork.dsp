# Microsoft Developer Studio Project File - Name="MultimediaFrameWork" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MultimediaFrameWork - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MultimediaFrameWork.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MultimediaFrameWork.mak" CFG="MultimediaFrameWork - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MultimediaFrameWork - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MultimediaFrameWork - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MultimediaFrameWork - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "MultimediaFrameWork - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib glu32.lib glaux.lib kernel32.lib user32.lib gdi32.lib winmm.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib shlwapi.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MultimediaFrameWork - Win32 Release"
# Name "MultimediaFrameWork - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\MMF3DObject.cpp
# End Source File
# Begin Source File

SOURCE=.\MMF3DSLoader.cpp
# End Source File
# Begin Source File

SOURCE=.\MMFApp.cpp
# End Source File
# Begin Source File

SOURCE=.\MMFAppManager.cpp
# End Source File
# Begin Source File

SOURCE=.\MMFBHVNode.cpp
# End Source File
# Begin Source File

SOURCE=.\MMFBHVObjectContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\MMFBHVTree.cpp
# End Source File
# Begin Source File

SOURCE=.\MMFBitmapLoader.cpp
# End Source File
# Begin Source File

SOURCE=.\MMFDebug.cpp
# End Source File
# Begin Source File

SOURCE=.\MMFIElementButton.cpp
# End Source File
# Begin Source File

SOURCE=.\MMFIElementFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\MMFImage.cpp
# End Source File
# Begin Source File

SOURCE=.\MMFInterfaceElement.cpp
# End Source File
# Begin Source File

SOURCE=.\MMFLogFiles.cpp
# End Source File
# Begin Source File

SOURCE=.\MMFOGLWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\MMFSceneNode.cpp
# End Source File
# Begin Source File

SOURCE=.\MMFString.cpp
# End Source File
# Begin Source File

SOURCE=.\MMFStringFunctions.cpp
# End Source File
# Begin Source File

SOURCE=.\MMFStringlist.cpp
# End Source File
# Begin Source File

SOURCE=.\MMFTGALoader.cpp
# End Source File
# Begin Source File

SOURCE=.\MMFWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\MMFXml.cpp
# End Source File
# Begin Source File

SOURCE=.\MMFXmlPage.cpp
# End Source File
# Begin Source File

SOURCE=.\timer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\common.h
# End Source File
# Begin Source File

SOURCE=.\MMF3DObject.h
# End Source File
# Begin Source File

SOURCE=.\MMF3DSChunkDetails.h
# End Source File
# Begin Source File

SOURCE=.\MMF3DSLoader.h
# End Source File
# Begin Source File

SOURCE=.\MMFApp.h
# End Source File
# Begin Source File

SOURCE=.\MMFAppManager.h
# End Source File
# Begin Source File

SOURCE=.\MMFBHVNode.h
# End Source File
# Begin Source File

SOURCE=.\MMFBHVObjectContainer.h
# End Source File
# Begin Source File

SOURCE=.\MMFBHVTree.h
# End Source File
# Begin Source File

SOURCE=.\MMFBitmapLoader.h
# End Source File
# Begin Source File

SOURCE=.\MMFDebug.h
# End Source File
# Begin Source File

SOURCE=.\MMFIElementButton.h
# End Source File
# Begin Source File

SOURCE=.\MMFIElementFrame.h
# End Source File
# Begin Source File

SOURCE=.\MMFImage.h
# End Source File
# Begin Source File

SOURCE=.\MMFInterfaceElement.h
# End Source File
# Begin Source File

SOURCE=.\MMFLogFiles.h
# End Source File
# Begin Source File

SOURCE=.\MMFMathLIB.h
# End Source File
# Begin Source File

SOURCE=.\MMFMathStructures.h
# End Source File
# Begin Source File

SOURCE=.\MMFOGLWindow.h
# End Source File
# Begin Source File

SOURCE=.\MMFSceneNode.h
# End Source File
# Begin Source File

SOURCE=.\MMFString.h
# End Source File
# Begin Source File

SOURCE=.\MMFStringFunctions.h
# End Source File
# Begin Source File

SOURCE=.\MMFStringlist.h
# End Source File
# Begin Source File

SOURCE=.\MMFTGALoader.h
# End Source File
# Begin Source File

SOURCE=.\MMFUsefullEnumerations.h
# End Source File
# Begin Source File

SOURCE=.\MMFWindow.h
# End Source File
# Begin Source File

SOURCE=.\MMFXml.h
# End Source File
# Begin Source File

SOURCE=.\MMFXmlPage.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\timer.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
