#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           rightDrive,    tmotorVex393, openLoop)
#pragma config(Motor,  port2,           middleDrive,   tmotorVex393, openLoop)
#pragma config(Motor,  port3,            ,             tmotorVex393, openLoop)
#pragma config(Motor,  port4,            ,             tmotorVex393, openLoop)
#pragma config(Motor,  port5,            ,             tmotorVex393, openLoop)
#pragma config(Motor,  port6,            ,             tmotorVex393, openLoop)
#pragma config(Motor,  port7,            ,             tmotorVex393, openLoop)
#pragma config(Motor,  port10,          leftDrive,     tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int deadzone = 10;

int ch2Deadzoned();
int ch3Deadzoned();

task main()
{
	while(true)
	{
		if(ch2Deadzoned() < 0 && ch3Deadzoned() >0){
			motor[rightDrive]  = ch2Deadzoned() / 2;
			motor[leftDrive]   = ch3Deadzoned() / 2;
			motor[middleDrive] = ((ch2Deadzoned() + ch3Deadzoned())/2) / 2;
			}else if(ch2Deadzoned() < 0 && ch3Deadzoned() >0){
			motor[rightDrive]  = ch2Deadzoned() / 2;
			motor[leftDrive]   = ch3Deadzoned() / 2;
			motor[middleDrive] = ((ch2Deadzoned() + ch3Deadzoned())/2) / 2;
	    }else{
			motor[rightDrive]  = ch2Deadzoned();
			motor[leftDrive]   = ch3Deadzoned();
			motor[middleDrive] = ((ch2Deadzoned() + ch3Deadzoned())/2);
		}
	}
}

int ch2Deadzoned()
{
	int value;
	if(((abs(vexRT[Ch2])) >= deadzone) && ((abs(vexRT[Ch2])) < 100 - deadzone)){ //If the value of ch2 >= the_threshold and < the_maximum_value_of_the_remote - the_threshold...
		value = vexRT[Ch2];                                                        //set the returned value to the channel value.
		}else if(vexRT[Ch2] >= 100 - deadzone){                                    //If the value is >= the_maximum_value_of_the_remote - the_threshold...
		value = 127;                                                               //set the return to 127.
		}else if(vexRT[Ch2] <= -(100 - deadzone)){                                 //Inverse of above if statment.
		value = -127;
		}else{                                                                     //If nothing else set return to zero.
		value = 0;
	}
	return value;
}

int ch3Deadzoned()
{
	int value;
	if(((abs(vexRT[Ch3])) >= deadzone) && ((abs(vexRT[Ch2])) < 100 - deadzone)){  //Same as the channel2 function.
		value = vexRT[Ch3];
		}else if(vexRT[Ch3] >= 100 - deadzone){
		value = 127;
		}else if(vexRT[Ch3] <= -(100 - deadzone)){
		value = -127;
		}else{
		value = 0;
	}
	return value;
}
