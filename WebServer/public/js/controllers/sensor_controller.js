(function() {
    'use strict';

    var app = angular.module('webtool');

    app.controller('sensorController', ['$rootScope','$scope','angularBase', function($rootScope, $scope, angularBase) {
        var Sensors = angularBase("http://localhost:27018","sensors");


        $scope.sensors = Sensors.getAll();


        $scope.changeSensorValues = function(index) {
            var sensor = $scope.sensors[index];
            sensor = { _id: sensor._id, sunlight: sensor.sunlight, temperature: sensor.temperature};
            Sensors.put(sensor);
        }


    }]);

})();




