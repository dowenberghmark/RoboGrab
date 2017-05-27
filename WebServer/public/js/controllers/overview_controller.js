(function() {
  'use strict';

  var app = angular.module('webtool');

  app.controller('overviewController', ['$scope','angularBase','$q', function($scope, angularBase,$q) {
    var that = this;
    
    var canvas = document.getElementById('canvas');
    var context = canvas.getContext('2d');

    
    //Set parameters
    this.tileSize = 50;
    context.fillStyle = "rgba(255,0,0,0.6)";
    canvas.width = 600;
    canvas.height = 400;

    this.base = angularBase("http://localhost:27019","map");
    var map = that.base.getAll(); 

    this.drawMap = function(nodes) {
        for(var node in nodes){
          that.drawTile(node.x, node.y)
        }
    }

    this.drawTile = function(x,y){
      context.fillRect(
      x * this.tileSize, y * this.tileSize,
      this.tileSize, this.tileSize
    )};

    that.drawMap(map[0].nodes);
    
 
  }]);

})();
