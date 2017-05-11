(function() {
  'use strict';

  var app = angular.module('webtool');

  app.controller('navigationController', function($scope, $location) {
    $scope.isActive = function(route) {
        return route === $location.path();
    }
  });
})();
