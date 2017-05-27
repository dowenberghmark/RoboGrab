// updating values in the database

var Location = require('../models/location');


var mongoose = require('mongoose');
mongoose.Promise = global.Promise;
mongoose.connect('localhost:27017/warehouseSWE');




var locations = [
    new Location({
    _id: "loc1",
    sensorID: 1,
    itemID: null,
    available: true,
    nodeID: "node4"
    }),

    new Location({
    _id: "loc2",
    sensorID: 1,
    itemID: null,
    available: true,
    nodeID: "node7"
    }),

    new Location({
    _id: "loc3",
    sensorID: 2,
    itemID: null,
    available: true,
    nodeID: "node13"
    }),

    new Location({
    _id: "loc4",
    sensorID: 1,
    itemID: null,
    available: true,
    nodeID: "node16"
    }),



];

var done = 0;

for(var i=0; i< locations.length; i++){
    locations[i].save(function(err,result) {
        done++;
        if(done === locations.length){
            exit();
        }
        });
}

function exit() {
    mongoose.disconnect();
}
