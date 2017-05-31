//creating a schema

var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var schema = new Schema({
    _id: String,
    xPosition:{type: Number, required:true},
    yPosition:{type: Number, required:true},
    available:{type: Boolean, required:true}
});

module.exports = mongoose.model('robots', schema);
