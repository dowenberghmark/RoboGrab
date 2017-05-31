(function() {
  'use strict';

  var app = angular.module('webtool');

  app.controller('overviewController', ['$scope','angularBase','$http', function($scope, angularBase,$http) {
    var that = this;
    var crossroad;
    var img = new Image();
    img.onload = function() {
      context.drawImage(img, 0, 0, 381, 537);
      that.drawRobots();
    }
    img.src= "/static/pictures/GSPD_Layout.png";
    
    var canvas = document.getElementById('canvas');
    var context = canvas.getContext('2d');
    canvas.width = 381;
    canvas.height = 537;

    //Set parameters
    this.tileSize = 20;

    this.base = angularBase("http://localhost:27019","map");
    var map = that.base.getAll();

    this.drawTile = function(x,y){
      context.fillRectangle(
      x*this.tileSize, y*this.tileSize,this.tileSize,this.tileSize
    )};

    this.drawRobots = function(){
      for (i in $scope.robots){
        console.log("Hurra");
      }
    }

    var Sensors = angularBase("http://localhost:27018","sensors");

    $scope.sensors = Sensors.getAll();

    var Robots = angularBase("http://localhost:27020","robots");

    $scope.robots = Robots.getAll();

  }]);

})();
