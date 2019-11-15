var express = require('express');
var fs = require('fs');
var csv = require('fast-csv');
var ws = fs.createWriteStream('data.csv', { flag: 'a' });
var app = express();
var bodyParser = require('body-parser')

app.get('/', function (req, res) {
    res.send("Hello from Server");
});

app.use(bodyParser.urlencoded({
    extended: false
}));

app.post('/', function (req, res) {
    //console.log(req);
    var latitude = (req.body).gps_coordinate_la;
    var longitude = (req.body).gps_coordinate_lo;
    var level = (req.body).pollution_level;
    let line = latitude + ", " + longitude + ", " + level + "\n";
    ws.write(line);
    res.send('DATA RECEIVED!!');
});

var server = app.listen(3000, function () {
    var host = server.address().address
    var port = server.address().port;
    console.log("Offloading server listening at localhost:%s", host, port)
});
