#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <windows.h>

#define CLEAR_SCREEN "\033[H\033[2J"

// ���ȭ
const int CAR_TYPE_MIN = 1, CAR_TYPE_MAX = 3;
const int ENGINE_MIN = 1, ENGINE_MAX = 4;
const int BRAKE_MIN = 1, BRAKE_MAX = 3;
const int STEERING_MIN = 1, STEERING_MAX = 2;
const int RUN_TEST_MIN = 1, RUN_TEST_MAX = 2;


enum class CarType { NONE, SEDAN, SUV, TRUCK };
enum class Engine { NONE, GM, TOYOTA, WIA, FAULTY };
enum class Brake { NONE, MANDO, CONTINENTAL, BOSCH };
enum class Steering { NONE, BOSCH, MOBIS };

// ��ǰ ���� ����/�޼��� ����
class Car {
public:
    CarType carType = CarType::NONE;
    Engine engine = Engine::NONE;
    Brake brake = Brake::NONE;
    Steering steering = Steering::NONE;

    void printStatus() const {
        printf("���� Ÿ��: %s\n", toString(carType));
        printf("����: %s\n", toString(engine));
        printf("������ġ: %s\n", toString(brake));
        printf("������ġ: %s\n", toString(steering));
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
        case Engine::FAULTY: return "���峭 ����";
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

// ���� ��Ģ ����
#if 1
class CarValidator {
public:
    static bool validate(const Car& car, std::string& reason) {
        if (car.carType == CarType::SEDAN && car.brake == Brake::CONTINENTAL) {
            reason = "Sedan���� Continental ������ġ ��� �Ұ�";
            return false;
        }
        if (car.carType == CarType::SUV && car.engine == Engine::TOYOTA) {
            reason = "SUV���� TOYOTA ���� ��� �Ұ�";
            return false;
        }
        if (car.carType == CarType::TRUCK && car.engine == Engine::WIA) {
            reason = "Truck���� WIA���� ��� �Ұ�";
            return false;
        }
        if (car.carType == CarType::TRUCK && car.brake == Brake::MANDO) {
            reason = "Truck���� MANDO ������ġ ��� �Ұ�";
            return false;
        }
        if (car.brake == Brake::BOSCH && car.steering != Steering::BOSCH) {
            reason = "Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�";
            return false;
        }
        reason = "PASS";
        return true;
    }
};
#endif

// �Է� �帧, �޴�, ���� ����
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
            else break; // ����
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
        printf("� ���� Ÿ���� �����ұ��?\n");
        printf("1. Sedan\n");
        printf("2. SUV\n");
        printf("3. Truck\n");
        int n; scanf_s("%d", &n);
        switch (n) {
        case 1: car.carType = CarType::SEDAN; break;
        case 2: car.carType = CarType::SUV; break;
        case 3: car.carType = CarType::TRUCK; break;
        default: 
            printf("���� Ÿ���� %d ~ %d ������ ���� ����\n", CAR_TYPE_MIN, CAR_TYPE_MAX);
            Sleep(2000);
            return inputCarType();      
        }
        return true;
    }
    bool inputEngine() {
        printf(CLEAR_SCREEN);
        printf ("� ������ ž���ұ��?\n 1.GM\n 2.TOYOTA\n 3.WIA\n 4.���峭 ����\n");
        int n; scanf_s("%d", &n);
        switch (n) {
        case 1: car.engine = Engine::GM; break;
        case 2: car.engine = Engine::TOYOTA; break;
        case 3: car.engine = Engine::WIA; break;
        case 4: car.engine = Engine::FAULTY; break;
        default: 
            printf("������ %d ~ %d ������ ���� ����\n", ENGINE_MIN, ENGINE_MAX);
            Sleep(2000);
            return inputEngine();
        }
        return true;
    }
    bool inputBrake() {
        printf(CLEAR_SCREEN);
        printf("� ������ġ�� �����ұ��?\n 1. MANDO\n 2. CONTINENTAL\n 3. BOSCH\n");
        int n; scanf_s("%d", &n);
        switch (n) {
        case 1: car.brake = Brake::MANDO; break;
        case 2: car.brake = Brake::CONTINENTAL; break;
        case 3: car.brake = Brake::BOSCH; break;
        default: 
            printf("������ġ�� %d ~ %d ������ ���� ����\n", BRAKE_MIN, BRAKE_MAX);
            Sleep(2000);
            return inputBrake();
        }
        return true;
    }
    bool inputSteering() {
        printf(CLEAR_SCREEN);
        printf("� ������ġ�� �����ұ��?\n 1. BOSCH\n 2. MOBIS\n");
        int n; scanf_s("%d", &n);
        switch (n) {
        case 1: car.steering = Steering::BOSCH; break;
        case 2: car.steering = Steering::MOBIS; break;
        default: 
            printf("������ġ�� %d ~ %d ������ ���� ����\n", STEERING_MIN, STEERING_MAX);
            Sleep(2000);
            return inputSteering();
        }
        return true;
    }
    int selectAction() {
        printf(CLEAR_SCREEN);
        printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
        printf("� ������ �ұ��?\n");
        printf("1. RUN\n");
        printf("2. Test\n");
        int n; scanf_s("%d", &n);
        switch (n) {
        case 1: return n;
        case 2: return n;
        default:
            printf("Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
            Sleep(2000);
            return selectAction();
        }
    }
    void runCar() {
        std::string reason;
        if (!CarValidator::validate(car, reason)) {
            printf("\n�ڵ����� ���۵��� �ʽ��ϴ�: %s\n", reason.c_str());
        }
        else if (car.engine == Engine::FAULTY) {
            printf("\n������ ���峪 �ֽ��ϴ�. �ڵ����� �������� �ʽ��ϴ�.\n");
        }
        else {
            car.printStatus();
            printf("�ڵ����� ���۵˴ϴ�.\n");
        }
    }
    void testCar() {
        std::string reason;
        if (!CarValidator::validate(car, reason)) {
            printf("\n�ڵ��� ��ǰ ���� �׽�Ʈ ���: FAIL\n%s\n", reason.c_str());
        }
        else {
            printf("\n�ڵ��� ��ǰ ���� �׽�Ʈ ���: PASS\n");
        }
    }
};
#endif