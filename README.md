# 4DOF_Robot_Arm
simple arduino code for controlling a 4 DOF servo arm


This is some basic control software I wrote as I (unknowingly) overwrote the software already on the board (which is nowhere to be found).



Here are some tips for the assembly and operating this arm:

- The 4 servo's cannot be powered by the arduino (not over USB nor via the Vin/barrel connector). 
The voltage regulator onboard just cannot handle the current. There are pins labelled 5V and GND on the top left corner of the joystick
board. Use these to connect to an external 5V source (I use a cut up USB cable and a powerbank)

- If the arm does not respond when you load the code, check the values of the analog inputs.
Just write some code to print all 4 inputs to Serial. If they are stuck on 1023 and the values do no change when moving the sticks,
your board is as crappy as mine and there is probably a short between ground and ARef. Bend the pin inward or cut it off. That should fix it.

- There are no build instructions. The link on AliExpress is dead. Use the KeyeStudio instructions 
found here: (https://wiki.keyestudio.com/Ks0198_keyestudio_4DOF_Robot_Mechanical_Arm_Kit_for_Arduino_DIY)
These things are all (mostly) the same, use your imagination where needed... you will need it for assembling the gripper...

OK, some simple ASCII art for the gripper (looking at it from the front):

            +-------+
            |       |
            | servo |
          =============      -->> plate to hold the servo down
            |       |
          =============      -->> base plate for gripper
          ===       ===      -->> 2 rings
    ===========   ========== -->> 2 grippers
          =============      -->> connecting plate
                 =========   --> big gear



- If you have a 3D printer, print a slew ring as pictured in the KeyeStudio instructions. It will make the arm more stable...

- If you run into problems: You're on your own, I am not the cheap-ass robot arm build guru so don't even think about messaging me about this.
I build this for my kid. What should have taken 2 hours took me on and off 3 days.

I'm done, stick a fork in me...

