#pragma config(Sensor, in1,    xLPot,          sensorPotentiometer)
#pragma config(Sensor, in2,    xRPot,          sensorPotentiometer)
#pragma config(Sensor, in3,    zAxis,          sensorGyro)
#pragma config(Sensor, dgtl1,  frontRightQuad, sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  backRightQuad,  sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  frontLeftQuad,  sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  backLeftQuad,   sensorQuadEncoder)
#pragma config(Motor,  port2,           frontRight,    tmotorVex393_MC29, openLoop, encoderPort, None)
#pragma config(Motor,  port3,           backRight,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           frontLeft,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           backLeft,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           xRight,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           xLeft,         tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#pragma config(Motor,  port6,           motorClaw,     tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
//All positive motor speed values move that motor fowar

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

//do not know if we need this yet
void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

//set-up
float wheelD = 10; //cm
float wheelC = wheelD * PI; //cm
float speedFrontRight;
float speedBackRight;
float speedFrontLeft;
float speedBackLeft;
float speedXRight;
float speedXLeft;
float previousSpeedFrontRight = 0;
float previousSpeedBackRight = 0;
float previousSpeedFrontLeft = 0;
float previousSpeedBackLeft = 0;

float xSpeed = 127;
float previousSpeedXRight = 0;
float previousSpeedXLeft = 0;

float errorCoeff = 4/5;

float errorFrontRight;
float errorBackRight;
float errorFrontLeft;
float errorBackLeft;
float errorXRight;
float errorXLeft;

float maxValue = 127;
float minValue = -127;
float maxproportion;
float minproportion;

float disBetweenWheel = 43.18; //in cm
float turnSpeed = 63;

float speedError = 9/10;

void driveForward(float speed)
{
		//Probability factor
		errorFrontRight 	= errorCoeff * (speed - previousSpeedFrontRight);
		errorBackRight	= errorCoeff * (speed - previousSpeedBackRight);
		errorFrontLeft	= errorCoeff * (speed - previousSpeedFrontLeft);
		errorBackLeft	= errorCoeff * (speed - previousSpeedBackLeft);

		//Swerve Drive with P-Loop
		motor[frontRight] 	= speed - errorFrontRight;
		motor[backRight] 	= speed - errorBackRight;
		motor[frontLeft] 	= speed - errorFrontLeft;
		motor[backLeft] 	= speed - errorBackLeft;

		//New previous Speed
		previousSpeedFrontRight = speed - errorFrontRight;
		previousSpeedBackRight 	= speed - errorBackRight;
		previousSpeedFrontLeft	= speed - errorFrontLeft;
		previousSpeedBackLeft	= speed - errorBackLeft;
}
void driveBackward(float speed)
{
//Probability factor
		errorFrontRight 	= errorCoeff * (-speed - previousSpeedFrontRight);
		errorBackRight	= errorCoeff * (-speed - previousSpeedBackRight);
		errorFrontLeft	= errorCoeff * (-speed - previousSpeedFrontLeft);
		errorBackLeft	= errorCoeff * (-speed - previousSpeedBackLeft);

		//Swerve Drive with P-Loop
		motor[frontRight] 	= -speed - errorFrontRight;
		motor[backRight] 	= -speed - errorBackRight;
		motor[frontLeft] 	= -speed - errorFrontLeft;
		motor[backLeft] 	= -speed - errorBackLeft;

		//New previous Speed
		previousSpeedFrontRight = -speed - errorFrontRight;
		previousSpeedBackRight 	= -speed - errorBackRight;
		previousSpeedFrontLeft	= -speed - errorFrontLeft;
		previousSpeedBackLeft	= -speed - errorBackLeft;
}
void turnLeft(float speed)
{
//Probability factor
		errorFrontRight 	= errorCoeff * (speed - previousSpeedFrontRight);
		errorBackRight	= errorCoeff * (speed - previousSpeedBackRight);
		errorFrontLeft	= errorCoeff * (-speed - previousSpeedFrontLeft);
		errorBackLeft	= errorCoeff * (-speed - previousSpeedBackLeft);

		//Swerve Drive with P-Loop
		motor[frontRight] 	= speed - errorFrontRight;
		motor[backRight] 	= speed - errorBackRight;
		motor[frontLeft] 	= -speed - errorFrontLeft;
		motor[backLeft] 	= -speed - errorBackLeft;

		//New previous Speed
		previousSpeedFrontRight = speed - errorFrontRight;
		previousSpeedBackRight 	= speed - errorBackRight;
		previousSpeedFrontLeft	= -speed - errorFrontLeft;
		previousSpeedBackLeft	= -speed - errorBackLeft;
}
void turnRight(float speed)
{
//Probability factor
		errorFrontRight 	= errorCoeff * (-speed - previousSpeedFrontRight);
		errorBackRight	= errorCoeff * (-speed - previousSpeedBackRight);
		errorFrontLeft	= errorCoeff * (speed - previousSpeedFrontLeft);
		errorBackLeft	= errorCoeff * (speed - previousSpeedBackLeft);

		//Swerve Drive with P-Loop
		motor[frontRight] 	= -speed - errorFrontRight;
		motor[backRight] 	= -speed - errorBackRight;
		motor[frontLeft] 	= speed - errorFrontLeft;
		motor[backLeft] 	= speed - errorBackLeft;

		//New previous Speed
		previousSpeedFrontRight = -speed - errorFrontRight;
		previousSpeedBackRight 	= -speed - errorBackRight;
		previousSpeedFrontLeft	= speed - errorFrontLeft;
		previousSpeedBackLeft	= speed - errorBackLeft;
}

