console.log("Hello from NodeJS");


var mem = {};

var yourself = {
    solution : function(a, n) {
        var s = new Array(n);
        var p = new Array(n);

        s[0]     = a[0];
        p[n - 1] = a[n - 1];

        for (var i = 1; i < n; ++i) {
            s[i] = s[i - 1] + a[i];
            p[n - i - 1] = p[n - i] + a[n - i - 1];
        }

        for (var i = 1; i < n - 1; ++i) {
            if (s[i - 1] == p[i + 1]) {
                console.log(i);
//                return i;
            }
        }

        if (s[n - 2] == 0)
            console.log(n - 1);

        if (p[1] == 0)
            console.log(1);

        return -1;
    }
};

//var a = [-1, 3, -4, 5, 1, -6, 2, 1];
var a = [0, -2147483648, -2147483648];
console.log(yourself.solution(a, a.length));


