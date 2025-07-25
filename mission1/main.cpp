#ifdef _DEBUG

#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLEAR_SCREEN "\033[H\033[2J"
#define INPUT_BUFFER_SIZE 100

// 상수화
const int CAR_TYPE_MIN = 1, CAR_TYPE_MAX = 3;
const int ENGINE_MIN = 1, ENGINE_MAX = 4;
const int BRAKE_MIN = 1, BRAKE_MAX = 3;
const int STEERING_MIN = 1, STEERING_MAX = 2;
const int RUN_TEST_MIN = 1, RUN_TEST_MAX = 2;

int stack[10];

void selectCarType(int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);
void runProducedCar();
void testProducedCar();
void delay(int ms);

int removeEnterAndCheckExit(char buf[INPUT_BUFFER_SIZE]);
void dsiplayQuestionStep(int step);
int checkInputNumber(const char* buf, int* answer);
void processInputNumber(int * step, int answer);
int isInRange(int value, int min, int max);
void printInputError(const char* msg);
int validateInputForStep(int step, int answer);

enum QuestionType
{
    CarType_Q,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
};

enum CarType
{
    SEDAN = 1,
    SUV,
    TRUCK
};

enum Engine
{
    GM = 1,
    TOYOTA,
    WIA
};

enum brakeSystem
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B
};

enum SteeringSystem
{
    BOSCH_S = 1,
    MOBIS
};

void delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}

int main()
{
    char buf[INPUT_BUFFER_SIZE];
    int step = CarType_Q;

    while (1)
    {
        // #1 Extrat Method (dsiplayQuestionStep)
        dsiplayQuestionStep(step);  
        fgets(buf, sizeof(buf), stdin);

        // #2 Extract Method (removeEnterAndCheckExit)
        if (!removeEnterAndCheckExit(buf)) {
            break;
        }

        int answer =0;
        // #3 Extract Method (checkInputNumber)
        if (!checkInputNumber(buf, &answer)) {
            printf("ERROR :: 숫자만 입력 가능\n");
            delay(800);
            continue;
        }

        // 처음 으로 돌아가기
        if (answer == 0 && step == Run_Test) {
            step = CarType_Q;
            continue;
        }
        // 이전으로 돌아가기
        if (answer == 0 && step >= 1) {
            step -= 1;
            continue;
        }

        // #4 Extract Method (validateInputForStep)
        if (!validateInputForStep(step, answer)) 
            continue;

        // #5 Extract Method (processInputNumber)
        processInputNumber(&step, answer);
   
    }
}

void processInputNumber(int *step, int answer) {
    if (*step == CarType_Q)
    {
        selectCarType(answer);
        delay(800);
        *step = Engine_Q;
    }
    else if (*step == Engine_Q)
    {
        selectEngine(answer);
        delay(800);
        *step = brakeSystem_Q;
    }
    else if (*step == brakeSystem_Q)
    {
        selectbrakeSystem(answer);
        delay(800);
        *step = SteeringSystem_Q;
    }
    else if (*step == SteeringSystem_Q)
    {
        selectSteeringSystem(answer);
        delay(800);
        *step = Run_Test;
    }
    else if (*step == Run_Test && answer == 1)
    {
        runProducedCar();
        delay(2000);
    }
    else if (*step == Run_Test && answer == 2)
    {
        printf("Test...\n");
        delay(1500);
        testProducedCar();
        delay(2000);
    }
}

void selectCarType(int answer)
{
    stack[CarType_Q] = answer;
    if (answer == 1)
        printf("차량 타입으로 Sedan을 선택하셨습니다.\n");
    if (answer == 2)
        printf("차량 타입으로 SUV을 선택하셨습니다.\n");
    if (answer == 3)
        printf("차량 타입으로 Truck을 선택하셨습니다.\n");
}

void selectEngine(int answer)
{
    stack[Engine_Q] = answer;
    if (answer == 1)
        printf("GM 엔진을 선택하셨습니다.\n");
    if (answer == 2)
        printf("TOYOTA 엔진을 선택하셨습니다.\n");
    if (answer == 3)
        printf("WIA 엔진을 선택하셨습니다.\n");
}

void selectbrakeSystem(int answer)
{
    stack[brakeSystem_Q] = answer;
    if (answer == 1)
        printf("MANDO 제동장치를 선택하셨습니다.\n");
    if (answer == 2)
        printf("CONTINENTAL 제동장치를 선택하셨습니다.\n");
    if (answer == 3)
        printf("BOSCH 제동장치를 선택하셨습니다.\n");
}

void selectSteeringSystem(int answer)
{
    stack[SteeringSystem_Q] = answer;
    if (answer == 1)
        printf("BOSCH 조향장치를 선택하셨습니다.\n");
    if (answer == 2)
        printf("MOBIS 조향장치를 선택하셨습니다.\n");
}

int isValidCheck()
{
    if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
    {
        return false;
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        return false;
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        return false;
    }
    else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
    {
        return false;
    }
    else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        return false;
    }
    else
    {
        return true;
    }
    return true;
}

