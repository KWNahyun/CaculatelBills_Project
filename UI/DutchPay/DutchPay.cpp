#include "pch.h"
#include "tipsware.h"
#include <string.h>

//********************************** <권나현 시작> ******************************************
// login page 데이터 관리
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

// login page 구성
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
    CreateEdit(200, 300, 200, 30, 3000, 0);
    printf(100, 350, "비밀번호");
    CreateEdit(200, 350, 200, 30, 3001, 0);
    CreateButton("로그인", 200, 400, 50, 30, 3002);

    // 회원가입 입럭받는 에디트와 버튼
    SelectFontObject("consolas", 30, 1);
    printf(510, 300, "아이디");
    CreateEdit(600, 300, 200, 30, 3003, 0);
    printf(510, 350, "비밀번호");
    CreateEdit(600, 350, 200, 30, 3004, 0);
    CreateButton("회원가입", 600, 400, 70, 30, 3005);


}
//*********************************<권나현 끝>******************************************************
// main page 데이터 관리

//개인항목 데이터 관리
int get_value1 = 0; //첫번째 구성원 개인 항목가격1 (ID:10002)
int get_value2 = 0; //첫번째 구성원 개인 항목 가격2 (20004)
int get_value3 = 0; //두번째구성원 개인 항목 가격1 (10004)
int get_value4 = 0;  //두번째구성원 개인 항목 가격2 (20004)
int get_value5 = 0;  //세번째구성원 개인 항목 가격1 (10006)
int get_value6 = 0;  //세번째 구성원 개인 항목 가격2 (20006)
int N = 0;
char personal_item[50][50];
char personal_names[50][50];



//멤버 정보 관리 구조체
struct MemberData {
	char name[10];
	int cost[10];
};

//저장..
char names[50][50];  //멤버
char item[50][50];   //공동비용 상품이름저장
int price[50];       //공동비용 상품 가격 
char name_paid[50][50];  //공동비용 지불자 이름



// main page 구성
void main_page() {
	ChangeWorkSize(1000, 600);
	SelectFontObject("consolas", 12, 0);
	SetTextColor(RGB(128, 128, 128));
	for (int x = 0; x < 20; x++) printf(x * 50, 0, "%d", x * 50);   //x좌표
	for (int y = 1; y < 20; y++)  printf(0, y * 50, "%d", y * 50); //y좌표
	SelectPenObject(RGB(128, 128, 128), 2); //박스선 색,두께
	Rectangle(50, 100, 300, 550); //MEMBER BOX
	Rectangle(350, 100, 650, 550); //공동비용 BOX
	Rectangle(700, 100, 950, 550); //개인비용 BOX
	CreateButton("NEXT", 900, 50, 30, 30, 3007);  //정산결과출력하기 버튼 ID :3007

	SelectFontObject("consolas", 45, 1);
	printf(125, 50, "MEMBER");
	printf(445, 50, "공동비용");
	printf(755, 50, "개인비용");


	CreateEdit(95, 490, 120, 30, 101, 0);  //멤버 이름 입력에디트 컨트롤(id:101)
	CreateButton("+", 220, 490, 30, 30, 1000);  //멤버 추가 버튼 (id=1000)


	//공동비용 부분 에디트 박스 
	SelectPenObject(RGB(128, 128, 128), 1);
	Rectangle(360, 110, 640, 540); //그냥 디자인용 박스 
	SelectFontObject("consolas", 20, 1);
	TextOut(485, 120, "#1");
	TextOut(400, 150, "항목:");
	TextOut(400, 180, "가격:");
	TextOut(390, 210, "지불자:");

	void* p111 = CreateEdit(450, 150, 120, 25, 1, 0); //항목 입력 컨트롤 (1번)
	void* p222 = CreateEdit(450, 180, 120, 25, 2, 0);//가격 입력 컨트롤(2번)
	void* p333 = CreateEdit(450, 210, 120, 25, 3, 0); //지불자 입력 컨트롤 (3번)

	EnableEnterKey(p333);

	TextOut(375, 250, "----------------------------");
	TextOut(485, 280, "#2");
	TextOut(400, 310, "항목:");
	TextOut(400, 340, "가격:");
	TextOut(390, 370, "지불자:");
	void* p444 = CreateEdit(450, 310, 120, 25, 4, 0);
	void* p555 = CreateEdit(450, 340, 120, 25, 5, 0);
	CreateEdit(450, 370, 120, 25, 6, 0);

	TextOut(375, 410, "----------------------------");

	CreateButton("계산", 380, 440, 60, 80, 7);  //계산 (id=7)


	ShowDisplay();
}

