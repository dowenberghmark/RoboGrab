
module.exports = (app,url,MongoClient) => {
  // Page routing being available for Angular
  const pages = [
    '/',
    '/inventory',
    '/test',
    '/events'
  ];

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

};