void runProducedCar()
{
    if (isValidCheck() == false)
    {
        printf("자동차가 동작되지 않습니다\n");
    }
    else
    {
        if (stack[Engine_Q] == 4)
        {
            printf("엔진이 고장나있습니다.\n");
            printf("자동차가 움직이지 않습니다.\n");
        }
        else
        {
            if (stack[CarType_Q] == 1)
                printf("Car Type : Sedan\n");
            if (stack[CarType_Q] == 2)
                printf("Car Type : SUV\n");
            if (stack[CarType_Q] == 3)
                printf("Car Type : Truck\n");
            if (stack[Engine_Q] == 1)
                printf("Engine : GM\n");
            if (stack[Engine_Q] == 2)
                printf("Engine : TOYOTA\n");
            if (stack[Engine_Q] == 3)
                printf("Engine : WIA\n");
            if (stack[brakeSystem_Q] == 1)
                printf("Brake System : Mando");
            if (stack[brakeSystem_Q] == 2)
                printf("Brake System : Continental\n");
            if (stack[brakeSystem_Q] == 3)
                printf("Brake System : Bosch\n");
            if (stack[SteeringSystem_Q] == 1)
                printf("SteeringSystem : Bosch\n");
            if (stack[SteeringSystem_Q] == 2)
                printf("SteeringSystem : Mobis\n");

            printf("자동차가 동작됩니다.\n");
        }
    }
}

void testProducedCar()
{
    if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Sedan에는 Continental제동장치 사용 불가\n");
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("SUV에는 TOYOTA엔진 사용 불가\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 WIA엔진 사용 불가\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 Mando제동장치 사용 불가\n");
    }
    else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
    }
    else
    {
        printf("자동차 부품 조합 테스트 결과 : PASS\n");
    }
}

int removeEnterAndCheckExit(char buf[INPUT_BUFFER_SIZE])
{
    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);

    if (!strcmp(buf, "exit"))
    {
        printf("바이바이\n");
        return false;
    }
    return true;
}

void dsiplayQuestionStep(int step) {
    if (step == CarType_Q)
    {
        printf(CLEAR_SCREEN);

        printf("        ______________\n");
        printf("       /|            | \n");
        printf("  ____/_|_____________|____\n");
        printf(" |                      O  |\n");
        printf(" '-(@)----------------(@)--'\n");
        printf("===============================\n");
        printf("어떤 차량 타입을 선택할까요?\n");
        printf("1. Sedan\n");
        printf("2. SUV\n");
        printf("3. Truck\n");
    }
    else if (step == Engine_Q)
    {
        printf(CLEAR_SCREEN);
        printf("어떤 엔진을 탑재할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. GM\n");
        printf("2. TOYOTA\n");
        printf("3. WIA\n");
        printf("4. 고장난 엔진\n");
    }
    else if (step == brakeSystem_Q)
    {
        printf(CLEAR_SCREEN);
        printf("어떤 제동장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. MANDO\n");
        printf("2. CONTINENTAL\n");
        printf("3. BOSCH\n");
    }
    else if (step == SteeringSystem_Q)
    {
        printf(CLEAR_SCREEN);
        printf("어떤 조향장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. BOSCH\n");
        printf("2. MOBIS\n");
    }
    else if (step == Run_Test)
    {
        printf(CLEAR_SCREEN);
        printf("멋진 차량이 완성되었습니다.\n");
        printf("어떤 동작을 할까요?\n");
        printf("0. 처음 화면으로 돌아가기\n");
        printf("1. RUN\n");
        printf("2. Test\n");
    }
    else {

    }
    printf("===============================\n");

    printf("INPUT > ");
}

int isInRange(int value, int min, int max) {
    return (value >= min && value <= max);
}

void printInputError(const char* msg) {
    printf("ERROR :: %s\n", msg);
    delay(800);
}

int validateInputForStep(int step, int answer) {
    switch (step) {
    case CarType_Q:
        if (!isInRange(answer, CAR_TYPE_MIN, CAR_TYPE_MAX)) {
            printInputError("차량 타입은 1 ~ 3 범위만 선택 가능");
            return 0;
        }
        break;
    case Engine_Q:
        if (!isInRange(answer, ENGINE_MIN, ENGINE_MAX)) {
            printInputError("엔진은 1 ~ 4 범위만 선택 가능");
            return 0;
        }
        break;
    case brakeSystem_Q:
        if (!isInRange(answer, BRAKE_MIN, BRAKE_MAX)) {
            printInputError("제동장치는 1 ~ 3 범위만 선택 가능");
            return 0;
        }
        break;
    case SteeringSystem_Q:
        if (!isInRange(answer, STEERING_MIN, STEERING_MAX)) {
            printInputError("조향장치는 1 ~ 2 범위만 선택 가능");
            return 0;
        }
        break;
    case Run_Test:
        if (!isInRange(answer, RUN_TEST_MIN, RUN_TEST_MAX)) {
            printInputError("Run 또는 Test 중 하나를 선택 필요");
            return 0;
        }
        break;
    default:
        break;
    }
    return 1;
}

int checkInputNumber(const char* buf, int* answer) {
    char* checkNumber = NULL;
    int value = strtol(buf, &checkNumber, 10);   // 문자열을 10진수로 변환
    if (*checkNumber != '\0')
        return 0;
    *answer = value;
    return 1;
}

#endif
