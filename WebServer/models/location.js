//creating a schema

var mongoose = require('mongoose');
var Schema = mongoose.Schema;
var ObjectID = mongoose.Schema.Types.ObjectId;
var schema = new Schema({
     
    _id:{type: String, required:true},
    name:{type: String, required:true},
    sensorID:{type: String, required:true},
    itemID:{type: ObjectID, required:false},
    available:{type: Boolean, required:true},
    X:{type: Number, required: true},
    Y:{type: Number, required: true}

});

module.exports = mongoose.model('locations', schema);