// ************************************<권나현 시작>***********************************************
// 마지막 페이지에 누가 누구한테 얼마를 줘야하는지 계산하고 출력하는 함수
// 일단 사용자들의 이름을 a, b, c로 출력함.
// when N = 2
void calcul_algo2(int a, int b, char names[][50])
{
	int atob = 0;
	int btoa = 0;

	int mean = (a + b) / 2;
	a = mean - a;
	b = mean - b;

	if (a > 0)
	{
		if (b < 0)
		{
			while (b != 0)
			{
				a--;
				b++;
				atob++;
			}
		}
	}

	if (b > 0)
	{
		if (a < 0)
		{
			while (a != 0)
			{
				b--;
				a++;
				btoa++;
			}
		}
	}

	// a의 개별 소비1
	if (personal_names[0] == names[1])
	{
		atob = atob + get_value1;
	}
	
	// a의 개별 소비2
	if (personal_names[1] == names[1])
	{
		atob = atob + get_value2;
	}
	
	// b의 개별 소비1
	if (personal_names[2] == names[0])
	{
		btoa = btoa + get_value3;
	}
	
	// b의 개별 소비2
	if (personal_names[3] == names[0])
	{
		btoa = btoa + get_value4;
	}
	
	printf(400, 450, "%s->%s: %d원\n",names[0], names[1], atob);
	printf(400, 470, "%s->%s: %d원\n", names[1], names[0], btoa);
}

// when N = 3
void calcul_algo3(int a, int b, int c, char names[][50])
{
	int mean = (a + b + c) / 3;
	a = mean - a;
	b = mean - b;
	c = mean - c;

	int atob = 0;
	int btoa = 0;
	int btoc = 0;
	int ctob = 0;
	int atoc = 0;
	int ctoa = 0;

	if (a > 0)
	{
		if (b < 0)
		{
			while (b != 0)
			{
				a--;
				b++;
				atob++;
			}
		}
		if (c < 0)
		{
			while (c != 0)
			{
				a--;
				c++;
				atoc++;
			}
		}
	}

	if (b > 0)
	{
		if (a < 0)
		{
			while (a != 0)
			{
				b--;
				a++;
				btoa++;
			}
		}
		if (c < 0)
		{
			while (c != 0)
			{
				b--;
				c++;
				btoc++;
			}
		}
	}

	if (c > 0)
	{
		if (a < 0)
		{
			while (a != 0)
			{
				c--;
				a++;
				ctoa++;
			}
		}
		if (b < 0)
		{
			while (b != 0)
			{
				c--;
				b++;
				ctob++;
			}
		}
	}

	// 개별 소비 더하기
	// a의 개별 소비1
	
	if (strcmp(personal_names[0], names[1]) == 0)
	{
		atob = atob + get_value1;
	}
	if (strcmp(personal_names[0], names[2]) == 0)
	{
		atoc = atoc + get_value1;
	}
	// a의 개별 소비2
	if (strcmp(personal_names[1], names[1]) == 0)
	{
		atob = atob + get_value2;
	}
	if (strcmp(personal_names[1], names[2]) == 0)
	{
		atoc = atoc + get_value2;
	}
	// b의 개별 소비1
	if (strcmp(personal_names[2], names[0]) == 0)
	{
		btoa = btoa + get_value3;
	}
	if (strcmp(personal_names[2], names[2]) == 0)
	{
		btoc = btoc + get_value3;
	}
	// b의 개별 소비2
	if (strcmp(personal_names[3], names[2]) == 0)
	{
		btoa = btoa + get_value4;
	}
	if (strcmp(personal_names[3], names[2]) == 0)
	{
		btoc = btoc + get_value4;
	}
	// c의 개별 소비1
	if (strcmp(personal_names[4], names[0]) == 0)
	{
		ctoa = ctoa + get_value5;
	}
	if (strcmp(personal_names[4], names[1]) == 0)
	{
		ctob = ctob + get_value5;
	}
	// c의 개별 소비2
	if (strcmp(personal_names[5], names[0]) == 0)
	{
		ctoa = ctoa + get_value6;
	}
	if (strcmp(personal_names[5], names[1]) == 0)
	{
		ctob = ctob + get_value6;
	}

	// 디버깅용
	//for (int i = 0; i < 6; i++)
	//{
	//	printf(100, 300 + 30 * i, "%s", personal_names[i]);
	//}
	//printf(100, 300, "%s: %d", personal_names[0], get_value1);
	//printf(100, 350, "%s: %d", personal_names[1], get_value2);
	//printf(100, 400, "%s: %d", personal_names[2], get_value3);


	printf(400, 450, "%s->%s: %d원\n", names[0], names[1], atob);
	printf(400, 470, "%s->%s: %d원\n", names[1], names[0], btoa);
	printf(400, 490, "%s->%s: %d원\n", names[1], names[2], btoc);
	printf(650, 450, "%s->%s: %d원\n", names[2], names[1], ctob);
	printf(650, 470, "%s->%s: %d원\n", names[0], names[2], atoc);
	printf(650, 490, "%s->%s: %d원\n", names[2], names[0], ctoa);
}

