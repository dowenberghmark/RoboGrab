//creating a schema

var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var schema = new Schema({
    name:{type: String},
    minHumidity:{type: Number, required:false},
    maxHumidity:{type: Number, required:false},
    minTemperature:{type: Number, required:false},
    maxTemperature:{type: Number, required:false},
    locationID:{type: String, required:false}
});

module.exports = mongoose.model('items', schema);