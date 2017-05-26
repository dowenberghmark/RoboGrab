//creating a schema

var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var schema = new Schema({
     
    sunlight:{type: Boolean, required:true},
    minTemperature:{type: Number, required:true},
    maxTemperature:{type: Number, required:true},
    locationID:{type: String, required:false}
});

module.exports = mongoose.model('items', schema);