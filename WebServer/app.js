// index.js - Runestone Team 2
const express = require('express');
const app = express();
var mongo = require("mongodb");
var MongoClient = require('mongodb').MongoClient;
var assert = require('assert');
var ObjectId = require('mongodb').ObjectID;
var url = 'mongodb://localhost:27017/warehouseSWE';
var public_path = require('path');
var router = express.Router();
const port = 3000;

//Set up the view engine: pug, pug is a HTML-interpreter
app.set('views', __dirname + '/views/');
app.set('view engine', 'pug');
app.locals.pretty = true;

//Set the static path (static path is used in Angular app)
app.use(express.static(public_path.join(__dirname, 'public')));

//For non-angular routing (normal GET/POST etc.)
app.use("/",router);

app.use(function(request, response, next) {
  response.header("Access-Control-Allow-Origin", "*");
  response.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
  next();
});

//include MongoDB-script
require(__dirname + '/app/mongoHandler')(app,mongo,MongoClient);

//Error message handling: should be last middleware
app.use((err, request, response, next) => {
  // log the error, for now just console.log
  console.log(err)
  response.status(500).send('Something broke!')
})

//Set the path to the public directory
app.use('/static', express.static(__dirname + '/public'));
app.use('/sys', express.static(__dirname + '/app'));

// Get routes for web access
require(__dirname + '/app/routes')(app,url,MongoClient);

app.listen(port, (err) => {
  if (err) {
    return console.log('something bad happened', err)
  }

  console.log(`server is listening on ${port}`)
})
