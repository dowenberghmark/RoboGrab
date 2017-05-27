//creating a schema

var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var schema = new Schema({
    _id: String,
    sunlight:{type: String, required:true},
    temperature:{type: String, required:true}
});

module.exports = mongoose.model('sensors', schema);
