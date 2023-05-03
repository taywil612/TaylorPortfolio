#CIS 476 - Presentation Demo
#Author - Taylor Williams
#Date - 03/13/2023


#Schedule Library
import schedule
import time


#class AlarmSystem
class AlarmSystem:

    #Display user's alarms to them
    def displayAlarm():
        #Welcome user message
        print("**** Welcome to Alarm System ****")

        #Stores the user's alarm names
        userAlarms = ["Work", "School", "Homework"]
        [print(i) for i in userAlarms]

    # returns all class tasks of the user's alarms, every task extends AlarmSystem and overrides the execute method
    def execute():
       return Work, School, Homework

    def getMessage():
        error_message = "Error has occured when setting alarm, re-open Alarm System and try again!!"
        print(error_message)

       

#class for task work, function to define execution time and when
class Work(AlarmSystem):
    def execute():
        print("Time to go to Work!")
    
    #alarm will go off every 20 seconds
    schedule.every(20).seconds.do(execute)
    
    
#class for task school, function to define execution time and when
class School(AlarmSystem):
    def execute():
        print("Time to go to School!")

    #alarm will go off every 15 seconds
    schedule.every(15).seconds.do(execute)

#class for task homework, function to define execution time and when
class Homework(AlarmSystem):
    def execute():
        print("Time to start homework!")

    #alarm will go off every 10 seconds
    schedule.every(10).seconds.do(execute)

#Main program to implement
if __name__ == '__main__':
    AlarmSystem.displayAlarm()
    
    user_input = input("Do you wish to activate your alarms? Yes or No: ")

    if(user_input == "Yes" or "yes"):
        AlarmSystem.execute()

    elif(user_input == "No" or "no"):
        print("Exiting.....")
        exit()

    while True:
        schedule.run_pending()
        time.sleep(1)

    while False:
        AlarmSystem.getMessage()
    





        
       


      













