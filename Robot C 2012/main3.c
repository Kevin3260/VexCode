#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    x_axis,         sensorAccelerometer)
#pragma config(Sensor, in2,    y_axis,         sensorAccelerometer)
#pragma config(Sensor, in3,    yaw,            sensorGyro)
#pragma config(Sensor, in7,    autonomousSelect, sensorPotentiometer)
#pragma config(Sensor, in8,    potentiometer,  sensorPotentiometer)
#pragma config(Sensor, I2C_1,  left,           sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  right,          sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           driveRightFront, tmotorVex393, openLoop, encoder, encoderPort, I2C_2, 1627776)
#pragma config(Motor,  port2,           driveLeftFront, tmotorVex393, openLoop, reversed, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port3,           rightArm1,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port4,           leftArm1,      tmotorVex393, openLoop)
#pragma config(Motor,  port5,           rightArm2,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port6,           leftArm2,      tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port7,           intakeRight,   tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port8,           intakeLeft,    tmotorVex393, openLoop)
#pragma config(Motor,  port9,           driveRightBack, tmotorVex393, openLoop)
#pragma config(Motor,  port10,          driveLeftBack, tmotorVex393, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/********\
*Settings*
\********/

int threshold = 10;      // Threshold for driving deadzone
int driveSlow = 1;       // Starting at 1, the greater the number, the slower it goes, formula:(value/driveSlow = speed)
int intakeSpeed = 80;    // Speed of the intake
int armSpeed = 127;      // Speed of arm for upward movment
int armDownSpeed = 127;  // Speed of arm for downward movement
int slowSpeed = 20;      // Speed of arm for downward movement while near the bottom to prevent the arm from slamming into the ground
int slowdPosition = 400; // Position to start slowing down the arm
int maxHeight = 1700;    // Maximum code allowed pot value number for arm to get to so the pot dosent break.
int scoreHeight = 1600;  // Height of arm that is optimum for scoring
int zeroValue = 255;     // Value of pot at zero arm height

/*********************\
*Function Declarations*
\*********************/

void lowerArm();
void raiseArm();
void drive();
void intake1();
void stopArm();
void positionArm(int position);
int armPosition();

void pivotTurnRight(int speed);
void pivotTurnLeft(int speed);
void zeroEncoders();

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{

	motor[intakeLeft]  = -127;
	motor[intakeRight] = -127;
	zeroEncoders();
	while(rightEncoder() + leftEncoder() < (1500)*2)
	{
		motor[driveLeftBack]   = 100;
		motor[driveLeftFront]  = 100;
		motor[driveRightBack]  = 100;
		motor[driveRightFront] = 100;
	}
	motor[driveLeftBack]   = 0; // Stop
	motor[driveLeftFront]  = 0;
	motor[driveRightBack]  = 0;
	motor[driveRightFront] = 0;
	motor[intakeLeft]  = 0; // Stop Arm
	motor[intakeRight] = 0;

	pivotTurnLeft(90);
	pivotTurnLeft(90);
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{
		drive();
		intake1();

		if(vexRT[Btn6U]== 1 && vexRT[Btn6D] == 0 && vexRT[Btn8U]== 0 && vexRT[Btn8D]== 0){
			raiseArm();
			}	else if(vexRT[Btn6U] == 0 && vexRT[Btn6D] == 1 && vexRT[Btn8U] == 0 && vexRT[Btn8D] == 0 && vexRT[Btn8R] == 0){
			lowerArm();
			} else if(vexRT[Btn6U] == 0 && vexRT[Btn6D] == 0 && vexRT[Btn8U] == 1 && vexRT[Btn8D] == 0 && vexRT[Btn8R] == 0){
			positionArm(scoreHeight);
			} else if(vexRT[Btn6U] == 0 && vexRT[Btn6D] == 0 && vexRT[Btn8U] == 0 && vexRT[Btn8D] == 1 && vexRT[Btn8R] == 0){
			positionArm(zeroValue);
		}
		else{
			stopArm();}
	}
}

/*********\
*Functions*
\*********/


