#include "pch.h"
#include "tipsware.h"
#include <string.h>

#define MAX_USERS 10
int userCount = 0;

struct UserInfo {
    char id[64];
    char pw[64];
};

// 유저 관리 구조체 선언
struct UserInfo users[MAX_USERS];

// 로그인 함수
int login(struct UserInfo* users, int userCount, const char* input_id, const char* input_pw) 
{
    for (int i = 0; i < userCount; ++i) {
        // 사용자 정보와 입력된 정보를 비교하여 일치하는지 확인
        if (strcmp(users[i].id, input_id) == 0 && strcmp(users[i].pw, input_pw) == 0) 
        {
            return 1; // 로그인 성공
        }
    }

    return 0; // 로그인 실패
}

// 회원가입 함수
int registerUser(struct UserInfo* users, int* userCount, const char* input_id, const char* input_pw) 
{
    // 사용자 수가 최대 사용자 수를 초과하는지 확인
    if (*userCount >= MAX_USERS) 
    {
        return 0; // 회원가입 실패 (최대 사용자 수 초과)
    }

    // 사용자 정보 저장
    strcpy_s(users[*userCount].id, input_id);
    strcpy_s(users[*userCount].pw, input_pw);

    // 사용자 수 증가
    (*userCount)++;

    return 1; // 회원가입 성공
}

void login_page()
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

    // UI 그리기
    SelectPenObject(RGB(128, 128, 128), 2);  // 디자인 설정
    Rectangle(50, 50, 950, 550);

    SelectFontObject("consolas", 50, 1);
    printf(350, 100, "정산 프로그램");

    SelectFontObject("consolas", 40, 1);
    Rectangle(70, 200, 470, 530);
    printf(250, 215, "로그인");
    Rectangle(500, 200, 930, 530);
    printf(650, 215, "회원가입");


    // 아이디 입럭받는 에디트와 버튼
    SelectFontObject("consolas", 30, 1);
    printf(100, 300, "아이디");
    CreateEdit(200, 300, 200, 30, 300, 0);
    printf(100, 350, "비밀번호");
    CreateEdit(200, 350, 200, 30, 301, 0);
    CreateButton("로그인", 200, 400, 50, 30, 302);

    // 회원가입 입럭받는 에디트와 버튼
    SelectFontObject("consolas", 30, 1);
    printf(510, 300, "아이디");
    CreateEdit(600, 300, 200, 30, 303, 0);
    printf(510, 350, "비밀번호");
    CreateEdit(600, 350, 200, 30, 304, 0);
    CreateButton("회원가입", 600, 400, 70, 30, 305);

}

// 컨트롤을 조작했을 때 호출할 함수 만들기
void OnCommand(INT32 a_ctrl_id, INT32 a_notify_code, void* ap_ctrl)
{
    // login page 안에서의 컨트롤
    if (a_ctrl_id == 302)  // 로그인 버튼이 눌렸을 때
    {
        char id[64]; // 아이디 문자열을 저장할 변수
        void* id_edit = FindControl(300); // 아이디 에디트 컨트롤의 주소를 얻는다.
        GetCtrlName(id_edit, id, 64);

        char pw[64]; // 패스워드 문자열을 저장할 변수
        void* pw_edit = FindControl(301); // 에디트 컨트롤의 주소를 얻는다.
        GetCtrlName(pw_edit, pw, 64);

        int flag = 0;  // 로그인 성공 여부를 받을 변수(1이면 성공)
        flag = login(users, userCount, id, pw);

        if (flag == 1)
        {
            printf(300, 500, "로그인 성공");
            CreateButton("정산하러 가기", 800, 100, 100, 30, 306);
        }
        else
        {
            ::MessageBox(gh_main_wnd, "로그인에 실패하였습니다.", "로그인 실패", MB_ICONSTOP);
        }
    }

    if (a_ctrl_id == 305)  // 회원 가입 버튼이 눌렸을 때
    {
        char newid[64]; // 아이디 문자열을 저장할 변수
        void* newid_edit = FindControl(303); // 아이디 에디트 컨트롤의 주소를 얻는다.
        GetCtrlName(newid_edit, newid, 64);

        char newpw[64]; // 패스워드 문자열을 저장할 변수
        void* newpw_edit = FindControl(304); // 에디트 컨트롤의 주소를 얻는다.
        GetCtrlName(newpw_edit, newpw, 64);

        int flag = 0;  // 회원가입 성공 여부를 받을 변수(1이면 성공)
        flag = registerUser(users, &userCount, newid, newpw);
        
        if (flag == 1)
        {
            ::MessageBox(gh_main_wnd, "회원가입에 성공하였습니다.", "회원가입 성공", MB_ICONSTOP);
        }
        else
        {
            ::MessageBox(gh_main_wnd, "회원가입에 실패하였습니다.", "회원가입 실패", MB_ICONSTOP);
        }
    }

    if (a_ctrl_id == 306)  // 정산 페이지로 가는 버튼을 누르면
    {
        Clear();
    }
    ShowDisplay(); // 정보를 윈도우에 출력한다.
}

// 컨트롤을 조작했을 때 호출할 함수 등록
CMD_MESSAGE(OnCommand)

int main()
{
    login_page();

    ShowDisplay(); // 정보를 윈도우에 출력한다.
    return 0;
}
