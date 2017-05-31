//creating a schema

var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var schema = new Schema({
    name:{type: String, requried:true},
    minHumidity:{type: Number, required:false},
    maxHumidity:{type: Number, required:false},
    minTemperature:{type: Number, required:false},
    maxTemperature:{type: Number, required:false},
    xPosition:{type: Number, required:true},
    yPosition:{type: Number, required:true}
});

module.exports = mongoose.model('items', schema);