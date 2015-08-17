var express = require('express');
var app = express();

app.use(express.static(__dirname + '/'));
app.set('views', __dirname + '/views');
app.engine('html', require('ejs').renderFile);
app.set('view engine', 'html');
app.set('port', (process.env.PORT || 5000));

app.get('/', function (req, res) {
	res.render('infinity-table.html');
});

var server = app.listen(app.get('port'), function () {

	var host = server.address().address;
	var port = server.address().port;

	console.log('Example app listening at http://%s:%s', host, port);
});