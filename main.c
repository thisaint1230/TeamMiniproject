#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // 시간 관련 헤더파일 추가
#include "Ledger.h"

int main()
{   
    srand(time(0));
    Data data[100];
    char name[100];
    int count = 0;
    int menuType;
    Goal goal;
    
    printf("사용자 이름을 영어로 입력하세요 (개인 데이터의 파일명이 됩니다): ");
 
    scanf("%s", name);
    getchar();
    count = loadFromFile(data, name);

    while (1)
    {
        menuType = menu();
        switch (menuType)
        {
        case 1:
            count = addExpense(data, count);
            break;
        case 2:
            viewExpense(data, count);
            break;
        case 3:
            updateExpense(data, count);
            break;
        case 4:
            count=deleteExpense(data, count);
            break;
        case 5:
            searchExpense(data, count);
            break;
        case 6:
            printMostUsedCategory(data, count);
            break;
        case 7:
            viewByMonth(data, count);
            break;
        case 8:
            viewByWeek(data, count);
            break;
        case 9:
            setExpenseGoal(data, count,&goal,name);
            break;
        case 10:
            checkGoalAchievement(data,count,&goal,name);
            break;
        case 0:
            saveToFile(data, count, name);
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 선택입니다. 다시 선택해주세요.\n");
            
        }
    }

    return 0;
}
