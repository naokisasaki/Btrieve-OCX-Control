# Microsoft Developer Studio Generated NMAKE File, Based on Btrieve.dsp
!IF "$(CFG)" == ""
CFG=Btrieve - Win32 Release
!MESSAGE Use the 'Win32 Release'
!ENDIF 

!IF "$(CFG)" != "Btrieve - Win32 Release" && "$(CFG)" !=\
 "Btrieve - Win32 Debug"
!MESSAGE Not recognized "$(CFG)"
!MESSAGE Please specify the option parameters in NMAKE
!MESSAGE 
!MESSAGE NMAKE /f "Btrieve.mak" CFG="Btrieve - Win32 Release"
!MESSAGE 
!MESSAGE You can choose the following options:
!MESSAGE 
!MESSAGE "Btrieve - Win32 Release" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE "Btrieve - Win32 Debug" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE 
!ERROR Invalid configurations
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Btrieve - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Btrieve.ocx" "$(OUTDIR)\Btrieve.pch" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\Btrieve.ocx" "$(OUTDIR)\Btrieve.pch" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Btrapi.obj"
	-@erase "$(INTDIR)\Btrieve.obj"
	-@erase "$(INTDIR)\Btrieve.pch"
	-@erase "$(INTDIR)\Btrieve.res"
	-@erase "$(INTDIR)\Btrieve.tlb"
	-@erase "$(INTDIR)\BtrieveCtl.obj"
	-@erase "$(INTDIR)\BtrievePpg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\Btrieve.exp"
	-@erase "$(OUTDIR)\Btrieve.lib"
	-@erase "$(OUTDIR)\Btrieve.ocx"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_USRDLL" /D "BTI_WIN_32" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)\Btrieve.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\Btrieve.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Btrieve.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=.\wbtrv32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\Btrieve.pdb" /machine:I386 /def:".\Btrieve.def"\
 /out:"$(OUTDIR)\Btrieve.ocx" /implib:"$(OUTDIR)\Btrieve.lib" 
DEF_FILE= \
	".\Btrieve.def"
LINK32_OBJS= \
	"$(INTDIR)\Btrapi.obj" \
	"$(INTDIR)\Btrieve.obj" \
	"$(INTDIR)\Btrieve.res" \
	"$(INTDIR)\BtrieveCtl.obj" \
	"$(INTDIR)\BtrievePpg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Btrieve.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Release
TargetPath=.\Release\Btrieve.ocx
InputPath=.\Release\Btrieve.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /c /s "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "Btrieve - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Btrieve.ocx" "$(OUTDIR)\Btrieve.pch" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\Btrieve.ocx" "$(OUTDIR)\Btrieve.pch" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Btrapi.obj"
	-@erase "$(INTDIR)\Btrieve.obj"
	-@erase "$(INTDIR)\Btrieve.pch"
	-@erase "$(INTDIR)\Btrieve.res"
	-@erase "$(INTDIR)\Btrieve.tlb"
	-@erase "$(INTDIR)\BtrieveCtl.obj"
	-@erase "$(INTDIR)\BtrievePpg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\Btrieve.exp"
	-@erase "$(OUTDIR)\Btrieve.ilk"
	-@erase "$(OUTDIR)\Btrieve.lib"
	-@erase "$(OUTDIR)\Btrieve.ocx"
	-@erase "$(OUTDIR)\Btrieve.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_USRDLL" /D "BTI_WIN_32" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)\Btrieve.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x411 /fo"$(INTDIR)\Btrieve.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Btrieve.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=.\wbtrv32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\Btrieve.pdb" /debug /machine:I386 /def:".\Btrieve.def"\
 /out:"$(OUTDIR)\Btrieve.ocx" /implib:"$(OUTDIR)\Btrieve.lib" 
DEF_FILE= \
	".\Btrieve.def"
LINK32_OBJS= \
	"$(INTDIR)\Btrapi.obj" \
	"$(INTDIR)\Btrieve.obj" \
	"$(INTDIR)\Btrieve.res" \
	"$(INTDIR)\BtrieveCtl.obj" \
	"$(INTDIR)\BtrievePpg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Btrieve.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\.\Debug
