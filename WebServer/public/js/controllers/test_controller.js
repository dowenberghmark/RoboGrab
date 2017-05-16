(function() {
  'use strict';

  var app = angular.module('webtool');

  app.controller('testController', ['$rootScope','$scope','angularBase', function($rootScope, $scope, angularBase) {
      var Sensors = angularBase("http://localhost:27017","sensors");

      $scope.sensors = Sensors.getAll();

    	$scope.changeSensorValues = function(index) {
    		var sensor = $scope.sensors[index];
    		sensor = { _id: sensor._id, sunlight: sensor.sunlight, temperature: sensor.temperature, __v: sensor.__v };
    		Todos.put(sensor);
    	}


  }]);
})();
