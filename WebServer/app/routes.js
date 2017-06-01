
module.exports = (app,url,MongoClient) => {
  // Page routing being available for Angular
  const pages = [
    '/',
    '/inventory',
    '/test',
    '/events'
  ];

  app.get('/map', (req,res) => {
    var mongoHandler = require('./mongoHandler.js'); 
    MongoClient.connect(url, function(err, db) {
    if(err) {
      console.log(err);
   }

    mongoHandler.findMap(db, function(err, map) {
      if (err) 
        console.log('Searching the database failed');
      else {
        if (!map)
          console.log('Map not found');
        else
          res.json(map);
      }
      db.close();
      return;
    });
  });
  })

  /* Register page routing */
  pages.forEach((page) => {
    app.get(page, (req, res) => {
      res.render('index', {
      });
    });
  });

  /* Views for Angular pages */
  app.get('/views/:view', (req, res) => {
    res.render('page_' + req.params.view, { });
  });

  app.get('/update-sensors', (req,res) => {
    var io = require('socket.io-client');
    var socket = io.connect('http://localhost:27018');
    socket.emit('updateValues');
    res.send("");
  });

  app.get('/update-robots', (req,res) => {
    var io = require('socket.io-client');
    var socket = io.connect('http://localhost:27020');
    socket.emit('updateValues');
    res.send("");
});

app.get('/update-robot_pos', (req,res) => {
    var mongoHandler = require('./mongoHandler.js'); 
    MongoClient.connect(url, function(err, db) {
    if(err) {
      console.log(err);
   }

    mongoHandler.findRobots(db, function(err, robots) {
      if (err) 
        console.log('Searching the database failed');
      else {
        if (!robots)
          console.log('No robots found');
        else
          res.json(robots);
          console.log('Robots found');
      }
      db.close();
      return;
    });
  });
  })
};
