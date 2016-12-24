// BtrieveCtl.cpp : Implimentation of CBtrieveCtrl OLE

#include "stdafx.h"
#include "Btrieve.h"
#include "btrclass.h"
#include "BtrieveCtl.h"
#include "BtrievePpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CBtrieveCtrl, COleControl)

BEGIN_MESSAGE_MAP(CBtrieveCtrl, COleControl)
	//{{AFX_MSG_MAP(CBtrieveCtrl)
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_EDIT, OnEdit)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CBtrieveCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CBtrieveCtrl)
	DISP_PROPERTY_EX(CBtrieveCtrl, "Status", GetStatus, SetStatus, VT_I4)
	DISP_FUNCTION(CBtrieveCtrl, "Open", Open, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CBtrieveCtrl, "Close", Close, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CBtrieveCtrl, "GetFirst", GetFirst, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CBtrieveCtrl, "GetNext", GetNext, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CBtrieveCtrl, "GetStringField", GetStringField, VT_BSTR, VTS_I2)
	DISP_FUNCTION(CBtrieveCtrl, "GetEqual", GetEqual, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CBtrieveCtrl, "StepFirst", StepFirst, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CBtrieveCtrl, "StepNext", StepNext, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CBtrieveCtrl, "PutStringField", PutStringField, VT_EMPTY, VTS_I2 VTS_BSTR)
	DISP_FUNCTION(CBtrieveCtrl, "Insert", Insert, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CBtrieveCtrl, "Update", Update, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CBtrieveCtrl, "Delete", Delete, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CBtrieveCtrl, "GetFieldValue", GetFieldValue, VT_VARIANT, VTS_VARIANT)
	DISP_FUNCTION(CBtrieveCtrl, "PutFieldValue", PutFieldValue, VT_BOOL, VTS_VARIANT VTS_VARIANT)
	DISP_FUNCTION(CBtrieveCtrl, "GetGTorEQ", GetGTorEQ, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CBtrieveCtrl, "GetLast", GetLast, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CBtrieveCtrl, "GetPrev", GetPrev, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CBtrieveCtrl, "GetGT", GetGT, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CBtrieveCtrl, "GetLT", GetLT, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CBtrieveCtrl, "GetLTorEQ", GetLTorEQ, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CBtrieveCtrl, "StepLast", StepLast, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CBtrieveCtrl, "StepPrev", StepPrev, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CBtrieveCtrl, "AllDelete", AllDelete, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CBtrieveCtrl, "GetRecordCount", GetRecordCount, VT_I4, VTS_NONE)
	DISP_FUNCTION(CBtrieveCtrl, "GetFieldCount", GetFieldCount, VT_I2, VTS_NONE)
	DISP_FUNCTION(CBtrieveCtrl, "GetFieldName", GetFieldName, VT_BSTR, VTS_I2)
	DISP_FUNCTION(CBtrieveCtrl, "GetFieldLength", GetFieldLength, VT_I2, VTS_I2)
	DISP_FUNCTION(CBtrieveCtrl, "SetKey", SetKey, VT_EMPTY, VTS_I2)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BEGIN_EVENT_MAP(CBtrieveCtrl, COleControl)
	//{{AFX_EVENT_MAP(CBtrieveCtrl)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()



////////////////////////////////////////////////////////////////////////////
// Property page

BEGIN_PROPPAGEIDS(CBtrieveCtrl, 1)
	PROPPAGEID(CBtrievePropPage::guid)
END_PROPPAGEIDS(CBtrieveCtrl)


IMPLEMENT_OLECREATE_EX(CBtrieveCtrl, "BTRIEVE.BtrieveCtrl.1",
	0x36f63c03, 0xade4, 0x11d0, 0x91, 0x8d, 0x44, 0x45, 0x53, 0x54, 0, 0)


IMPLEMENT_OLETYPELIB(CBtrieveCtrl, _tlid, _wVerMajor, _wVerMinor)


const IID BASED_CODE IID_DBtrieve =
		{ 0x36f63c01, 0xade4, 0x11d0, { 0x91, 0x8d, 0x44, 0x45, 0x53, 0x54, 0, 0 } };
const IID BASED_CODE IID_DBtrieveEvents =
		{ 0x36f63c02, 0xade4, 0x11d0, { 0x91, 0x8d, 0x44, 0x45, 0x53, 0x54, 0, 0 } };


static const DWORD BASED_CODE _dwBtrieveOleMisc =
	OLEMISC_INVISIBLEATRUNTIME |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CBtrieveCtrl, IDS_BTRIEVE, _dwBtrieveOleMisc)


