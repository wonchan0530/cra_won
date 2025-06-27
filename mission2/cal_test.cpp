#include "gmock/gmock.h"
#include "car_class.cpp"


TEST(CarValidation, Sedan_Continental_Fail) {
    Car car(
        CarType carType = CarType::SEDAN,
        Engine engine = Engine::GM,
        Brake brake = Brake::CONTINENTAL,
        Steering steering = Steering::BOSCH
    );
    std::string msg;
    //EXPECT_FALSE(car.IsValid(msg));
    EXPECT_EQ(msg, "Sedan에는 Continental 제동장치 사용 불가");
}
