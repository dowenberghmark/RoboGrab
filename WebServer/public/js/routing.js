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
      .when('/test', {
        templateUrl: '/views/test',
        controller: 'testController',
        controllerAs: 'testCtrl'
      })
      .otherwise({
        redirectTo: '/'
      });

      $locationProvider.html5Mode(true);
  });
})();
