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
    EXPECT_EQ(msg, "Sedan에는 Continental 제동장치 사용 불가");
}

TEST(CarValidation, SUV_Toyota_Fail) {
    Car car(
        CarType carType = CarType::SUV,
        Engine engine = Engine::TOYOTA,
        Brake brake = Brake::MANDO,
        Steering steering = Steering::BOSCH
    );
    std::string msg;
    EXPECT_EQ(msg, "SUV에는 TOYOTA 엔진 사용 불가");
}

TEST(CarValidation, Truck_WIA_Fail) {
    Car car(
        CarType carType = CarType::TRUCK,
        Engine engine = Engine::WIA,
        Brake brake = Brake::BOSCH,
        Steering steering = Steering::BOSCH
    );
    std::string msg;
    EXPECT_EQ(msg, "Truck에는 WIA엔진 사용 불가");
}

TEST(CarValidation, Truck_Mando_Fail) {
    Car car(
        CarType carType = CarType::TRUCK,
        Engine engine = Engine::TOYOTA,
        Brake brake = Brake::MANDO,
        Steering steering = Steering::BOSCH
    );
    std::string msg;
    EXPECT_EQ(msg, "Truck에는 MANDO 제동장치 사용 불가");
}

TEST(CarValidation, Bosch_Bosch_Fail) {
    Car car(
        CarType carType = CarType::TRUCK,
        Engine engine = Engine::WIA,
        Brake brake = Brake::BOSCH,
        Steering steering = Steering::BOSCH
    );
    std::string msg;
    EXPECT_EQ(msg, "Bosch제동장치에는 Bosch조향장치 이외 사용 불가");
}