BOOL CBtrieveCtrl::CBtrieveCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_BTRIEVE,
			IDB_BTRIEVE,
			afxRegInsertable | afxRegApartmentThreading,
			_dwBtrieveOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}

CBtrieveCtrl::CBtrieveCtrl()
{
	InitializeIIDs(&IID_DBtrieve, &IID_DBtrieveEvents);
	m_bOpened = FALSE;
}

CBtrieveCtrl::~CBtrieveCtrl()
{
	Close();
}

void CBtrieveCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// Show icon
	CBitmap bitmap;
	BITMAP  bmp;
	CPictureHolder picHolder;
	CRect rcSrcBounds;

	// Load bitmap
	bitmap.LoadBitmap(IDB_LARGE);
	bitmap.GetObject(sizeof(BITMAP), &bmp);
	rcSrcBounds.right = bmp.bmWidth;
	rcSrcBounds.bottom = bmp.bmHeight;

	// Create picture and render
	picHolder.CreateFromBitmap((HBITMAP)bitmap.m_hObject, NULL, FALSE);
	picHolder.Render(pdc, rcBounds, rcSrcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CBtrieveCtrl::DoPropExchange - support persistant

void CBtrieveCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
}

void CBtrieveCtrl::OnResetState()
{
	COleControl::OnResetState();
}

long CBtrieveCtrl::GetStatus() 
{
	return m_pBtr->Status;
}

void CBtrieveCtrl::SetStatus(long nNewValue) 
{
	SetModifiedFlag();
}


/////////////////////////////////////////////////////////////////////////////
// Open / Close

BOOL CBtrieveCtrl::Open(LPCTSTR lpszFilePath) 
{
	CString strBtrvPath = lpszFilePath;
	CString strFinfoPath = lpszFilePath;

	m_pBtr = (BTRIEVE*)new BTRIEVE(strBtrvPath + ".DAT", strFinfoPath + ".FIF");

	if(m_pBtr->Status == B_NO_ERROR)
		m_bOpened = TRUE;
	else
		m_bOpened = FALSE;

	return m_bOpened;
}

BOOL CBtrieveCtrl::Close() 
{
	if(m_bOpened == TRUE) {
		delete m_pBtr;
		m_bOpened = FALSE;
	}

	return TRUE;
}


//////////////////////////////////////////////////////////////////////////////
// Record Query

BOOL CBtrieveCtrl::GetFirst() 
{
	return m_pBtr->GetFirst() == B_NO_ERROR;
}

BOOL CBtrieveCtrl::GetLast() 
{
	return m_pBtr->GetLast() == B_NO_ERROR;
}

BOOL CBtrieveCtrl::GetNext() 
{
	return m_pBtr->GetNext() == B_NO_ERROR;
}

BOOL CBtrieveCtrl::GetPrev() 
{
	return m_pBtr->GetPrev() == B_NO_ERROR;
}

BOOL CBtrieveCtrl::GetEqual(LPCTSTR lpszFindKey) 
{
	return m_pBtr->GetEqual(lpszFindKey) == B_NO_ERROR;
}

BOOL CBtrieveCtrl::GetGT(LPCTSTR lpszFindKey) 
{
	return m_pBtr->GetGT(lpszFindKey) == B_NO_ERROR;
}

BOOL CBtrieveCtrl::GetGTorEQ(LPCTSTR lpszFindKey) 
{
	return m_pBtr->GetGTorEQ(lpszFindKey) == B_NO_ERROR;
}

BOOL CBtrieveCtrl::GetLT(LPCTSTR lpszFindKey) 
{
	return m_pBtr->GetLT(lpszFindKey) == B_NO_ERROR;
}

BOOL CBtrieveCtrl::GetLTorEQ(LPCTSTR lpszFindKey) 
{
	return m_pBtr->GetLTorEQ(lpszFindKey) == B_NO_ERROR;
}

BOOL CBtrieveCtrl::StepFirst() 
{
	return m_pBtr->StepFirst() == B_NO_ERROR;
}

BOOL CBtrieveCtrl::StepLast() 
{
	return m_pBtr->StepLast() == B_NO_ERROR;
}

BOOL CBtrieveCtrl::StepNext() 
{
	return m_pBtr->StepNext() == B_NO_ERROR;
}

BOOL CBtrieveCtrl::StepPrev() 
{
	return m_pBtr->StepPrev() == B_NO_ERROR;
}


//////////////////////////////////////////////////////////////////////////////
// Record Insert, Update, Delete...

BOOL CBtrieveCtrl::Insert() 
{
	return m_pBtr->Insert() == B_NO_ERROR;
}

BOOL CBtrieveCtrl::Update() 
{
	return m_pBtr->Update() == B_NO_ERROR;
}

