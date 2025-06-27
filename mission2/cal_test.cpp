#include "gmock/gmock.h"
#include "car_class.cpp"

TEST(CarValidation, Pass) {
    Car car(
        CarType carType = CarType::SEDAN,
        Engine engine = Engine::GM,
        Brake brake = Brake::MANDO,
        Steering steering = Steering::BOSCH
    );
    std::string msg;
    //EXPECT_FALSE(car.IsValid(msg));
    EXPECT_EQ(msg, "PASS");
}

TEST(CarValidation, Sedan_Continental_Fail) {
    Car car(
        CarType carType = CarType::SEDAN,
        Engine engine = Engine::GM,
        Brake brake = Brake::CONTINENTAL,
        Steering steering = Steering::BOSCH
    );
    std::string msg;
    EXPECT_EQ(msg, "Sedan���� Continental ������ġ ��� �Ұ�");
}

TEST(CarValidation, SUV_Toyota_Fail) {
    Car car(
        CarType carType = CarType::SUV,
        Engine engine = Engine::TOYOTA,
        Brake brake = Brake::MANDO,
        Steering steering = Steering::BOSCH
    );
    std::string msg;
    EXPECT_EQ(msg, "SUV���� TOYOTA ���� ��� �Ұ�");
}

TEST(CarValidation, Truck_WIA_Fail) {
    Car car(
        CarType carType = CarType::TRUCK,
        Engine engine = Engine::WIA,
        Brake brake = Brake::BOSCH,
        Steering steering = Steering::BOSCH
    );
    std::string msg;
    EXPECT_EQ(msg, "Truck���� WIA���� ��� �Ұ�");
}

TEST(CarValidation, Truck_Mando_Fail) {
    Car car(
        CarType carType = CarType::TRUCK,
        Engine engine = Engine::TOYOTA,
        Brake brake = Brake::MANDO,
        Steering steering = Steering::BOSCH
    );
    std::string msg;
    EXPECT_EQ(msg, "Truck���� MANDO ������ġ ��� �Ұ�");
}

TEST(CarValidation, Bosch_Bosch_Fail) {
    Car car(
        CarType carType = CarType::TRUCK,
        Engine engine = Engine::WIA,
        Brake brake = Brake::BOSCH,
        Steering steering = Steering::BOSCH
    );
    std::string msg;
    EXPECT_EQ(msg, "Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�");
}