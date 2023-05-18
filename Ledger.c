#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
    scanf("%d", &menu);

    return menu;
}

int askCartegory() // 카테고리를 묻는 함수
{
    int cartegory;
    printf("1. 식비\n");
    printf("2. 교통비\n");
    printf("3. 고정 지출\n");
    printf("4. 취미·여가\n");
    printf("5. 기타\n");
    printf("0. 종료\n");

    printf("선택: ");
    scanf("%d \n", &cartegory);

    return cartegory;
}

int addExpense(Data *Data, int count) // 데이터 추가하는 함수
{
    struct tm *currentTime;
    time_t t = time(NULL);
    currentTime = localtime(&t);

    char torf;

    printf("오늘의 가계부를 작성하시겠습니까? 맞으면 't', 다른 날짜를 입력하고 싶다면 'f': ");
    scanf(" %c", &torf);

    if (torf == 't')
    {
        Data[count].date.year = currentTime->tm_year + 1900;
        Data[count].date.month = currentTime->tm_mon + 1;
        Data[count].date.day = currentTime->tm_mday;
        printf("오늘의 날짜: %d년 %d월 %d일\n", currentTime->tm_year + 1900, currentTime->tm_mon + 1, currentTime->tm_mday);
        // 오늘 날짜를 사용하여 작업을 수행
    }
    else
    {
        printf("날짜를 입력하세요 (년 월 일): ");
        scanf("%d %d %d", &Data[count].date.year, &Data[count].date.month, &Data[count].date.day);

        // 입력한 날짜를 사용하여 작업을 수행
    }

    printf("지출 내역을 입력하세요: \n");
    printf("1. 식비 :");
    scanf("%d", &Data[count].expenses[0]);

    printf("2. 교통비 :");
    scanf("%d", &Data[count].expenses[1]);

    printf("3. 고정 지출 :");
    scanf("%d", &Data[count].expenses[2]);

    printf("4. 취미·여가 :");
    scanf("%d", &Data[count].expenses[3]);

    printf("5. 기타 :");
    scanf("%d", &Data[count].expenses[4]);

    Data[count].amount = 0;
    for (int i = 0; i < 5; i++)
    {
        Data[count].amount += Data[count].expenses[i];
    }

    printf("메모를 입력하세요 (없을경우 x 가 입력됩니다 ): ");
    getchar();
    scanf("%[^\n]s", Data[count].memo);

    if (strlen(Data[count].memo) == 0) {
        strcpy(Data[count].memo, "x");
    }
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

    printf("----- 지출 조회 ----- \n");

    for (int i = 0; i < count; i++)
    {
        printf("날짜: %d-%d-%d\n", Data[i].date.year, Data[i].date.month, Data[i].date.day);
        printf("1. 식비 : %d \n", Data[i].expenses[0]);
        printf("2. 교통비 : %d \n", Data[i].expenses[1]);
        printf("3. 고정 지출 : %d \n", Data[i].expenses[2]);
        printf("4. 취미·여가 : %d \n", Data[i].expenses[3]);
        printf("5. 기타 : %d \n", Data[i].expenses[4]);
        printf("지출 금액: %d\n", Data[i].amount);
        printf("메모: %s\n", Data[i].memo);
        printf("\n");
    }
}

void updateExpense(Data *Data, int count) // 수정 함수
{
    if (count == 0)
    {
        printf("지출 내역이 없습니다.\n");
        return;
    }
    viewExpense(Data, count);
    printf("수정할 날짜를 입력하세요 (년 월 일): ");
    int updateYear, updateMonth, updateDay;
    scanf("%d %d %d", &updateYear, &updateMonth, &updateDay);

    int found = 0;
    int category = 1;
    for (int i = 0; i < count; i++)
    {
        if (Data[i].date.year == updateYear && Data[i].date.month == updateMonth && Data[i].date.day == updateDay)
        {
            while (1)
            {
                printf("수정할 카테고리 번호를 입력하세요:\n");
                category = askCartegory();
                if (category == 0)
                    break;
                printf("수정전 금액입니다 : %d 원 \n 수정될 금액을 입력해주세요: ", Data[i].expenses[category - 1]);
                scanf("%d", &Data[i].expenses[category - 1]);
            }

            Data[i].amount = 0;
            for (int j = 0; j < 5; j++)
            {
                Data[i].amount += Data[i].expenses[j];
            }

            printf("메모를 입력하세요: ");
            getchar();
            scanf("%[^\n]s", Data[i].memo);

            printf("지출 내역이 수정되었습니다.\n");

            found = 1;
            break;
        }
    }
    if (found == 0)
    {
        printf("해당 날짜의 지출 내역을 찾을 수 없습니다.\n");
    }
}