BOOL CBtrieveCtrl::Delete() 
{
	return m_pBtr->Delete() == B_NO_ERROR;
}

BOOL CBtrieveCtrl::AllDelete() 
{
	return m_pBtr->AllDelete() == B_NO_ERROR;
}

long CBtrieveCtrl::GetRecordCount() 
{
	return m_pBtr->GetRecordCount();
}

//////////////////////////////////////////////////////////////////////////////
// Field Access

BSTR CBtrieveCtrl::GetStringField(short nFieldNo) 
{
	CString strResult;

	if(nFieldNo > m_pBtr->GetFieldCount()) {
		strResult = "";
	} else {
		char* lpszTemp = new char[m_pBtr->GetFieldLength(nFieldNo) + 1];
		m_pBtr->GetStringField(nFieldNo, lpszTemp);
		strResult = lpszTemp;
		delete lpszTemp;
	}

	return strResult.AllocSysString();
}

void CBtrieveCtrl::PutStringField(short nFieldNo, LPCTSTR lpszStr) 
{
	m_pBtr->PutField(nFieldNo, lpszStr);
}

short CBtrieveCtrl::GetFieldNo(const char *lpszFieldName)
{
	short nCount;

	for(nCount = 0; nCount < m_pBtr->GetFieldCount(); nCount++) {
		if(!strcmp(m_pBtr->GetFieldName(nCount), lpszFieldName)) {
			return nCount;
		}
	}

	return -1; // Can't Find
}

VARIANT CBtrieveCtrl::GetFieldValue(const VARIANT FAR& vaField) 
{
	CString strTemp;
	short nFieldNo;
	
	switch(vaField.vt) {
	case VT_I2:
		nFieldNo = vaField.iVal;
		break;
	case VT_I4:
		nFieldNo = (short)vaField.lVal;
		break;
	case VT_BSTR:
		strTemp = vaField.bstrVal;
		nFieldNo = GetFieldNo((const char *)strTemp);
		break;
	default:
		nFieldNo = -1;
	}

	if(nFieldNo > MAX_FIELD_NO || nFieldNo == -1) {
		strTemp = "";
	} else {
		char* lpszTemp = new char[m_pBtr->GetFieldLength(nFieldNo) + 1];
		m_pBtr->GetStringField(nFieldNo, lpszTemp);
		strTemp = lpszTemp;
		delete lpszTemp;
	}


	return COleVariant(strTemp).Detach();
}

BOOL CBtrieveCtrl::PutFieldValue(const VARIANT FAR& vaField, const VARIANT FAR& vaValue) 
{
	CString strTemp;
	short nFieldNo;

	switch(vaField.vt) {
	case VT_I2:
		nFieldNo = vaField.iVal;
		break;
	case VT_I4:
		nFieldNo = (short)vaField.lVal;
		break;
	case VT_BSTR:
		strTemp = vaField.bstrVal;
		nFieldNo = GetFieldNo((LPCSTR)strTemp);
		break;
	default:
		return FALSE;
	}

	if(nFieldNo > MAX_FIELD_NO || nFieldNo == -1) {
		return FALSE;
	}

	switch(vaValue.vt) {
	case VT_I2:
		//MessageBox("PutFieldValue() VT_I2", "TEST");
		m_pBtr->PutField(nFieldNo, (long)vaValue.iVal);
		break;
	case VT_I4:
		strTemp.Format("%ld", (long)vaValue.lVal);
		//MessageBox(strTemp+":PutFieldValue() VT_I4", "TEST");
		m_pBtr->PutField(nFieldNo, (long)vaValue.lVal);
		break;
	case VT_BSTR:
		strTemp = vaValue.bstrVal;
		//MessageBox(strTemp+":PutFieldValue() VT_BSTR", "TEST");
		m_pBtr->PutField(nFieldNo, (LPCSTR)strTemp);
		break;
	default:
		return FALSE;
	}

	//MessageBox("PutFieldValue() END", "TEST");

	return m_pBtr->Status == B_NO_ERROR;
}

short CBtrieveCtrl::GetFieldCount() 
{
	return m_pBtr->GetFieldCount();
}

BSTR CBtrieveCtrl::GetFieldName(short nFieldNo) 
{
	CString strResult = m_pBtr->GetFieldName(nFieldNo);
	return strResult.AllocSysString();
}

short CBtrieveCtrl::GetFieldLength(short nFieldNo) 
{
	return m_pBtr->GetFieldLength(nFieldNo);
}

void CBtrieveCtrl::SetKey(short nKeyNo) 
{
	m_pBtr->SetKey(nKeyNo);
}
