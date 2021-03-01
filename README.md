# ReversePower
Raise an integer to the power of its reverse

Abdelrahman Fahmy, 11/01/2021.

1.Document Scope:
	Documentation for a program calculating and testing raising an integer to the power of its reverse.

2.Abstract:
	The C program calculates the value of a positive integer raised to the power of its own reverse. A test script reads that output and compares it to the value
	returned by WolframAlpha maths engine to decide whether it's correct or not. This process is automated via Bash script.

3.Package Contents:

	README.txt: This file.

	rev_pow.c: The C program to calculate the power.
	rev_pow	 : Executable of the C file.
	power_output.txt: The result of the calculation

	power_test.py: The Python 2.7 test script

	run_power.sh: Bash script to automate the process.


4.Run Information:
	-This program was developed on "Raspbian GNU/Linux 10 (buster)" and "Raspberry Pi 3 Model B Plus Rev 1.3".
	-gcc compiler is required for compiling the C file.
	-WolframAlpha Python library can be installed via: "pip install wolframalpha", it can be found here https://pypi.org/project/wolframalpha/.

	The entry point and the execution of the program and the test is carried out by the bash script "run_power.sh" as shown in the following steps:
		1-Open terminal and navigate to the folder where the script and the rest of the attached files are located.
		2-Run the script by typing: "./run_power.sh". (see attached picture launch_bash_valid.png)
		3-This will automatically compile rev_pow.c using the following command : "gcc rev_pow.c -o rev_pow".
		4-The script will then run the program using the command "./rev_pow".
		5-The user will be prompted to enter the multi-digit positive integer and press Enter.
		6-After the calculation is finished it will be shown in the terminal, and written to the text file "power_output.txt".
		7-The test script will then read the text file "power_output.txt" contents that also has the base and exponent numbers.
		8-The test script will pass the base and exponent to WolframAlpha math engine, save the result and show it as "Model Answer".
		9-The test script will compare the C program output to the "Model Answer" and display "PASS" or "FAIL".

5.Design Overview:
	Since the expected output will be beyond regular data types, so the approach used is aiming to deal with the output digits separately. Using long multiplication, the base is multiplied by itself
	exponent times-1.
	The program is split into 2 main steps 1)reverse the input number 2)perform the long multiplication. 
	More details can be found in the comments.
	
6.Test Limitation:
	Although WolframAlpha is capable of calculating extermely large numbers, but the value returned by the Python library was cropped. Perhaps the "More_Digits" property needs 
	to be set, but unfortunately there wasn't enough time to pursue this.
	
7.Design Limitation:
	Since the output number is stored in an array, the number of bytes it can hold is bound by the RAM size of the machine running the program, and the MAX_SIZE of the biggest integer data type that hardware can support.
	One further possible improvement would be storing two single digits in one output array index, instead of one, that would double the capacity but will take a toll on the performance.
	
	
