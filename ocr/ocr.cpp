
// ImageRecognition.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "ImageRecognition.h"
#include "ImageRecognitionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageRecognitionApp

BEGIN_MESSAGE_MAP(CImageRecognitionApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CImageRecognitionApp 생성

CImageRecognitionApp::CImageRecognitionApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CImageRecognitionApp 개체입니다.

CImageRecognitionApp theApp;


// CImageRecognitionApp 초기화

BOOL CImageRecognitionApp::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다.
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));

	CImageRecognitionDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 여기에 [확인]을 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 여기에 [취소]를 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}

	// 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고  응용 프로그램을 끝낼 수 있도록 FALSE를
	// 반환합니다.
	return FALSE;
}

/*stdafx*/
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// ImageRecognition.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"



/*OCR*/

#include "StdAfx.h"
#include "OCR.h"

//---------------------------------------------------------------------------------------------------
COCR::COCR(void)
{
	GetStandardImageDataFromBinaryFile("standard.bin");

	letterSpace.letter.value = ' ';
	letterSpace.isFixed = true;
	letterSpace.isDeleted = false;
}

//---------------------------------------------------------------------------------------------------
COCR::~COCR(void)
{
}

//---------------------------------------------------------------------------------------------------
// Standard Image Data를 만든다.
void COCR::RunOCR(CImage* newImage, CString outFileName, int colorLetter) {

	image = newImage;
	colorToCheck = colorLetter;

	for (int i = 0; i < MAX_COUNT_DATA; i++) {
		allData.data[i].isFixed = false;
		allData.data[i].isDeleted = false;
	}

	ParsingStepFirst();
	MakeImageData();

	FindLetterValue();

	AddSpaceValue();
	MakePeriodApostrophe();
	MakeQuotationMark();

	ChangeBigSmallLetter();

	//StoreLetterToTextFile(outFileName);
	StoreLetterToTextFile2(outFileName);
}

//---------------------------------------------------------------------------------------------------
void COCR::GetStandardImageDataFromBinaryFile(char* fileName) {

	FILE* fp;
	fp = fopen(fileName, "rb");

	int i, y;
	Letter* letter;

	fscanf(fp, "%d\n", &standard.count);

	for (i = 0; i < standard.count; i++) {

		letter = &standard.letter[i];

		fscanf(fp, "%c\n", &letter->value);

		for (y = 0; y < 48; y++)
			fscanf(fp, "%d\n", &letter->image[y]);
	}

	fclose(fp);
}

//---------------------------------------------------------------------------------------------------
// Image Parsing을 진행한다.
void COCR::ParsingStepFirst() {

	allData.count = 0;
	data = &allData.data[0];

	int xMax = image->GetWidth();
	int yMax = image->GetHeight();

	int x, y;
	COLORREF rgb;
	int yTop, yBottom;
	bool isLetterLine;
	bool flagPrevLine;

	int xStart = (int)(xMax * RATE_START_FOR_PARSING);
	int xEnd = (int)(xMax * RATE_END_FOR_PARSING);

	flagPrevLine = false;

	//----------- get letter lines and parse letters on each line ----------- 
	for (y = 0; y < yMax; y++) {

		isLetterLine = false;

		for (x = xStart; x < xEnd; x++) {

			rgb = image->GetPixel(x, y);

			if (GetRValue(rgb) < colorToCheck + RANGE_OF_COLOR_TO_CHECK) {
				isLetterLine = true;
				break;
			}
		}

		if (isLetterLine) {
			if (!flagPrevLine) {
				yTop = y;				//set the top of a letter line
			}
		}
		else {
			if (flagPrevLine) {
				yBottom = y - 1;

				ParsingStepSecond(yTop, yBottom);
			}
		}

		flagPrevLine = isLetterLine;
	}
}

