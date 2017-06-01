
//var mongo = require('mongodb').MongoClient();
var url = "mongodb://localhost:27017/warehouseSWE";
var app = angular.module('webtool');

(function() {
    'use strict';


    app.controller('newItemController', ['$scope','angularBase','$http', function($scope, angularBase, http) {
  


   
             var Locations = angularBase("http://localhost:27021",'locations');
          $scope.locations = Locations.getAll();
          $scope.changeLocationValues = function(index){
              var location = $scope.locations[index];
              location ={ _id: location._id, sensorID: location.sensorID, itemID: location.itemID, available: location.available,
              xPosition: location.xPosition};
              Locations.put(location);
          }



    
        var Items = angularBase("http://localhost:27022", "items"); // NOTE: The configuration here must match with the server - obviously

     //   

    console.log("ITEMS")
     console.log($scope.items)
     console.log("jobs")
     console.log($scope.jobs)

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

        $scope.addItemToJob = function () {
 var Jobs = angularBase("http://localhost:27023", "jobs");
        var job = {
            name: $scope.nameJobInput,
            jobType: "PICK-UP",
            x: $scope.loc
        
        };

            Jobs.put(job);
         


            $scope.nameJobInput = "";
 
        }
   


    }]);



})(app);


