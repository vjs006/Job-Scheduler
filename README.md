# READ ME FILE

## Application Design

![image](https://github.com/user-attachments/assets/80364532-b958-4894-818f-962feea7ebe1)


cURL must be installed in the system before running our application. Below are the steps to do so.

Step 1: Open the link we have provided by copy and pasting it in your browser: https://curl.se/download.html

Step 2: Scroll down until you find your required Operating system and type. (PLEASE NOTE: OUR CODE ONLY RUNS ON WINDOWS DUE TO cURL COMPATIBILITY)

Step 3: Download the the zip file, and extract its details to the C drive of your system. (ONLY TO C: DRIVE, OTHERWISE THERE MAY BE CHANGES IN THE COMPILATION OF THE CODE) 

Step 4: Rename that folder to "libcurl".

Step 5: Go to startup and type environment variables.

Step 6: Under system variables click path and select edit.

Step 7: After that select new and paste the file path of the "bin" folder in the libcurl folder.

Step 8: To verify curl installation, open command prompt and type the exact wordings: curl --version.

Step 9: It should show you the version of curl you have installed.

STEPS TO RUN OUR PROGRAM

Step 1: Open the folder given in the zip file and copy and paste every file in the folder into the same folder in your pc.

Step 2: Open command prompt and type these exact wordings to compile our code: gcc Project.c -IC:\libcurl\include -LC:\libcurl\lib -lcurl -o JobApplication

Step 3: After compilation,enter ".\JobApplication" to get the output our program.

Step 4: Enter Sign-Up in the username part to create a new account. Otherwise, enter the username and password of the account and proceed.

SPLITTING OF FILES

1. All of our code is in the form of a single c program file.

2. However, there are 4 seperate files. One acts as a database for Recruiters, one for seekers, and one for Users.

3. The last file, Temp.txt, is used the code to act as a temporary file for copying. It does not hold any important significance in the program.

4. The 3 files will be updated automatically on form submission. There is absolutely no need to manually update the files, by the use of cURL and appscript the updation process is automated.

5. Do not change the content of any of the files manually. It may disrupt the running of the code.

Please follow all instructions in the code and in the forms carefully. Keep in mind the details in the google form ARE CASE SENSITIVE.

It is NOT possible to run the executable file without compiling it first by following the above steps. This is due to the use of cURL in the program.
Please compile the code manually first before running the code. An exe file is present with the code HOWEVER it will NOT run without manual compilation first.
Also, if the libcurl files are stored elsewhere, replace that with the file path accordingly in place of "IC:\libcurl\include -LC:\libcurl\lib". This line assumes that libcurl has been installed in the C: Drive directly, not inside any other folder.

Thank you for trying out our program. We hope the code and the program runs well and provides the desired output.