void strafeRight(float speed)
{
		//Probability factor
		errorFrontRight 	= errorCoeff * (speed - previousSpeedFrontRight);
		errorBackRight	= errorCoeff * (-speed - previousSpeedBackRight);
		errorFrontLeft	= errorCoeff * (-speed - previousSpeedFrontLeft);
		errorBackLeft	= errorCoeff * (speed - previousSpeedBackLeft);

		//Swerve Drive with P-Loop
		motor[frontRight] 	= speed - errorFrontRight;
		motor[backRight] 	= -speed - errorBackRight;
		motor[frontLeft] 	= -speed - errorFrontLeft;
		motor[backLeft] 	= speed - errorBackLeft;

		//New previous Speed
		previousSpeedFrontRight = speed - errorFrontRight;
		previousSpeedBackRight 	= -speed - errorBackRight;
		previousSpeedFrontLeft	= -speed - errorFrontLeft;
		previousSpeedBackLeft	= speed - errorBackLeft;
}

void strafeLeft(float speed)
{
		//Probability factor
		errorFrontRight 	= errorCoeff * (-speed - previousSpeedFrontRight);
		errorBackRight	= errorCoeff * (speed - previousSpeedBackRight);
		errorFrontLeft	= errorCoeff * (speed - previousSpeedFrontLeft);
		errorBackLeft	= errorCoeff * (-speed - previousSpeedBackLeft);

		//Swerve Drive with P-Loop
		motor[frontRight] 	= -speed - errorFrontRight;
		motor[backRight] 	= speed - errorBackRight;
		motor[frontLeft] 	= speed - errorFrontLeft;
		motor[backLeft] 	= -speed - errorBackLeft;

		//New previous Speed
		previousSpeedFrontRight = -speed - errorFrontRight;
		previousSpeedBackRight 	= speed - errorBackRight;
		previousSpeedFrontLeft	= speed - errorFrontLeft;
		previousSpeedBackLeft	= -speed - errorBackLeft;
}
void stopRobot()
{
//Probability factor
		errorFrontRight 	= errorCoeff * (previousSpeedFrontRight);
		errorBackRight	= errorCoeff * (previousSpeedBackRight);
		errorFrontLeft	= errorCoeff * (previousSpeedFrontLeft);
		errorBackLeft	= errorCoeff * (previousSpeedBackLeft);

		//Swerve Drive with P-Loop
		motor[frontRight] 	= errorFrontRight;
		motor[backRight] 	= errorBackRight;
		motor[frontLeft] 	= errorFrontLeft;
		motor[backLeft] 	= errorBackLeft;

		//New previous Speed
		previousSpeedFrontRight = errorFrontRight;
		previousSpeedBackRight 	= errorBackRight;
		previousSpeedFrontLeft	= errorFrontLeft;
		previousSpeedBackLeft	= errorBackLeft;
}

