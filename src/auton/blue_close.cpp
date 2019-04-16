#include "main.h"
#include "okapi/api.hpp"
#include "korvexlib.h"

using namespace okapi;

void auton_blue_close() {
    intakeMotor.move_velocity(200);
    chassis.moveDistance(37_in); // going to cap with ball under it
    chassis.moveDistanceAsync(-39.5_in);

    // wait until we intake ball to bot
    timeHold = pros::millis();
    while (!isBallTouchBottomSensor())
    {
        pros::delay(20);
    }

    // theres a ball at the top, we want to pull it down back to the trigger
    intakeMotor.move_relative(500, 200);

    pros::delay(300);

    // theres a ball at the top, we want to pull it down back to the trigger
    intakeMotor.move_relative(-400, 200);
    pros::delay(200);
    // there is now a ball in both positions

    // back and turn into shooting position
    flywheelController.moveVelocity(580);
    chassis.waitUntilSettled();

    // aim for flag
    chassis.turnAngle(83.5_deg);
    chassis.moveDistance(10.5_in);

    // shoot first ball when ready
    while (!(flywheelController.getActualVelocity() > 575))
    {
        pros::delay(20);
    }
    intakeMotor.move_relative(1000, 200);

    // wait for first ball to get shot
    timeHold = pros::millis();
    while (!(flywheelController.getActualVelocity() <= 450) && (timeHold + 700 > pros::millis()))
    {
        pros::delay(20);
    }

    // quick switch to mid flag, so when flywheel power lowers cuz of stress of launch, we can use the decel to improve speed
    flywheelController.moveVelocity(450);

    // wait for spinup
    pros::delay(400);

    // shoot 2nd ball
    intakeMotor.move_relative(1200, 200);
    // wait for second ball to get shot
    pros::delay(400);
    chassis.setMaxVelocity(150);
    flywheelController.moveVelocity(0);

    // flip bot flag
    chassis.turnAngle(7.5_deg);
    chassis.moveDistance(50_in);

    // move back for scrape
    chassis.setMaxVelocity(180);
    chassis.moveDistance(-40_in);

    // turn to scrape cap
    flywheelController.moveVelocity(550); // feed-through shot velocity
    chassis.turnAngle(-57.5_deg);

    // move to cap
    chassis.moveDistance(12_in);

    // scrape
    capflipMotor.move_absolute(-550, 200);
    intakeMotor.move_velocity(200);
    pros::delay(200);
    chassis.moveDistance(-10_in);
    chassis.turnAngle(-17.5_deg);
    capflipMotor.move_absolute(0, 200);
    chassis.moveDistanceAsync(10_in);

    // wait for first ball to get to top pos
    while (!isBallTouchUpperSensor())
    {
        pros::delay(20);
    }

    // wait for second ball to get to bot pos
    timeHold = pros::millis();
    while (!isBallTouchBottomSensor() && (timeHold + 5000 > pros::millis()))
    {
        pros::delay(20);
    }

    // we got a second ball, let it pull up a bit
    intakeMotor.move_relative(400, 200);
    pros::delay(500);
    intakeMotor.move_relative(-500, 200);

    capflipMotor.move_absolute(0, 200);
    chassis.waitUntilSettled();
    flywheelController.moveVelocity(520);
    chassis.turnAngle(-15_deg); // aim for flags

    // shoot closest pole to red
    pros::delay(500);
    intakeMotor.move_relative(1500, 200);
    pros::delay(300);

    // second ball
    flywheelController.moveVelocity(550);
    pros::delay(1500);
    intakeMotor.move_relative(1000, 200);
    pros::delay(500);
    flywheelController.moveVelocity(0);
}