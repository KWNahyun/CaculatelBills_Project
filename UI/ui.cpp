
#include "pch.h"
#include "tipsware.h"

int get_value1 = 0;
int get_value2 = 0;
int get_value3 = 0;
int get_value4 = 0;
int get_value5 = 0;
int get_value6 = 0;
int N = 0;
int main() {
	ChangeWorkSize(1000, 600);
	SelectFontObject("consolas", 12, 0);
	SetTextColor(RGB(128, 128, 128));
	for (int x = 0; x < 20; x++) printf(x * 50, 0,"%d", x * 50);
	for (int y = 1; y < 20; y++)  printf(0, y * 50, "%d", y * 50);
	SelectPenObject(RGB(128, 128, 128),2);
	Rectangle(50, 100, 300, 550); //MEMBER BOX
	Rectangle(350, 100, 650, 550); //공동비용 BOX
	Rectangle(700, 100, 950, 550); //개인비용 BOX

	SelectFontObject("consolas", 45, 1);
	printf(125, 50, "MEMBER");
	printf(445, 50, "공동비용");
	printf(755, 50, "개인비용");
	CreateEdit(95, 490, 120, 30, 101, 0);
	CreateButton("+", 220, 490, 30, 30, 1000);


	//공동비용 부분 에디트 박스 
	SelectPenObject(RGB(128, 128, 128), 1);
	Rectangle(360, 110, 640, 540); //시작점,끝점 좌표
	SelectFontObject("consolas", 25, 1);
	TextOut(375, 120, "#1");
	TextOut(375, 160, "항목:");
	TextOut(375, 200, "가격:");
	void* p111 = CreateEdit(450, 160, 120, 30, 1, 0);
	void* p222 = CreateEdit(450, 200, 120, 30, 2, 0);
	TextOut(375, 245, "---------------------");
	TextOut(375, 280, "#2");
	TextOut(375, 320, "항목:");
	TextOut(375, 360, "가격:");
	void* p333 = CreateEdit(450, 320, 120, 30, 3, 0);
	void* p444 = CreateEdit(450, 360, 120, 30, 4, 0);
	TextOut(375, 400, "---------------------");



	//선 pen 채우기 브러쉬 
	ShowDisplay();
}


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
		ShowDisplay();
	}


	else if (a_ctrl_id == 200) {
		//구성원 첫번째 이름 버튼 누르는 경우
		SelectPenObject(RGB(128, 128, 128), 1);
		Rectangle(710, 110, 940, 540); //시작점,끝점 좌표
		char str1[64];
		GetCtrlName(FindControl(101), str1, 35);
		SelectFontObject("consolas", 25, 1);
		TextOut(720, 120, str1);
		TextOut(725, 160, "항목:");
		TextOut(725, 200, "가격:");
		void*p1=CreateEdit(790, 160, 120, 30, 10001, 0);
		void *p2=CreateEdit(790, 200, 120, 30, 10002, 0);
		EnableEnterKey(p2);
		
		CreateButton("+", 730, 490, 180, 35, 100);
	

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
	else if (a_ctrl_id == 100) {
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

		TextOut(730, 450, "총:%d원", get_value1 + get_value2);
		ShowDisplay();
	}
	
	//========================================================================


	else if (a_ctrl_id == 201) { //2번째 사람버튼

		SelectPenObject(RGB(128, 128, 128), 1);
		Rectangle(710, 110, 940, 540); //시작점,끝점 좌표
		char str2[64];
		GetCtrlName(FindControl(101), str2, 35);
		SelectFontObject("consolas", 25, 1);
		TextOut(720, 120, str2);
		TextOut(725, 160, "항목:");
		TextOut(725, 200, "가격:");
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
		char str3[64];
		GetCtrlName(FindControl(101), str3, 35);
		SelectFontObject("consolas", 25, 1);
		TextOut(720, 120, str3);
		TextOut(725, 160, "항목:");
		TextOut(725, 200, "가격:");
		void*p3=CreateEdit(790, 160, 120, 30, 10005, 0);
		void* p4 = CreateEdit(790, 200, 120, 30, 10006, 0);
		EnableEnterKey(p4);

		CreateButton("+", 730, 490, 180, 35, 333); //3번째사람 개인항목 추가버튼 생성


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