TargetPath=.\Debug\Btrieve.ocx
InputPath=.\Debug\Btrieve.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /c /s "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ENDIF 

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(CFG)" == "Btrieve - Win32 Release" || "$(CFG)" ==\
 "Btrieve - Win32 Debug"
SOURCE=.\Btrapi.c

!IF  "$(CFG)" == "Btrieve - Win32 Release"

DEP_CPP_BTRAP=\
	".\btitypes.h"\
	".\btrapi.h"\
	".\btrconst.h"\
	

"$(INTDIR)\Btrapi.obj" : $(SOURCE) $(DEP_CPP_BTRAP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Btrieve - Win32 Debug"

DEP_CPP_BTRAP=\
	".\btitypes.h"\
	".\btrapi.h"\
	".\btrconst.h"\
	

"$(INTDIR)\Btrapi.obj" : $(SOURCE) $(DEP_CPP_BTRAP) "$(INTDIR)"


!ENDIF 

SOURCE=.\Btrieve.cpp
DEP_CPP_BTRIE=\
	".\Btrieve.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Btrieve.obj" : $(SOURCE) $(DEP_CPP_BTRIE) "$(INTDIR)"


SOURCE=.\Btrieve.odl

!IF  "$(CFG)" == "Btrieve - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\Btrieve.tlb" /mktyplib203\
 /win32 

"$(OUTDIR)\Btrieve.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Btrieve - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\Btrieve.tlb" /mktyplib203\
 /win32 

"$(OUTDIR)\Btrieve.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Btrieve.rc

!IF  "$(CFG)" == "Btrieve - Win32 Release"

DEP_RSC_BTRIEV=\
	".\large.bmp"\
	".\Release\Btrieve.tlb"\
	".\small.bmp"\
	

"$(INTDIR)\Btrieve.res" : $(SOURCE) $(DEP_RSC_BTRIEV) "$(INTDIR)"\
 "$(INTDIR)\Btrieve.tlb"
	$(RSC) /l 0x411 /fo"$(INTDIR)\Btrieve.res" /i ".\Release" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "Btrieve - Win32 Debug"

DEP_RSC_BTRIEV=\
	".\large.bmp"\
	".\small.bmp"\
	
NODEP_RSC_BTRIEV=\
	".\Debug\Btrieve.tlb"\
	

"$(INTDIR)\Btrieve.res" : $(SOURCE) $(DEP_RSC_BTRIEV) "$(INTDIR)"\
 "$(INTDIR)\Btrieve.tlb"
	$(RSC) /l 0x411 /fo"$(INTDIR)\Btrieve.res" /i ".\Debug" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

SOURCE=.\BtrieveCtl.cpp

!IF  "$(CFG)" == "Btrieve - Win32 Release"

DEP_CPP_BTRIEVE=\
	".\btitypes.h"\
	".\btrapi.h"\
	".\btrconst.h"\
	".\Btrieve.h"\
	".\BtrieveCtl.h"\
	".\BtrievePpg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\BtrieveCtl.obj" : $(SOURCE) $(DEP_CPP_BTRIEVE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Btrieve - Win32 Debug"

DEP_CPP_BTRIEVE=\
	".\btitypes.h"\
	".\btrapi.h"\
	".\btrconst.h"\
	".\Btrieve.h"\
	".\BtrieveCtl.h"\
	".\BtrievePpg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\BtrieveCtl.obj" : $(SOURCE) $(DEP_CPP_BTRIEVE) "$(INTDIR)"


!ENDIF 

SOURCE=.\BtrievePpg.cpp
DEP_CPP_BTRIEVEP=\
	".\Btrieve.h"\
	".\BtrievePpg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\BtrievePpg.obj" : $(SOURCE) $(DEP_CPP_BTRIEVEP) "$(INTDIR)"


SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Btrieve - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_USRDLL" /D "BTI_WIN_32" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)\Btrieve.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Btrieve.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Btrieve - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_USRDLL" /D "BTI_WIN_32" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)\Btrieve.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Btrieve.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 
