(function() {
  'use strict';

  var app = angular.module('webtool');

  app.controller('overviewController', ['$scope','angularBase','$http', function($scope, angularBase,$http) {
    var that = this;
    
    var canvas = document.getElementById('canvas');
    var context = canvas.getContext('2d');
    canvas.width = 381;
    canvas.height = 537;

    var img = new Image();
        img.onload = function() {
            context.drawImage(img, 0, 0, 381, 537);
            context.fillStyle="#0101DF";
            //Pixel values of the vertical lines:
            var xGrid = [5,69,152,234,315,350];
            var yGrid = [29,100,164,230,310,375,440,520];
            context.fillRect(xGrid[0],525-yGrid[0],25,25);
            context.fillStyle = "white";
            context.textAlign = "center";
            context.font = "20px Helvetica";
            context.fillText("1",xGrid[0]+13,525-yGrid[0]+19);
        }
        img.src= "/static/pictures/GSPD_Layout.png";

      $scope.$watch('robots[0]', function() {
        var robotList = $scope.robots;
        img.onload = function() {
          context.drawImage(img, 0, 0, 381, 537);
          for (var i in robotList){
            context.fillStyle="#0101DF";
             //Pixel values of the vertical lines:
            var xGrid = [5,69,152,234,315,350];
            var yGrid = [29,100,164,230,310,375,440,520];
            context.fillRect(15,67,25,25);
            context.fillStyle = "white";
            context.textAlign = "center";
            context.font = "20px Helvetica";
            context.fillText("1",xGrid[robotList[i].xPosition]+13,525-yGrid[robotList[i].yPosition]+19);}
      }});

    var Sensors = angularBase("http://localhost:27018","sensors");

    $scope.sensors = Sensors.getAll();

    var Robots = angularBase("http://localhost:27020","robots");

    $scope.robots = Robots.getAll();

  }]);

})();
