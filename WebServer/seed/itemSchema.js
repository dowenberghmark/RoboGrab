// updating values in the database

var Item = require('../models/item');


var mongoose = require('mongoose');
mongoose.Promise = global.Promise;
mongoose.connect('localhost:27017/warehouseSWE');




var items = [
  new Item({
 
    sunlight: false,
    minTemperature: 0,
    maxTemperature: 23,
    locationID: null
    }),

];

var done = 0;

for(var i=0; i< items.length; i++){
    items[i].save(function(err,result) {
        done++;
        if(done === items.length){
            exit();
        }
        });
}

function exit() {
    mongoose.disconnect();
}
