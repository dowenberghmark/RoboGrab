
var app = angular.module('webtool');

(function() {
    'use strict';


    app.controller('newJobController', ['$scope','angularBase','$http', function($scope, angularBase, http) {
  
          var Jobs = angularBase("http://localhost:27023",'jobs');
          $scope.jobs = Jobs.getAll();

            $scope.valueJob = function(index) {
            var job = $scope.jobs[index];
            job = { jobType: job.jobType, X: job.X, Y: job.Y, name: job.name};
            Jobs.put(job);
        }


    }]);



})(app);


