#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Ledger.h"

int menu()
{ // 메뉴 함수
    int menu;
    printf("========== 가계부 MENU ==========\n");
    printf("\n\t1. 지출 추가\n");
    printf("\t2. 지출 조회\n");
    printf("\t3. 지출 수정\n");
    printf("\t4. 지출 삭제\n");
    printf("\t5. 지출 검색\n");
    printf("\t6. 가장 많이 쓴 지출 분야는?\n");
    printf("\t7. 월별 지출 조회\n");
    printf("\t8. 주차별 지출 조회\n");
    printf("\t9. 지출 목표 설정\n");
    printf("\t10. 목표 달성 여부 확인\n");
    printf("\t11. REWARD OR PENALTY\n");
    printf("\t0. 종료\n");
    printf("\n==================================\n");

    printf("\n=> 메뉴를 선택하세요! : ");
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
    scanf("%d", &cartegory);

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

    printf("메모를 입력하세요 (없을경우 x가 입력됩니다 ): ");
    getchar();
    scanf("%[^\n]s", Data[count].memo);

    if (strlen(Data[count].memo) == 0)
    {
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
        printf("식비 : %d ", Data[i].expenses[0]);
        printf("| 교통비 : %d ", Data[i].expenses[1]);
        printf("| 고정 지출 : %d ", Data[i].expenses[2]);
        printf("| 취미·여가 : %d ", Data[i].expenses[3]);
        printf("| 기타 : %d \n", Data[i].expenses[4]);
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
                printf("수정전 금액입니다 : %d 원 \n수정될 금액을 입력해주세요: ", Data[i].expenses[category - 1]);
                scanf("%d", &Data[i].expenses[category - 1]);
            }

            Data[i].amount = 0;
            for (int j = 0; j < 5; j++)
            {
                Data[i].amount += Data[i].expenses[j];
            }
            char yorn;
            char plusMemo[100];
            char *ptr;

            printf("메모를 추가하시겠습니까 아니면 수정하시겠습니까? (수정은 c 추가는 p 아무것도 아니라면 아무거나 입력해주세요): ");
            getchar();
            scanf("%c", &yorn);
            if (yorn == 'c')
            {
                printf("수정 전 메모입니다 : %s \n", Data[i].memo);

                printf("수정할 내용를 입력해주세요 : ");
                getchar();
                scanf("%[^\n]s", plusMemo);
                strcpy(Data[i].memo, plusMemo);
                printf("수정된 메모 입니다 %s", Data[i].memo);
            }
            else if (yorn == 'p')
            {
                printf("추가할 내용를 입력해주세요 : ");
                getchar();
                scanf("%[^\n]s", plusMemo);
                strcat(Data[i].memo, plusMemo);
                printf("추가된 메모 입니다 %s", Data[i].memo);
            }

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

        if (strlen(Data[count].memo) == 0)
        {
            strcpy(Data[count].memo, "x");
        }
        fprintf(file, "%s\n", Data[i].memo); // 메모를 파일에 저장
    }

    fclose(file);

    printf("파일이 저장되었습니다.\n");
}

