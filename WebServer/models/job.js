//creating a schema

var mongoose = require('mongoose');
var Schema = mongoose.Schema;
var ObjectID = mongoose.Schema.Types.ObjectId;

var schema = new Schema({
	name:{type: ObjectID, requried:false},
    Y:{type: Number, requried:false},
    X:{type: Number, required:false},
/*  using .getTimestamp();
   year:{type: Number, required:false},
    month:{type: Number, required:false},
    day:{type: Number, required:false},
    hour:{type: Number, required:false},
    min:{type: Number, required:false},
    sec:{type: Number, required:false},
*/
    jobType:{type: String, required:false}

});

module.exports = mongoose.model('jobs', schema);