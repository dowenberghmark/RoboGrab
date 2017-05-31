// updating values in the database

var Job = require('../models/job');


var mongoose = require('mongoose');
mongoose.Promise = global.Promise;
mongoose.connect('localhost:27017/warehouseSWE');
var ObjectID = mongoose.Schema.Types.ObjectId;



var jobs = [
  new Job({
    itemID: mongoose.Types.ObjectId(),
    Y: 2,
    X: 4,
    year: 1990,
    month: 4,
    day: 11,
    hour: 1,
    min: 1,
    sec: 1,
    jobType: "PUT-IN"
    }),

];

/*
itemID:{type: Number, requried:false},
    row:{type: Number, requried:true},
    col:{type: Number, required:false},
    year:{type: Number, required:false},
    month:{type: Number, required:false},
    day:{type: Number, required:false},
    hour:{type: Number, required:true},
    min:{type: Number, required:true},
    sec:{type: Number, required:true},
    jobType:{type: String, required:true},
    */

var done = 0;

for(var i=0; i< jobs.length; i++){
    jobs[i].save(function(err,result) {
        done++;
        if(done === jobs.length){
            exit();
        }
        });
}

function exit() {
    mongoose.disconnect();
}
