// ImageRecognition.h : PROJECT_NAME 
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.


// CImageRecognitionApp:


class CImageRecognitionApp : public CWinAppEx
{
public:
	CImageRecognitionApp();

// 재정의입니다.
	public:
	virtual BOOL InitInstance();

// 구현입니다.

	DECLARE_MESSAGE_MAP()
};

extern CImageRecognitionApp theApp;

//targetver.h//

#pragma once


#ifndef WINVER                          
#define WINVER 0x0600           
#endif

#ifndef _WIN32_WINNT            
#define _WIN32_WINNT 0x0600     
#endif

#ifndef _WIN32_WINDOWS          
#define _WIN32_WINDOWS 0x0410 
#endif

#ifndef _WIN32_IE                       
#define _WIN32_IE 0x0700      
#endif

//stdafx.h//



#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.


#include <afxdisp.h>        // MFC 자동화 클래스입니다.



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


//resource.h//
//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by ImageRecognition.rc
//
#define IDM_ABOUTBOX                    0x0010
#define IDD_ABOUTBOX                    100
#define IDS_ABOUTBOX                    101
#define IDD_IMAGERECOGNITION_DIALOG     102
#define IDR_MAINFRAME                   128
#define IDC_BTN_RUNOCR                  1000
#define IDC_EDIT_INPUTFILE              1001
#define IDC_EDIT_OUTPUTFILE             1002
#define IDC_STATIC_MESSAGE              1003

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        129
#define _APS_NEXT_COMMAND_VALUE         32771
#define _APS_NEXT_CONTROL_VALUE         1004
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif

//OCR.h//
#pragma once

//---------------------------------------------------------------------------------------------------
#define MAX_COUNT_STANDARD			80
#define MAX_COUNT_DATA				2000
#define RANGE_OF_COLOR_TO_CHECK		130

#define RATE_START_FOR_PARSING		0.1
#define RATE_END_FOR_PARSING		0.3

//---------------------------------------------------------------------------------------------------
struct Point {
	int x;
	int y;
};

struct Rect {
	Point start;
	Point end;
};

struct Letter {
	char value;
	unsigned int image[48];
};

struct Standard {
	int count;
	Letter letter[MAX_COUNT_STANDARD];
};

struct Data {
	bool isFixed;
	bool isDeleted;
	Letter letter;
	Rect rect;
};

struct AllData {
	int count;
	Data data[MAX_COUNT_DATA];
};

struct AllDataPointer {
	int count;
	Data* data[MAX_COUNT_DATA + MAX_COUNT_DATA];
};

//---------------------------------------------------------------------------------------------------
class COCR {

private:
	CImage* image;
	Standard standard;
	AllData allData;
	AllDataPointer allDataPointer;
	Data* data;

	Data letterSpace;

	int colorToCheck;

public:
	COCR(void);
	~COCR(void);

	void RunOCR(CImage* image, CString outFileName, int colorLetter);
	void GetStandardImageDataFromBinaryFile(char* fileName);
	void ParsingStepFirst();
	void ParsingStepSecond(int yTop, int yBottom);
	void ParsingStepThird(Rect* rect);
	void ParsingStepThird2(Rect* rect);
	void MakeImageData();
	void MakeLetterData(Rect* rect);
	void FindLetterValue();
	void AddSpaceValue();
	void AddSpaceValueInLine(int* index, int start, int end);
	int CalculateGapSpace(int start, int end);

	int CalculateMidlineValue(int index);
	void MakePeriodApostrophe();
	void MakeQuotationMark();

	bool isAlphabet(char value);
	bool isBigLetter(char value);
	bool isSmallLetter(char value);
	void ChangeBigSmallLetter();
	void ChangeBigToSmallLetter(char* value);
	void ChangeSmallToBigLetter(char* value);

	void StoreLetterToTextFile(CString outFileName);
	void StoreLetterToTextFile2(CString outFileName);
	//void PrintImageToFile(int fileNo, Rect *rect);
	//void PrintImageDataToFile(int fileNo, Letter *letter);
	//void PrintEveryImageDataInTextFile(char * fileName);
	//void GetStandardImageDataFromTextFile(char * fileName);
	//void PrintEveryImageDataInBinaryFile(char * fileName);
	//void PrintAllStandardImageToTextFile(char * fileName);
};


//imagerecognitionDlg.h//
#pragma once

#include "OCR.h"

//---------------------------------------------------------------------------------------------------
class CImageRecognitionDlg : public CDialog
{
public:

	COCR* ocr;
	CImage image;

	CString m_inputfile;
	CString m_outputfile;
	CString m_message;

	CImageRecognitionDlg(CWnd* pParent = NULL);
	enum { IDD = IDD_IMAGERECOGNITION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedBtnRunocr();
};

