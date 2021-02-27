var intervals = 0;
var timeouts = 0;
var stopRequested = false;

var idTm = setTimeout(function(){
    //console.log("Called by timeout");
    ++timeouts;
}, 10);

var idIv = setInterval(function(){
    //console.log("Called by interval");
    ++intervals;
}, 10);

setTimeout(function() {
    clearInterval(idIv);
    clearTimeout(idTm);

    stopRequested = true;

    console.log("Intervals: ", intervals);
    console.log("Timeouts: ", timeouts);
}, 1100);
