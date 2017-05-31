(function() {
    'use strict';

    var app = angular.module('webtool');

    app.controller('inventoryController', ['$rootScope','$scope','angularBase','$http', function($rootScope, $scope, angularBase,$http) {

    $scope.nodes = [];
    $scope.items = [];

    var Items = angularBase("http://localhost:27022","items");
    $scope.items = Items.getAll();

    $http.get('http://localhost:3000/map')
    .then(function(map) {
      $scope.nodes = map.data.nodes;
    })
    .catch(function(errRes) {
      console.log(errRes);
    });

}]);



})();
