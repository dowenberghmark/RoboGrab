// updating values in the database

var Robot = require('../models/robot');


var mongoose = require('mongoose');
mongoose.Promise = global.Promise;
mongoose.connect('localhost:27017/warehouseSWE');




var sensors = [
    new Robot({
    _id : 'bluetoothID',
    available: true,
    xPosition: 0,
    yPosition: -1
    }),

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
