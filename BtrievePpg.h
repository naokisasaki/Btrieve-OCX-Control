// BtrievePpg.h : Omplement property page CBtrievePropPage

////////////////////////////////////////////////////////////////////////////
// CBtrievePropPage : see the BtrievePpg.cpp.cpp

class CBtrievePropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CBtrievePropPage)
	DECLARE_OLECREATE_EX(CBtrievePropPage)

public:
	CBtrievePropPage();

	//{{AFX_DATA(CBtrievePropPage)
	enum { IDD = IDD_PROPPAGE_BTRIEVE };
	//}}AFX_DATA

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// Message mapping
protected:
	//{{AFX_MSG(CBtrievePropPage)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
