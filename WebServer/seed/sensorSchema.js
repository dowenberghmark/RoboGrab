// updating values in the database

var Sensor = require('../models/sensor');


var mongoose = require('mongoose');
mongoose.Promise = global.Promise;
mongoose.connect('localhost:27017/warehouseSWE');




var sensors = [
    new Sensor({
    _id : 'sensor1',
    humidity: 1,
    temperature: 14
    }),

    new Sensor({
        _id : 'sensor2',
        humidity: 1,
        temperature: 14
    }),

    new Sensor({
        _id : 'sensor3',
        humidity: 1,
        temperature: 14
    }),

    new Sensor({
        _id : 'sensor4',
        humidity: 1,
        temperature: 15
    })
];

var done = 0;

for(var i=0; i< sensors.length; i++){
    sensors[i].save(function(err,result) {
        done++;
        if(done === sensors.length){
            exit();
        }
        });
}

function exit() {
    mongoose.disconnect();
}