/////////ENCODERS////////////
////////Front Right Motor as
////////ASSUMING THAT WE ARE USING DIGITAL ENCODERS
////////IF WE ARE USING INTEGRATED EMCPDER CHANGE ALL SensorValue() TO nMotorEncoder()
////////AND FIND RPM of MOTOR

void resetValues(){

	SensorValue(frontRightQuad) = 0;
	SensorValue(backRightQuad) = 0;
	SensorValue(frontLeftQuad) = 0;
	SensorValue(backLeftQuad) = 0;
}

void encoderForward(float speed, float dist){

	resetValues();

	float ticks = dist/wheelC * 360;
	while( (abs(SensorValue(frontRightQuad)) < ticks) &&
		(abs(SensorValue(backRightQuad)) < ticks) &&
		(abs(SensorValue(frontLeftQuad)) < ticks) &&
		(abs(SensorValue(backLeftQuad)) < ticks)){
	/*
		int rDiff = abs(nMotorEncoder[frontRight]) - abs(nMotorEncoder[frontLeft]);
		int rMod = sgn(rDiff)*speed*.1;
		motor[backLeft] = speed;
		motor[backRight] = speed;
		motor[frontLeft] = speed+rMod;
		motor[frontRight] = speed+rMod;
		*/

		float speedChangeFactor = speed * speedError * abs(SensorValue(frontRightQuad))/ ticks;
		driveForward(speed - speedChangeFactor);
	}
}

void encoderBackward(float speed, float dist){

	resetValues();

	float ticks = dist/wheelC * 360;
	while( (abs(SensorValue(frontRightQuad)) < ticks) &&
		(abs(SensorValue(backRightQuad)) < ticks) &&
		(abs(SensorValue(frontLeftQuad)) < ticks) &&
		(abs(SensorValue(backLeftQuad)) < ticks)){
		float speedChangeFactor = speed * speedError * abs(SensorValue(frontRightQuad))/ ticks;
		driveForward(speed - speedChangeFactor);
		}
}

void encoderTurnLeft(float speed, float dist){

	resetValues();

	float ticks = dist/wheelC * 360;
	while( (abs(SensorValue(frontRightQuad)) < ticks) &&
		(abs(SensorValue(backRightQuad)) < ticks) &&
		(abs(SensorValue(frontLeftQuad)) < ticks) &&
		(abs(SensorValue(backLeftQuad)) < ticks)){
		float speedChangeFactor = speed * speedError * abs(SensorValue(frontRightQuad))/ ticks;
		driveForward(speed - speedChangeFactor);
	}
}

void encoderTurnRight(float speed, float dist){

	resetValues();

	float ticks = (dist/wheelC * 360);
	while( (abs(SensorValue(frontRightQuad)) < ticks) &&
		(abs(SensorValue(backRightQuad)) < ticks) &&
		(abs(SensorValue(frontLeftQuad)) < ticks) &&
		(abs(SensorValue(backLeftQuad)) < ticks)){
		float speedChangeFactor = speed * speedError * abs(SensorValue(frontRightQuad))/ ticks;
		driveForward(speed - speedChangeFactor);
	}
}

void encoderStop()
{
	while (abs(previousSpeedFrontRight) > 3)
	{
		stopRobot();
		delay(50);
	}
	motor[frontRight] 	= 0;
	motor[backRight] 	= 0;
	motor[frontLeft] 	= 0;
	motor[backLeft] 	= 0;

}

float distTurn()
{
	float turndist = pow((disBetweenWheel / 2), 2) * PI / 4;
	return turndist;
}

void turnExactRight()
{
	encoderTurnRight(turnSpeed, distTurn());
}

void turnExactLeft()
{
	encoderTurnLeft(turnSpeed, distTurn());
}

void xScissorUp()
{
	errorXRight 	= errorCoeff * (xSpeed - previousSpeedXRight);
	errorXLeft 	= errorCoeff * (xSpeed - previousSpeedXLeft);

	speedXRight 	= xSpeed - errorXRight;
	speedXLeft 	= xSpeed - errorXLeft;

	motor[xRight]	= speedXRight;
	motor[xLeft] 	= speedXLeft;

	previousSpeedXRight 	= speedXRight;
	previousSpeedXLeft 	= speedXLeft;
}

