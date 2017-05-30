(function() {
    'use strict';

    var app = angular.module('webtool');

    app.controller('inventoryController', ['$rootScope','$scope','angularBase', function($rootScope, $scope, angularBase) {
        var Items = angularBase("http://localhost:27022","items");


        $scope.items = Items.getAll();


        $scope.getItemValues = function(index) {
            var item = $scope.items[index];
            item = { _id: item._id, maxHumidity: item.maxHumidity, minHumidity: item.minHumidity, maxTemperature: item.maxTemperature, minTemperature: item.minTemperature, locationID: item.locationID, name: item.name};
            Items.put(item);
        }



    }]);

})();