int deleteExpense(Data *Data, int count) // 삭제 함수
{
    if (count == 0)
    {
        printf("지출 내역이 없습니다.\n");
        return count;
    }
    viewExpense(Data, count);
    printf("삭제할 날짜를 입력하세요 (년 월 일): ");
    int deleteYear, deleteMonth, deleteDay;
    scanf("%d %d %d", &deleteYear, &deleteMonth, &deleteDay);

    int deleteindex = 0;
    while (1)
    {
        for (int i = 0; i < count; i++)
        {
            if (Data[i].date.year == deleteYear && Data[i].date.month == deleteMonth && Data[i].date.day == deleteDay)
            {
                deleteindex = i; // 날짜에서 인덱스번호 찾기
            }
        }
        if (deleteindex == 0)
        {
            printf("날짜를 잘못 입력하셨습니다 다시 입력해주세요 \n");
        }
        else
            break;
    }

    for (int i = deleteindex; i < count - 1; i++)
    {
        Data[i] = Data[i + 1]; // 한칸씩 앞으로 땡겨서 삭제하기
    }

    count--;

    printf("지출 내역이 삭제되었습니다.\n");

    return count;
}
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

        fprintf(file, "%d %d %d ", Data[i].date.year, Data[i].date.month, Data[i].date.day); // 날짜를 파일에 저장

        for (int j = 0; j < 5; j++)
        {
            fprintf(file, "%d ", Data[i].expenses[j]); // 지출 내역을 파일에 저장
        }
        fprintf(file, "%d\n", Data[i].amount); // 지출 금액을 파일에 저장

        if (strlen(Data[count].memo) == 0) {
            strcpy(Data[count].memo, "x");
        }
        fprintf(file, "%s\n", Data[i].memo);   // 메모를 파일에 저장
    }

    fclose(file);

    printf("파일이 저장되었습니다.\n");
}

int loadFromFile(Data *Data, char filename[100]) // 파일에서 읽어오는 함수
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf(" 기존 파일이 없거나 열 수 없어 \n 사용자 의 이름으로 파일을 만듭니다 .\n");
        return 0;
    }

    int count = -1;
    int a = 0;
    for (int i = 0; i < 100; i++)
    {
       if (feof(file))
                    break;
        fscanf(file, "%d %d %d", &Data[i].date.year, &Data[i].date.month, &Data[i].date.day); // 날짜를 파일에서 읽어옴
       
        for (int j = 0; j < 5; j++)
        {
            fscanf(file, " %d", &Data[i].expenses[j]); // 지출 내역을 파일에서 읽어옴
        }
        fscanf(file, "%d", &Data[i].amount);    // 지출 금액을 파일에서 읽어옴
        fscanf(file, " %[^\n]s", Data[i].memo); // 메모를 파일에서 읽어옴
        count++;
    }

    fclose(file);

    printf("파일이 불러와졌습니다.\n");

    return count;
}

void searchExpense(Data *Data, int count) // 검색 함수
{
    if (count == 0)
    {
        printf("지출 내역이 없습니다.\n");
        return;
    }

    char keyword[100];
    printf("메모에서 검색할 단어 또는 문자들을 입력하세요: ");
    scanf(" %[^\n]s", keyword);

    printf("검색 결과:\n");
    int found = 0;

    for (int i = 0; i < count; i++)
    {
        if (strstr(Data[i].memo, keyword) != NULL)
        {
            printf("날짜: %d-%d-%d\n", Data[i].date.year, Data[i].date.month, Data[i].date.day);
            printf("1. 식비 : %d \n", Data[i].expenses[0]);
            printf("2. 교통비 : %d \n", Data[i].expenses[1]);
            printf("3. 고정 지출 : %d \n", Data[i].expenses[2]);
            printf("4. 취미·여가 : %d \n", Data[i].expenses[3]);
            printf("5. 기타 : %d \n", Data[i].expenses[4]);
            printf("지출 금액: %d\n", Data[i].amount);
            printf("메모: %s\n", Data[i].memo);
            printf("\n");
            found = 1;
        }
    }

    if (found == 0)
    {
        printf("해당 메모 내역을 찾을 수 없습니다.\n");
    }
}

void printMostUsedCategory(Data *Data, int count)
{
    if (count == 0)
    {
        printf("지출 내역이 없습니다.\n");
        return;
    }

    struct CategoryTotal
    {
        int categoryIndex;
        int totalExpense;
    };

    struct CategoryTotal categoryTotals[5];
    for (int i = 0; i < 5; i++){
        categoryTotals[i].totalExpense=0;
    }

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            categoryTotals[j].categoryIndex = j;
            categoryTotals[j].totalExpense += Data[i].expenses[j];
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            if (categoryTotals[j].totalExpense > categoryTotals[i].totalExpense)
            {
                struct CategoryTotal temp = categoryTotals[i];
                categoryTotals[i] = categoryTotals[j];
                categoryTotals[j] = temp;
            }
        }
    }

    // 카테고리 순위 출력
    printf("지출 분야 순위:\n");
    int rank = 1;
    int previousTotalExpense = categoryTotals[0].totalExpense;
    for (int i = 0; i < 5; i++)
    {
        int categoryIndex = categoryTotals[i].categoryIndex;
        int totalExpense = categoryTotals[i].totalExpense;

        if (totalExpense < previousTotalExpense)
            rank++;

        switch (categoryIndex)
        {
        case 0:
            printf("%d위: 식비 (총 지출: %d)\n", rank, totalExpense);
            break;
        case 1:
            printf("%d위: 교통비 (총 지출: %d)\n", rank, totalExpense);
            break;
        case 2:
            printf("%d위: 고정 지출 (총 지출: %d)\n", rank, totalExpense);
            break;
        case 3:
            printf("%d위: 취미·여가 (총 지출: %d)\n", rank, totalExpense);
            break;
        case 4:
            printf("%d위: 기타 (총 지출: %d)\n", rank, totalExpense);
            break;
        }

        previousTotalExpense = totalExpense;
    }
}

void viewByMonth(Data *Data, int count); // 월별로 조회 함수

void viewByWeek(Data *Data, int count); // 주차별로 조회 함수

void setExpenseGoal(Data *Data, int count); // 지출 목표 설정 함수

void checkGoalAchievement(Data *Data, int count); // 목표 달성 여부 확인 함수

void applyRewardOrPenalty(Data *Data, int count); // 리워드 또는 패널티 적용 함수