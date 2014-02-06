$(function () {
    var char3_1 = new Highcharts.Chart({
	chart:{renderTo:'BIB'},
        title: {
            text: 'Number of BI actions buy on the market',
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
            name: 'BI',
            data: [7.0, 6.9, 9.5, 14.5, 18.2, 21.5, 25.2]
        }]
    });

    var char3_2 = new Highcharts.Chart({
	chart:{renderTo:'BIS'},
        title: {
            text: 'Number of BI actions sell on the market',
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
            name: 'BI',
            data: [7.0, 6.9, 9.5, 14.5, 18.2, 21.5, 25.2]
        }]
    });

    var char3_3 = new Highcharts.Chart({
	chart:{renderTo:'BIP'},
        title: {
            text: 'BI action price',
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
            name: 'BI',
            data: [7.0, 6.9, 9.5, 14.5, 18.2, 21.5, 25.2]
        }]
    });

});
