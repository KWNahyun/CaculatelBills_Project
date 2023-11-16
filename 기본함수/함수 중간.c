#include <stdio.h>
#include <string.h>

// 사용자 정보를 저장하는 구조체
struct User 
{
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
void registerUser(char *username, char *password) 
{
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



int main() {
    char username[50];
    char password[50];
    int loginAttempts = 3; // 로그인 시도 횟수 제한
    int itemIndex; // Declare itemIndex

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
                return 1; // 에러 코드 반환
            }
        }
    }

    // 로그인 성공한 후의 코드 (물건 선택 및 더치페이)은 이어서 구현
    // 상품 추가 코드
    while (1) {
        int itemAdd;
        double itemPrice; // Declare itemPrice
        printf("상품을 추가하려면 1, 추가가 모두 완료되면 0을 누르세요: ");
        scanf("%d", &itemAdd);
        if (itemAdd == 1) {
            printf("추가할 상품의 이름을 입력하세요: ");
            scanf("%s", username);
            printf("추가할 상품의 가격을 입력하세요: ");
            scanf("%lf", &itemPrice);
            addItem(username, itemPrice);
        } else {
            break;
        }
    }

    for (int i = 0; i < itemCount; i++) {
        printf("%s를 함께 산 사람의 인원수를 입력하세요: ", items[i].name);
        scanf("%d", &items[i].participants);
    }

    for (int i =0; i< itemCount; i++ )
    {
        printf("%d번: %s\n", i+1, items[i].name);
    }
    
    while (1) {
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

    double totalCost = 0.0;
    int totalParticipants = 0;

    // Calculate total cost and participants for selected items
    for (int i = 0; i < selectedItemCount; i++) {
        totalCost += items[selectedItems[i]].price;
        totalParticipants += items[selectedItems[i]].participants;
    }

    if (totalParticipants > 0) {
        double costPerParticipant = totalCost / totalParticipants;

        // Calculate and display the total cost for the items you've selected
        double totalOwed = selectedItemCount * costPerParticipant;
        printf("내가 선택한 상품의 경우 총 내야할 금액: %.2f 원\n", totalOwed);
    } else {
        printf("선택한 상품이 없거나 함께 산 사람이 없습니다.\n");
    }


    return 0;
}
