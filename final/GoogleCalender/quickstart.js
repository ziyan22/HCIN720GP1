//attention: you need to make sure that there are three days in 14 days


var fs = require('fs');
var readline = require('readline');
var google = require('googleapis');
var request = require('request');
var googleAuth = require('google-auth-library');
var applicationBalls = [
  {
    id:0,
    time: new Date(2115, 0, 0, 0, 0, 0),
    summary: "none"
  },
  {
    id:1,
    time: new Date(2115, 0, 0, 0, 0, 0),
    summary: "none"
  },
  {
    id:2,
    time: new Date(2115, 0, 0, 0, 0, 0),
    summary: "none"
  }
];

var applicationBlanks;

var SCOPES = ['https://www.googleapis.com/auth/calendar.readonly'];
var TOKEN_DIR = (process.env.HOME || process.env.HOMEPATH ||
    process.env.USERPROFILE) + '/.credentials/';
var TOKEN_PATH = TOKEN_DIR + 'calendar-nodejs-quickstart.json';

// Load client secrets from a local file.
fs.readFile('client_secret.json', function processClientSecrets(err, content) {
  if (err) {
    console.log('Error loading client secret file: ' + err);
    return;
  }
  // Authorize a client with the loaded credentials, then call the
  // Google Calendar API.
  authorize(JSON.parse(content), listEvents);
});



/**
 * Create an OAuth2 client with the given credentials, and then execute the
 * given callback function.
 *
 * @param {Object} credentials The authorization client credentials.
 * @param {function} callback The callback to call with the authorized client.
 */
function authorize(credentials, callback) {
  var clientSecret = credentials.installed.client_secret;
  var clientId = credentials.installed.client_id;
  var redirectUrl = credentials.installed.redirect_uris[0];
  var auth = new googleAuth();
  var oauth2Client = new auth.OAuth2(clientId, clientSecret, redirectUrl);

  // Check if we have previously stored a token.
  fs.readFile(TOKEN_PATH, function(err, token) {
    if (err) {
      getNewToken(oauth2Client, callback);
    } else {
      oauth2Client.credentials = JSON.parse(token);
      callback(oauth2Client);
    }
  });
}

/**
 * Get and store new token after prompting for user authorization, and then
 * execute the given callback with the authorized OAuth2 client.
 *
 * @param {google.auth.OAuth2} oauth2Client The OAuth2 client to get token for.
 * @param {getEventsCallback} callback The callback to call with the authorized
 *     client.
 */
function getNewToken(oauth2Client, callback) {
  var authUrl = oauth2Client.generateAuthUrl({
    access_type: 'offline',
    scope: SCOPES
  });
  console.log('Authorize this app by visiting this url: ', authUrl);
  var rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
  });
  rl.question('Enter the code from that page here: ', function(code) {
    rl.close();
    oauth2Client.getToken(code, function(err, token) {
      if (err) {
        console.log('Error while trying to retrieve access token', err);
        return;
      }
      oauth2Client.credentials = token;
      storeToken(token);
      callback(oauth2Client);
    });
  });
}

/**
 * Store token to disk be used in later program executions.
 *
 * @param {Object} token The token to store to disk.
 */
function storeToken(token) {
  try {
    fs.mkdirSync(TOKEN_DIR);
  } catch (err) {
    if (err.code != 'EEXIST') {
      throw err;
    }
  }
  fs.writeFile(TOKEN_PATH, JSON.stringify(token));
  console.log('Token stored to ' + TOKEN_PATH);
}

/**
 * Lists the next 10 events on the user's primary calendar.
 *
 * @param {google.auth.OAuth2} auth An authorized OAuth2 client.
 */

