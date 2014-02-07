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
    var char2_1 = new Highcharts.Chart({
	chart:{renderTo:'TIB'},
        title: {
            text: 'Number of TI actions on the market',
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
            name: 'TI',
            data: stock
        }]
    });


    var char2_3 = new Highcharts.Chart({
	chart:{renderTo:'TIP'},
        title: {
            text: 'TI action price',
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
            name: 'TI',
            data: price
        }]
    });

});