void lowerArm()
{
	// Arm lowers
	// Speed decreases as we near the bottom.
	if(armPosition() > slowdPosition)
	{
		motor[rightArm1] = -armDownSpeed;
		motor[rightArm2] = -armDownSpeed;
		motor[leftArm1]  = -armDownSpeed;
		motor[leftArm2]  = -armDownSpeed;
		} else if(armPosition() > zeroValue){
		motor[rightArm1] = -slowSpeed;
		motor[rightArm2] = -slowSpeed;
		motor[leftArm1]  = -slowSpeed;
		motor[leftArm2]  = -slowSpeed;
	}
	else{
		stopArm();
	}
}


void drive()
{
	if(abs(vexRT[Ch3]) > threshold)
	{
		// Tank drive left side with deadzones.
		motor[driveLeftBack]  = ((vexRT[Ch3])/driveSlow);
		motor[driveLeftFront] = ((vexRT[Ch3])/driveSlow);
		} else {
		// Stop left side movement.
		motor[driveLeftBack]  = 0;
		motor[driveLeftFront] = 0;
	}


	if(abs(vexRT[Ch2]) > threshold)
	{
		// Tank drive right side with deadzones.
		motor[driveRightBack] = ((vexRT[Ch2]) / driveSlow);
		motor[driveRightFront]  = ((vexRT[Ch2]) / driveSlow);
		} else {
		// Stop right side movement.
		motor[driveRightBack] = 0;
		motor[driveRightFront]  = 0;
	}
}

void intake1()
{// Intake for 1 controller.
	if(vexRT[Btn5D] == 1 && vexRT[Btn5U] == 0)
	{
		// Intake roller inward.
		motor[intakeLeft] = intakeSpeed;
		motor[intakeRight] = intakeSpeed;
		} else  if(vexRT[Btn5D]==0&&vexRT[Btn5U]==1) {
		// Intake roller outward.
		motor[intakeLeft] = -intakeSpeed;
		motor[intakeRight] = -intakeSpeed;
		} else {
		// Stop intake roller movement.
		motor[intakeLeft] = 0;
		motor[intakeRight] = 0;
	}
}



void raiseArm()
{// Arm goes up.
	if(armPosition() < maxHeight){
		motor[rightArm1] = armSpeed;
		motor[rightArm2] = armSpeed;
		motor[leftArm1]  = armSpeed;
		motor[leftArm2]  = armSpeed;
		}else{
		stopArm();
	}
}


void stopArm()
{// This is to stop the arm motors.
	motor[rightArm1] = 0;
	motor[rightArm2] = 0;
	motor[leftArm1]  = 0;
	motor[leftArm2]  = 0;
}

void positionArm(int position)
{// Positions arm to a specified place

	if (armPosition() < position )
	{
		while(armPosition() < position && vexRT[Btn6U] == 0 && vexRT[Btn6D] == 0 && vexRT[Btn8D] == 0 &&vexRT[Btn8R] == 0){
			raiseArm();
			drive();
			intake1();
		}
		stopArm();
	} else if (armPosition() > position)
	{
		while (armPosition() > position && vexRT[Btn6U] == 0 && vexRT[Btn6D] == 0 && vexRT[Btn8D] == 0 &&vexRT[Btn8R] == 0){
			lowerArm();
			drive();
			intake1();
		}
	}
}


int armPosition()
{// Returns pot value
	return (SensorValue[potentiometer]);
}

void pivotTurnRight(int speed)
{
	zeroEncoders();
	while(leftEncoder() - rightEncoder() < (inchesFor90Turn * ticksPerInch))
	{ // Turn right while encoders are less than target value
		motor[driveLeftBack]   = speed;
		motor[driveLeftFront]  = speed;
		motor[driveRightBack]  = -speed;
		motor[driveRightFront] = -speed;
	}
	motor[driveLeftBack]   = 0; // Stop
	motor[driveLeftFront]  = 0;
	motor[driveRightBack]  = 0;
	motor[driveRightFront] = 0;
}

void pivotTurnLeft(int speed)
{
	zeroEncoders();
	while(rightEncoder() - leftEncoder() < (inchesFor90Turn * ticksPerInch))
	{ // Turn left while encoders are less than target value
		motor[driveLeftBack]   = -speed;
		motor[driveLeftFront]  = -speed;
		motor[driveRightBack]  = speed;
		motor[driveRightFront] = speed;
	}
	motor[driveLeftBack]   = 0; // Stop
	motor[driveLeftFront]  = 0;
	motor[driveRightBack]  = 0;
	motor[driveRightFront] = 0;
}

void zeroEncoders()
{
	SensorValue[left]  = 0;
	SensorValue[right] = 0;
}