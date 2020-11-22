
// FileDateReadDlg.h: 헤더 파일
//

#pragma once


// CFileDateReadDlg 대화 상자
class CFileDateReadDlg : public CDialogEx
{
// 생성입니다.
public:
	CFileDateReadDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILEDATEREAD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_btnPath;
	CEdit m_editPaht;
	CDateTimeCtrl m_dtpMake;
	CDateTimeCtrl m_dtpMake2;
	CDateTimeCtrl m_dtpModify;
	CDateTimeCtrl m_dtpModify2;
	CDateTimeCtrl m_dtpAccess;
	CDateTimeCtrl m_dtpAccess2;
	afx_msg void OnBnClickedOk();
	afx_msg void OnClickedBtnPath();

private:
	CString m_strPath;
	FILETIME m_ftCreate_time, m_ftAccess_time, m_ftWrite_time;
	void SetEditText();
	void ReadFile(CString filePath);

};