var ifDeleteApp = [];
function listEvents(auth, currentID) {
  var currentID = currentID || "null";
  var calendar = google.calendar('v3');
  var eventTimeMax = new Date();
  var month = eventTimeMax.getMonth();
  eventTimeMax.setMonth( month + 1 );
  calendar.events.list({
    auth: auth,
    calendarId: "primary",
    timeMax: eventTimeMax.toISOString(),
    timeMin: (new Date()).toISOString(),
    maxResults: 30,
    singleEvents: true,
    orderBy: 'startTime',
    //updatedMin: (new Date(2015, 9, 26, 14, 42, 22, 0)).toISOString()
  }, function(err, response){
    if (err) {
      console.log('The API returned an error: ' + err);
      return;
    }


    var events = response.items;


    if (events.length == 0) {
      console.log('No upcoming events found.');
    } else {

      // for (var i = 0; i < events.length; i++) {
      //   var event = events[i];
      //   var start = event.start.dateTime || event.start.date;
      //   var end = event.end.dateTime || event.end.date;
      //   console.log('%s - %s:  %s', start, end, event.summary);
      // }

      //判断当前的event 是否有被删掉的, ifdelete 为1就需要删掉，ifdelete 为0就不需要删掉
      ifDeleteApp[0] = 1;
      ifDeleteApp[1] = 1; 
      ifDeleteApp[2] = 1;
      for(var i = 0; i < applicationBalls.length; i++){
        // console.log(" the applicationBalls " + i + " : " + applicationBalls[i].summary +"is under cheking");
        if(applicationBalls[i].summary == "none"){
          ifDeleteApp[i] = 0;
          continue;
        }
        for(var j = 0; j < events.length; j++){
          if(events[j].id == applicationBalls[i].id){
            ifDeleteApp[i] = 0;
            break;
          }
        }
      }
      //delte whatever that need to be delete.
      for(var i = applicationBalls.length - 1; i >=0; i--){
        // console.log(" the applicationBalls " + i + " : " + applicationBalls[i].summary +"is under cheking");
        if(ifDeleteApp[i] == 1){
          applicationBalls[i].time = new Date(2115, 0, 0, 0, 0, 0);
          applicationBalls[i].summary = "none";
        }
      }


      //applicationBlanks = events.length - 3;
      events.splice(3, events.length-3);
      var newEvents = [];

      for(var i = 0; i < events.length; i++){
        newEvents[i] = {
          id:events[i].id,
          time:events[i].end.dateTime || events[i].end.date,
          summary: events[i].summary
        }
      }

      newEvents = updateTime(newEvents);
      updateApplicationBalls(newEvents);
        // var recentEvent = events[events.length-1];
        // if (currentID != recentEvent.id){
        //   console.log("most recentEvent:", events[events.length-1].summary);
        // currentID = events[events.length-1].id;
        // var currentTime = (new Date()).getTime();
        // var endTime = (new Date(events[events.length-1].end.dateTime)).getTime();
        // var intervalTime = endTime - currentTime;
        // var intervalsecond = intervalTime/1000;
        // var intervalsMinute = intervalsecond/60;
        // var intervalHours = intervalsMinute/60;
        //
        //
        // console.log("Current Time: ", currentTime)
        // console.log("End Time:", endTime);
        // console.log("time between:", intervalTime);



        //trigle the photon
        // var url = "https://api.particle.io/v1/devices/2f0038000547343339373536/led?access_token=ee9c688ffe1f9bc47dbb85ed10701010bb647eeb";
        // $.post(url, {"arg" : "off"});
      //}
    }
  });

  timeouts = setTimeout( function() {
    listEvents(auth, currentID);
  }, 2000 );
}

function updateTime(balls){
  // console.log(balls[0].id);

  for(var i = 0; i < applicationBalls.length; i++){
    // console.log(" the applicationBalls " + i + " : " + applicationBalls[i].summary +"is under cheking");
    for(var j = 0; j < balls.length; j++){
      // console.log(" the newball " + j + " id : " + balls[j].id);
      // console.log(" the applicationBalls " + i + " id : " + applicationBalls[i].id);
      if(balls[j].id == applicationBalls[i].id){
        var endTimeNow = balls[j].time;
        applicationBalls[i].time = endTimeNow;
        balls.splice(j, 1);
        break;
      }
    }
  }

  // //!!!!!!!!!!!!!!!!!!!!!! have not checking !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // for(var i = 0; i < balls.length; i++){
  //   if(balls[i].id == "no"){
  //     balls.splice(i, 1);
  //   }
  //
  // }

  // console.log('New events:');
  // for(var i = 0; i < balls.length; i++){
  //   console.log(balls[i].summary+":"+balls[i].time);
  // }

  //check if due day have already past, if past set due day to default day
  for(var i = 0; i < applicationBalls.length; i++){
    var duration = (new Date(applicationBalls[i].time)).getTime() - (new Date()).getTime();
    if(duration<0){
      applicationBalls[i].time = new Date(2115, 0, 0, 0, 0, 0);
    }
  }

  return balls;
}

