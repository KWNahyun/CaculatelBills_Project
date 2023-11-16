#include "pch.h"
#include "tipsware.h"

void AddItem(INT32 a_ctrl_id, INT32 a_notify_code, void* ap_ctrl)  // 비용란의 항목을 추가하는 함수
{
	// 초기 좌표 설정
	int x1 = 50;
	int y1 = 60;

	if (a_ctrl_id == 2000)
	{
		CreateEdit(x1, y1 + 50, 100, 30, 3000, 1);
		y1 += 50;
	}

	ShowDisplay();
}

CMD_MESSAGE(AddItem)


int main(void)
{
	ChangeWorkSize(800, 400);

	// 편의를 위한 모눈 좌표(50, 50 칸)
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 16; ++j) {
			// 각 정사각형의 좌표 계산
			int x1 = j * 50;
			int y1 = i * 50;
			int x2 = x1 + 50; // 가로 길이가 10이므로 x1에서 100를 더함
			int y2 = y1 + 50; // 세로 길이가 10이므로 y1에서 100를 더함

			// Rectangle 함수를 호출하여 직사각형을 그림
			Rectangle(x1, y1, x2, y2, RGB(200, 200, 200));
		}
	}

	// 구역 나누기
	Rectangle(0, 0, 400, 400, RGB(0, 0, 0));
	Rectangle(400, 0, 800, 400, RGB(0, 0, 0));

	// 타이틀 넣을 자리 ex. 점심밥
	CreateEdit(100, 0, 200, 50, 1000, 1);  // id = 1000

	// 비용/정산 부제목(?) 텍스트 넣을 자리
	Rectangle(150, 60, 250, 90, RGB(0, 0, 0), RGB(252, 255, 208));  // 비용
	printf(184, 68, "비용");
	Rectangle(550, 10, 650, 40, RGB(0, 0, 0), RGB(252, 255, 208));  // 정산
	printf(584, 18, "정산");
	
	// 항목 추가 버튼 만들기
	CreateButton("+", 260, 60, 30, 30, 2000);  // 비용 항목 추가
	CreateButton("+", 660, 10, 30, 30, 2001);  // 정산 인원 추가

	// 

	ShowDisplay();
	return 0;
}