void calculate_final(int N) {
	// 디버깅용
	//char names[3][64] = { "kwon", "ryu", "lee" };
	//char name_paid[2][64] = { "kwon", "lee" };
	//int price[2] = { 3000, 3000 };

	int a = 0;
	int b = 0;
	int c = 0;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			if (strcmp(name_paid[i], names[j]) == 0) {
				// Update the amounts based on the corresponding prices
				if (j == 0) {
					a += price[i];
				}
				else if (j == 1) {
					b += price[i];
				}
				else if (j == 2) {
					c += price[i];
				}
			}
		}
	}

	// 디버깅용
	//printf(100, 300, "a = % d\n", a);
	//printf(100, 400, "b = %d\n", b);
	//printf(100, 500, "c = %d\n", c);

	if (N == 2) {
		calcul_algo2(a, b, names);
	}

	if (N == 3) {
		calcul_algo3(a, b, c, names);
	}
}

//*************************************<권나현 끝>*************************************************
//정산결과출력페이지
void final_page() {

	ChangeWorkSize(1000, 600);
	SelectFontObject("consolas", 12, 0);
	SetTextColor(RGB(128, 128, 128));
	for (int x = 0; x < 20; x++) printf(x * 50, 0, "%d", x * 50);   //x좌표
	for (int y = 1; y < 20; y++)  printf(0, y * 50, "%d", y * 50); //y좌표
	SelectPenObject(RGB(128, 128, 128), 2); //박스선 색,두께
	Rectangle(50, 100, 300, 550); //MEMBER BOX
	SelectFontObject("consolas", 45, 1);
	printf(125, 50, "MEMBER");
	Rectangle(330, 100, 950, 550); //최종정산 결과 출력박스
	printf(600, 50, "정산");



	//나중에 지워야함 일단 실행 돌려볼라고 임의로 앞계속 반복하기 귀찮아서 일단 썻으




	for (int i = 0; i < N; i++) {

		CreateButton(names[i], 90, 120 + 35 * i, 120, 30, 301 + i);
		//생성 순서대로 301번박스,302,303~~

	}

}




