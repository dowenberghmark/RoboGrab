// index.js - Runestone Team 2
const express = require('express');
const app = express();
var public_path = require('path');
var router = express.Router();
var path = __dirname + '/views/';
const port = 3000;

//Set up the view engine: pug, pug is a HTML-interpreter
app.set('views', __dirname + '/views/');
app.set('view engine', 'pug');
app.locals.pretty = true;

app.use(express.static(public_path.join(__dirname, 'public')));

app.use("/",router);

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
require(__dirname + '/app/routes')(app);

app.listen(port, (err) => {
  if (err) {
    return console.log('something bad happened', err)
  }

  console.log(`server is listening on ${port}`)
})
