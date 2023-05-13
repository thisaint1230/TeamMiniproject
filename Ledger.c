#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ledger.h"

int menu()
{ // 메뉴 함수
    int menu;
    printf("----- 메뉴 -----\n");
    printf("1. 지출 추가\n");
    printf("2. 지출 조회\n");
    printf("3. 지출 수정\n");
    printf("4. 지출 삭제\n");
    printf("5. 지출 검색\n");
    printf("6. 가장 많이 쓴 지출 분야 출력\n");
    printf("7. 월별로 조회\n");
    printf("8. 주차별로 조회\n");
    printf("9. 지출 목표 설정\n");
    printf("10. 목표 달성 여부 확인\n");
    printf("11. 리워드 또는 패널티 적용\n");
    printf("0. 종료\n");

    printf("메뉴를 선택하세요: ");
    scanf(" %d", &menu);

    return menu;
}

int askCartegory() // 카테고리를 묻는 함수
{
    int cartegory;
    printf("카테고리를 선택하세요:\n");
    printf("1. 식비\n");
    printf("2. 교통비\n");
    printf("3. ...\n"); // 여기에 추가할것들 추가해주세용
    printf("4. ...\n");
    printf("5. 기타\n");
    printf("0. 종료\n");

    printf("선택: ");
    scanf(" %d \n", &cartegory);

    return cartegory;
}

int addExpense(Data *Data, int count)
{
    printf("지출 내역을 입력하세요: \n");

            printf("1. 식비 :");
            scanf(" %d ", &Data[count].expenses[0]);
      
            printf("2. 교통비 :");
            scanf(" %d ", &Data[count].expenses[1]);
    
            printf("3. ... :");
            scanf(" %d ", &Data[count].expenses[2]);
    
            printf("4. ... :");
            scanf(" %d ", &Data[count].expenses[3]);
      
            printf("5. 기타 :");
            scanf(" %d ", &Data[count].expenses[4]);
        
    Data[count].amount = 0;
    for (int i = 0; i < 5; i++)
    {
        Data[count].amount += Data[count].expenses[i];
    }

    printf("날짜를 입력하세요 (년 월 일): ");
    scanf(" %d %d %d", &Data[count].date.year, &Data[count].date.month, &Data[count].date.day);

    printf("메모를 입력하세요: ");
    getchar();
    scanf(" %[^\n]s", Data[count].memo);

    count++;
    printf("지출이 추가되었습니다.\n");
    return count;
}

void viewExpense(Data *Data, int count) // 조회 함수
{
    if (count == 0)
    {
        printf("지출 내역이 없습니다.\n");
        return;
    }
     printf("----- 지출 조회 ----- %d \n",count);

    for(int i=0; i<count; i++){

    printf(" 1. 식비 : %d \n", Data[count].expenses[0]);
    printf("2. 교통비 : %d \n", Data[count].expenses[1]);
    printf("3. ... : %d \n", Data[count].expenses[2]);
    printf("4. ... : %d \n", Data[count].expenses[3]);
    printf("5. 기타 : %d \n", Data[count].expenses[4]);
    printf("지출 금액: %d\n", Data[count].amount);
    printf("날짜: %d-%d-%d\n", Data[count].date.year, Data[count].date.month, Data[count].date.day);
    printf("메모: %s\n", Data[count].memo);
    printf("\n");

    }
}

void updateExpense(Data *Data, int count); // 수정 함수

void deleteExpense(Data *Data, int count); // 삭제 함수

void saveToFile(Data *Data, int count, char filename[100]) // 파일 저장 함수
{

    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            fprintf(file, "%d\n", Data[i].expenses[j]);
        }
        fprintf(file, "%d\n", Data[i].amount);     // 지출 금액을 파일에 저장
        fprintf(file, "%d\n", Data[i].date.year);  // 년도를 파일에 저장
        fprintf(file, "%d\n", Data[i].date.month); // 월을 파일에 저장
        fprintf(file, "%d\n", Data[i].date.day);   // 일을 파일에 저장
        fprintf(file, "%s\n", Data[i].memo);       // 메모를 파일에 저장
    }

    fclose(file);

    printf("파일이 저장되었습니다.\n");
}
int loadFromFile(Data *Data, char filename[100]) // 파일에서 읽어오는 함수
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("파일을 열 수 없습니다.\n");
        return 0;
    }
    int count = 0;
    for (int i = 0; i < 100; i++)
    {
        if (feof(file))
            break;
        for (int j = 0; j < 5; j++)
        {
            fscanf(file, "%d", &Data[i].expenses[j]);
        }
        fscanf(file, "%d", &Data[i].amount);     // 지출 금액을 파일에서 읽어옴
        fscanf(file, "%d", &Data[i].date.year);  // 년도를 파일에서 읽어옴
        fscanf(file, "%d", &Data[i].date.month); // 월을 파일에서 읽어옴
        fscanf(file, "%d", &Data[i].date.day);   // 일을 파일에서 읽어옴
        fscanf(file, " %[^\n]s", Data[i].memo);  // 메모를 파일에서 읽어옴
        count++;
    }

    fclose(file);

    printf("파일이 불러와졌습니다.\n");

    return count;
}

void searchExpense(Data *Data, int count); // 검색 함수

void printMostUsedCategory(Data *Data, int count); // 가장 많이 쓴 지출 분야 출력 함수

void viewByMonth(Data *Data, int count); // 월별로 조회 함수

void viewByWeek(Data *Data, int count); // 주차별로 조회 함수

void setExpenseGoal(Data *Data, int count); // 지출 목표 설정 함수

void checkGoalAchievement(Data *Data, int count); // 목표 달성 여부 확인 함수

void applyRewardOrPenalty(Data *Data, int count); // 리워드 또는 패널티 적용 함수