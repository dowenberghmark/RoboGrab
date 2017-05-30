(function() {
  'use strict';

  var app = angular.module('webtool');

  app.controller('overviewController', ['$scope','angularBase','$http', function($scope, angularBase,$http) {
    var that = this;
    $scope.map;
    var img = document.getElementById('map_img');
    
    var canvas = document.getElementById('canvas');
    var context = canvas.getContext('2d');
    context.drawImage(img, 0, 0);

    //Set parameters
    this.tileSize = 50;
    context.fillStyle = "rgba(255,0,0,0.6)";

    this.base = angularBase("http://localhost:27019","map");
    var map = that.base.getAll();

    this.drawMap = function(nodes) { 
      canvas.width = 7*50;
      canvas.height = 7*50;
      var im = $scope.crossroad;
        for(var i in nodes){
        }
    }

    this.drawTile = function(x,y){
      context.fillRect(
      x * this.tileSize, y * this.tileSize,
      this.tileSize, this.tileSize
    )};

    
 
  }]);

})();