int loadFromFile(Data *Data, char filename[100]) // 파일에서 읽어오는 함수
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf(" 기존 파일이 없거나 열 수 없어 사용자 의 이름으로 파일을 만듭니다 .\n");
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
            printf("식비 : %d ", Data[i].expenses[0]);
            printf("| 교통비 : %d ", Data[i].expenses[1]);
            printf("| 고정 지출 : %d ", Data[i].expenses[2]);
            printf("| 취미·여가 : %d ", Data[i].expenses[3]);
            printf("| 기타 : %d \n", Data[i].expenses[4]);
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
    for (int i = 0; i < 5; i++)
    {
        categoryTotals[i].totalExpense = 0;
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

void viewByMonth(Data *Data, int count)
{
    int year, month;
    int totalExpenses = 0;
    int found = 0;
    printf("조회할 연도와 월을 입력하세요 (년 월): ");
    scanf("%d %d", &year, &month);

    printf("\n[월별 지출 내역 - %d년 %d월]\n", year, month);

    // 해당 월의 지출 내역 출력
    for (int i = 0; i < count; i++)
    {
        if (Data[i].date.year == year && Data[i].date.month == month)
        {
            printf("날짜: %d년 %d월 %d일\n", Data[i].date.year, Data[i].date.month, Data[i].date.day);
            printf("지출 내역:\n");
            printf("식비 : %d ", Data[i].expenses[0]);
            printf("| 교통비 : %d ", Data[i].expenses[1]);
            printf("| 고정 지출 : %d ", Data[i].expenses[2]);
            printf("| 취미·여가 : %d ", Data[i].expenses[3]);
            printf("| 기타 : %d \n", Data[i].expenses[4]);
            printf("총 지출: %d\n", Data[i].amount);
            printf("메모: %s\n", Data[i].memo);
            printf("--------------------\n");
            totalExpenses += Data[i].amount;
            found = 1;
        }
    }
    if (found == 0)
    {
        printf("\n 해당 월에 지출 내역이 없습니다 \n\n");
    }
    printf("월 지출: %d\n", totalExpenses);
} // 월별로 조회 함수

void viewByWeek(Data *Data, int count)
{

    int year, month, week;
    int found = 0;
    printf("### 단, 그 주차의 달은 월요일이 속한 달을 따라갑니다 \n    예를 들어 5월의 마지막 날이 월요일인 경우 6월 1일은 6월 1주차가 아닌 5월 마지막 주차 입니다. \n");
    printf("조회할 연도와 월, 조회할 주를 입력하세요 (년 월 주차): ");
    scanf("%d %d %d", &year, &month, &week);

    struct tm firstDate = {.tm_year = year - 1900, .tm_mon = month - 1, .tm_mday = 1};
    mktime(&firstDate); // 해당 달의 처음 날의 요일 0이면 일요일

    struct tm lastDate = {.tm_year = year - 1900, .tm_mon = month, .tm_mday = 0};
    mktime(&lastDate); // 해당 달의 마지막 날짜

    int firstDayOfWeek = firstDate.tm_wday;
    if (firstDayOfWeek == 0)
    {
        firstDayOfWeek = 6; // 일요일을 월요일로 변경
    }
    else
    {
        firstDayOfWeek--; // 기존 요일 값을 0부터 6까지로 조정
    }

    int daysToAdd = (week - 1) * 7 - firstDayOfWeek;

    if (daysToAdd < 0)
    {
        daysToAdd += 7;
    }

    int day = 1 + daysToAdd;
    int maxDay = lastDate.tm_mday;

    printf("Dates in Week %d:\n", week);
    int j = -1;

    for (int i = 0; i < 7; i++)
    {
        if (day <= maxDay)
        {
            printf("날짜: %d년 %d월 %d일\n", year, month, day);
            found=0;
            for (int i = 0; i < count; i++)
            {   
                if (Data[i].date.year == year && Data[i].date.month == month && Data[i].date.day == day)
                {
                    printf("지출 내역:\n");
                    printf("식비 : %d ", Data[i].expenses[0]);
                    printf("| 교통비 : %d ", Data[i].expenses[1]);
                    printf("| 고정 지출 : %d ", Data[i].expenses[2]);
                    printf("| 취미·여가 : %d ", Data[i].expenses[3]);
                    printf("| 기타 : %d \n", Data[i].expenses[4]);
                    printf("총 지출: %d\n", Data[i].amount);
                    printf("메모: %s\n", Data[i].memo);
                    printf("--------------------\n");
                    found=1;
                }
            }
            if(found==0)
                {
                    printf("######### 지출 내역 이 없습니다 ######### \n");
                }
            day++;
        }
        else
        {
            j = i;
            break;
        }
    }

    if (month >= 12) // 만약 해당 주차는 끝나지 않았지만 달이 끝났을 경우 남은 날짜 출력
    {
        year++;
        month = 1;
        day = 1;
    }

    else
    {
        month++;
        day = 1;
    }



    if (j != -1)
    {    found=0;
        for (int i = j; i < 7; i++)
        {
            printf("날짜: %d년 %d월 %d일\n", year, month, day);
            for (int i = 0; i < count; i++)
            {   
                if (Data[i].date.year == year && Data[i].date.month == month && Data[i].date.day == day)
                {
                    printf("지출 내역:\n");
                    printf("식비 : %d ", Data[i].expenses[0]);
                    printf("| 교통비 : %d ", Data[i].expenses[1]);
                    printf("| 고정 지출 : %d ", Data[i].expenses[2]);
                    printf("| 취미·여가 : %d ", Data[i].expenses[3]);
                    printf("| 기타 : %d \n", Data[i].expenses[4]);
                    printf("총 지출: %d\n", Data[i].amount);
                    printf("메모: %s\n", Data[i].memo);
                    printf("--------------------\n");
                    found=1;
                }

            }
            if(found==0)
                {
                    printf("######### 지출 내역 이 없습니다 ######### \n");
                }
            day++;
        }
    }
}

void setExpenseGoal(Data *Data, int count); // 지출 목표 설정 함수

void checkGoalAchievement(Data *Data, int count); // 목표 달성 여부 확인 함수

void applyRewardOrPenalty(Data *Data, int count); // 리워드 또는 패널티 적용 함수
