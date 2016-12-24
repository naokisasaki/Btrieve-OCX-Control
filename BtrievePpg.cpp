
// BtrievePpg.cpp : Implement of CBtrievePropPage

#include "stdafx.h"
#include "Btrieve.h"
#include "BtrievePpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CBtrievePropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message mapping

BEGIN_MESSAGE_MAP(CBtrievePropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CBtrievePropPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

IMPLEMENT_OLECREATE_EX(CBtrievePropPage, "BTRIEVE.BtrievePropPage.1",
	0x36f63c04, 0xade4, 0x11d0, 0x91, 0x8d, 0x44, 0x45, 0x53, 0x54, 0, 0)

BOOL CBtrievePropPage::CBtrievePropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_BTRIEVE_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

CBtrievePropPage::CBtrievePropPage() :
	COlePropertyPage(IDD, IDS_BTRIEVE_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CBtrievePropPage)
	// メモ: ClassWizard はこの位置にメンバの初期化処理を追加します
	//    この位置に生成されるコードを編集しないでください！
	//}}AFX_DATA_INIT
}

void CBtrievePropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CBtrievePropPage)
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}
