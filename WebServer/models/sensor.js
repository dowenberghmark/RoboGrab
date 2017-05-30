//creating a schema

var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var schema = new Schema({
    _id: String,
    humidity:{type: Number, required:true},
    temperature:{type: Number, required:true}
});

module.exports = mongoose.model('sensors', schema);
