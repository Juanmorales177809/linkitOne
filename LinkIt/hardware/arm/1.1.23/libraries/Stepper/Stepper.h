/*
  Stepper.h - - Stepper library for Wiring/Arduino - Version 0.4
  
  Original library     (0.1) by Tom Igoe.
  Two-wire modifications   (0.2) by Sebastian Gassner
  Combination version   (0.3) by Tom Igoe and David Mellis
  Bug fix for four-wire   (0.4) by Tom Igoe, bug fix from Noah Shibley

  Drives a unipolar or bipolar stepper motor using  2 wires or 4 wires.

  When wiring multiple stepper motors to a microcontroller,
  you quickly run out of output pins, with each motor requiring 4 connections. 

  By making use of the fact that at any time two of the four motor
  coils are the inverse  of the other two, the number of
  control connections can be reduced from 4 to 2. 

  A slightly modified circuit around a Darlington transistor array or an L293 H-bridge
  connects to only 2 microcontroller pins, inverts the signals received,
  and delivers the 4 (2 plus 2 inverted ones) output signals required
  for driving a stepper motor.

  The sequence of control signals for 4 control wires is as follows:

  Step C0 C1 C2 C3
     1  1  0  1  0
     2  0  1  1  0
     3  0  1  0  1
     4  1  0  0  1

  The sequence of controls signals for 2 control wires is as follows
  (columns C1 and C2 from above):

  Step C0 C1
     1  0  1
     2  1  1
     3  1  0
     4  0  0

  The circuits can be found at 
  http://www.arduino.cc/en/Tutorial/Stepper
  
  Modified 20 Aug 2014 by MediaTek Inc.
*/

// Ensure this library description is only included once.
#ifndef Stepper_h
#define Stepper_h

//The stepper Library controls unipolar and multi-polar stepper motors.
//
//The stepper motor receives pulse signals; it stops when there is no pulse signals, and its rotation speed is proportional to pulse frequency. Immediate activation and rapid stop are its features. You can change the pulse order to change its rotation direction.
//
//The stepper motor is applied in machines requiring precision, for example, drawing and printing machines. 
class Stepper {
  public:
    // Constructors:

    // DESCRIPTION
    //  Creates a new stepper instance to represent a particular stepper motor.
    //  The number of parameters is decided by the design of the stepper motor; 2 and 4 pins are supported.
    // RETURNS
    //  None.
    // EXAMPLE
    //	<code>
    //	Stepper myStepper(100, 5, 6);       // For 2 pins stepper with 100 steps that's connected to pin D5 and D6.
    //  Stepper myStepper(100, 5, 6, 7, 8); // For 4 pins stepper with 100 steps that's connected to pin D5, D6, D7 and D8.    
    //	</code> 
    Stepper(
        int number_of_steps, //Number of steps of the current stepper motor. If your motor provides degree per step, divide 360 degree by the degree per step to get the total number of steps.
        int motor_pin_1,	//The pin bound to stepper motor (int).
        int motor_pin_2		//The pin bound to stepper motor (int).
        );

    // DESCRIPTION
    //  Creates a new stepper instance to represent a particular stepper motor.
    //  The number of parameters is decided by the design of the stepper motor; 2 and 4 pins are supported.
    // RETURNS
    //  None.
    // EXAMPLE
    //	<code>
    //	Stepper myStepper(100, 5, 6);       // For 2 wire pins stepper with 100 steps that's connected to pin D5 and D6.
    //  Stepper myStepper(100, 5, 6, 7, 8); // For 4 wire pins stepper with 100 steps that's connected to pin D5, D6, D7 and D8.
    //	</code> 
    Stepper(
        int number_of_steps, //Number of steps of the current stepper motor. If your motor provides degree per step, divide 360 degree by the degree per step to get the total number of steps.
        int motor_pin_1,	//Pin bound to stepper motor (int).
        int motor_pin_2,	//Pin bound to stepper motor (int).
        int motor_pin_3,	//Optional, for 4+1 stepper only (int).
        int motor_pin_4		//Optional, for 4+1 stepper only (int).
        );

    // DESCRIPTION
    //  Sets up the speed of stepper motor in RPMs (Rotation per Minute).
    // RETURNS
    //  None.
    void setSpeed(
		long whatSpeed	//The rotation speed (long).
		);

    // DESCRIPTION
    //  Rotates stepper motor at the speed set in setSpeed.
    // RETURNS
    //  None.
    // EXAMPLE
    //<code>
    // #include <Stepper.h>
    //  
    // #define STEPS 100   // Set up by particular stepper motor.
    //  
    // // The 4-pin stepper motor, connecting 4 pins.
    // Stepper stepper(STEPS, 8, 9, 10, 11);
    //  
    // int prev = 0;       // Reserve the previous value.
    //   
    // void setup()
    // {
    //   stepper.setSpeed(40);      // Sets up rotation speed to 40 RPMs.
    // }
    //   
    // void loop()
    // {
    //   int value = analogRead(0); // Gets data from the sensor.
    //   stepper.step(value- prev); // The movement.
    //   prev = value;              // Records the previous displacement.
    // }
    // </code> 
    void step(
		int number_of_steps	//Steps of stepper motor. Positive value means rotating in one direction; negative value means rotating in the opposite direction.
		);

    int version(void);

  private:
    void stepMotor(int this_step);
    
    int direction;        // Direction of rotation.
    int speed;          // Speed in RPMs.
    unsigned long step_delay;    // Delay between steps, in microseconds, based on the speed.
    int number_of_steps;      // Total number of steps this motor can take.
    int pin_count;        // The pin used - 2 or 4 pin, to drive the motor.
    int step_number;        // The step which the motor is on.
    bool modeset;        // Sets pin mode after constructor.
    
    // motor pin numbers:
    int motor_pin_1;
    int motor_pin_2;
    int motor_pin_3;
    int motor_pin_4;
    
    long last_step_time;      // The time stamp of the last step taken in microseconds.
};

#endif