void xScissorDown()
{
	errorXRight 	= errorCoeff * (-xSpeed - previousSpeedXRight);
	errorXLeft 	= errorCoeff * (-xSpeed - previousSpeedXLeft);

	speedXRight 	= -xSpeed - errorXRight;
	speedXLeft 	= -xSpeed - errorXLeft;

	motor[xRight]	= speedXRight;
	motor[xLeft] 	= speedXLeft;

	previousSpeedXRight 	= speedXRight;
	previousSpeedXLeft 	= speedXLeft;
}

void xScissorStop()
{
	errorXRight 	= errorCoeff * previousSpeedXRight;
	errorXLeft 	= errorCoeff * previousSpeedXLeft;

	speedXRight	= errorXRight;
	speedXLeft	= errorXLeft;

	motor[xRight]	= speedXRight;
	motor[xLeft] 	= speedXLeft;

	previousSpeedXRight	= speedXRight;
	previousSpeedXLeft	= speedXLeft;
}

task autonomous()
{
	///////////////////////////////////////
	//     without encoders by time			 //
	///////////////////////////////////////
	//change this as see fit
	driveForward(120); //go forward at 120/127 speed
	wait1Msec(1000); //stop for 1 sec
	encoderStop();

	turnLeft(95); // turn left at 95/127 speed
	wait1Msec(1000); //stop for 1 sec
	encoderStop();

	driveBackward(120);  //drive backward at 120/127 speed
	wait1Msec(1000); //stop for 1 sec
	encoderStop();

	turnRight(120);  //drive backward at 120/127 speed
	wait1Msec(1000); //stop for 1 sec
	encoderStop();

	/////////////////////////////////////
	//				with encoders            //
	//	I don't know if this is works  //
	/////////////////////////////////////
	encoderForward(120, 69); //go forward 69cm at 120 power
	encoderStop();
	wait1Msec(1000);

	encoderTurnLeft(95, 10);
	encoderStop();
	wait1Msec(1000);

	encoderBackward(120, 50);
	encoderStop();
	wait1Msec(1000);

	encoderTurnRight(95, 20);
	encoderStop();
	wait1Msec(1000);

	turnExactLeft();
	encoderStop();
	wait1Msec(1000);

	turnExactRight();
	encoderStop();
	wait1Msec(1000);

	strafeRight(63);
	encoderStop();
	wait1Msec(1000);

	strafeLeft(127);
	encoderStop();
	wait1Msec(1000);

	xScissorUp();
	delay(500);
	xScissorStop();
	delay(500);
	xScissorDown();
	delay(500);
	xScissorStop();
}

task usercontrol()

