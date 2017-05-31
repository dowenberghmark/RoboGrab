//creating a schema

var mongoose = require('mongoose');
var Schema = mongoose.Schema;
var ObjectID = mongoose.Schema.Types.ObjectId;

var schema = new Schema({
	itemID:{type: ObjectID, requried:false},
    Y:{type: Number, requried:true},
    X:{type: Number, required:false},
    year:{type: Number, required:false},
    month:{type: Number, required:false},
    day:{type: Number, required:false},
    hour:{type: Number, required:true},
    min:{type: Number, required:true},
    sec:{type: Number, required:true},
    jobType:{type: String, required:true}

});

module.exports = mongoose.model('jobs', schema);