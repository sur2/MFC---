
// FileDateReadDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "FileDateRead.h"
#include "FileDateReadDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFileDateReadDlg 대화 상자



CFileDateReadDlg::CFileDateReadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILEDATEREAD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strPath = "";
}

void CFileDateReadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_PATH, m_btnPath);
	DDX_Control(pDX, IDC_EDIT_PATH, m_editPaht);
	DDX_Control(pDX, IDC_DATETIMEPICKER_MAKE, m_dtpMake);
	DDX_Control(pDX, IDC_DATETIMEPICKER_MAKE2, m_dtpMake2);
	DDX_Control(pDX, IDC_DATETIMEPICKER_MODIFY, m_dtpModify);
	DDX_Control(pDX, IDC_DATETIMEPICKER_MODIFY2, m_dtpModify2);
	DDX_Control(pDX, IDC_DATETIMEPICKER_ACCESS, m_dtpAccess);
	DDX_Control(pDX, IDC_DATETIMEPICKER_ACCESS2, m_dtpAccess2);
}

BEGIN_MESSAGE_MAP(CFileDateReadDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_PATH, &CFileDateReadDlg::OnClickedBtnPath)
	ON_BN_CLICKED(IDOK, &CFileDateReadDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CFileDateReadDlg 메시지 처리기

BOOL CFileDateReadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SetEditText();
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CFileDateReadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CFileDateReadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFileDateReadDlg::OnClickedBtnPath()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T("All files(*.*) |*.*|");
	// str = _T("Excel 파일 (*.xls, *.xlsx) |*.xls; *.xlsx|"); 와 같이 확장자를 제한하여 표시할 수 있음
	CFileDialog dlg(TRUE, _T(".dat"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

	if (dlg.DoModal() == IDOK)
	{
		m_strPath = dlg.GetPathName();
		SetDlgItemText(IDC_EDIT_PATH, m_strPath);
		// 파일을 읽어 날짜 정보 불러오기
		ReadFile(m_strPath);
	}
}

void CFileDateReadDlg::SetEditText()
{
	CRect rect;
	m_editPaht.GetRect(rect);
	rect.left += 0;
	rect.right -= 0;
	rect.top += 10;
	rect.bottom -= 0;
	m_editPaht.SetRect(rect);
}

void CFileDateReadDlg::ReadFile(CString filePath)
{
	// CreateFile에 GENERIC_READ 옵션을 사용하여 특정파일을 연다.
	HANDLE h_file = CreateFile(filePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (h_file != INVALID_HANDLE_VALUE) {

		// 지정된 파일에서 파일의 생성, 최근 사용 그리고 최근 갱신된 시간을 얻는다.
		GetFileTime(h_file, &m_ftCreate_time, &m_ftAccess_time, &m_ftWrite_time);

		SYSTEMTIME create_system_time, create_local_time;
		SYSTEMTIME write_system_time, write_local_time;
		SYSTEMTIME access_system_time, access_local_time;
		// FILETIME 구조체정보를 SYSTEMTIME 구조체 정보로 변환한다. FILETIME 구조체에 들어있는 정보는
		// 우리가 직접적으로 이용하려면 계산이 복잡해지기 때문에 사용하기 편리한 SYSTEMTIME 구조체
		// 형식으로 변환해서 사용한다.
		FileTimeToSystemTime(&m_ftCreate_time, &create_system_time);
		FileTimeToSystemTime(&m_ftWrite_time, &write_system_time);
		FileTimeToSystemTime(&m_ftAccess_time, &access_system_time);

		// FILETIME 구조체에서 SYSTEMTIME 구조체로 변환되면 시간정보가 UTC(Universal Time Coordinated) 형식의
		// 시간이기 때문에 탐색기나 기타 프로그램에서 보는 시간과 다르다. 따라서 정확한 시간정보를 얻기 위해서
		// UTC 형식의 시간을 지역시간으로 변환해야 한다. 아래의 함수는 해당 작업을 하는 함수이다.
		SystemTimeToTzSpecificLocalTime(NULL, &create_system_time, &create_local_time);
		SystemTimeToTzSpecificLocalTime(NULL, &write_system_time, &write_local_time);
		SystemTimeToTzSpecificLocalTime(NULL, &access_system_time, &access_local_time);

		// write_local_time 을 사용하면 된다.
		m_dtpMake.SetTime(create_local_time);
		//CTime ctimeMake = (create_system_time.wHour * 3600) + (create_system_time.wMinute * 60) + create_system_time.wSecond;
		m_dtpMake2.SetTime(create_local_time);

		m_dtpModify.SetTime(write_local_time);
		//CTime ctimeModify = (write_system_time.wHour * 3600) + (write_system_time.wMinute * 60) + write_system_time.wSecond;
		m_dtpModify2.SetTime(write_local_time);

		m_dtpAccess.SetTime(access_local_time);
		//CTime ctimeAccess = (access_system_time.wHour * 3600) + (access_system_time.wMinute * 60) + access_system_time.wSecond;
		m_dtpAccess2.SetTime(access_local_time);

		//UpdateData(TRUE);
		CloseHandle(h_file);
	}
}


void CFileDateReadDlg::OnBnClickedOk()
{
	if (m_strPath == "")
	{
		AfxMessageBox(_T("파일을 선택하십시오."));
	}
	else {
		HANDLE h_file = CreateFile(m_strPath, FILE_WRITE_ATTRIBUTES, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (h_file != INVALID_HANDLE_VALUE)
		{
			SYSTEMTIME create_system_time, create_local_time, create_local_time2;
			SYSTEMTIME write_system_time, write_local_time, write_local_time2;
			SYSTEMTIME access_system_time, access_local_time, access_local_time2;

			m_dtpMake.GetTime(&create_local_time);
			m_dtpModify.GetTime(&write_local_time);
			m_dtpAccess.GetTime(&access_local_time);

			m_dtpMake2.GetTime(&create_local_time2);
			m_dtpModify2.GetTime(&write_local_time2);
			m_dtpAccess2.GetTime(&access_local_time2);

			create_local_time.wHour = create_local_time2.wHour;
			create_local_time.wMinute = create_local_time2.wMinute;
			create_local_time.wSecond = create_local_time2.wSecond;

			write_local_time.wHour = write_local_time2.wHour;
			write_local_time.wMinute = write_local_time2.wMinute;
			write_local_time.wSecond = write_local_time2.wSecond;

			access_local_time.wHour = access_local_time2.wHour;
			access_local_time.wMinute = access_local_time2.wMinute;
			access_local_time.wSecond = access_local_time2.wSecond;

			TzSpecificLocalTimeToSystemTime(NULL, &write_local_time, &write_system_time);
			TzSpecificLocalTimeToSystemTime(NULL, &create_local_time, &create_system_time);
			TzSpecificLocalTimeToSystemTime(NULL, &access_local_time, &access_system_time);

			SystemTimeToFileTime(&write_system_time, &m_ftWrite_time);
			SystemTimeToFileTime(&create_system_time, &m_ftCreate_time);
			SystemTimeToFileTime(&access_system_time, &m_ftAccess_time);

			SetFileTime(h_file, &m_ftCreate_time, &m_ftAccess_time, &m_ftWrite_time);
			
			CloseHandle(h_file);

		}

	}
}
