#include <stdio.h>
#include <string.h>

// 상품 정보를 저장하는 구조체
struct Item {
    char name[50];
    double price;
    int participants; // 함께 산 사람들의 인원수
};

// 상품 정보를 저장하는 배열
struct Item items[10]; // 최대 10개의 상품을 저장할 수 있도록 배열 크기 설정
int itemCount = 0; // 현재 상품 개수

// 사용자가 선택한 상품 목록을 저장하는 배열
int selectedItems[10]; // 최대 10개의 선택한 상품을 저장할 수 있도록 배열 크기 설정
int selectedItemCount = 0; // 현재 선택한 상품 개수

// 새로운 상품 추가 함수
void addItem(char *name, double price) {
    if (itemCount < sizeof(items) / sizeof(items[0])) {
        strcpy(items[itemCount].name, name);
        items[itemCount].price = price;
        items[itemCount].participants = 0; // 초기 인원수는 0으로 설정
        itemCount++;
        printf("상품 추가 성공!\n");
    } else {
        printf("최대 상품 개수를 초과하여 추가할 수 없습니다.\n");
    }
}

// 상품 선택 함수
void selectItem(int itemIndex) {
    if (selectedItemCount < sizeof(selectedItems) / sizeof(selectedItems[0])) {
        selectedItems[selectedItemCount] = itemIndex;
        selectedItemCount++;
        printf("%s(을)를 선택하였습니다.\n", items[itemIndex].name);
    } else {
        printf("최대 선택 가능한 상품 개수를 초과하였습니다.\n");
    }
}

int main() {
    char itemName[50]; // 문자열을 저장할 변수 선언
    double itemPrice;  //  상품 가격을 저장할 변수 선언
    int itemIndex;
    int participants;
    int input;

    // 상품 추가 코드
    while (1) {
        int itemAdd;
        printf("상품을 추가하려면 1, 추가가 모두 완료되면 0을 누르세요: ");
        scanf("%d", &itemAdd);
        if (itemAdd == 1) {
            printf("추가할 상품의 이름을 입력하세요: ");
            scanf("%s", itemName);  // 수정: 문자열을 입력받도록 변경
            printf("추가할 상품의 가격을 입력하세요: ");
            scanf("%lf", &itemPrice);  // 수정: 실수를 입력받도록 변경
            addItem(itemName, itemPrice); // 수정: 수정된 변수 사용
        } else {
            break;
        }
    }

    for (int i = 0; i < itemCount; i++) {
            printf("%s를 함께 산 사람의 인원수를 입력하세요: ", items[i].name);
            scanf("%d", &participants);
            items[i].participants = participants;
        }

    for (int i =0; i< itemCount; i++ )
    {
        printf("%d번: %s\n", i+1, items[i].name);
    }
    
    while (1) {
        
        printf("당신이 산 상품 번호를 선택하세요 (0 입력 시 종료): ");
        scanf("%d", &itemIndex);

        while ((input = getchar()) != '\n' && input != EOF) {} // 입력 버퍼 비우기

        if (itemIndex == 0) {
            break;
        }

        if (itemIndex >= 1 && itemIndex <= itemCount) {
            selectItem(itemIndex - 1);
        } else {
            printf("유효하지 않은 선택입니다. 다시 선택하세요.\n");
        }
    }

    double totalCost = 0.0;
    int totalParticipants = 0;

    for (int i = 0; i < selectedItemCount; i++) {
        totalCost += items[selectedItems[i]].price;
        totalParticipants += items[selectedItems[i]].participants;
    }

    if (totalParticipants > 0) {
        double costPerParticipant = totalCost / totalParticipants;
        double totalOwed = selectedItemCount * costPerParticipant;
        printf("인당 내야할 금액: %.2f 원\n", costPerParticipant);
        printf("내가 선택한 상품의 경우 총 내야할 금액: %.2f 원\n", totalOwed);
    } else {
        printf("선택한 상품이 없거나 함께 산 사람이 없습니다.\n");
    }

    return 0;
}
