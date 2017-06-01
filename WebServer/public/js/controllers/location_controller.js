(function() {
  'use strict';

  var app = angular.module('webtool');

  app.controller('locationController', ['$rootScope','$scope','angularBase', function($rootScope, $scope, angularBase) {
      var Sensors = angularBase("http://localhost:27018","sensors");

      $scope.sensors = Sensors.getAll();

    	$scope.changeSensorValues = function(index) {
    		var sensor = $scope.sensors[index];
    		sensor = { _id: sensor._id, sunlight: sensor.sunlight, temperature: sensor.temperature, __v: sensor.__v };
    		Sensors.put(sensor);
    	}






          var Locations = angularBase("http://localhost:27021",'locations');
          $scope.locations = Locations.getAll();
          $scope.changeLocationValues = function(index){
              var location = $scope.locations[index];
              location ={ _id: location._id, sensorID: location.sensorID, itemID: location.itemID, available: location.available,
              nodeID: location.nodeID};
              Locations.put(location);
          }





  }]);

})();




