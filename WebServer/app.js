// index.js - Runestone Team 2

require('./app/index')
const express = require('express')
const app = express()
 var public_path = require('path')
var router = express.Router();
var path = __dirname + '/views/';
const port = 3000

router.use(function (req,res,next) {
  console.log("/" + req.method);
  next();
});

router.get("/",function(req,res){
  res.sendFile(path + "index.html");
});

router.get("/inventory",function(req,res){
  res.sendFile(path + "inventory.html");
});

router.get("/settings",function(req,res){
  res.sendFile(path + "settings.html");
});

app.use(express.static(public_path.join(__dirname, 'public')));

app.use("/",router);

app.use("*",function(req,res){
  res.sendFile(path + "404.html");
});

//Error message handling: should be last middleware
app.use((err, request, response, next) => {
  // log the error, for now just console.log
  console.log(err)
  response.status(500).send('Something broke!')
})

app.listen(port, (err) => {
  if (err) {
    return console.log('something bad happened', err)
  }

  console.log(`server is listening on ${port}`)
})
