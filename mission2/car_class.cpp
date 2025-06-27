#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <windows.h>

#define CLEAR_SCREEN "\033[H\033[2J"

// 상수화
const int CAR_TYPE_MIN = 1, CAR_TYPE_MAX = 3;
const int ENGINE_MIN = 1, ENGINE_MAX = 4;
const int BRAKE_MIN = 1, BRAKE_MAX = 3;
const int STEERING_MIN = 1, STEERING_MAX = 2;
const int RUN_TEST_MIN = 1, RUN_TEST_MAX = 2;


enum class CarType { NONE, SEDAN, SUV, TRUCK };
enum class Engine { NONE, GM, TOYOTA, WIA, FAULTY };
enum class Brake { NONE, MANDO, CONTINENTAL, BOSCH };
enum class Steering { NONE, BOSCH, MOBIS };

// 부품 선택 상태/메서드 보관
class Car {
public:
    CarType carType = CarType::NONE;
    Engine engine = Engine::NONE;
    Brake brake = Brake::NONE;
    Steering steering = Steering::NONE;

    void printStatus() const {
        printf("차량 타입: %s\n", toString(carType));
        printf("엔진: %s\n", toString(engine));
        printf("제동장치: %s\n", toString(brake));
        printf("조향장치: %s\n", toString(steering));
    }
 
    static const char* toString(CarType type) {
        switch (type) {
        case CarType::SEDAN: return "Sedan";
        case CarType::SUV: return "SUV";
        case CarType::TRUCK: return "Truck";
        default: return "-";
        }
    }
    static const char* toString(Engine eng) {
        switch (eng) {
        case Engine::GM: return "GM";
        case Engine::TOYOTA: return "TOYOTA";
        case Engine::WIA: return "WIA";
        case Engine::FAULTY: return "고장난 엔진";
        default: return "-";
        }
    }
    static const char* toString(Brake b) {
        switch (b) {
        case Brake::MANDO: return "MANDO";
        case Brake::CONTINENTAL: return "CONTINENTAL";
        case Brake::BOSCH: return "BOSCH";
        default: return "-";
        }
    }
    static const char* toString(Steering s) {
        switch (s) {
        case Steering::BOSCH: return "BOSCH";
        case Steering::MOBIS: return "MOBIS";
        default: return "-";
        }
    }
};

// 조합 규칙 검증
#if 1
class CarValidator {
public:
    static bool validate(const Car& car, std::string& reason) {
        if (car.carType == CarType::SEDAN && car.brake == Brake::CONTINENTAL) {
            reason = "Sedan에는 Continental 제동장치 사용 불가";
            return false;
        }
        if (car.carType == CarType::SUV && car.engine == Engine::TOYOTA) {
            reason = "SUV에는 TOYOTA 엔진 사용 불가";
            return false;
        }
        if (car.carType == CarType::TRUCK && car.engine == Engine::WIA) {
            reason = "Truck에는 WIA엔진 사용 불가";
            return false;
        }
        if (car.carType == CarType::TRUCK && car.brake == Brake::MANDO) {
            reason = "Truck에는 MANDO 제동장치 사용 불가";
            return false;
        }
        if (car.brake == Brake::BOSCH && car.steering != Steering::BOSCH) {
            reason = "Bosch제동장치에는 Bosch조향장치 이외 사용 불가";
            return false;
        }
        reason = "PASS";
        return true;
    }
};
#endif

// 입력 흐름, 메뉴, 동작 선택
#if 1
class CarConfigurator {
private:
    Car car;
public:
    void run() {
        while (true) {
            if (!inputCarType()) break;
            if (!inputEngine()) break;
            if (!inputBrake()) break;
            if (!inputSteering()) break;
            int action = selectAction();
            if (action == 1) runCar();
            else if (action == 2) testCar();
            else break; // 종료
            Sleep(3000);
        }
    }
    bool inputCarType() {
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
        int n; scanf_s("%d", &n);
        switch (n) {
        case 1: car.carType = CarType::SEDAN; break;
        case 2: car.carType = CarType::SUV; break;
        case 3: car.carType = CarType::TRUCK; break;
        default: 
            printf("차량 타입은 %d ~ %d 범위만 선택 가능\n", CAR_TYPE_MIN, CAR_TYPE_MAX);
            Sleep(2000);
            return inputCarType();      
        }
        return true;
    }
    bool inputEngine() {
        printf(CLEAR_SCREEN);
        printf ("어떤 엔진을 탑재할까요?\n 1.GM\n 2.TOYOTA\n 3.WIA\n 4.고장난 엔진\n");
        int n; scanf_s("%d", &n);
        switch (n) {
        case 1: car.engine = Engine::GM; break;
        case 2: car.engine = Engine::TOYOTA; break;
        case 3: car.engine = Engine::WIA; break;
        case 4: car.engine = Engine::FAULTY; break;
        default: 
            printf("엔진은 %d ~ %d 범위만 선택 가능\n", ENGINE_MIN, ENGINE_MAX);
            Sleep(2000);
            return inputEngine();
        }
        return true;
    }
    bool inputBrake() {
        printf(CLEAR_SCREEN);
        printf("어떤 제동장치를 선택할까요?\n 1. MANDO\n 2. CONTINENTAL\n 3. BOSCH\n");
        int n; scanf_s("%d", &n);
        switch (n) {
        case 1: car.brake = Brake::MANDO; break;
        case 2: car.brake = Brake::CONTINENTAL; break;
        case 3: car.brake = Brake::BOSCH; break;
        default: 
            printf("제동장치는 %d ~ %d 범위만 선택 가능\n", BRAKE_MIN, BRAKE_MAX);
            Sleep(2000);
            return inputBrake();
        }
        return true;
    }
    bool inputSteering() {
        printf(CLEAR_SCREEN);
        printf("어떤 조향장치를 선택할까요?\n 1. BOSCH\n 2. MOBIS\n");
        int n; scanf_s("%d", &n);
        switch (n) {
        case 1: car.steering = Steering::BOSCH; break;
        case 2: car.steering = Steering::MOBIS; break;
        default: 
            printf("조향장치는 %d ~ %d 범위만 선택 가능\n", STEERING_MIN, STEERING_MAX);
            Sleep(2000);
            return inputSteering();
        }
        return true;
    }
    int selectAction() {
        printf(CLEAR_SCREEN);
        printf("멋진 차량이 완성되었습니다.\n");
        printf("어떤 동작을 할까요?\n");
        printf("1. RUN\n");
        printf("2. Test\n");
        int n; scanf_s("%d", &n);
        switch (n) {
        case 1: return n;
        case 2: return n;
        default:
            printf("Run 또는 Test 중 하나를 선택 필요\n");
            Sleep(2000);
            return selectAction();
        }
    }
    void runCar() {
        std::string reason;
        if (!CarValidator::validate(car, reason)) {
            printf("\n자동차가 동작되지 않습니다: %s\n", reason.c_str());
        }
        else if (car.engine == Engine::FAULTY) {
            printf("\n엔진이 고장나 있습니다. 자동차가 움직이지 않습니다.\n");
        }
        else {
            car.printStatus();
            printf("자동차가 동작됩니다.\n");
        }
    }
    void testCar() {
        std::string reason;
        if (!CarValidator::validate(car, reason)) {
            printf("\n자동차 부품 조합 테스트 결과: FAIL\n%s\n", reason.c_str());
        }
        else {
            printf("\n자동차 부품 조합 테스트 결과: PASS\n");
        }
    }
};
#endif