function updateApplicationBalls(newBalls){
  var theAll = [];
  var theOrder = [];
  // 讲新近的球和以前的球放在theall里面
  for(var i = 0; i < applicationBalls.length; i++){
    theAll[i] = applicationBalls[i];
  }


  for (var j = applicationBalls.length; j < applicationBalls.length+newBalls.length; j++){
    theAll[j] = newBalls[j-applicationBalls.length];
  }

  //
  //
  // console.log('theAll:');
  // for(var i = 0; i < theAll.length; i++){
  //   console.log(theAll[i].summary+":"+theAll[i].time);
  // }


  //将theall里面的球按照时间顺序排列
  for ( var i = 0; i < theAll.length; i++ ){
    if ( !theOrder[0] ){
      theOrder[0] = theAll[i];
    } else {

      // theAll[i] compare with all the elements in theOrder
      // if there is one is bigger than theAll[i], the element in theAll[i] will be added in theOrder
      //if thre is no one bigger than theAll[i], the element added in the end of theOrder
      //checked
      for ( var j = 0; j < theOrder.length+1; j++ ){
        //当length theAll
        if (j == theOrder.length ) {
          theOrder.push(theAll[i]);
          break;
        }
        if ( (new Date(theAll[i].time)).getTime() < (new Date(theOrder[j].time)).getTime() ){
          theOrder.splice(j, 0, theAll[i]);
          break;
        }

      }
    }
  }


  // console.log('theOrder:');
  // for(var i = 0; i < theOrder.length; i++){
  //   console.log(theOrder[i].summary+":"+theOrder[i].time);
  // }

  //将application中已经不在列的进行处理
  for ( var i = 0; i < applicationBalls.length; i++ ) {
    if ( theOrder.indexOf(applicationBalls[i]) >= applicationBalls.length ){
      //console.log("the ApplicationBall" + i + ": " + applicationBalls[i].summary + " need to be changed")
      for ( var j = 0; j < newBalls.length; j++ ){
        if ( theOrder.indexOf(newBalls[j]) < applicationBalls.length ) {
          //console.log("use the newBalls" + j + ": " + newBalls[j].summary + " to change the applicationBall")
          applicationBalls[i].id = newBalls[j].id;
          applicationBalls[i].time = newBalls[j].time;
          applicationBalls[i].summary = newBalls [j].summary;
          newBalls.splice(j,1);
          break;
        }
      }
    }
  }

  var leftDays = [];
  console.log('applicationBalls:');
  for(var i = 0; i < applicationBalls.length; i++){
    if (applicationBalls[i].summary != "none") {
      leftDays[i] = parseInt(((new Date(applicationBalls[i].time)).getTime() - (new Date()).getTime()) / 1000 / 60 / 60 / 24 ) + 1;
    }else{
      leftDays[i] = 0;
    }
    
    console.log(applicationBalls[i].summary);
    console.log(leftDays[i]);
  }

  //Lets configure and request
request({
    //url: 'https://api.particle.io/v1/devices/2f0038000547343339373536/newDue1?access_token=ee9c688ffe1f9bc47dbb85ed10701010bb647eeb', //URL to hit
    url: 'https://api.particle.io/v1/devices/21001f001647343337363432/newDue1?access_token=aec31db0e35e7f0969dcfbbf7f417210aa391ac5',
    //qs: {from: 'blog example', time: +new Date()}, //Query string data
    method: 'POST',
    //Lets post the following key/values as form
    form: {
        "arg": leftDays[0],
    }
}, function(error, response, body){
    if(error) {
        console.log(error);
    } else {
        console.log(response.statusCode, body);
    }
});

request({
    //url: 'https://api.particle.io/v1/devices/2f0038000547343339373536/newDue2?access_token=ee9c688ffe1f9bc47dbb85ed10701010bb647eeb', //URL to hit
    url: 'https://api.particle.io/v1/devices/21001f001647343337363432/newDue2?access_token=aec31db0e35e7f0969dcfbbf7f417210aa391ac5',
    //qs: {from: 'blog example', time: +new Date()}, //Query string data
    method: 'POST',
    //Lets post the following key/values as form
    form: {
        "arg": leftDays[1],
    }
}, function(error, response, body){
    if(error) {
        console.log(error);
    } else {
        console.log(response.statusCode, body);
    }
});

request({
    //url: 'https://api.particle.io/v1/devices/2f0038000547343339373536/newDue3?access_token=ee9c688ffe1f9bc47dbb85ed10701010bb647eeb', //URL to hit
    url: 'https://api.particle.io/v1/devices/21001f001647343337363432/newDue3?access_token=aec31db0e35e7f0969dcfbbf7f417210aa391ac5',
    //qs: {from: 'blog example', time: +new Date()}, //Query string data
    method: 'POST',
    //Lets post the following key/values as form
    form: {
        "arg": leftDays[2],
    }
}, function(error, response, body){
    if(error) {
        console.log(error);
    } else {
        console.log(response.statusCode, body);
    }
});
}
