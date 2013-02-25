// LCD Display Variables
const short leftButton = 1,
						centerButton = 2,
						rightButton = 4;
						string autonNames[] = {"None", "Autonomous_1", "Autonomous_2", "Autonomous_3"};

// Autonomous Selection Variables
const int totalAutons = 3,
					selectedAuton = 0;

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...

	clearLCD();
	displayLCDCenteredString(0, autonNames[selectedAuton]);
	displayLCDCenteredString(1, "<  Enter   >");

	while(nLCDButtons != centerButton) // Center LCD button is not pressed
	{
		if(nLCDButtons == 0) // There are currently no buttons pressed
		{
			wait1Msec(10); // No need to waste processor cycles
		}
		else
		{
			if(nLCDButtons == leftButton && (selectedAuton - 1) >= 0) // The left button is pressed and a subtraction of 1 won't lead to a non-choice
			{
				selectedAuton--; // Decrease current autonomous selection index by 1
			}

			if(nLCDButtons == rightButton && (selectedAuton + 1) <= totalAutons)// The right button is pressed and an addition of 1 won't lead to a non-choice
			{
				selectedAuton++; // Increase current autonomous selection index by 1
			}

			while(nLCDButtons != 0) // Make sure the button is released to prevent it being impossible to use 1 step
			{
				wait1Msec(10); // No need to waste processor cycles
			}
		}

		// Add selections to the display
		clearLCDLine(0);
		displayLCDCenteredString(0, autonNames[selectedAuton]);
	}

	clearLCD();
	displayLCDCenteredString(0, autonNames[selectedAuton]);
	displayLCDCenteredString(1, "Locked In");
}
