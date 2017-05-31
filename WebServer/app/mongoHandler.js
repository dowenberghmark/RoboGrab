module.exports = (app,mongo) => {

  function MongoConnection(config) {

  	// Validate input configuration
      function validateConfig() {
          if(typeof(config)!="object") {
              throw("config required for MongoConnection");
          }
          if(config.SocketIOPorts.length == 0 || typeof(config.SocketIOPorts[0])!="number") {
              throw("SocketIOPort required and must be a number");
          }
          if(config.Collections.length == 0 || typeof(config.Collections[0])!="string") {
              throw("At least 1 collection required");
          }
          if(typeof(config.Database)!="string") {
              throw("Database required");
          }
          if(typeof(config.MongoServer)!="string") {
              throw("MongoServer required");
          }
      }

      validateConfig();

  	/*
  		Create a socket and listen on the mentioned port.
  		-- When  a client connects, emit a string "connected"
  		-- Attach listeners to socket commands on a new connection.
  	*/
  	function loadSocket(collection,collection_nr) {
  		var io = require('socket.io').listen(config.SocketIOPorts[collection_nr]);

  		function cleanup(documents) {
  			var max_limit = 100;
  			if(documents.length > max_limit) {
  				var to_delete = documents.splice(max_limit);
  				for(var i=0;i<to_delete.length;i++){
  					collection.remove(to_delete[i],true,function(del_err){
  						if(del_err){
  							console.log("Cleanup error: ", del_err);
  						}
  					})
  				}
  			}
  		}

  		function findAllData(callback) {
  			collection.find({}, function(error, cursor) {
  				cursor.toArray(function(err,documents){

  					callback(err, documents)
  				});
  			});
  		}

  		function insertData(data,callback) {
  			collection.insert(data, {safe:true},callback);
  		}

  		function updateData(data, callback) {
  			console.log('Update called', data);
  			var id = data._id;
  			delete data["_id"];
  			collection.update({"_id": new mongo.ObjectID(id)},{$set: data}, {safe:true}, callback);
  		}

  		function deleteData(data, callback) {
  			console.log('Delete called', data);
  			collection.remove({_id: new mongo.ObjectID(data._id)}, true, callback);
  		}

  		function sendTo(o,command,items) {
  			var o = io.sockets;
  			o.emit.apply(o,[command, items]);
  		}

  		function sendAllItems(to, items) {
  			sendTo(to,'items-update-all', items);
  		}
  		var broadcastData = function() {
  			findAllData(function(error, items){
  				sendAllItems(io.sockets, items);
  			});
  		}

  		var sendData = function(sock) {
  			findAllData(function(error, items){
  				sendAllItems(sock, items);
  			});
  		}

  		io.sockets.on('connection', function(socket) {

  			socket.on('get-all-data', function() {
  				console.log("called get-data");
  				sendData(socket);
  			});

  			socket.on('insert', function(data) {
  				insertData(data, broadcastData);
  			});

  			socket.on('update', function(data) {
  				updateData(data, broadcastData);
  			});

  			socket.on('delete', function(data) {
  				deleteData(data, broadcastData);
  			});

			socket.on('updateValues', function() {
				console.log("Someone wants to update values");
				broadcastData();
			})

  			socket.emit('message', {message: 'Connected to socket'});

  		});
  	}


  	/*
  		Start the mongo server based on config
  	*/
  	function start() {
  		var host = config.MongoServer;

  		var port;
  		if(config.MongoPort) {
  			port = config.MongoPort;
  		} else {
  			port = 27017; //27017 is the mongoDB default port
  		}

  		var db = new mongo.Db(config.Database,
  								new mongo.Server(host,port,{}));

  		db.open(function(err){
  			if(err) {
  				console.log("DB connection error: ", err);
  				return;
  			}

  			console.log("Connection to the database established");

			for(i in config.Collections){
				var coll = config.Collections[i];
				var coll_name = coll;
				db.collection(coll, function(error, coll) {
					console.log("We have the collection \"",coll_name,"\", starting socket. Collection can now be accessed at //http://localhost:", config.SocketIOPorts[i]);
					loadSocket(coll,i);
				});
				i = i+1;
			}
  		});
  	}

  	start();
  }


	// The port for the socket to listen
	var socketPort = 27018;


  // Start a MongoConnection
  var m = new MongoConnection({
  	SocketIOPorts: [socketPort,socketPort+1, socketPort+2,socketPort+3,socketPort+4,socketPort+5], // SocketIO port, one for each collection!
  	Collections: ["sensors","map","robots","locations","items","jobs"], // we have the robograb collection
  	Database: "warehouseSWE", // database name
  	MongoServer:"localhost" // server name
  });

  
};


var findMap = function(db, callback) {
		// Get the map
		var collection = db.collection('map');
		// Find the map document
		collection.findOne({}, function(err, document) {
		if (err) return callback(err, null);
		console.log("Found map");
    	return callback(null, document);
	});
}

module.exports.findMap = findMap;
