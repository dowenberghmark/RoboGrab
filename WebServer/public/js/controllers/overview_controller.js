(function() {
  'use strict';

  var app = angular.module('webtool');

  app.controller('overviewController', ['$scope','angularBase','$http', function($scope, angularBase,$http) {
    var that = this;
    var crossroad;
    var img = new Image();
    img.onload = function() {
      context.drawImage(img, 0, 0, 381, 537);
    }
    img.src= "/static/pictures/GSPD_Layout.png";

    /*$http.get('http://localhost:3000/map')
    .then(function(map) {
      console.log("awuba");
      var map = map.data;
      crossroad = new Image();
      crossroad.onload = function() {
      that.drawMap(map.nodes);
      }
      crossroad.src= "/static/pictures/crossroad_nswe.png";
    })
    .catch(function(errRes) {
      console.log(errRes);
    });*/
    
    var canvas = document.getElementById('canvas');
    var context = canvas.getContext('2d');
    canvas.width = 381;
    canvas.height = 537;

    //Set parameters
    this.tileSize = 50;

    this.base = angularBase("http://localhost:27019","map");
    var map = that.base.getAll();

    this.drawTile = function(x,y){
      context.drawImage(
      crossroad,
      x*this.tileSize, y*this.tileSize
    )};
    
    this.drawMap = function(nodes) { 
      var im = crossroad;
        for(var i in nodes){
          that.drawTile(nodes[i].x, nodes[i].y)
        }
    }

      var Sensors = angularBase("http://localhost:27018","sensors");

      $scope.sensors = Sensors.getAll();

      var Robots = angularBase("http://localhost:27020","robots");

      $scope.robots = Robots.getAll();

  }]);

})();
