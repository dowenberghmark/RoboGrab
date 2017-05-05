var firebase = require('firebase');

var config = {
    apiKey: "AIzaSyAdK51GKgUwaVvgvSn_8srsWG4byioNeT8",
    authDomain: "warehouse-247d7.firebaseapp.com",
    databaseURL: "https://warehouse-247d7.firebaseio.com",
    projectId: "warehouse-247d7",
    storageBucket: "warehouse-247d7.appspot.com",
    messagingSenderId: "725276381572"
};
firebase.initializeApp(config);

// reference to the right part of the json tree
// this example im trying to reach sensor child and the node 1;
var sensorRef = firebase.database().ref('sensor');
var sensorOne = sensorRef.child('1');
var sensorTwo = sensorRef.child('2');
var payload = {};


// adding/updating/removing attributes


//adding values  OBS very dangerous to use!
//sensorOne.set



//update values

/*
sensorOne.update({
    sunlight: 1,
    temp: 200
});

sensorTwo.update({
    sunlight: 0,
    temp: 20
});

*/

sensorRef.once('value')
    .then(function(snap){
        console.log(snap.key, "\n\n");
        console.log(snap.ref.toString(), "\n\n");
        console.log(snap.val());

    })





