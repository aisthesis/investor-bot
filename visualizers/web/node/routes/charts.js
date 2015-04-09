var express = require('express');
var router = express.Router();

var MongoClient = require('mongodb').MongoClient;

// middleware specific to this router
router.use(function timeLog(req, res, next) {
    res.locals.layout = 'charts';
    next();
});

router.get('/', function (req, res) {
    res.render('charts/index');
});

router.get('/data', function (req, res, next) {
    //if (req.xhr) {
    //    var url = 'mongodb://localhost:27017/quotes';
    //    MongoClient.connect(url, function (err, db) {
    //        var quotes = db.collection('quotes');
            
    //        var threeMonthsAgo = new Date();
    //        threeMonthsAgo.setMonth(threeMonthsAgo.getMonth() - 3);

    //        var query = {
    //            Underlying: { $eq: 'SCTY' },
    //            Quote_Time: { $gte: threeMonthsAgo }
    //        };
            
    //        var project = {
    //            Quote_Time: 1,
    //            Strike: 1
    //        };

    //        quotes.find(query, project).toArray(function (err, docs) {
    //            db.close();
    //            res.json(docs);
    //        });
    //    });
    //} else {
        next();
    //}
});

module.exports = router;