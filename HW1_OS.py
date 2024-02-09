# Importing required module
import subprocess
import os
 
while(True):
    #getting user input
    print("1. List directory contents\n2. Print working directory\n3. Create a new directory\n4. Display a message\n5. Concatenate and display content of a file\n6. Exit")
    usrChoice = input("Select a shell command: ")

    # Using system() method to
    # execute shell commands, python has "match" statements inplace of switch
    match int(usrChoice):
        case 1:
            subprocess.Popen('dir', shell=True)
        case 2:
            usrDir = input("Which directory to enter? ")
            try:
                os.chdir(usrDir)
                print("Current directory:", os.getcwd())
            except FileNotFoundError:
                print("Directory not found:", usrDir)
        case 3:
            newDir = input("Enter the name of the new directory: ")
            try:
                os.mkdir(newDir)
                print("Directory", newDir, "created successfully.")
            except FileExistsError:
                print("Directory", newDir, "already exists.")
        case 4:
            usrMsg = input("Enter a message: ")
            subprocess.Popen(f'echo {usrMsg}', shell=True)
        case 5:
            file1 = input("Enter the name of the first file: ")
            file2 = input("Enter the name of the second file: ")
            final_file = input("Enter the name for the combined file: ")
            # Concatenate the contents of file1 and file2 into the final file
            subprocess.Popen(f'type {file1} {file2} > {final_file}', shell=True)
            # Display the contents of the concatenated file
            subprocess.Popen(f'type {final_file}', shell=True)
        case 6:
            break
        
