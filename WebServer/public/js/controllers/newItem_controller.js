var app = angular.module('webtool');

(function() {
    'use strict';


    app.controller('newItemController', ['$rootScope','$scope','angularBase', function($rootScope, $scope, angularBase) {
        var Locations = angularBase("http://localhost:27021", "locations");
        var Items = angularBase("http://localhost:27022", "items"); // NOTE: The configuration here must match with the server - obviously
        
     //   
      $scope.locations = Locations.getAll();
     $scope.items = Items.getAll();
    console.log("ITEMS")
     console.log($scope.items)
     console.log("LOCATIONS")
     console.log($scope.locations)
     console.log("SCOPE")
     console.log($scope)
        
        $scope.addItem = function () {
            var item = {name: $scope.nameInput,

            minHumidity: $scope.minHumInput,
            maxHumidity: $scope.maxHumInput,
            minTemperature: $scope.minTempInput,
            maxTemperature: $scope.maxTempInput};

            
            Items.put(item);

            $scope.nameInput = "";
            $scope.minHumInput = "";
            $scope.maxHumInput = "";
            $scope.minTempInput = "";
            $scope.maxTempInput = "";

        }

// var Locations = angularBase("http://localhost:27021", "locations");


    }]);


})(app);