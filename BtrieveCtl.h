// max of fields
#define MAX_FIELD_NO	255

// error status
#define SYS_FILEIO_ERROR	-1
#define SYS_INVALID_TYPE	-2
#define SYS_NO_FIELD		-3


/////////////////////////////////////////////////////////////////////////////
// CBtrieveCtrl : Control Class

class CBtrieveCtrl : public COleControl
{
	DECLARE_DYNCREATE(CBtrieveCtrl)

public:
	CBtrieveCtrl();

	//{{AFX_VIRTUAL(CBtrieveCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

protected:
	~CBtrieveCtrl();

	DECLARE_OLECREATE_EX(CBtrieveCtrl)
	DECLARE_OLETYPELIB(CBtrieveCtrl)
	DECLARE_PROPPAGEIDS(CBtrieveCtrl)
	DECLARE_OLECTLTYPE(CBtrieveCtrl)

	//{{AFX_MSG(CBtrieveCtrl)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	//{{AFX_DISPATCH(CBtrieveCtrl)
	afx_msg long GetStatus();
	afx_msg void SetStatus(long nNewValue);
	afx_msg BOOL Open(LPCTSTR filePath);
	afx_msg BOOL Close();
	afx_msg BOOL GetFirst();
	afx_msg BOOL GetNext();
	afx_msg BSTR GetStringField(short fieldNo);
	afx_msg BOOL GetEqual(LPCTSTR findKey);
	afx_msg BOOL StepFirst();
	afx_msg BOOL StepNext();
	afx_msg void PutStringField(short fieldNo, LPCTSTR strValue);
	afx_msg BOOL Insert();
	afx_msg BOOL Update();
	afx_msg BOOL Delete();
	afx_msg VARIANT GetFieldValue(const VARIANT FAR& field);
	afx_msg BOOL PutFieldValue(const VARIANT FAR& field, const VARIANT FAR& value);
	afx_msg BOOL GetGTorEQ(LPCTSTR findkey);
	afx_msg BOOL GetLast();
	afx_msg BOOL GetPrev();
	afx_msg BOOL GetGT(LPCTSTR strFindKey);
	afx_msg BOOL GetLT(LPCTSTR lpszFindKey);
	afx_msg BOOL GetLTorEQ(LPCTSTR lpszFindKey);
	afx_msg BOOL StepLast();
	afx_msg BOOL StepPrev();
	afx_msg BOOL AllDelete();
	afx_msg long GetRecordCount();
	afx_msg short GetFieldCount();
	afx_msg BSTR GetFieldName(short FieldNo);
	afx_msg short GetFieldLength(short nFieldNo);
	afx_msg void SetKey(short nKeyNo);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	//{{AFX_EVENT(CBtrieveCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

public:
	enum {
	//{{AFX_DISP_ID(CBtrieveCtrl)
	dispidStatus = 1L,
	dispidOpen = 2L,
	dispidClose = 3L,
	dispidGetFirst = 4L,
	dispidGetNext = 5L,
	dispidGetStringField = 6L,
	dispidGetEqual = 7L,
	dispidStepFirst = 8L,
	dispidStepNext = 9L,
	dispidPutStringField = 10L,
	dispidInsert = 11L,
	dispidUpdate = 12L,
	dispidDelete = 13L,
	dispidGetFieldValue = 14L,
	dispidPutFieldValue = 15L,
	dispidGetGTorEQ = 16L,
	dispidGetLast = 17L,
	dispidGetPrev = 18L,
	dispidGetGT = 19L,
	dispidGetLT = 20L,
	dispidGetLTorEQ = 21L,
	dispidStepLast = 22L,
	dispidStepPrev = 23L,
	dispidAllDelete = 24L,
	dispidGetRecordCount = 25L,
	dispidGetFieldCount = 26L,
	dispidGetFieldName = 27L,
	dispidGetFieldLength = 28L,
	dispidSetKey = 29L,
	//}}AFX_DISP_ID
	};

private:
	BTRIEVE* m_pBtr;
	BOOL m_bOpened;
	short GetFieldNo(const char *fieldName);
};
