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
};

// 물건 정보를 저장하는 배열
struct Item items[] = {
    {"사과", 1.0},
    {"바나나", 0.5},
    {"오렌지", 0.8},
    {"딸기", 1.2},
    // 여기에 필요한 물건 정보를 추가할 수 있습니다.
};

// 물건의 개수
int itemCount = sizeof(items) / sizeof(items[0]);

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

int main() {
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
                return 1; // 에러 코드 반환
            }
        }
    }

    // 로그인 성공한 후의 코드 (물건 선택 등)은 이어서 구현
    int choice;
    double totalCost = 0.0;

    printf("물건 목록:\n");
    for (int i = 0; i < itemCount; i++) {
        printf("%d. %s - %.2f 달러\n", i + 1, items[i].name, items[i].price);
    }

    while (1) {
        printf("물건 번호를 선택하세요 (0을 입력하면 계산 종료): ");
        scanf("%d", &choice);

        if (choice == 0) {
            break;
        }

        if (choice >= 1 && choice <= itemCount) {
            totalCost += items[choice - 1].price;
            printf("%s를 선택하였습니다. 현재 총 금액: %.2f 달러\n", items[choice - 1].name, totalCost);
        } else {
            printf("유효하지 않은 선택입니다. 다시 선택하세요.\n");
        }
    }

    printf("총 금액: %.2f 달러\n", totalCost);
    return 0;
}
