(function() {
    'use strict';

    var app = angular.module('webtool');

    app.controller('inventoryController', ['$rootScope','$scope','angularBase','$http', function($rootScope, $scope, angularBase,$http) {



    var Items = angularBase("http://localhost:27022","items");
    $scope.items = Items.getAll();
    var Locations = angularBase("http://localhost:27021","locations");
    $scope.locations = Locations.getAll();

}]);



})();
