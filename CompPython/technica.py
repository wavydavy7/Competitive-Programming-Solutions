import csv
import random

fieldNames = ["Project Title", "Submission Url","Project Status","Judging Status","Highest Step Completed","Project Created At","About The Project", "Try it out Links", "Video Demo Link","Opt-In Prizes","Built With","Submitter First Name","Submitter Last Name","Submitter Email","Notes","Attendance","Team Colleges/Universities","Additional Team Member Count"]

prizeCategories = [ 
    "Bloomberg: Best Hack Promoting Education or Public Health",
  "Capital One: Best Financial Hack",
  "Best Education Hack",
  "T. Rowe Price: Best Use of FinTech",
  "Optiver: Best Hack for Sustainability",
  "Fannie Mae: Climate Change Sentiment Analysis and Impacts on Housing",
  "CACI International: Most “Ever Vigilant” Hack Against Spyware",
  "Best Gamification Hack - Create Your Own Reality",
  "Best Accessibility Hack",
  "Best Startup Track Hack",
  "Best Research Track Hack",
  "Best UI/UX Hack",
  "Best Beginner Hack (College)",
  "Best Beginner Hack (Middle & High School)",
  "Best Social Good Hack",
  "Best Active-Wellness/Health Hack - Herbal Apothecary"
]

attendance = [
    "Virtual", 
    "In-person",
    "Combo"
]
def runTestGenerator(n, mCategories):
    with open("expo_tests.csv", "w", newline = '') as file:
        writer = csv.writer(file)
        writer.writerow(fieldNames)
        data = []
        for counter in range(n):
            copy = prizeCategories.copy()
            categoriesAmount = random.randint(1, mCategories)
            categories = []
            for i in range(categoriesAmount):
                index = random.randint(0, len(copy) - 1)
                categories.append(copy[index])
                copy.pop(index)
            print(copy)
            data.append(["Test" + str(counter), "youtube.com", "Submitted (Gallery/Visible)", "Pending", "Submit", "10/21/2023 11:00:00", "Inspirational Explanation goes here", "", "", " , ".join(categories), "Python", "Faris", "Ali", "fali@gmail.com", "", attendance[random.randint(0, 2)], "UMD", "0"])

        for d in data:
            writer.writerow(d)
    
#Test201,https://technica-2023.devpost.com/submissions/441243-test20,Submitted (Gallery/Visible),Pending,Submit,10/14/2023 03:45:55,"InspiWhat we learned\ntest20st20","","","Bloomberg:, Capital One: Best Financial Hack, Best Education Hack: ",Python,James,Walker,james.walker@gmail.com,,in-person,Harvard University,0

runTestGenerator(80, 7) #first param = num of test cases, second param = num of prize categories 
            
