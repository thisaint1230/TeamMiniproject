
typedef struct
{
    int year;
    int month;
    int day;
} Date;

// 사용자 정보 구조체
typedef struct
{   
    int expenses[5]; // 지출 내역을 담을 int 배열
    int amount;      // 총 지출 금액
    Date date;       // 지출 날짜       날짜는 년도, 월,일 3가지의 데이터를 가지고 있어야 하므로 구조체 포인터로 정의
    char memo[100];  // 메모 (공백 가능)
} Data;

int menu(); // 메뉴

int askExpenses(); // 카테고리를 묻고 리턴하는 함수

int addExpense(Data *Data, int count); // 추가 함수

void viewExpense(Data *Data, int count); // 조회 함수

void updateExpense(Data *Data, int count); // 수정 함수

int deleteExpense(Data *Data, int count); // 삭제 함수

void saveToFile(Data *Data, int count, char filename[100]); // 파일 저장 함수

int loadFromFile(Data *Data, char filename[100]); // 파일에서 읽어오는 함수

void searchExpense(Data *Data, int count); // 검색 함수

void printMostUsedCategory(Data *Data, int count); // 가장 많이 쓴 지출 분야 출력 함수

void viewByMonth(Data *Data, int count); // 월별로 조회 함수

void viewByWeek(Data *Data, int count); // 주차별로 조회 함수

void setExpenseGoal(Data *Data, int count); // 지출 목표 설정 함수

void checkGoalAchievement(Data *Data, int count); // 목표 달성 여부 확인 함수

void applyRewardOrPenalty(Data *Data, int count); // 리워드 또는 패널티 적용 함수