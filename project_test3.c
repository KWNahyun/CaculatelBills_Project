#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ��� ������ ������ ����ü
typedef struct {
    char name[50]; // ��� �̸�
    // int account[50]; // ���� ���� 
} MemberInfo;

// ���� ����� ������ ����ü
typedef struct {
    int payer_id;  // ������ ID
    double price; // ���� �ݾ�
} DutchPayInfo;

int main() {
    int numMembers;
    printf("��� �� �Է�: ");
    scanf("%d", &numMembers);

    // ��� ���� �迭 �ʱ�ȭ
    MemberInfo members[numMembers];
    for (int i = 0; i < numMembers; i++) {
        printf("��� %d �̸� �Է�: ", i + 1);
        scanf("%s", members[i].name);
    }

    int numDutchPay;
    printf("���� Ƚ�� �Է�: ");
    scanf("%d", &numDutchPay);

    // ���� ���� �迭 �ʱ�ȭ
    DutchPayInfo dutchPay[numDutchPay];
    for (int i = 0; i < numDutchPay; i++) {
        char payerName[50];
        double price;

        printf("%d�� �� �� ��� �̸�: ", i+1);
        scanf("%s", payerName);
        int payerID = -1;  // payerID�� -1�� �ʱ�ȭ 

        // �Էµ� ������ �̸��� ��� ���� �迭���� ã��
        for (int j = 0; j < numMembers; j++) {
            if (strcmp(payerName, members[j].name) == 0) {
                payerID = j; // �������� ��� ID�� ����
                break;
            }
        }

        if (payerID != -1) {
            printf("������ �ݾ�: ");
            scanf("%lf", &price);

            dutchPay[i].payer_id = payerID; // ���� ������ ������ ID ����
            dutchPay[i].price = price;    // ���� ������ �ݾ� ����
        } else {
            printf("����� ã�� �� �����ϴ�.\n");
            i--; // �ٽ� �Է� �ޱ� ���� i ����
        }
    }

    // ����� �� ���� �ݾ� ���
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

    // ���� ��� ���
	printf("\n���� ����:\n");
	for (int i = 0; i < numMembers; i++) {
    	for (int j = 0; j < numMembers; j++) {
        	if (i != j) {
            	double amountToPay = totalAmount[i] - totalAmount[j];
            	if (amountToPay > 0) {
                	printf("%s���� %s�Կ��� %.2lf���� �����ؾ� �մϴ�.\n", members[i].name, members[j].name, amountToPay);
            	}
        	}
    	}
	}
    return 0;
}