//-------------------------------------------------------------------------------------------------
void COCR::ParsingStepSecond(int yTop, int yBottom) {

	int xMax = image->GetWidth();

	int x, y;
	COLORREF rgb;
	bool isLetterLine;
	bool flagPrevLine;

	flagPrevLine = false;

	for (x = 0; x < xMax; x++) {

		isLetterLine = false;

		for (y = yTop; y <= yBottom; y++) {
			rgb = image->GetPixel(x, y);

			if (GetRValue(rgb) < colorToCheck + RANGE_OF_COLOR_TO_CHECK) {

				isLetterLine = true;
				break;
			}
		}

		if (isLetterLine) {
			if (!flagPrevLine) {
				data->rect.start.x = x;
				data->rect.start.y = yTop;
			}
		}
		else {
			if (flagPrevLine) {

				data->rect.end.x = x - 1;
				data->rect.end.y = yBottom;

				ParsingStepThird(&data->rect);
				ParsingStepThird2(&data->rect);
				ParsingStepThird(&data->rect);

				allData.count += 1;
				data = &allData.data[allData.count];
			}
		}

		flagPrevLine = isLetterLine;
	}

	data->isFixed = true;
	data->letter.value = '\n';

	allData.count += 1;
	data = &allData.data[allData.count];
}

//-------------------------------------------------------------------------------------------------
void COCR::ParsingStepThird(Rect* rect) {

	int x, y;
	COLORREF rgb;
	bool isLetterLine;

	//------------------------------ Letter Top -------------------------------
	for (y = rect->start.y; ; y--) {

		isLetterLine = false;

		for (x = rect->start.x; x <= rect->end.x; x++) {

			rgb = image->GetPixel(x, y);

			if (GetRValue(rgb) < colorToCheck + RANGE_OF_COLOR_TO_CHECK) {
				rect->start.y = y;
				isLetterLine = true;
				break;
			}
		}
		if (!isLetterLine)
			break;
	}
	for (y = rect->start.y; ; y++) {

		isLetterLine = false;

		for (x = rect->start.x; x <= rect->end.x; x++) {

			rgb = image->GetPixel(x, y);

			if (GetRValue(rgb) < colorToCheck + RANGE_OF_COLOR_TO_CHECK) {
				rect->start.y = y;
				isLetterLine = true;
				break;
			}
		}
		if (isLetterLine)
			break;
	}
	//------------------------------ Letter Bottom -------------------------------
	for (y = rect->end.y; ; y++) {

		isLetterLine = false;

		for (x = rect->start.x; x <= rect->end.x; x++) {
			rgb = image->GetPixel(x, y);

			if (GetRValue(rgb) < colorToCheck + RANGE_OF_COLOR_TO_CHECK) {
				rect->end.y = y;
				isLetterLine = true;
				break;
			}
		}
		if (!isLetterLine)
			break;
	}
	for (y = rect->end.y;; y--) {

		isLetterLine = false;

		for (x = rect->start.x; x <= rect->end.x; x++) {
			rgb = image->GetPixel(x, y);

			if (GetRValue(rgb) < colorToCheck + RANGE_OF_COLOR_TO_CHECK) {
				rect->end.y = y;
				isLetterLine = true;
				break;
			}
		}
		if (isLetterLine)
			break;
	}
}

