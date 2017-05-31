(function() {
  'use strict';

  var app = angular.module('webtool');

  app.controller('overviewController', ['$scope','angularBase','$http', function($scope, angularBase,$http) {
    var that = this;
    
    var canvas = document.getElementById('canvas');
    var context = canvas.getContext('2d');
    canvas.width = 381;
    canvas.height = 537;

    $http.get('http://localhost:3000/update-robot_pos')
    .then(function(robots) {
      var robotList = robots.data;
      var img = new Image();
      img.onload = function() {
        console.log("What");
        
        context.drawImage(img, 0, 0, 381, 537);
        for (var i in robotList){
          context.fillStyle="#FF5733";
          context.fillRect(robotList[i].xPosition,robotList[i].yPosition,20,20);
        }
    }
    img.src= "/static/pictures/GSPD_Layout.png";
    })
    .catch(function(errRes) {
      console.log(errRes);
    });

    this.base = angularBase("http://localhost:27019","map");
    var map = that.base.getAll();

    var Sensors = angularBase("http://localhost:27018","sensors");

    $scope.sensors = Sensors.getAll();

    var Robots = angularBase("http://localhost:27020","robots");

    $scope.robots = Robots.getAll();

  }]);

})();
