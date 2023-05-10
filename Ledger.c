#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ledger.h"

void menu(User *user, int count); // 메뉴 함수

void addExpense(User *user, int count); // 추가 함수

void viewExpense(User *user, int count); // 조회 함수

void updateExpense(User *user, int count); // 수정 함수

void deleteExpense(User *user, int count); // 삭제 함수

void saveToFile(User *user, int count); // 파일 저장 함수

void loadFromFile(User *user, int count); // 파일에서 읽어오는 함수

void searchExpense(User *user, int count); // 검색 함수

void printMostUsedCategory(User *user, int count); // 가장 많이 쓴 지출 분야 출력 함수

void viewByMonth(User *user, int count); // 월별로 조회 함수

void viewByWeek(User *user, int count); // 주차별로 조회 함수

void setExpenseGoal(User *user, int count); // 지출 목표 설정 함수

void checkGoalAchievement(User *user, int count); // 목표 달성 여부 확인 함수

void applyRewardOrPenalty(User *user, int count); // 리워드 또는 패널티 적용 함수