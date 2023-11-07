#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 멤버 정보를 저장할 구조체
typedef struct {
    char name[50]; // 멤버 이름
    // int account[50]; // 계좌 정보 
} MemberInfo;

// 정산 결과를 저장할 구조체
typedef struct {
    int payer_id;  // 지불자 ID
    double price; // 정산 금액
} DutchPayInfo;

int main() {
    int numMembers;
    printf("멤버 수 입력: ");
    scanf("%d", &numMembers);

    // 멤버 정보 배열 초기화
    MemberInfo members[numMembers];
    for (int i = 0; i < numMembers; i++) {
        printf("멤버 %d 이름 입력: ", i + 1);
        scanf("%s", members[i].name);
    }

    int numDutchPay;
    printf("정산 횟수 입력: ");
    scanf("%d", &numDutchPay);

    // 정산 정보 배열 초기화
    DutchPayInfo dutchPay[numDutchPay];
    for (int i = 0; i < numDutchPay; i++) {
        char payerName[50];
        double price;

        printf("%d차 돈 낸 사람 이름: ", i+1);
        scanf("%s", payerName);
        int payerID = -1;  // payerID를 -1로 초기화 

        // 입력된 지불자 이름을 멤버 정보 배열에서 찾음
        for (int j = 0; j < numMembers; j++) {
            if (strcmp(payerName, members[j].name) == 0) {
                payerID = j; // 지불자의 멤버 ID를 설정
                break;
            }
        }

        if (payerID != -1) {
            printf("정산할 금액: ");
            scanf("%lf", &price);

            dutchPay[i].payer_id = payerID; // 정산 정보에 지불자 ID 저장
            dutchPay[i].price = price;    // 정산 정보에 금액 저장
        } else {
            printf("멤버를 찾을 수 없습니다.\n");
            i--; // 다시 입력 받기 위해 i 감소
        }
    }

    // 멤버별 총 정산 금액 계산
    double totalAmount[numMembers];
    for (int i = 0; i < numMembers; i++) {
        totalAmount[i] = 0.0;
    }

    for (int i = 0; i < numDutchPay; i++) {
        int payerID = dutchPay[i].payer_id;
        double price = dutchPay[i].price;

        for (int j = 0; j < numMembers; j++) {
            if (j != payerID) {
                totalAmount[j] += price / numMembers;
            }
        }
    }

    // 정산 결과 출력
	printf("\n지불 내용:\n");
	for (int i = 0; i < numMembers; i++) {
    	for (int j = 0; j < numMembers; j++) {
        	if (i != j) {
            	double amountToPay = totalAmount[i] - totalAmount[j];
            	if (amountToPay > 0) {
                	printf("%s님이 %s님에게 %.2lf원을 지불해야 합니다.\n", members[i].name, members[j].name, amountToPay);
            	}
        	}
    	}
	}
    return 0;
}

