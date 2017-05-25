//creating a schema

var mongoose = require('mongoose');
var Schema = mongoose.Schema;
var ObjectID = mongoose.Schema.Types.ObjectId;
var schema = new Schema({
     
    _id:{type: String, required:true},
    sensorID:{type: String, required:true},
    itemID:{type: ObjectID, required:false},
    available:{type: Boolean, required:true},
    nodeID:{type: String, required:true}

});

module.exports = mongoose.model('locations', schema);