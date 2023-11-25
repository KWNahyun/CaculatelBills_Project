#include <stdio.h>
#include <string.h>

// 사용자 정보를 저장하는 구조체
struct User {
    char username[50];
    char password[50];
};

// 등록된 사용자 정보를 저장하는 배열
struct User users[100]; // 최대 100명의 사용자를 저장할 수 있도록 배열 크기 설정
int userCount = 0; // 등록된 사용자 수를 나타내는 변수

// 사용자가 로그인되어 있는지 확인하는 함수
int isUserLoggedIn = 0;

// 물건과 물건값을 저장하는 구조체
struct Item {
    char name[50];
    double price;
    int participants; // 함께 산 사람들의 인원수
};

// 물건 정보를 저장하는 배열
struct Item items[10]; // 최대 10개의 상품을 저장할 수 있도록 배열 크기 설정
int itemCount = 0; // 현재 상품 개수

// 사용자가 선택한 상품 목록을 저장하는 배열
int selectedItems[10]; // 최대 10개의 선택한 상품을 저장할 수 있도록 배열 크기 설정
int selectedItemCount = 0; // 현재 선택한 상품 개수

// 로그인 함수
int login(char *username, char *password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            isUserLoggedIn = 1;
            return 1; // 로그인 성공
        }
    }
    return 0; // 로그인 실패
}

// 회원가입 함수
void registerUser(char *username, char *password) {
    if (userCount < sizeof(users) / sizeof(users[0])) {
        strcpy(users[userCount].username, username);
        strcpy(users[userCount].password, password);
        userCount++;
        printf("회원가입 성공!\n");
    } else {
        printf("최대 사용자 수를 초과하여 회원가입할 수 없습니다.\n");
    }
}

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

// 사용자가 선택한 상품에 대한 정보를 저장하는 구조체
struct SelectedItem {
    char payerName[50]; // 결제한 사용자의 이름
    int itemIndex;      // 선택한 상품의 인덱스
};

// 사용자가 선택한 상품 정보를 저장하는 배열
struct SelectedItem selectedItemsInfo[10]; // 최대 10개의 선택한 상품 정보를 저장할 수 있도록 배열 크기 설정
int selectedItemsInfoCount = 0; // 현재 선택한 상품 정보 개수

// 로그인 처리 함수
void handleLogin() {
    char username[50];
    char password[50];
    int loginAttempts = 3; // 로그인 시도 횟수 제한

    while (loginAttempts > 0) {
        printf("사용자 이름: ");
        scanf("%s", username);
        printf("비밀번호: ");
        scanf("%s", password);

        if (login(username, password)) {
            printf("로그인 성공!\n");
            break;
        } else {
            printf("로그인 실패. 사용자 이름 또는 비밀번호를 확인하세요.\n");
            loginAttempts--;
            if (loginAttempts > 0) {
                printf("남은 로그인 시도 횟수: %d\n", loginAttempts);
                printf("1. 재시도\n");
                printf("2. 회원가입\n");
                int choice;
                printf("선택하세요 (1 또는 2): ");
                scanf("%d", &choice);
                if (choice == 1) {
                    continue; // 다시 시도
                } else if (choice == 2) {
                    // 회원가입을 진행하도록 구현
                    printf("회원가입을 진행합니다.\n");
                    printf("새로운 사용자 이름: ");
                    scanf("%s", username);
                    printf("새로운 비밀번호: ");
                    scanf("%s", password);
                    registerUser(username, password); // 사용자 정보를 등록
                    printf("회원가입 및 로그인 성공!\n");
                    break;
                }
            } else {
                printf("로그인 시도 횟수를 모두 사용했습니다. 프로그램을 종료합니다.\n");
                return; // 함수 종료
            }
        }
    }
}

// 상품 추가 처리 함수
void addItemProcess() {
    while (1) {
        int itemAdd;
        double itemPrice;
        printf("상품을 추가하려면 1, 추가가 모두 완료되면 0을 누르세요: ");
        scanf("%d", &itemAdd);
        if (itemAdd == 1) {
            char itemName[50];
            printf("추가할 상품의 이름을 입력하세요: ");
            scanf("%s", itemName);
            printf("추가할 상품의 가격을 입력하세요: ");
            scanf("%lf", &itemPrice);
            addItem(itemName, itemPrice);
        } else {
            break;
        }
    }
}

// 상품별 인원 파악 함수
void specifyParticipants() {
    for (int i = 0; i < itemCount; i++) {
        printf("%s를 함께 산 사람의 인원수를 입력하세요: ", items[i].name);
        scanf("%d", &items[i].participants);
    }
}

