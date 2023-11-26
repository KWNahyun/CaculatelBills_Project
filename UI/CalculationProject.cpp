#include "pch.h"
#include "tipsware.h"

int N = 0;  // 항목 버튼 증가(?)를 위한 변수

// main page 안의 항목의 데이터를 관리하기 위한 구조체
struct ExpenseClass {
    // 각 항목에서 누가 얼마를 냈는지 관리하기 위한 구조체
    struct WhoPaid {
        char payer[10];
        int expense;
    };
};

// 멤버 정보를 관리하기 위한 구조체
struct MemberData {
    char name[10];
    int cost[10];
};
// main pge 그리기
void main_page()
{
    // 기본 화면 설정
    ChangeWorkSize(1000, 600);  // 크기
    SelectFontObject("consolas", 12, 0);  // 폰트
    SetTextColor(RGB(128, 128, 128));  // 텍스트 컬러

    // 배경 그리드(좌표 표현)
    for (int x = 0; x < 20; x++)
        printf(x * 50, 0, "%d", x * 50);
    for (int y = 1; y < 20; y++)
        printf(0, y * 50, "%d", y * 50);

    // 구역 나누는 UI 그리기
    SelectPenObject(RGB(128, 128, 128), 2);  // 디자인 설정
    Rectangle(50, 100, 300, 550); // 멤버 BOX
    Rectangle(350, 100, 650, 550); // 항목 BOX
    Rectangle(700, 100, 950, 550); // 정산 BOX

    SelectFontObject("consolas", 45, 1);
    printf(125, 50, "멤버");
    printf(445, 50, "항목");
    printf(755, 50, "정산");

    // 멤버 Box를 ListBox로 구성한다(id: 1000)
    CreateListBox(50, 100, 250, 420, 1000);
    CreateEdit(50, 520, 220, 30, 1001, 0);  // 멤버 이름을 입력할 에디트 컨트롤
    CreateButton("+", 270, 520, 30, 30, 1002);  // 에디트에 입력된 멤버 이름을 리스트 박스에 추가할 때 사용할 버튼

    // 항목 리스트를 추가할 수 있도록 하는 부분(에디트 + 버튼)
    CreateEdit(400, 490, 150, 30, 1003, 0);
    CreateButton("+", 570, 490, 30, 30, 1004);

}

// 정산 페이지 그리기
void dutch_page()
{
    // 기본 화면 설정
    ChangeWorkSize(1000, 600);  // 크기
    SelectFontObject("consolas", 12, 0);  // 폰트
    SetTextColor(RGB(128, 128, 128));  // 텍스트 컬러

    // 배경 그리드(좌표 표현)
    for (int x = 0; x < 20; x++)
        printf(x * 50, 0, "%d", x * 50);
    for (int y = 1; y < 20; y++)
        printf(0, y * 50, "%d", y * 50);

    // 구역 나누는 UI 그리기
    SelectPenObject(RGB(128, 128, 128), 2);  // 디자인 설정
    Rectangle(50, 100, 450, 550); // 전체 비용을 입력하는 구역 Box
    Rectangle(500, 100, 950, 550); // 개별 정산된 금액을 보여주는 구역 Box

    SelectFontObject("consolas", 45, 1);
    printf(200, 50, "비용");
    printf(700, 50, "정산");

}

// 컨트롤을 조작했을 때 호출할 함수 만들기
// 컨트롤의 아이디(a_ctrl_id), 컨트롤의 조작 상태(a_notify_code), 선택한 컨트롤 객체(ap_ctrl)
void OnCommand(INT32 a_ctrl_id, INT32 a_notify_code, void* ap_ctrl)
{
    // main page 안에서의 컨트롤
    if (a_ctrl_id == 1002)  // 1002번 버튼(멤버 추가)이 눌러진 경우
    {
        char str[64]; // 선택된 항목의 문자열을 저장할 변수
        void* p_edit = FindControl(1001); // 에디트 컨트롤의 주소를 얻는다.
        // 에디터(1001번) 컨트롤에 입력된 문자열을 str 배열에 복사한다.
        GetCtrlName(p_edit, str, 64);
        SetCtrlName(p_edit, ""); // 에디트 컨트롤에 쓰여진 문자열을 지운다.
        // str 배열의 내용을 리스트 박스의 마지막 위치에 추가한다.
        ListBox_InsertString(FindControl(1000), -1, str, 1);
    }

    // 항목 버튼 생성
    if (a_ctrl_id == 1004) 
    {
        char str[64];
        void* p_edit = FindControl(1003); // 에디트 컨트롤의 주소를 얻는다.
        GetCtrlName(FindControl(1003), str, 25);
        CreateButton(str, 390, 120 + 35 * N, 150, 30, 200 + N);
        N++;
        SelectFontObject("consolas", 25, 1);
        SetCtrlName(p_edit, ""); // 에디트 컨트롤에 쓰여진 문자열을 지운다.
    }

    // dutch page 안에서의 컨트롤

}

// 컨트롤을 조작했을 때 호출할 함수 등록
CMD_MESSAGE(OnCommand)

int main()
{
	
    main_page();
    // dutch_page();

    ShowDisplay(); // 정보를 윈도우에 출력한다.
    return 0;
}