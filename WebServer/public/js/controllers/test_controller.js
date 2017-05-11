(function() {
  'use strict';

  var app = angular.module('webtool');

  app.controller('testController', ['$rootScope','$scope','$firebaseObject', function($rootScope, $scope, $firebaseObject) {

    var sensorRef = firebase.database().ref('sensor');
    var sensorOne = sensorRef.child('1');
    var sensorTwo = sensorRef.child('2');
    // download the data into a local object
    var syncObject1 = $firebaseObject(sensorOne);
    var syncObject2 = $firebaseObject(sensorTwo);
    // synchronize the object with a three-way data binding
    // click on `index.html` above to see it used in the DOM!
    syncObject1.$bindTo($scope, "sensor1");
    syncObject2.$bindTo($scope, "sensor2");

  }]);
})();