// 상품 번호 선택 함수
void selectItemsProcess() {
    while (1) {
        int itemIndex;
        printf("당신이 산 상품 번호를 선택하세요 (0 입력 시 종료): ");
        scanf("%d", &itemIndex);

        if (itemIndex == 0) {
            break;
        }

        if (itemIndex >= 1 && itemIndex <= itemCount) {
            selectItem(itemIndex - 1);
        } else {
            printf("유효하지 않은 선택입니다. 다시 선택하세요.\n");
        }
    }
}

// 상품 결제 정보 출력 함수
void displayPaymentInfo() {
    double totalCost = 0.0;
    int totalParticipants = 0;

    // 최종 가격 계산과 상품들의 인당 금액 계산
    for (int i = 0; i < selectedItemsInfoCount; i++) {
        totalCost += items[selectedItemsInfo[i].itemIndex].price;
        totalParticipants += items[selectedItemsInfo[i].itemIndex].participants;
    }

    if (totalParticipants > 0) {
        double costPerParticipant = totalCost / totalParticipants;

        // 사용자가 선택한 상품의 총가격
        double totalOwed = selectedItemsInfoCount * costPerParticipant;
        printf("내가 선택한 상품의 경우 총 내야할 금액: %.2f 원\n", totalOwed);

        // 사용자가 선택한 상품 정보 출력
        printf("결제 정보:\n");
        for (int i = 0; i < selectedItemsInfoCount; i++) {
            printf("%s이(가) %s를 선택하여 결제\n", selectedItemsInfo[i].payerName, items[selectedItemsInfo[i].itemIndex].name);
        }
    } else {
        printf("선택한 상품이 없거나 함께 산 사람이 없습니다.\n");
    }
}

int main() {
    // 로그인 처리 함수 호출
    handleLogin();

    // 상품 추가 처리 함수 호출
    addItemProcess();

    // 상품별 인원 파악 함수 호출
    specifyParticipants();

    // 상품 번호 선택 함수 호출
    selectItemsProcess();

    double totalCost = 0.0;
    int totalParticipants = 0;

    // 최종 가격 계산과 상품들의 인당 금액 계산
    for (int i = 0; i < selectedItemCount; i++) {
        totalCost += items[selectedItems[i]].price;
        totalParticipants += items[selectedItems[i]].participants;
    }

    if (totalParticipants > 0) {
        double costPerParticipant = totalCost / totalParticipants;

        // 사용자가 선택한 상품의 총가격
        double totalOwed = selectedItemCount * costPerParticipant;
        printf("내가 선택한 상품의 경우 총 내야할 금액: %.2f 원\n", totalOwed);
    }

    // 결제 정보 입력
    int paymentOption;
    printf("한 사람이 결제하려면 1, 여러 사람이 결제하려면 0을 입력하세요: ");
    scanf("%d", &paymentOption);

    if (paymentOption == 1) {
        // 한 사람이 결제한 경우
        displayPaymentInfo();
    } else if (paymentOption == 0) {
        // 여러 사람이 결제한 경우
        int payerCount;

        // 결제한 사람의 숫자를 입력받기
        printf("결제한 사람의 숫자를 입력하세요: ");
        scanf("%d", &payerCount);

        if (payerCount > 0) {
            printf("결제한 사람의 정보를 입력하세요:\n");
            for (int i = 0; i < payerCount; i++) {
                printf("이름: ");
                scanf("%s", selectedItemsInfo[i].payerName);
                printf("상품 번호: ");
                scanf("%d", &selectedItemsInfo[i].itemIndex);
            }

            // 결제 계산 = 사용자가 결제를 한 경우, 즉 사용자의 이름이 selectedItemsInfo.payerName에 있을때, 결제한 사람들끼리 우선 비교
            // 만약 인당금액이 사용자가 크면 사용자 인당금액 - 타 결제사람 인당금액 만큼 받고, 작으면 타 결제 사람 인당 금액- 사용자 인당 금액 만큼 줌
            // 다른 사람들에게는 인당 금액만큼 받으면 된다고 안내 메세지 표출

            // 사용자가 결제를 하지 않은 경우, 즉 사용자의 이름이 selectedItemsInfo.payerName에 없을때, 결제한 사람에게 얼마씩 줘야하는지 안내 메세지 표출

        } else {
            printf("올바른 인원 수를 입력하세요.\n");
        }
    } else {
        printf("올바른 옵션을 선택하세요.\n");
    }
    return 0;
}
