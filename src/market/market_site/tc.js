$(function () {
    var char1_1 = new Highcharts.Chart({
	chart:{renderTo:'TCB'},
        title: {
            text: 'Number of TC actions buy on the market',
            x: -20 //center
        },
        subtitle: {
            text: 'Source: 127.0.0.1:4242',
            x: -20
        },
        xAxis: {
            categories: ['Day 1', 'Day 2','Day 3', 'Day 4','Day 5', 'Day 6', 'Day 7']
        },
        yAxis: {
            title: {
                text: 'Quantity'
            },
            plotLines: [{
                value: 0,
                width: 1,
                color: '#808080'
            }]
        },
        tooltip: {
            valueSuffix: 'U'
        },
        legend: {
            layout: 'vertical',
            align: 'right',
            verticalAlign: 'middle',
            borderWidth: 0
        },
        series: [{
            name: 'TC',
            data: [7.0, 6.9, 9.5, 14.5, 18.2, 21.5, 25.2]
        }]
    });

    var char1_2 = new Highcharts.Chart({
	chart:{renderTo:'TCS'},
        title: {
            text: 'Number of TC actions sell on the market',
            x: -20 //center
        },
        subtitle: {
            text: 'Source: 127.0.0.1:4242',
            x: -20
        },
        xAxis: {
            categories: ['Day 1', 'Day 2','Day 3', 'Day 4','Day 5', 'Day 6', 'Day 7']
        },
        yAxis: {
            title: {
                text: 'Quantity'
            },
            plotLines: [{
                value: 0,
                width: 1,
                color: '#808080'
            }]
        },
        tooltip: {
            valueSuffix: 'U'
        },
        legend: {
            layout: 'vertical',
            align: 'right',
            verticalAlign: 'middle',
            borderWidth: 0
        },
        series: [{
            name: 'TC',
            data: [7.0, 6.9, 9.5, 14.5, 18.2, 21.5, 25.2]
        }]
    });

    var char1_3 = new Highcharts.Chart({
	chart:{renderTo:'TCP'},
        title: {
            text: 'TC action price',
            x: -20 //center
        },
        subtitle: {
            text: 'Source: 127.0.0.1:4242',
            x: -20
        },
        xAxis: {
            categories: ['Day 1', 'Day 2','Day 3', 'Day 4','Day 5', 'Day 6', 'Day 7']
        },
        yAxis: {
            title: {
                text: 'Price($)'
            },
            plotLines: [{
                value: 0,
                width: 1,
                color: '#808080'
            }]
        },
        tooltip: {
            valueSuffix: 'U'
        },
        legend: {
            layout: 'vertical',
            align: 'right',
            verticalAlign: 'middle',
            borderWidth: 0
        },
        series: [{
            name: 'TC',
            data: [7.0, 6.9, 9.5, 14.5, 18.2, 21.5, 25.2]
        }]
    });

});