{
	//float minControl = 90;
	//float strafeSpeed = 127/2;
	//float turnSpeed = 127/2;
	//Loop Forever
	//Tank uses Ch 2 and Ch3
	//Strafe use Ch 1
	//Turn in Place use Ch 4

	//Use Probability loop to slowly ram up speed

	while(true)
	{
		//Remote Control Commands
		speedFrontRight = - vexRT[Ch2] + vexRT[Ch1] + vexRT[Ch4];
		speedBackRight 	= - vexRT[Ch2] - vexRT[Ch1] + vexRT[Ch4];
		speedFrontLeft	= - vexRT[Ch3] - vexRT[Ch1] - vexRT[Ch4];
		speedBackLeft		= - vexRT[Ch3] + vexRT[Ch1] - vexRT[Ch4];

		float speedArray[4] 	= {speedFrontRight, speedBackRight, speedFrontLeft, speedBackLeft};
		float maximum 		= -127;
		int maxPos 		= 0;
		float minimum 		= 127;
		int minPos 		= 0;

		//Find max and min speed and which one is each
		for (int i = 0; i < 4; i++)
		{
			if(speedArray[i] > maximum)
			{
				maximum = speedArray[i];
				maxPos 	= i;
			}
			if(speedArray[i] < minimum)
			{
				minimum = speedArray[i];
				minPos 	= i;
			}
		}

		//If drive speed is greater max or min value then create proportion
		if (maximum > maxValue)
		{
			if (minimum < minValue)
			{
				maxproportion 	= maxValue / speedArray[maxPos];
				minproportion 	= minValue / speedArray[minPos];

				if (maxproportion < minproportion)
				{
					speedFrontRight = maxproportion * speedArray[0];
					speedBackRight 	= maxproportion * speedArray[1];
					speedFrontLeft 	= maxproportion * speedArray[2];
					speedBackLeft 	= maxproportion * speedArray[3];
				}
				else
				{
					speedFrontRight = minproportion * speedArray[0];
					speedBackRight 	= minproportion * speedArray[1];
					speedFrontLeft 	= minproportion * speedArray[2];
					speedBackLeft 	= minproportion * speedArray[3];
				}
			}
			else
			{
				maxproportion 	= maxValue / speedArray[maxPos];
				speedFrontRight = maxproportion * speedArray[0];
				speedBackRight 	= maxproportion * speedArray[1];
				speedFrontLeft 	= maxproportion * speedArray[2];
				speedBackLeft 	= maxproportion * speedArray[3];
			}
		}
		else if (minimum < minValue)
		{
			minproportion 	= minValue / speedArray[minPos];
			speedFrontRight = minproportion * speedArray[0];
			speedBackRight 	= minproportion * speedArray[1];
			speedFrontLeft 	= minproportion * speedArray[2];
			speedBackLeft 	= minproportion * speedArray[3];
		}

		//Probability factor
		errorFrontRight 	= errorCoeff * (speedFrontRight - previousSpeedFrontRight);
		errorBackRight	= errorCoeff * (speedBackRight - previousSpeedBackRight);
		errorFrontLeft	= errorCoeff * (speedFrontLeft - previousSpeedFrontLeft);
		errorBackLeft	= errorCoeff * (speedBackLeft - previousSpeedBackLeft);

		//Swerve Drive with P-Loop
		motor[frontRight] 	= speedFrontRight - errorFrontRight;
		motor[backRight] 	= speedBackRight - errorBackRight;
		motor[frontLeft] 	= speedFrontLeft - errorFrontLeft;
		motor[backLeft] 	= speedBackLeft - errorBackLeft;

		//New previous Speed
		previousSpeedFrontRight = speedFrontRight - errorFrontRight;
		previousSpeedBackRight 	= speedBackRight - errorBackRight;
		previousSpeedFrontLeft	= speedFrontLeft - errorFrontLeft;
		previousSpeedBackLeft	= speedBackLeft - errorBackLeft;

		//X-Lift with P-Loop
		//Lift-up
		if (vexRT[Btn5U] == 1)
		{
			errorXRight 	= errorCoeff * (xSpeed - previousSpeedXRight);
			errorXLeft 	= errorCoeff * (xSpeed - previousSpeedXLeft);

			speedXRight 	= xSpeed - errorXRight;
			speedXLeft 	= xSpeed - errorXLeft;

			motor[xRight]	= speedXRight;
			motor[xLeft] 	= speedXLeft;

			previousSpeedXRight 	= speedXRight;
			previousSpeedXLeft 	= speedXLeft;
		}
		//Lower
		else if (vexRT[Btn5D] == 1)
		{
			errorXRight 	= errorCoeff * (-xSpeed - previousSpeedXRight);
			errorXLeft 	= errorCoeff * (-xSpeed - previousSpeedXLeft);

			speedXRight 	= -xSpeed - errorXRight;
			speedXLeft 	= -xSpeed - errorXLeft;

			motor[xRight]	= speedXRight;
			motor[xLeft] 	= speedXLeft;

			previousSpeedXRight 	= speedXRight;
			previousSpeedXLeft 	= speedXLeft;
		}
		//Stop
		else
		{
			errorXRight 	= errorCoeff * previousSpeedXRight;
			errorXLeft 	= errorCoeff * previousSpeedXLeft;

			speedXRight	= errorXRight;
			speedXLeft	= errorXLeft;

			motor[xRight]	= speedXRight;
			motor[xLeft] 	= speedXLeft;

			previousSpeedXRight	= speedXRight;
			previousSpeedXLeft	= speedXLeft;
		}

		//Wait before running loop again by 50ms
		delay(50);
	}
}
