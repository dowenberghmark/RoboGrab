var app = angular.module('webtool');

(function() {
    'use strict';


    app.controller('newItemController', ['$rootScope','$scope','angularBase', function($rootScope, $scope, angularBase) {
        var Items = angularBase("http://localhost:27022", "items"); // NOTE: The configuration here must match with the server - obviously

        $scope.items = Items.getAll();

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

        $scope.deleteItem = function (index) {
            var item = $scope.items[index];
            Items.remove(item);
        }

        $scope.changeItem = function (index) {
            var item = $scope.items[index];
            item = {_id: item._id};
            Items.put(item);
        }
    }]);
})(app);