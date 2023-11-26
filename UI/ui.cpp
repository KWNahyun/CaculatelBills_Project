#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "pch.h"
#include "tipsware.h"

int get_value1 = 0; //첫번째 구성원 개인 항목가격1 (ID:10002)
int get_value2 = 0; //첫번째 구성원 개인 항목 가격2 (20004)
int get_value3 = 0; //두번째구성원 개인 항목 가격1 (10004)
int get_value4 = 0;  //두번째구성원 개인 항목 가격2 (20004)
int get_value5 = 0;  //세번째구성원 개인 항목 가격1 (10006)
int get_value6 = 0;  //세번째 구성원 개인 항목 가격2 (20006)
int N = 0;

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


void main_page() {
	ChangeWorkSize(1000, 600);
	SelectFontObject("consolas", 12, 0);
	SetTextColor(RGB(128, 128, 128));
	for (int x = 0; x < 20; x++) printf(x * 50, 0,"%d", x * 50);   //x좌표
	for (int y = 1; y < 20; y++)  printf(0, y * 50, "%d", y * 50); //y좌표
	SelectPenObject(RGB(128, 128, 128),2); //박스선 색,두께
	Rectangle(50, 100, 300, 550); //MEMBER BOX
	Rectangle(350, 100, 650, 550); //공동비용 BOX
	Rectangle(700, 100, 950, 550); //개인비용 BOX

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
	void* p333= CreateEdit(450, 210, 120, 25, 3, 0);             //지불자 입력 컨트롤 (3번)
	
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



//컨트롤을 조작했을 때 호출 함수
// 컨트롤의 아이디(a_ctrl_id), 컨트롤의 조작 상태(a_notify_code), 선택한 컨트롤 객체(ap_ctrl)
void OnCommand(INT32 a_ctrl_id, INT32 a_notify_code, void* ap_ctrl) {


	if (a_ctrl_id == 1000) {//1000번 버튼(멤버 추가 버튼 누르는 경우)
		char str[64];
		GetCtrlName(FindControl(101), str, 25);
		CreateButton(str,90,120+35*N,120,30,200+N);
		N++;
		SelectFontObject("consolas", 25, 1);
		SelectPenObject(RGB(0, 0, 0), 1);
		Rectangle(150, 450, 220, 475); //시작점,끝점 좌표
		TextOut(150, 450, "총:%d명",N);  //총 인원출력
		strcpy_s(names[N - 1], str);
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
		GetCtrlName(FindControl(3), str6, 25);
		strcpy_s(name_paid[0], str3);
		strcpy_s(name_paid[1], str6);



		SelectFontObject("consolas", 25, 1);
		
		TextOut(460, 450, "총합:%d원", price[0] + price[1]);
		TextOut(460, 480, "N빵:%d원", ( price[0] + price[1])/N );
		ShowDisplay();
		
	}


	else if (a_ctrl_id == 200) {
		//구성원 첫번째 이름 버튼 누르는 경우
		SelectPenObject(RGB(128, 128, 128), 1);
		Rectangle(710, 110, 940, 540); //시작점,끝점 좌표
		SelectFontObject("consolas", 25, 1);
		TextOut(720, 120, names[0]);  //첫번째 구성원 이름 출력
		TextOut(725, 160, "항목:");
		TextOut(725, 200, "가격:");
		void*p1=CreateEdit(790, 160, 120, 30, 10001, 0);  //첫번째 구성원 개인 항목 1(ID:10001)
		void *p2=CreateEdit(790, 200, 120, 30, 10002, 0); //첫번째 구성원 개인 가격 1(ID:10002)
		EnableEnterKey(p2);  //ENTER누르면 아래 총합 출력
		
		CreateButton("+", 730, 490, 180, 35, 10000);    // 개인항목 입력 추가버튼  (ID: 10000)
	

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
	}

	//개인비용 추가 버튼 
	else if (a_ctrl_id == 10000) {
		SelectFontObject("consolas", 25, 1);
		TextOut(725, 250, "항목:");
		TextOut(725, 290, "가격:");
		void*p3=CreateEdit(790, 250, 120, 30, 20001, 0);
		void* p4 = CreateEdit(790, 290, 120, 30, 20002, 0);
		EnableEnterKey(p4);

		ShowDisplay();


	}
	//개인비용 두번째 값 입력시 엔터->총합계산
	else if (a_ctrl_id == 20002 && a_notify_code == 1000) {
		SelectFontObject("consolas", 25, 1);
		get_value2 = GetIntDataFromControl(20002);
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
		
		//*****에디트박스 지우는코드 넣어야함
		//10001 10002 20001 20002 지워야함 


		//두번째구성원 에디트박스 생성
		void*p5=CreateEdit(790, 160, 120, 30, 10003, 0);
		void* p6 = CreateEdit(790, 200, 120, 30, 10004, 0);
		EnableEnterKey(p6);

		CreateButton("+", 730, 490, 180, 35, 111); 
		//두번째사람 개인항목 추가버튼 생성


		ShowDisplay();
	}

	//2번째 사람 첫번째 개인값 입력 엔터 -> 총합계산
	else if (a_ctrl_id == 10004 && a_notify_code == 1000) {
		SelectFontObject("consolas", 25, 1);
		get_value3 = GetIntDataFromControl(10004);
		SelectFontObject("consolas", 25, 1);
		SelectPenObject(RGB(0, 0, 0), 1);
		Rectangle(725, 450, 850, 475);
		TextOut(730, 450, "총:%d원", get_value3 + get_value4);
		ShowDisplay();
	}


	else if (a_ctrl_id == 111) { //2번째 사람 개인항목 추가 버튼 번호
		SelectFontObject("consolas", 25, 1);
		TextOut(725, 250, "항목:");
		TextOut(725, 290, "가격:");
		void*p7=CreateEdit(790, 250, 120, 30, 20003, 0);
		void* p8 = CreateEdit(790, 290, 120, 30, 20004, 0);
		EnableEnterKey(p8);


		ShowDisplay();


	}
	//
	else if (a_ctrl_id == 20004 && a_notify_code == 1000) {
		SelectFontObject("consolas", 25, 1);
		get_value4 = GetIntDataFromControl(20004);
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

		//에디트박스 제거해야함 10003 10004 20003 20004 


		void*p3=CreateEdit(790, 160, 120, 30, 10005, 0);
		void* p4 = CreateEdit(790, 200, 120, 30, 10006, 0);
		EnableEnterKey(p4);

		CreateButton("+", 730, 490, 180, 35, 222); //3번째사람 개인항목 추가버튼 생성


		ShowDisplay();
		}
	else if (a_ctrl_id == 10006 && a_notify_code == 1000) {
			SelectFontObject("consolas", 25, 1);
			get_value5 = GetIntDataFromControl(10006);
			SelectFontObject("consolas", 25, 1);
			SelectPenObject(RGB(0, 0, 0), 1);
			Rectangle(725, 450, 850, 475);
			TextOut(730, 450, "총:%d원", get_value5 + get_value6);
			ShowDisplay();
			}


	else if (a_ctrl_id == 222) { //2번째 사람 개인항목 추가 버튼 번호
				SelectFontObject("consolas", 25, 1);
				TextOut(725, 250, "항목:");
				TextOut(725, 290, "가격:");
				CreateEdit(790, 250, 120, 30, 20005, 0);
				void* p3 = CreateEdit(790, 290, 120, 30, 20006, 0);
				EnableEnterKey(p3);



				ShowDisplay();


				}

	else if (a_ctrl_id == 20006 && a_notify_code == 1000) {
					SelectFontObject("consolas", 25, 1);
					get_value6 = GetIntDataFromControl(20006);
					SelectFontObject("consolas", 25, 1);
					SelectPenObject(RGB(0, 0, 0), 1);
					Rectangle(725, 450, 850, 475);

					TextOut(730, 450, "총:%d원", get_value5 + get_value6);
					ShowDisplay();
					}






}
CMD_MESSAGE(OnCommand)


int main() {

	main_page();

	ShowDisplay();
	return 0;

}