//-------------------------------------------------------------------------------------------------
void COCR::ParsingStepThird2(Rect* rect) {

	int x, y;
	COLORREF rgb;
	bool isLetterLine;

	//------------------------------ Letter Left -------------------------------
	for (x = rect->start.x; ; x--) {

		isLetterLine = false;

		for (y = rect->start.y; y <= rect->end.y; y++) {

			rgb = image->GetPixel(x, y);

			if (GetRValue(rgb) < colorToCheck + RANGE_OF_COLOR_TO_CHECK) {
				rect->start.x = x;
				isLetterLine = true;
				break;
			}
		}
		if (!isLetterLine)
			break;
	}
	for (x = rect->start.x; ; x++) {

		isLetterLine = false;

		for (y = rect->start.y; y <= rect->end.y; y++) {

			rgb = image->GetPixel(x, y);

			if (GetRValue(rgb) < colorToCheck + RANGE_OF_COLOR_TO_CHECK) {
				rect->start.x = x;
				isLetterLine = true;
				break;
			}
		}
		if (isLetterLine)
			break;
	}
	//------------------------------ Letter Right -------------------------------
	for (x = rect->end.x; ; x++) {

		isLetterLine = false;

		for (y = rect->start.y; y <= rect->end.y; y++) {
			rgb = image->GetPixel(x, y);

			if (GetRValue(rgb) < colorToCheck + RANGE_OF_COLOR_TO_CHECK) {
				rect->end.x = x;
				isLetterLine = true;
				break;
			}
		}
		if (!isLetterLine)
			break;
	}
	for (x = rect->end.x;; x--) {

		isLetterLine = false;

		for (y = rect->start.y; y <= rect->end.y; y++) {
			rgb = image->GetPixel(x, y);

			if (GetRValue(rgb) < colorToCheck + RANGE_OF_COLOR_TO_CHECK) {
				rect->end.x = x;
				isLetterLine = true;
				break;
			}
		}
		if (isLetterLine)
			break;
	}
}

