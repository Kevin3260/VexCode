#pragma config(I2C_Usage, I2C1, i2cSensors)
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

task main()
{
	while(true)
	{
		if(vexRT[Btn7D] == 1){
			motor[rightArm1] = -10;
			motor[rightArm2] = -10;
		}else if(vexRT[Btn7U] == 1){
			motor[rightArm1] = 10;
			motor[rightArm2] = 10;
		}else{
			motor[rightArm1] = 0;
			motor[rightArm2] = 0;
		}
	}
}