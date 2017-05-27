//creating a schema

var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var schema = new Schema({
    _id: String,
    position:{type: String, required:true},
    available:{type: Boolean, required:true}
});

module.exports = mongoose.model('robots', schema);
