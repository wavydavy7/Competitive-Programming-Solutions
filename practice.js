//data types
//undefined, null, boolean, string, symbol, number, object
//var is global
/* this script reads data from the devpost csv stored in 'devpostFile',
then goes by project name and assigns each one to a zoom room and
outputs a csv with Project Name, Prize Category, Time, and Zoom Link */
​
/* HOW TO USE
  - Download Devpost Metrics CSV. Hackathon -> Manage Hackathon -> Metrics -> Generate report -> Download report
  - Below, update the file path accordingly
  - Execute node ./zoom_assign.js, and wait for Success Message
  - Go to expo_schedule.csv for results!
*/
​
/* NOTES
  - The script works with some specific formatting in Devpost. Make sure these are satisfied before downloading csv!
  - Don't sort by opt-in prize category
  - Opt-in prize category should be a list, with each entry being in the following format:
    - "NameOfPrizeCategory - SponsorName"
  - Depending on number of submissions and time parameters, there could be a non-ideal expo length!
  - Make sure your expo timing is what you want, there are details in the success message
*/
​
const { time } = require('console');
const csv = require('csvtojson'); // using csvtojson to convert from... well, csv to json :/
const fs = require('fs'); // including Node.js file system module
const { exit } = require('process');
​
const devpostFile = './2022_devpost_data.csv';
​
const numRooms = 2; // number of max. breakout rooms per prize category
const lengthOfMeeting = 5; // in minutes, can be changed to whatever length of expo is
const startTime = new Date(2022, 9, 16, 12, 30); // time that expo starts, will start assigning demos from here (month is 0-based)
const takenTimes = {}; // maps a prize category to set of its taken times
const finalCSV = []; // array of arays, will hold final results
let endTime = startTime;
​
​
const linkDict = { //dictionary, mapping each prize category to zoom link
  'Reaching High: Best Beginner Hack (Middle or High School)' :	'https://umd.zoom.us/j/5979048793',
  'Reaching Higher: Best Beginner Hack (College/General)' :	'https://umd.zoom.us/j/5016085158',
  'Friendly Neighbors: Best Service Hack' :	'https://umd.zoom.us/my/mmredpath',
  'City Skyline: Best UX Design' :	'https://umd.zoom.us/j/2405583708',
  'Subway Surfers: Best Travel/Transportation Hack' :	'https://umd.zoom.us/my/elainegao',
  'Best Hardware Hack' :	'https://umd.zoom.us/j/9204135920',
  'Best IoT Product Hack - Qualcomm' : 'https://umd.zoom.us/j/8531596239',
  'Best Startup Track Hack' :	'https://umd.zoom.us/j/7305193821',
  'Best Hack for Adulting - Fannie Mae' :	'https://umd.zoom.us/j/2644599386',
  'Best Pedagogical App that Sparks Innovation & Learning - GenSpark' :	'https://umd.zoom.us/j/8693698198',
  'Best Hack Promoting Education or Public Health - Bloomberg' :	'https://umd.zoom.us/j/2589679759?pwd=Y0FZNDdqODZpNXlZTWdCcy9vTTFOUT09',
  'Most “Ever Vigilant” Hack for Social Media - CACI International' :	'https://umd.zoom.us/j/6998986000',
  'Best Financial Hack - Capital One' :	'https://umd.zoom.us/j/5069052724',
  'Best Hack for Connecting People - Sprout Social' :	'https://umd.zoom.us/j/3077178564',
  'Best Hack that Benefits Immigrants or International Students - Remitly' :	'https://umd.zoom.us/j/6577570407',
  'Best Use of an AI Model - Travelers' :	'https://umd.zoom.us/j/2877506907',
  'Best AI Artwork - Johns Hopkins University Applied Physics Lab' :	'https://umd.zoom.us/my/aasthasenjalia',
  'Best Autonomy or Automation Hack - Shield AI' :	'https://umd.zoom.us/j/2460229577',
  'Best Inclusive Future Hack - Cisco Talos' :	'https://umd.zoom.us/j/6255497966',
  'Best Hack for Recruiting Public Servants - Accenture Federal Services' :	'https://umd.zoom.us/j/4489531625',
  'Best Data Visualization - Optiver' :	'https://umd.zoom.us/j/7051461449',
  'Best FinTech Hack - T. Rowe Price' :	'gotechnica.org/ashlee',
  'Best Hack for Social Good - JPMorgan Chase & Co.': 'https://umd.zoom.us/j/7494658412',
  'Most Creative Data - Visionist Inc': 'https://umd.zoom.us/j/9106012278'
} 
​const b = true
// using csvtojson, convert to json and make it ez pz to work with
csv()
  .fromFile(devpostFile) // change this path to the devpost csv (not sorted by opt-in prize)
  .then(async (csvResult) => {
    csvResult.forEach( // iterate over all teams
      (item) => { // each item is a project name
        if (item['Project Title'] !== null && item['Project Status'] !== 'Draft' && item['Project Status'] !== 'Submitted (Hidden)' && item['Opt-In Prizes']) { // idk why drafts show up in this csv, but ignoring them is good
          const personalTimes = {}; // stores timeslots this team is booked for, so as to not overlap demos
          const prizes = item['Opt-In Prizes'].split(','); // separate all opt-in prizes
          let b = !b
          if (b){
            let place = "virtual"

          }
          else{
            let place = "in-person"
          }
          for (let i = 0; i < prizes.length; i++) { // iterate over all prize categories for this team (comma separated)
            let demoTime; // resultant time to give for this specific team
            let prizeName, sponsName; //current prize name and sponsor names
            

​
            // extract sponsor name from category ( this is for a format where the prize category is denoted as: "CategoryName - SponsorName" )
            const prizeString = prizes[i].split(' - ');
            if (prizeString.length !== 1) {
              [prizeName, sponsName] = prizeString; // eslint doesn't like this, but I don't care :))
              if (sponsName == "Major League Hacking") { //ignoring MLH prize category since for 2022 they are doing video demos
                continue;
              }
              if (!linkDict[prizes[i].trim()]) {
                console.error("Oh no! I didn't find a zoom link for \"" + prizes[i] + "\"! check linkDict.");
                exit();
              }
            } else {
              if (prizes[i].trim() == "Best Domain Name from Domain.com") { //this was an MLH prize in 2022, ignoring it too
                continue;
              }
              prizeName = prizeString[0];
              sponsName = 'Technica'; // since technica don't end in '- Technica'
            }
            prizeName.trim();
            if (!takenTimes[prizeName]) { // prize category hasn't been seen yet, initialize JSON object
              takenTimes[prizeName] = {}; // nested json object, initialize new property for this sponsor
            }
            // now prize category is set, time to find a valid time
            demoTime = startTime; // start at the earliest possible time, then let's go through until we find a good fit!
            let timeResult = takenTimes[prizeName][demoTime];
            // if the current sponsor already has at capacity for this time slot, OR the current team already has a demo for this time slot
            while ((typeof timeResult !== 'undefined' && timeResult >= numRooms) || personalTimes[demoTime]) { // if either of these mappings exist, the time won't work
              demoTime = new Date(demoTime.getTime() + lengthOfMeeting * 60000); // try next slot of meetings, increment by length of meeting
              timeResult = takenTimes[prizeName][demoTime];
            }
​
            if (demoTime > endTime) { //keep track of latest demo time
              endTime = demoTime;
            }
​
            let projectTitle = [item['Project Title']];
            
            if (projectTitle.toString().includes(',')) { //replace any comments in project title, can mess up csv
              projectTitle = projectTitle.toString().replace(",", "")
            }
​
            //in the case of breakout rooms, check if a demo is already present and if so, increment it. otherwise, assign to 1
            takenTimes[prizeName][demoTime] = (timeResult) ? timeResult + 1 : 1; // update the dictionary entry, add a mapping for this time slot
            personalTimes[demoTime] = 1; // store that we now have a demo for this time slot
            finalCSV.push([projectTitle, demoTime, new Date(demoTime.getTime() + lengthOfMeeting * 60000), prizeName, sponsName, linkDict[prizes[i].trim()]], place);
          }
        }
      },
    );
​
    let output = 'team_name,start_time,end_time,prize_category,sponsor_name,zoom_link\n'; // define headings
​
    finalCSV.forEach((row) => { // creating csv format from array of arrays
      output += `${row.join(',')}\n`;
    });
​
    // https://www.w3schools.com/nodejs/nodejs_filesystem.asp
    fs.writeFile('expo_schedule.csv', output, (err) => {
      if (err) throw err;
      console.log(`~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nSchedule Created & Saved Sucessfully! look at expo_schedule.csv for results :)\n\nYour expo starts at: \n-${startTime} \nand ends at: \n-${endTime}!\n\nBest of Luck :)\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`);
    });
  });