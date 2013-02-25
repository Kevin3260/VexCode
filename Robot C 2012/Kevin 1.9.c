#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    armPotentiometer, sensorPotentiometer)
#pragma config(Sensor, in7,    driveSelector,  sensorNone)
#pragma config(Sensor, in8,    slowSelector,  sensorPotentiometer)
#pragma config(Sensor, dgtl1,  solenoid,       sensorDigitalOut)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           rightDrive,    tmotorVex393, openLoop, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port2,           middleDrive,   tmotorVex393, openLoop)
#pragma config(Motor,  port3,           armRight,      tmotorVex393, openLoop)
#pragma config(Motor,  port4,           armLeft,       tmotorVex393, openLoop)
#pragma config(Motor,  port5,           armRight2,     tmotorVex393, openLoop)
#pragma config(Motor,  port6,           armLeft2,      tmotorVex393, openLoop)
#pragma config(Motor,  port7,           flipper,       tmotorVex393, openLoop)
#pragma config(Motor,  port10,          leftDrive,     tmotorVex393, openLoop, encoder, encoderPort, I2C_2, 1000)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int deadzone = 10;
float slowSpeed = .70; // driveSpeed = joystickValue * slowSpeed

int ch1Deadzoned();
int ch2Deadzoned();
int ch3Deadzoned();
void tankDriveSlowedPointTurns();
void tankDriveNormal();
void tankDriveSlow();
void arcadeDriveNormal();
void arcadeDriveSlow() ;
void beltPneumatics();

task main()
{
	while(true)
	{
		if(SensorValue[driveSelector] > 500)
		{ while(SensorValue[driveSelector] > 500 && SensorValue[slowSelector] <= 500){
				arcadeDriveNormal();
				beltPneumatics();
				}while(SensorValue[driveSelector] > 500 && SensorValue[slowSelector] > 500){
				arcadeDriveSlow();
				beltPneumatics();
			}
			}else{
			while(SensorValue[driveSelector] <= 500 && SensorValue[slowSelector] <= 340){
				tankDriveNormal();
				beltPneumatics();
				}while(SensorValue[driveSelector] <= 500 && SensorValue[slowSelector] > 340 && SensorValue[slowSelector] < 680){
				tankDriveSlowedPointTurns();
				beltPneumatics();
				}while(SensorValue[driveSelector] <= 500 && SensorValue[slowSelector] >= 680){
				tankDriveSlow();
				beltPneumatics();
			}
		}
	}
}

int ch1Deadzoned()
{int value;
	if(((abs(vexRT[Ch1])) >= deadzone) && ((abs(vexRT[Ch1])) < 127 - deadzone)){ // If the value of Ch1 >= the_threshold and < the_maximum_value_of_the_remote - the_threshold...
		value = vexRT[Ch1];                                                        // set the returned value to the channel value.
		}else if(vexRT[Ch1] >= 127 - deadzone){                                    // If the value is >= the_maximum_value_of_the_remote - the_threshold...
		value = 127;                                                               // set the return to 127.
		}else if(vexRT[Ch1] <= -(127 - deadzone)){                                 // Inverse of above if statment.
		value = -127;
		}else{                                                                     // If nothing else, return zero.
		value = 0;
	}
	return value;
}

int ch2Deadzoned()
{int value;
	if(((abs(vexRT[Ch2])) >= deadzone) && ((abs(vexRT[Ch2])) < 127 - deadzone)){ // Same as the channel 1 function.
		value = vexRT[Ch2];
		}else if(vexRT[Ch2] >= 127 - deadzone){
		value = 127;
		}else if(vexRT[Ch2] <= -(127 - deadzone)){
		value = -127;
		}else{
		value = 0;
	}
	return value;
}

int ch3Deadzoned()
{	int value;
	if(((abs(vexRT[Ch3])) >= deadzone) && ((abs(vexRT[Ch2])) < 127 - deadzone)){ // Same as the channel 2 function...
		value = vexRT[Ch3];
		}else if(vexRT[Ch3] >= 127 - deadzone){
		value = 127;
		}else if(vexRT[Ch3] <= -(127 - deadzone)){
		value = -127;
		}else{
		value = 0;
	}
	return value;
}

void tankDriveSlowedPointTurns()
{
	if(ch2Deadzoned() < 0 && ch3Deadzoned() > 0){                             // If ch2 is negative and ch3 is positive(Point turn counterclockwise)
		motor[rightDrive]  = ch2Deadzoned() * slowSpeed;                        // Run motors at slowed speed.
		motor[leftDrive]   = ch3Deadzoned() * slowSpeed;
		motor[middleDrive] = ((ch2Deadzoned() + ch3Deadzoned())/2) * slowSpeed; // Middle motor is the average of the two channels because it runs the differential.
		}else if(ch2Deadzoned() > 0 && ch3Deadzoned() < 0){                     // If ch2 is positive and ch3 is negative(Point turn clockwise)
		motor[rightDrive]  = ch2Deadzoned() * slowSpeed;                        // Run motors at slowed speed.
		motor[leftDrive]   = ch3Deadzoned() * slowSpeed;
		motor[middleDrive] = ((ch2Deadzoned() + ch3Deadzoned())/2) * slowSpeed;
		}else{                                                                  // If strait, soft turn, or stopped
		motor[rightDrive]  = ch2Deadzoned();                                    // Run motors at 100% speed.
		motor[leftDrive]   = ch3Deadzoned();
		motor[middleDrive] = (ch2Deadzoned() + ch3Deadzoned());
	}
}

void tankDriveNormal()
{ motor[rightDrive]  = ch2Deadzoned();                                      // Always run motors at 100% of speed.
	motor[leftDrive]   = ch3Deadzoned();
	motor[middleDrive] = ((ch2Deadzoned() + ch3Deadzoned())/2);
}

void tankDriveSlow()
{	motor[rightDrive]  = ch2Deadzoned() * slowSpeed;                          // Always run motors at slowed speed.
	motor[leftDrive]   = ch3Deadzoned() * slowSpeed;
	motor[middleDrive] = ((ch2Deadzoned() + ch3Deadzoned())/2) * slowSpeed;
}

void arcadeDriveNormal()                                                    // Arcade Drive at full power
{ int right = ch2Deadzoned() - ch1Deadzoned();		                          // Variables are to allow the middle motor to work easily.
	int left = ch2Deadzoned() + ch1Deadzoned();
	motor[rightDrive]  = right;
	motor[leftDrive]   = left;
	motor[middleDrive] = ((right + left)/2);
}

void arcadeDriveSlow()                                                      // Arcade drive with motors slowed.
{ int right = ch2Deadzoned() - ch1Deadzoned();
	int left = ch2Deadzoned() + ch1Deadzoned();
	motor[rightDrive]  = right * slowSpeed;
	motor[leftDrive]   = left * slowSpeed;
	motor[middleDrive] = ((right + left)/2) * slowSpeed;
}

void beltPneumatics()
{
	if(vexRT[Btn7U] == 1 && vexRT[Btn7D] == 0)
	{ SensorValue[solenoid] = 1;  // Extend belt
		}else if(vexRT[Btn7D] == 1 && vexRT[Btn7U] == 0){
		SensorValue[solenoid] = 0;  // Reatract belt
		}else{
	}                             // Keep the state unchanged
}
/*************\
* PLEASE WORK *
\*************/