// 컨트롤을 조작했을 때 호출할 함수 만들기
void OnCommand(INT32 a_ctrl_id, INT32 a_notify_code, void* ap_ctrl)
{

	//final_page에서 사용하는 컨트롤 코드================================
	if (a_ctrl_id == 301) {

		
		SelectPenObject(RGB(128, 128, 128), 2); //박스선 색,두께
		Rectangle(330, 100, 950, 550); //최종정산 결과 출력박스
		Rectangle(350, 120, 930, 420); //최종정산 결과 출력박스
		SelectFontObject("consolas", 30, 1);
		TextOut(400, 150, "<공용소비>"); //구성원1이름 출력
		SelectFontObject("consolas", 25, 1);
		TextOut(400, 200, "-%s : %d원",item[0],price[0]);
		TextOut(400, 250,"-%s : %d원", item[1],price[1]);
		TextOut(400, 300, "===============");
		TextOut(400, 350, "N빵: %d원", (price[0]+price[1])/N);
		SelectFontObject("consolas", 30, 1);
		TextOut(650,150,"<%s의 개별소비>",names[0]); //구성원1이름 출력
		SelectFontObject("consolas", 25, 1);
		TextOut(650, 200, "-%s :%d원", personal_item[0],get_value1); //개인비용 출력
		TextOut(650, 250, "-%s :%d원", personal_item[1], get_value2);
		TextOut(650, 300, "===============");
		TextOut(650, 350, "총: %d원", get_value1+get_value2);
		Line(615, 150, 615, 400);
	

		calculate_final(N);
	}

	if (a_ctrl_id == 302) {


		SelectPenObject(RGB(128, 128, 128), 2); //박스선 색,두께
		Rectangle(330, 100, 950, 550); //최종정산 결과 출력박스
		Rectangle(350, 120, 930, 420); //최종정산 결과 출력박스
		SelectFontObject("consolas", 30, 1);
		TextOut(400, 150, "<공용소비>"); //구성원1이름 출력
		SelectFontObject("consolas", 25, 1);
		TextOut(400, 200, "-%s : %d원",item[0],price[0]);
		TextOut(400, 250,"-%s : %d원", item[1],price[1]);
		TextOut(400, 300, "===============");
		TextOut(400, 350, "N빵: %d원", (price[0]+price[1])/N);
		SelectFontObject("consolas", 30, 1);
		TextOut(650, 150, "<%s의 개별소비>", names[1]); //구성원이름 출력
		SelectFontObject("consolas", 25, 1);
		TextOut(650, 200, "-%s :%d원", personal_item[2], get_value3); //개인비용 출력
		TextOut(650, 250, "-%s :%d원", personal_item[3], get_value4);
		TextOut(650, 300, "===============");
		TextOut(650, 350, "총: %d원", get_value3 + get_value4);
		Line(615, 150, 615, 400);

		calculate_final(N);

	}

	if (a_ctrl_id == 303) {


		SelectPenObject(RGB(128, 128, 128), 2); //박스선 색,두께
		Rectangle(330, 100, 950, 550); //최종정산 결과 출력박스
		Rectangle(350, 120, 930, 420); //최종정산 결과 출력박스
		SelectFontObject("consolas", 30, 1);
		TextOut(400, 150, "<공용소비>"); //구성원1이름 출력
		SelectFontObject("consolas", 25, 1);
		TextOut(400, 200, "-%s : %d원", item[0], price[0]);
		TextOut(400, 250, "-%s : %d원", item[1], price[1]);
		TextOut(400, 300, "===============");
		TextOut(400, 350, "N빵: %d원", (price[0] + price[1]) / N);
		SelectFontObject("consolas", 30, 1);
		TextOut(650, 150, "<%s의 개별소비>", names[2]); //구성원이름 출력
		SelectFontObject("consolas", 25, 1);
		TextOut(650, 200, "-%s :%d원", personal_item[4], get_value5); //개인비용 출력
		TextOut(650, 250, "-%s :%d원", personal_item[5], get_value6);
		TextOut(650, 300, "===============");
		TextOut(650, 350, "총: %d원", get_value5 + get_value6);
		Line(615, 150, 615, 400);

		calculate_final(N);


	}

// ************************************<권나현 시작>************************************************
    // login page 안에서의 컨트롤
    if (a_ctrl_id == 3002)  // 로그인 버튼이 눌렸을 때
    {
        char id[64]; // 아이디 문자열을 저장할 변수
        void* id_edit = FindControl(3000); // 아이디 에디트 컨트롤의 주소를 얻는다.
        GetCtrlName(id_edit, id, 64);

        char pw[64]; // 패스워드 문자열을 저장할 변수
        void* pw_edit = FindControl(3001); // 에디트 컨트롤의 주소를 얻는다.
        GetCtrlName(pw_edit, pw, 64);

		SetCtrlName(id_edit, ""); // 에디트 컨트롤에 쓰여진 문자열을 지운다.
		SetCtrlName(pw_edit, ""); // 에디트 컨트롤에 쓰여진 문자열을 지운다.


        int flag = 0;  // 로그인 성공 여부를 받을 변수(1이면 성공)
        flag = login(users, userCount, id, pw);

        if (flag == 1)
        {
            printf(300, 500, "로그인 성공");
            CreateButton("정산하러 가기", 800, 100, 100, 30, 3006);
        }
        else
        {
            ::MessageBox(gh_main_wnd, "로그인에 실패하였습니다.", "로그인 실패", MB_ICONSTOP);
        }
    }

    if (a_ctrl_id == 3005)  // 회원 가입 버튼이 눌렸을 때
    {
        char newid[64]; // 아이디 문자열을 저장할 변수
        void* newid_edit = FindControl(3003); // 아이디 에디트 컨트롤의 주소를 얻는다.
        GetCtrlName(newid_edit, newid, 64);

        char newpw[64]; // 패스워드 문자열을 저장할 변수
        void* newpw_edit = FindControl(3004); // 에디트 컨트롤의 주소를 얻는다.
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

    if (a_ctrl_id == 3006)  // 메인 페이지로 가는 버튼을 누르면
    {
        Clear();
        DestroyControl(FindControl(3000));
        DestroyControl(FindControl(3001));
        DestroyControl(FindControl(3002));
        DestroyControl(FindControl(3003));
        DestroyControl(FindControl(3004));
        DestroyControl(FindControl(3005));
        DestroyControl(FindControl(3006));

		main_page();  // 메인 페이지 불러오기
    }

	// ***********************************<권나현 끝>********************************************
    // main page 안에서의 컨트롤
	if (a_ctrl_id == 1000) {//1000번 버튼(멤버 추가 버튼 누르는 경우)
		char str[64];
		GetCtrlName(FindControl(101), str, 25);
		CreateButton(str, 90, 120 + 35 * N, 120, 30, 200 + N);
		N++;
		SelectFontObject("consolas", 25, 1);
		SelectPenObject(RGB(0, 0, 0), 1);
		Rectangle(150, 450, 220, 475); //시작점,끝점 좌표
		TextOut(150, 450, "총:%d명", N);  //총 인원출력
		strcpy_s(names[N - 1], str);
		SetCtrlName(FindControl(101), ""); // 에디트 컨트롤에 쓰여진 문자열을 지운다.
		ShowDisplay();
	}


	else if (a_ctrl_id == 7) {

		char str1[60];
		char str4[60];
		GetCtrlName(FindControl(1), str1, 25);
		GetCtrlName(FindControl(4), str4, 25);
		strcpy_s(item[0], str1);
		strcpy_s(item[1], str4);

		price[0] = GetIntDataFromControl(2);
		price[1] = GetIntDataFromControl(5);

		char str3[60];
		char str6[60];
		GetCtrlName(FindControl(3), str3, 25);
		GetCtrlName(FindControl(6), str6, 25);
		strcpy_s(name_paid[0], str3);
		strcpy_s(name_paid[1], str6);



		SelectFontObject("consolas", 25, 1);

		TextOut(460, 450, "총합:%d원", price[0] + price[1]);
		TextOut(460, 480, "N빵:%d원", (price[0] + price[1]) / N);

		// 디버깅용
		//for (int i = 0; i < 3; i++)
		//{
		//	printf(750, 300 + i * 50, "%s", names[i]);
		//	printf(750, 320 + i * 50, "%s", name_paid[i]);
		//	printf(750, 340 + i * 50, "%d", price[i]);
		//}
		ShowDisplay();


	}

	else if (a_ctrl_id == 200) {
		//구성원 첫번째 이름 버튼 누르는 경우

		//생성된 에디트박스 제거 초기화
		DestroyControl(FindControl(10003));
		DestroyControl(FindControl(10004));
		DestroyControl(FindControl(20003));
		DestroyControl(FindControl(20004));
		DestroyControl(FindControl(10));
		DestroyControl(FindControl(11));
		DestroyControl(FindControl(10005));
		DestroyControl(FindControl(10006));
		DestroyControl(FindControl(12));
		DestroyControl(FindControl(20005));
		DestroyControl(FindControl(20006));
		DestroyControl(FindControl(13));
		DestroyControl(FindControl(111));
		DestroyControl(FindControl(222));

		SelectPenObject(RGB(128, 128, 128), 1);
		Rectangle(710, 110, 940, 540); //시작점,끝점 좌표
		SelectFontObject("consolas", 25, 1);
		TextOut(720, 120, names[0]);  //첫번째 구성원 이름 출력
		TextOut(725, 160, "항목:");
		TextOut(725, 200, "가격:");
		TextOut(725, 240, "지불자:");
		void* p1 = CreateEdit(790, 160, 120, 30, 10001, 0);  //첫번째 구성원 개인 항목 1(ID:10001)
		void* p2 = CreateEdit(790, 200, 120, 30, 10002, 0); //첫번째 구성원 개인 가격 1(ID:10002)
		CreateEdit(790, 240, 120, 30, 8, 0);               //지불자 (8)
		EnableEnterKey(p2);  //ENTER누르면 아래 총합 출력

		CreateButton("+", 730, 490, 180, 35, 100);    // 개인항목 입력 추가버튼  (ID: 10000)

		ShowDisplay();
	}

	//개인비용 첫번째 값 엔터 -> 총원 계산 
	else if (a_ctrl_id == 10002 && a_notify_code == 1000) {
		SelectFontObject("consolas", 25, 1);
		get_value1 = GetIntDataFromControl(10002);
		SelectFontObject("consolas", 25, 1);
		SelectPenObject(RGB(0, 0, 0), 1);
		Rectangle(725, 450, 850, 475);
		TextOut(730, 450, "총:%d원", get_value1 + get_value2);
		ShowDisplay();

		char personal_item1[60];
		GetCtrlName(FindControl(10001), personal_item1, 25);
		strcpy_s(personal_item[0], personal_item1);
		char personal_name1[60];
		GetCtrlName(FindControl(8), personal_name1, 25);
		strcpy_s(personal_names[0], personal_name1);



	}

	//개인비용 추가 버튼 
	else if (a_ctrl_id == 100) {
		SelectFontObject("consolas", 25, 1);
		TextOut(725, 280, "항목:");
		TextOut(725, 320, "가격:");
		TextOut(725, 360, "지불자:");
		void* p3 = CreateEdit(790, 280, 120, 30, 20001, 0);
		void* p4 = CreateEdit(790, 320, 120, 30, 20002, 0);
		CreateEdit(790, 360, 120, 30, 9, 0);
		EnableEnterKey(p4);

		ShowDisplay();


	}
	//개인비용 두번째 값 입력시 엔터->총합계산
	else if (a_ctrl_id == 20002 && a_notify_code == 1000) {
		SelectFontObject("consolas", 25, 1);

		//입력값 저장
		get_value2 = GetIntDataFromControl(20002);

		char personal_item2[60];
		char personal_name2[60];

		GetCtrlName(FindControl(20001), personal_item2, 25);
		GetCtrlName(FindControl(9), personal_name2, 25);
		strcpy_s(personal_item[1], personal_item2);
		strcpy_s(personal_names[1], personal_name2);





		SelectFontObject("consolas", 25, 1);
		SelectPenObject(RGB(0, 0, 0), 1);
		Rectangle(725, 450, 850, 475);
		//개인비용총합 출력
		TextOut(730, 450, "총:%d원", get_value1 + get_value2); //10002박스 + 20002 박스
		ShowDisplay();
	}

	//========================================================================


	else if (a_ctrl_id == 201) { //2번째 사람버튼

		SelectPenObject(RGB(128, 128, 128), 1);
		Rectangle(710, 110, 940, 540); //시작점,끝점 좌표
		SelectFontObject("consolas", 25, 1);
		TextOut(720, 120, names[1]);  //개인비용 입력칸에 이름 출력 
		TextOut(725, 160, "항목:");
		TextOut(725, 200, "가격:");
		TextOut(725, 240, "지불자:");



		//*****에디트박스 지우는코드 넣어야함
		DestroyControl(FindControl(10001));
		DestroyControl(FindControl(10002));
		DestroyControl(FindControl(20001));
		DestroyControl(FindControl(20002));
		DestroyControl(FindControl(8));
		DestroyControl(FindControl(9));
		DestroyControl(FindControl(10005));
		DestroyControl(FindControl(10006));
		DestroyControl(FindControl(12));
		DestroyControl(FindControl(20005));
		DestroyControl(FindControl(20006));
		DestroyControl(FindControl(13));
		DestroyControl(FindControl(100));
		DestroyControl(FindControl(222));

		//두번째구성원 에디트박스 생성
		void* p5 = CreateEdit(790, 160, 120, 30, 10003, 0);
		void* p6 = CreateEdit(790, 200, 120, 30, 10004, 0);
		CreateEdit(790, 240, 120, 30, 10, 0);               //지불자 (10)

		EnableEnterKey(p6);

		CreateButton("+", 730, 490, 180, 35, 111);
		//두번째사람 개인항목 추가버튼 생성


		ShowDisplay();
	}

	//2번째 사람 첫번째 개인값 입력 엔터 -> 총합계산
	else if (a_ctrl_id == 10004 && a_notify_code == 1000) {
		SelectFontObject("consolas", 25, 1);
		get_value3 = GetIntDataFromControl(10004);

		char personal_item3[60];
		GetCtrlName(FindControl(10003), personal_item3, 25);
		strcpy_s(personal_item[2], personal_item3);
		char personal_name3[60];
		GetCtrlName(FindControl(10), personal_name3, 25);
		strcpy_s(personal_names[2], personal_name3);





		SelectFontObject("consolas", 25, 1);
		SelectPenObject(RGB(0, 0, 0), 1);
		Rectangle(725, 450, 850, 475);
		TextOut(730, 450, "총:%d원", get_value3 + get_value4);
		ShowDisplay();
	}


	else if (a_ctrl_id == 111) { //2번째 사람 개인항목 추가 버튼 번호

		SelectFontObject("consolas", 25, 1);
		TextOut(725, 280, "항목:");
		TextOut(725, 320, "가격:");
		TextOut(725, 360, "지불자:");
		void* p7 = CreateEdit(790, 280, 120, 30, 20003, 0);
		void* p8 = CreateEdit(790, 320, 120, 30, 20004, 0);
		CreateEdit(790, 360, 120, 30, 11, 0);

		EnableEnterKey(p8);


		ShowDisplay();


	}
	//
	else if (a_ctrl_id == 20004 && a_notify_code == 1000) {
		SelectFontObject("consolas", 25, 1);
		get_value4 = GetIntDataFromControl(20004);


		char personal_item4[60];
		GetCtrlName(FindControl(20003), personal_item4, 25);
		strcpy_s(personal_item[3], personal_item4);
		char personal_name4[60];
		GetCtrlName(FindControl(11), personal_name4, 25);
		strcpy_s(personal_names[3], personal_name4);


		SelectFontObject("consolas", 25, 1);
		SelectPenObject(RGB(0, 0, 0), 1);
		Rectangle(725, 450, 850, 475);

		TextOut(730, 450, "총:%d원", get_value3 + get_value4);
		ShowDisplay();
	}

	//========================================================================


	else if (a_ctrl_id == 202) { //3번째 사람버튼

		SelectPenObject(RGB(128, 128, 128), 1);
		Rectangle(710, 110, 940, 540); //시작점,끝점 좌표
		SelectFontObject("consolas", 25, 1);
		TextOut(720, 120, names[2]);  //3번째 사람 이름 출력
		TextOut(725, 160, "항목:");
		TextOut(725, 200, "가격:");
		TextOut(725, 240, "지불자:");

		//에디트박스 제거해야함 10003 10004 20003 20004 10 11
		DestroyControl(FindControl(10003));
		DestroyControl(FindControl(10004));
		DestroyControl(FindControl(20003));
		DestroyControl(FindControl(20004));
		DestroyControl(FindControl(10));
		DestroyControl(FindControl(11));
		DestroyControl(FindControl(10001));
		DestroyControl(FindControl(10002));
		DestroyControl(FindControl(20001));
		DestroyControl(FindControl(20002));
		DestroyControl(FindControl(8));
		DestroyControl(FindControl(9));
		DestroyControl(FindControl(111));
		DestroyControl(FindControl(100));


		void* p3 = CreateEdit(790, 160, 120, 30, 10005, 0);
		void* p4 = CreateEdit(790, 200, 120, 30, 10006, 0);
		CreateEdit(790, 240, 120, 30, 12, 0);
		EnableEnterKey(p4);

		CreateButton("+", 730, 490, 180, 35, 222); //3번째사람 개인항목 추가버튼 생성


		ShowDisplay();
	}
	else if (a_ctrl_id == 10006 && a_notify_code == 1000) {
		SelectFontObject("consolas", 25, 1);
		get_value5 = GetIntDataFromControl(10006);



		char personal_item5[60];
		GetCtrlName(FindControl(10005), personal_item5, 25);
		strcpy_s(personal_item[4], personal_item5);
		char personal_name5[60];
		GetCtrlName(FindControl(12), personal_name5, 25);
		strcpy_s(personal_names[4], personal_name5);







		SelectFontObject("consolas", 25, 1);
		SelectPenObject(RGB(0, 0, 0), 1);
		Rectangle(725, 450, 850, 475);
		TextOut(730, 450, "총:%d원", get_value5 + get_value6);
		ShowDisplay();
	}


	else if (a_ctrl_id == 222) { //3번째 사람 개인항목 추가 버튼 번호

		SelectFontObject("consolas", 25, 1);
		TextOut(725, 280, "항목:");
		TextOut(725, 320, "가격:");
		TextOut(725, 360, "지불자:");
		CreateEdit(790, 280, 120, 30, 20005, 0);
		void* p3 = CreateEdit(790, 320, 120, 30, 20006, 0);
		CreateEdit(790, 360, 120, 30, 13, 0);

		EnableEnterKey(p3);


		ShowDisplay();


	}

	else if (a_ctrl_id == 20006 && a_notify_code == 1000) {
		SelectFontObject("consolas", 25, 1);
		get_value6 = GetIntDataFromControl(20006);

		char personal_item6[60];
		GetCtrlName(FindControl(20005), personal_item6, 25);
		strcpy_s(personal_item[5], personal_item6);
		char personal_name6[60];
		GetCtrlName(FindControl(13), personal_name6, 25);
		strcpy_s(personal_names[5], personal_name6);




		SelectFontObject("consolas", 25, 1);
		SelectPenObject(RGB(0, 0, 0), 1);
		Rectangle(725, 450, 850, 475);

		TextOut(730, 450, "총:%d원", get_value5 + get_value6);
		ShowDisplay();
	}



	//=====================================================================
	//정산페이지
	if (a_ctrl_id == 3007)  // 정산 페이지로 가는 버튼을 누르면
	{
		Clear();
		DestroyControl(FindControl(101));
		DestroyControl(FindControl(1000));
		DestroyControl(FindControl(1));
		DestroyControl(FindControl(2));
		DestroyControl(FindControl(3));
		DestroyControl(FindControl(4));
		DestroyControl(FindControl(5));
		DestroyControl(FindControl(6));
		DestroyControl(FindControl(7));
		DestroyControl(FindControl(8));
		DestroyControl(FindControl(9));
		DestroyControl(FindControl(10));
		DestroyControl(FindControl(11));
		DestroyControl(FindControl(12));
		DestroyControl(FindControl(13));
		DestroyControl(FindControl(10001));
		DestroyControl(FindControl(10002));
		DestroyControl(FindControl(10003));
		DestroyControl(FindControl(10004));
		DestroyControl(FindControl(10005));
		DestroyControl(FindControl(10006));
		DestroyControl(FindControl(20001));
		DestroyControl(FindControl(20002));
		DestroyControl(FindControl(20003));
		DestroyControl(FindControl(20004));
		DestroyControl(FindControl(20005));
		DestroyControl(FindControl(20006));
		DestroyControl(FindControl(100));
		DestroyControl(FindControl(111));
		DestroyControl(FindControl(222));
		DestroyControl(FindControl(200));
		DestroyControl(FindControl(201));
		DestroyControl(FindControl(202));
		DestroyControl(FindControl(203));
		DestroyControl(FindControl(204));
		DestroyControl(FindControl(205));
		DestroyControl(FindControl(222));
		DestroyControl(FindControl(222));
		DestroyControl(FindControl(222));
		DestroyControl(FindControl(100));




		//정산결과 출력페이지 불러오기();
		final_page();


	}






    ShowDisplay(); // 정보를 윈도우에 출력한다.
}

// 컨트롤을 조작했을 때 호출할 함수 등록
CMD_MESSAGE(OnCommand)

int main()
{
    login_page();
	// main_page();
	//final_page();

    ShowDisplay(); // 정보를 윈도우에 출력한다.
    return 0;
}