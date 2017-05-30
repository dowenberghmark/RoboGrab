/**
 * The angularJS routing for all pages available on the webtool and define there urls and controllers
 */
(function() {
  'use strict';

  var app = angular.module('webtool');

  app.config(function($routeProvider, $locationProvider) {
    $routeProvider
      .when('/', {
        templateUrl: '/views/overview',
        controller: 'overviewController',
        controllerAs: 'ovwCtrl'
      })
      .when('/location', {
        templateUrl: '/views/location',
        controller: 'locationController',
        controllerAs: 'locCtrl'
      })
      .when('/sensor', {
            templateUrl: '/views/sensor',
            controller: 'sensorController',
            controllerAs: 'sensorCtrl'
      })
      .when('/inventory', {
            templateUrl: '/views/inventory',
            controller: 'inventoryController',
            controllerAs: 'inventCtrl'
      })
      .when('/newItem', {
            templateUrl: '/views/newItem',
            controller: 'newItemController',
            controllerAs: 'newCtrl'
      })
      .otherwise({
        redirectTo: '/'
      });

      $locationProvider.html5Mode(true);
  });
})();
