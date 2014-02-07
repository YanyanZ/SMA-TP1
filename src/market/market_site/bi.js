var price = new Array();
var stock = new Array();

$.get('bi.stock', function(myContentFile)
      {
	  var lines = myContentFile.split("\n");

	  for(var i  in lines)
	  {
	      var data2 = lines[i].split(" ");
	      price.push(parseInt(data2[0]));
	      stock.push(parseInt(data2[1]));
	  }
      },
      'text');

$(function () {
    var char3_1 = new Highcharts.Chart({
	chart:{renderTo:'BIB'},
        title: {
            text: 'Number of BI actions on the market',
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
            data: stock
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
            data: price
        }]
    });

});