//-------------------------------------------------------------------------------------------------
void COCR::MakeImageData() {

	int i, j;

	for (i = 0; i < allData.count; i++) {

		Data* data = &allData.data[i];
		Letter* letter = &data->letter;
		Rect* rect = &data->rect;

		if (!data->isFixed) {

			float xRate, yRate;
			int x, y;
			unsigned int buffer;
			COLORREF rgb;

			for (j = 0; j < 48; j++)
				letter->image[j] = 0x00000000;

			xRate = (float)(rect->end.x - rect->start.x) / (32 - 1);
			yRate = (float)(rect->end.y - rect->start.y) / (48 - 1);

			for (y = 0; y < 48; y++) {
				for (x = 0; x < 32; x++) {

					rgb = image->GetPixel((int)(rect->start.x + (x * xRate)), (int)(rect->start.y + (y * yRate)));

					if (GetRValue(rgb) < colorToCheck + RANGE_OF_COLOR_TO_CHECK) {
						buffer = 0x80000000;
						buffer >>= x;
						letter->image[y] |= buffer;
					}
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
void COCR::FindLetterValue() {

	int count, maxCount;
	unsigned int buffer, bit;
	int i, j, x, y;


	for (i = 0; i < allData.count; i++) {

		Data* data = &allData.data[i];
		Letter* letter = &data->letter;
		Rect* rect = &data->rect;

		if (!data->isFixed) {

			maxCount = 0;

			for (j = 0; j < standard.count; j++) {

				count = 0;

				for (y = 0; y < 48; y++) {

					buffer = letter->image[y] ^ standard.letter[j].image[y];

					for (x = 0; x < 32; x++) {

						bit = 0x80000000;
						bit >>= x;
						bit = bit & buffer;

						if (!bit)
							count += 1;
					}
				}

				if (count > maxCount) {
					letter->value = standard.letter[j].value;
					maxCount = count;
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
void COCR::AddSpaceValue() {

	int index, start, end;

	index = 0;
	start = 0;

	for (int i = 0; i < allData.count; i++) {

		if (allData.data[i].letter.value == '\n') {

			end = i;
			AddSpaceValueInLine(&index, start, end);

			start = i + 1;
		}
	}

	allDataPointer.count = index;
}

//-------------------------------------------------------------------------------------------------
void COCR::AddSpaceValueInLine(int* index, int start, int end) {

	int i;
	int gapSpace = CalculateGapSpace(start, end);

	allDataPointer.data[*index] = &allData.data[start];
	*index += 1;

	for (i = start + 1; i < end; i++) {

		Data* prevData = &allData.data[i - 1];
		Data* currData = &allData.data[i];

		if ((currData->rect.start.x - prevData->rect.end.x) > gapSpace) {
			allDataPointer.data[*index] = &letterSpace;
			*index += 1;
		}

		allDataPointer.data[*index] = &allData.data[i];
		*index += 1;
	}

	allDataPointer.data[*index] = &allData.data[i];
	*index += 1;
}

//-------------------------------------------------------------------------------------------------
int COCR::CalculateGapSpace(int start, int end) {

	int totalGap, count;

	totalGap = 0;
	count = 0;

	for (int i = start + 1; i < end; i++) {

		Data* prevData = &allData.data[i - 1];
		Data* currData = &allData.data[i];

		totalGap += (currData->rect.start.x - prevData->rect.end.x);
		count += 1;
	}

	return ((int)(totalGap / (count * 0.7))); //한줄에 10개의 space가 있으면, 보통 40개 조금 넘는 문자들이 있다.
}

//-------------------------------------------------------------------------------------------------
int COCR::CalculateMidlineValue(int index) {

	int count = 0;
	float sumHeight = 0;

	for (int i = index; i < allData.count; i++) {

		if (allData.data[i].letter.value == '\n')
			break;

		sumHeight += ((allData.data[i].rect.end.y + allData.data[i].rect.start.y) / 2);
		count += 1;
	}

	return (int)(sumHeight / count);
}

//-------------------------------------------------------------------------------------------------
void COCR::MakePeriodApostrophe() {

	int avgMidline;

	for (int i = 0; i < allData.count;) {

		avgMidline = CalculateMidlineValue(i);

		while (allData.data[i].letter.value != '\n') {

			if (allData.data[i].rect.start.y > avgMidline) {
				if ((allData.data[i].letter.value == 'I') ||
					(allData.data[i].letter.value == 'l')) {

					allData.data[i].letter.value = '.';
				}
			}
			else if (allData.data[i].rect.end.y < avgMidline) {
				if ((allData.data[i].letter.value == 'I') ||
					(allData.data[i].letter.value == 'l') ||
					(allData.data[i].letter.value == ',')) {

					allData.data[i].letter.value = 0x27;//''';
				}
			}

			i += 1;
		}
		i += 1;
	}
}

//-------------------------------------------------------------------------------------------------
void COCR::MakeQuotationMark() {

	for (int i = 0; i < allData.count; i++) {
		if (!(allData.data[i].isDeleted) && allData.data[i].letter.value == 0x27) {
			if (allData.data[i + 1].letter.value == 0x27) {
				allData.data[i].letter.value = 0x22;//'"'
				allData.data[i + 1].isDeleted = true;
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
bool COCR::isAlphabet(char value) {

	if (value >= 'A' && value <= 'Z')
		return true;
	else if (value >= 'a' && value <= 'z')
		return true;

	return false;
}

//-------------------------------------------------------------------------------------------------
bool COCR::isBigLetter(char value) {

	if (value >= 'A' && value <= 'Z')
		return true;

	return false;
}

//-------------------------------------------------------------------------------------------------
bool COCR::isSmallLetter(char value) {

	if (value >= 'a' && value <= 'z')
		return true;

	return false;
}

//-------------------------------------------------------------------------------------------------
void COCR::ChangeBigSmallLetter() {

	bool isFirstChar = true;
	char* ch, * chNext;

	for (int i = 0; i < (allData.count - 1); i++) {

		ch = &(allData.data[i].letter.value);
		chNext = &(allData.data[i + 1].letter.value);

		if (isFirstChar) {

			if (isSmallLetter(*ch)) {

				ChangeSmallToBigLetter(ch);
				isFirstChar = false;

			}
			else if (isBigLetter(*ch)) {

				isFirstChar = false;

			}
			else if (*ch == '0') { //숫자 0
				if (isAlphabet(*chNext))
					*ch = '0'; //알파벳 O

				isFirstChar = false;
			}
		}
		else {

			if (isBigLetter(*ch)) {

				ChangeBigToSmallLetter(ch);

			}
			else if (*ch == '0') { //숫자 0
				if (isAlphabet(*chNext))
					*ch = 'o'; //알파벳 o
			}

			if ((*ch == '.') || (*ch == 0x22)) {
				isFirstChar = true;
			}
		}
	}
}

//---------------------------------------------------------------------------------------------------
void COCR::ChangeBigToSmallLetter(char* value) {

	if (*value == 'I')	//대문자 'I'
		*value = 'l';	//소문자 'ㅣ'
	else if (*value == 'C')
		*value = 'c';
	else if (*value == 'O')
		*value = 'o';
	else if (*value == 'S')
		*value = 's';
	else if (*value == 'U')
		*value = 'u';
	else if (*value == 'V')
		*value = 'v';
	else if (*value == 'W')
		*value = 'w';
	else if (*value == 'X')
		*value = 'x';
	else if (*value == 'Z')
		*value = 'z';
}

//---------------------------------------------------------------------------------------------------
void COCR::ChangeSmallToBigLetter(char* value) {

	if (*value == 'l')	//소문자 'ㅣ'
		*value = 'I';	//대문자 'I'
	else if (*value == 'c')
		*value = 'C';
	else if (*value == 'o')
		*value = 'O';
	else if (*value == 's')
		*value = 'S';
	else if (*value == 'u')
		*value = 'U';
	else if (*value == 'v')
		*value = 'V';
	else if (*value == 'w')
		*value = 'W';
	else if (*value == 'x')
		*value = 'X';
	else if (*value == 'z')
		*value = 'Z';
}

//---------------------------------------------------------------------------------------------------
void COCR::StoreLetterToTextFile(CString outFileName) {

	FILE* fp;
	fp = fopen((char*)((LPCSTR)(outFileName)), "wt");

	for (int i = 0; i < allData.count; i++)
		fputc(allData.data[i].letter.value, fp);

	fclose(fp);
}

//---------------------------------------------------------------------------------------------------
void COCR::StoreLetterToTextFile2(CString outFileName) {

	FILE* fp;
	fp = fopen((char*)((LPCSTR)(outFileName)), "wt");

	for (int i = 0; i < allDataPointer.count; i++) {
		if (!(allDataPointer.data[i]->isDeleted)) {
			fputc(allDataPointer.data[i]->letter.value, fp);
		}
	}

	fclose(fp);
}

/*ImageRecognitionDlg*/
#include "stdafx.h"
#include "ImageRecognition.h"
#include "ImageRecognitionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

protected:
	DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------------------------------
CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

//---------------------------------------------------------------------------------------------------
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

//---------------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

//---------------------------------------------------------------------------------------------------
CImageRecognitionDlg::CImageRecognitionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageRecognitionDlg::IDD, pParent)
	, m_inputfile(_T("aesop_1.png"))
	, m_outputfile(_T("aesop_1.txt"))
	, m_message(_T("Press 'OCR' button."))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//---------------------------------------------------------------------------------------------------
void CImageRecognitionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INPUTFILE, m_inputfile);
	DDX_Text(pDX, IDC_EDIT_OUTPUTFILE, m_outputfile);
	DDX_Text(pDX, IDC_STATIC_MESSAGE, m_message);
}

//---------------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CImageRecognitionDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_RUNOCR, &CImageRecognitionDlg::OnBnClickedBtnRunocr)
END_MESSAGE_MAP()

//---------------------------------------------------------------------------------------------------
BOOL CImageRecognitionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	ocr = new COCR();

	return TRUE;
}

//---------------------------------------------------------------------------------------------------
void CImageRecognitionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

//---------------------------------------------------------------------------------------------------
void CImageRecognitionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//---------------------------------------------------------------------------------------------------
HCURSOR CImageRecognitionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//---------------------------------------------------------------------------------------------------
void CImageRecognitionDlg::OnBnClickedBtnRunocr()
{
	UpdateData(TRUE);

	m_message.Format(_T("OCR is Running..."));
	UpdateData(FALSE);

	if (image != NULL)
		image.Destroy();

	HRESULT hResult = image.Load(m_inputfile);

	if (FAILED(hResult)) {
		m_message.Format(_T("Error : Can't Open Input File."));
		UpdateData(FALSE);
		return;
	}

	//---------------------------- OCR --------------------------
	ocr->RunOCR(&image, m_outputfile, 50);

	m_message.Format(_T("OCR is Completed..."));
	UpdateData(FALSE);
}


