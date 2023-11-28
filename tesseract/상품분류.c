#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 구조체 정의
struct Item {
    char name[50];
    int price;
};

int main() {
    // 텍스트 파일에서 데이터 읽기
    FILE *file = fopen("/Users/jeon-yuli/Desktop/숭실대학교/1학년 2학기/프로그래밍2/프로젝트/extracted_text.txt", "r");  // 텍스트 파일 경로를 적절히 수정하세요.

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // 품명과 가격을 저장할 구조체 배열
    struct Item items[10];  // 최대 10개의 품목을 저장할 수 있는 배열로 가정
    int itemCount = 0;

    // 파일에서 데이터 읽어 구조체에 저장
    while (fscanf(file, "%s %d", items[itemCount].name, &items[itemCount].price) == 2) {
        // 다음 품목으로 이동
        itemCount++;

        // 최대 품목 개수를 초과하면 종료
        if (itemCount >= 10) {
            printf("Exceeded maximum number of items.\n");
            break;
        }
    }

    // 파일 닫기
    fclose(file);

    // 품명과 가격이 저장된 구조체 확인
    printf("Items:\n");
    for (int i = 0; i < itemCount; i++) {
        printf("%s\t%d\n", items[i].name, items[i].price);
    }

    return 0;
}
