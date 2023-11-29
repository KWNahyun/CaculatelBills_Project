#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

// 구조체 정의: 상품 정보를 저장하기 위한 구조체
typedef struct {
    char payment_time[MAX_LINE_LENGTH];
    char product_name[MAX_LINE_LENGTH];
    int price;
} ProductInfo;

int main() {
    // 텍스트 파일 경로
    const char *file_path = "/Users/jeon-yuli/Desktop/숭실대학교/1학년 2학기/프로그래밍2/프로젝트/extracted_text.txt";

    // 파일 열기
    FILE *file = fopen(file_path, "r");
    if (!file) {
        perror("파일 열기 실패");
        return 1;
    }

    // 초기 동적 배열 할당
    ProductInfo *product_infos = malloc(sizeof(ProductInfo));
    if (!product_infos) {
        perror("메모리 할당 실패");
        fclose(file);
        return 1;
    }

    // 한 줄씩 읽어가며 처리
    char line[MAX_LINE_LENGTH];

    int num_products = 0;
    while (fgets(line, sizeof(line), file)) {
        // 줄 끝에 있는 개행문자 제거
        line[strcspn(line, "\n")] = '\0';

        // 결제시간 추출
        strcpy(product_infos[num_products].payment_time, line);

        // 상품명 추출
        fgets(line, sizeof(line), file);
        line[strcspn(line, "\n")] = '\0'; // 개행문자 제거
        strcpy(product_infos[num_products].product_name, line);

        // 뛰어넘기
        fgets(line, sizeof(line), file);

        // 가격 추출
        fgets(line, sizeof(line), file);
        // "출금"이 포함된 줄인지 확인
        if (strstr(line, "출금")) {
            // 출금 가격 추출
            char *price_str = strtok(line, "출금 ");
            // 쉼표를 제거하고 가격을 정수로 변환
            for (int i = 0; price_str[i]; i++) {
                if (price_str[i] == ',') {
                    memmove(price_str + i, price_str + i + 1, strlen(price_str) - i);
                }
            }
            product_infos[num_products].price = atoi(price_str);
        } else {
            // 그 외의 경우는 가격을 0으로 설정
            product_infos[num_products].price = 0;
        }

        // 동적 배열 크기 확장
        num_products++;
        product_infos = realloc(product_infos, (num_products + 1) * sizeof(ProductInfo));
        if (!product_infos) {
            perror("메모리 재할당 실패");
            fclose(file);
            return 1;
        }
        // 뛰어넘기
        fgets(line, sizeof(line), file);

    }

    // 파일 닫기
    fclose(file);

    // 결과 출력
    for (int i = 0; i < num_products; i++) {
        printf("상품명: %s\n", product_infos[i].product_name);
        printf("가격: %d 원\n", product_infos[i].price);
        printf("\n");
    }

    // 동적 배열 메모리 해제
    free(product_infos);

    return 0;
}
