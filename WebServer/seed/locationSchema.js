// updating values in the database

var Location = require('../models/location');


var mongoose = require('mongoose');
mongoose.Promise = global.Promise;
mongoose.connect('localhost:27017/warehouseSWE');




var locations = [
    new Location({
    _id: "loc1",
    name: "Shelf 1",
    sensorID: 1,
    itemID: null,
    available: true,
    x: 1,
    y: 1
    }),

    new Location({
    _id: "loc2",
    name: "Shelf 2",
    sensorID: 1,
    itemID: null,
    available: true,
    x: 2,
    y: 1
    }),

    new Location({
    _id: "loc3",
    name: "Shelf 3",
    sensorID: 2,
    itemID: null,
    available: true,
    x: 3,
    y: 1
    }),

    new Location({
    _id: "loc4",
    name: "Shelf 4",
    sensorID: 2,
    itemID: null,
    available: true,
    x: 4,
    y: 1
}),

    new Location({
    _id: "loc5",
    name: "Shelf 5",
    sensorID: 1,
    itemID: null,
    available: true,
    x: 1,
    y: 2
    }),

    new Location({
    _id: "loc6",
    name: "Shelf 6",
    sensorID: 1,
    itemID: null,
    available: true,
    x: 2,
    y: 2
    }),

    new Location({
    _id: "loc7",
    name: "Shelf 7",
    sensorID: 2,
    itemID: null,
    available: true,
    x: 3,
    y: 2
    }),

    new Location({
    _id: "loc8",
    name: "Shelf 8",
    sensorID: 2,
    itemID: null,
    available: true,
    x: 4,
    y: 2
}),
    new Location({
    _id: "loc9",
    name: "Shelf 9",
    sensorID: 3,
    itemID: null,
    available: true,
    x: 1,
    y: 4
    }),

    new Location({
    _id: "loc10",
    name: "Shelf 10",
    sensorID: 3,
    itemID: null,
    available: true,
    x: 2,
    y: 4
    }),

    new Location({
    _id: "loc11",
    name: "Shelf 11",
    sensorID: 4,
    itemID: null,
    available: true,
    x: 3,
    y: 4
    }),

    new Location({
    _id: "loc12",
    name: "Shelf 12",
    sensorID: 4,
    itemID: null,
    available: true,
    x: 4,
    y: 4
}),

    new Location({
    _id: "loc13",
    name: "Shelf 13",
    sensorID: 3,
    itemID: null,
    available: true,
    x: 1,
    y: 5
    }),

    new Location({
    _id: "loc14",
    name: "Shelf 14",
    sensorID: 3,
    itemID: null,
    available: true,
    x: 2,
    y: 5
    }),

    new Location({
    _id: "loc15",
    name: "Shelf 15",
    sensorID: 4,
    itemID: null,
    available: true,
    x: 3,
    y: 5
    }),

    new Location({
    _id: "loc16",
    name: "Shelf 16",
    sensorID: 5,
    itemID: null,
    available: true,
    x: 4,
    y: 5
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
